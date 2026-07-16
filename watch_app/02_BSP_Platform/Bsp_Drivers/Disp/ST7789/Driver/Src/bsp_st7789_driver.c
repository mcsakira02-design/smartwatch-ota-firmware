#include "bsp_st7789_driver.h"
#include "st7789_reg_define.h"
#include <string.h>

#define SET_PIN      1
#define RESET_PIN    0

#define HOR_LEN 	40	//	Also mind the resolution of your screen!
#define ST7789_WIDTH 240
#define ST7789_HEIGHT 280
#define X_SHIFT 0
#define Y_SHIFT 20

#define ABS(x) ((x) > 0 ? (x) : -(x))

static uint16_t disp_buf[ST7789_WIDTH * HOR_LEN];

static uint8_t st7789_write_command(bsp_st7789_driver_t * const driver_instance, const uint8_t cmd, uint32_t dataLength)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->p_st7789_basic_operation->pf_write_dc_pin(RESET_PIN);

    uint8_t dataSend = cmd;
    driver_instance->p_st7789_basic_operation->pf_spi_transmit(&dataSend, 1);

    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_write_data(bsp_st7789_driver_t * const driver_instance, const uint8_t * dataSend, uint32_t dma_buf_size)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->p_st7789_basic_operation->pf_write_dc_pin(SET_PIN);
    while(dma_buf_size > 0)
    {
        uint16_t chunk_size = dma_buf_size > 65535 ? 65535 : dma_buf_size;
        if(dma_buf_size >= 16)
        {
            driver_instance->p_st7789_basic_operation->pf_spi_transmit_dma(dataSend, chunk_size);
        }
        else
        {
            driver_instance->p_st7789_basic_operation->pf_spi_transmit(dataSend, chunk_size);
        }
        dataSend += chunk_size;
        dma_buf_size -= chunk_size;
    }
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_write_simple_data(bsp_st7789_driver_t * const driver_instance, const uint8_t dataSend)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->p_st7789_basic_operation->pf_write_dc_pin(SET_PIN);

    driver_instance->p_st7789_basic_operation->pf_spi_transmit(&dataSend, 1);

    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

/**
 * @brief Set the rotation direction of the display
 * @param m -> rotation parameter(please refer it in st7789.h)
 *              0:
 * @return none
 */
static uint8_t st7789_set_direction(bsp_st7789_driver_t * const driver_instance, uint8_t dir)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_MADCTL, 1);

	switch (dir) {
	case 0:
        driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 
                            ST7789_MADCTL_RGB);
		break;
	case 1:
        driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 
                            ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	case 2:
        driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 
                            ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
		break;
	case 3:
        driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 
                            ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	default:
		break;
	}
}

static uint8_t st7789_set_addr_window(bsp_st7789_driver_t * const driver_instance, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select

    uint16_t x_start = x0 + X_SHIFT, x_end = x1 + X_SHIFT;
	uint16_t y_start = y0 + Y_SHIFT, y_end = y1 + Y_SHIFT;

    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_CASET, 1);
    {
        uint8_t data[] = {x_start >> 8, x_start & 0xFF, x_end >> 8, x_end & 0xFF};
        driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
    }
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_RASET, 1);
    {
        uint8_t data[] = {y_start >> 8, y_start & 0xFF, y_end >> 8, y_end & 0xFF};
		driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
    }
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_RAMWR, 1);

    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;

}

static uint8_t st7789_fill_color(bsp_st7789_driver_t * const driver_instance, uint16_t color)
{
    uint16_t i;
    driver_instance->pf_set_addr_window(driver_instance, 0, 0, ST7789_WIDTH - 1, ST7789_HEIGHT - 1);
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select

	for (i = 0; i < ST7789_HEIGHT / HOR_LEN; i++)
	{
		memset(disp_buf, color, sizeof(disp_buf));
        driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, (uint8_t *)&disp_buf, sizeof(disp_buf));
	}
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_init(bsp_st7789_driver_t * const driver_instance)
{
    memset(disp_buf, 0, sizeof(disp_buf));
    driver_instance->p_timebase_instance->pf_delay_no_os(10);
    driver_instance->p_st7789_basic_operation->pf_write_reset_pin(RESET_PIN);
    driver_instance->p_timebase_instance->pf_delay_no_os(10);
    driver_instance->p_st7789_basic_operation->pf_write_reset_pin(SET_PIN);
    driver_instance->p_timebase_instance->pf_delay_no_os(20);

    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_COLMOD, 1);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, ST7789_COLOR_MODE_16bit);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xB2, 1);
	{
		uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
		driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
	}
    driver_instance->pf_set_direction(driver_instance, 0);

	/* Internal LCD Voltage generator settings */
    //	Gate Control
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0XB7, 1);
    //	Default value
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x35);
    //	VCOM setting
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xBB, 1);
    //	0.725v (default 0.75v for 0x20)
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x19);
    //	LCMCTRL	
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xC0, 1);
    //	Default value
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x2C);
    //	VDV and VRH command Enable
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xC2, 1);
    //	Default value
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x01);
    //	VRH set
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xC3, 1);
    //	+-4.45v (defalut +-4.1v for 0x0B)
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x12);
    //	VDV set
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xC4, 1);
    //	Default value
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x20);
    //	Frame rate control in normal mode
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xC6, 1);
    //	Default value (60HZ)
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0x0F);
    //	Power control
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xD0, 1);
    //	Default value
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0xA4);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data(driver_instance, 0xA1);
	/**************** Division line ****************/

    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xE0, 1);
	{
        uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
		driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
	}

    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, 0xE1, 1);
	{
        uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
		driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
	}
    //	Inversion ON
	//	Out of sleep mode
  	//	Normal Display on
  	//	Main screen turned on	
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_INVON, 1);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_SLPOUT, 1);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_NORON, 1);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, ST7789_DISPON, 1);

    driver_instance->p_timebase_instance->pf_delay_no_os(50);
    driver_instance->pf_fill_color(driver_instance, BLACK);
    return 0;
}

static uint8_t st7789_draw_pixel(bsp_st7789_driver_t * const driver_instance, uint16_t x, uint16_t y, uint16_t color)
{
    if ((x < 0) || (x >= ST7789_WIDTH) ||
	(y < 0) || (y >= ST7789_HEIGHT))	return 1;

    driver_instance->pf_set_addr_window(driver_instance, x, y, x, y);
    uint8_t data[] = {color >> 8, color & 0xFF};
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select

    driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));

    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip select
    return 0;
}

static uint8_t st7789_fill(bsp_st7789_driver_t * const driver_instance, uint16_t xSta, 
                                 uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{
    if ((xEnd < 0) || (xEnd >= ST7789_WIDTH) ||
	(yEnd < 0) || (yEnd >= ST7789_HEIGHT))	return 1;
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    uint16_t i, j;
    driver_instance->pf_set_addr_window(driver_instance, xSta, ySta, xEnd, yEnd);
    for (i = ySta; i <= yEnd; i++)
    {
		for (j = xSta; j <= xEnd; j++) {
			uint8_t data[] = {color >> 8, color & 0xFF};
			driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
		}
    }
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_pixel_4px(bsp_st7789_driver_t * const driver_instance, uint16_t x, uint16_t y, uint16_t color)
{
    if ((x <= 0) || (x > ST7789_WIDTH) ||
	(y <= 0) || (y > ST7789_HEIGHT))	return 1;
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->pf_fill(driver_instance, x - 1, y - 1, x + 1, y + 1, color);
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_line(bsp_st7789_driver_t * const driver_instance, 
                                uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint16_t swap;
    uint16_t steep = ABS(y1 - y0) > ABS(x1 - x0);
    if (steep) {
		swap = x0;
		x0 = y0;
		y0 = swap;

		swap = x1;
		x1 = y1;
		y1 = swap;
        //_swap_int16_t(x0, y0);
        //_swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
		swap = x0;
		x0 = x1;
		x1 = swap;

		swap = y0;
		y0 = y1;
		y1 = swap;
        //_swap_int16_t(x0, x1);
        //_swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = ABS(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            driver_instance->pf_draw_pixel(driver_instance, y0, x0, color);
        } else {
            driver_instance->pf_draw_pixel(driver_instance, x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
    return 0;
}
static uint8_t st7789_draw_rectangle(bsp_st7789_driver_t * const driver_instance, 
                                     uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->pf_draw_line(driver_instance, x1, y1, x2, y1, color);
    driver_instance->pf_draw_line(driver_instance, x1, y1, x1, y2, color);
    driver_instance->pf_draw_line(driver_instance, x1, y2, x2, y2, color);
    driver_instance->pf_draw_line(driver_instance, x2, y1, x2, y2, color);
    driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_circle(bsp_st7789_driver_t * const driver_instance, uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->pf_draw_pixel(driver_instance, x0, y0 + r, color);
    driver_instance->pf_draw_pixel(driver_instance, x0, y0 - r, color);
    driver_instance->pf_draw_pixel(driver_instance, x0 + r, y0, color);
    driver_instance->pf_draw_pixel(driver_instance, x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
        driver_instance->pf_draw_pixel(driver_instance, x0 + x, y0 + y, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 - x, y0 + y, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 + x, y0 - y, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 - x, y0 - y, color);

        driver_instance->pf_draw_pixel(driver_instance, x0 + y, y0 + x, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 - y, y0 + x, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 + y, y0 - x, color);
        driver_instance->pf_draw_pixel(driver_instance, x0 - y, y0 - x, color);
	}
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_image(bsp_st7789_driver_t * const driver_instance, uint16_t x, uint16_t y, 
                                 uint16_t w, uint16_t h, const uint16_t *data)
{
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return 1;
	if ((x + w - 1) >= ST7789_WIDTH)
		return 1;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return 1;

	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->pf_set_addr_window(driver_instance, x, y, x + w - 1, y + h - 1);
    driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, (uint8_t *)data, sizeof(uint16_t) * w * h);
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_invert_colors(bsp_st7789_driver_t * const driver_instance, uint8_t invert)
{
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->p_st7789_spi_instance->pf_st7789_write_command(driver_instance, invert ? 0x21 /* INVON */ : 0x20 /* INVOFF */, 1);
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_write_char(bsp_st7789_driver_t * const driver_instance, uint16_t x, uint16_t y, char ch, 
                                 font_def_t font, uint16_t color, uint16_t bgcolor)
{
	uint32_t i, b, j;
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    driver_instance->pf_set_addr_window(driver_instance, x, y, x + font.width - 1, y + font.height - 1);

	for (i = 0; i < font.height; i++) {
		b = font.data[(ch - 32) * font.height + i];
		for (j = 0; j < font.width; j++) {
			if ((b << j) & 0x8000) {
				uint8_t data[] = {color >> 8, color & 0xFF};
                driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
			}
			else {
				uint8_t data[] = {bgcolor >> 8, bgcolor & 0xFF};
                driver_instance->p_st7789_spi_instance->pf_st7789_write_data(driver_instance, data, sizeof(data));
			}
		}
	}
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_write_string(bsp_st7789_driver_t * const driver_instance, uint16_t x, uint16_t y, 
                                   const char *str, font_def_t font, uint16_t color, uint16_t bgcolor)
{
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
	while (*str) {
		if (x + font.width >= ST7789_WIDTH) {
			x = 0;
			y += font.height;
			if (y + font.height >= ST7789_HEIGHT) {
				break;
			}

			if (*str == ' ') {
				// skip spaces in the beginning of the new line
				str++;
				continue;
			}
		}
        driver_instance->pf_write_char(driver_instance, x, y, *str, font, color, bgcolor);
		x += font.width;
		str++;
	}
	driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_filled_rectangle (bsp_st7789_driver_t * const st7789_driver_instance, uint16_t x, 
                                             uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
	uint8_t i;

	/* Check input parameters */
	if (x >= ST7789_WIDTH ||
		y >= ST7789_HEIGHT) {
		/* Return error */
		return 1;
	}

	/* Check width and height */
	if ((x + w) >= ST7789_WIDTH) {
		w = ST7789_WIDTH - x;
	}
	if ((y + h) >= ST7789_HEIGHT) {
		h = ST7789_HEIGHT - y;
	}

	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x, y + i, x + w, y + i, color);
	}
	st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_triangle(bsp_st7789_driver_t * const st7789_driver_instance, uint16_t x1, uint16_t y1, 
                                    uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color)
{
    st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
	/* Draw lines */
    st7789_driver_instance->pf_draw_line(st7789_driver_instance, x1, y1, x2, y2, color);
    st7789_driver_instance->pf_draw_line(st7789_driver_instance, x2, y2, x3, y3, color);
    st7789_driver_instance->pf_draw_line(st7789_driver_instance, x3, y3, x1, y1, color);
	st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_filled_triangle(bsp_st7789_driver_t * const st7789_driver_instance, uint16_t x1, uint16_t y1, 
                                           uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color)
{
    st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
			yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
			curpixel = 0;

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	}
	else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	}
	else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay) {
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	}
	else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
	st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_draw_filled_circle(bsp_st7789_driver_t * const st7789_driver_instance, int16_t x0, 
                                         int16_t y0, int16_t r, uint16_t color)
{
    st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    st7789_driver_instance->pf_draw_pixel(st7789_driver_instance, x0, y0 + r, color);
    st7789_driver_instance->pf_draw_pixel(st7789_driver_instance, x0, y0 - r, color);
    st7789_driver_instance->pf_draw_pixel(st7789_driver_instance, x0 + r, y0, color);
    st7789_driver_instance->pf_draw_pixel(st7789_driver_instance, x0 - r, y0, color);
    st7789_driver_instance->pf_draw_line(st7789_driver_instance, x0 - r, y0, x0 + r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x0 - x, y0 + y, x0 + x, y0 + y, color);
        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x0 + x, y0 - y, x0 - x, y0 - y, color);
        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x0 + y, y0 + x, x0 - y, y0 + x, color);
        st7789_driver_instance->pf_draw_line(st7789_driver_instance, x0 + y, y0 - x, x0 - y, y0 - x, color);

	}
	st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}

static uint8_t st7789_tear_effect(bsp_st7789_driver_t * const st7789_driver_instance, uint8_t tear)
{
    st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(RESET_PIN);  //chip select
    st7789_driver_instance->p_st7789_spi_instance->pf_st7789_write_command(st7789_driver_instance, tear ? 0x35 /* TEON */ : 0x34 /* TEOFF */, 1);
	st7789_driver_instance->p_st7789_basic_operation->pf_write_cs_pin(SET_PIN);  //chip unselect
    return 0;
}


static uint8_t st7789_test_your_device(bsp_st7789_driver_t * const st7789_driver_instance)
{
//   st7789_driver_instance->pf_st7789_init(st7789_driver_instance);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, WHITE);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, LIGHTBLUE);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, BROWN);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, CYAN);
//   st7789_driver_instance->pf_draw_rectangle(st7789_driver_instance, 30, 30, 100, 100, YELLOW);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_write_string(st7789_driver_instance, 50, 30, "Font test.", Font_16x26_t, YELLOW, BROWN);
//   st7789_driver_instance->pf_write_string(st7789_driver_instance, 50, 90, "my_work.", Font_16x26_t, YELLOW, BROWN);
//   st7789_driver_instance->pf_write_string(st7789_driver_instance, 50, 125, "2024-12-5.", Font_16x26_t, YELLOW, BROWN);
//   st7789_driver_instance->pf_write_string(st7789_driver_instance, 50, 220, "17:00.", Font_16x26_t, YELLOW, BROWN);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, WHITE);
//   st7789_driver_instance->pf_draw_filled_circle(st7789_driver_instance, 30, 90, 25, YELLOW);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, WHITE);
//   st7789_driver_instance->pf_draw_filled_rectangle(st7789_driver_instance, 100, 100, 40, 90, GREEN);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, WHITE);
//   st7789_driver_instance->pf_draw_filled_triangle(st7789_driver_instance, 25, 150, 25, 50, 100, 15, GRAYBLUE);
//   st7789_driver_instance->p_timebase_instance->pf_delay_no_os(1000);
//   st7789_driver_instance->pf_fill_color(st7789_driver_instance, WHITE);
//   st7789_driver_instance->pf_draw_image(st7789_driver_instance, 50, 50, 128, 128, (uint16_t *)saber);
  return 0;
}

uint8_t st7789_instance_driver_link  (bsp_st7789_driver_t * const st7789_driver_instance,
                                       basic_oper_driver_interface_t * const st7789_basic_operation_instance,
                                       st7789_spi_driver_interface_t * const st7789_spi_instance,
                                       st7789_timebase_interface_t   * const timebase_instance,
                                       st7789_yield_interface_t      * const yield_instance)
{
    st7789_driver_instance->p_st7789_basic_operation = st7789_basic_operation_instance;
    st7789_driver_instance->p_st7789_spi_instance = st7789_spi_instance;
    st7789_driver_instance->p_timebase_instance = timebase_instance;
    st7789_driver_instance->p_yield_instance = yield_instance;

    st7789_driver_instance->pf_st7789_init = (uint8_t (*)(void *const))st7789_init;
    st7789_driver_instance->pf_fill_color = (uint8_t (*)(void *const, uint16_t))st7789_fill_color;
    st7789_driver_instance->pf_set_addr_window = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t))st7789_set_addr_window;
    st7789_driver_instance->pf_set_direction = (uint8_t (*)(void *const, uint8_t))st7789_set_direction;
    st7789_driver_instance->p_st7789_spi_instance->pf_st7789_write_command = (uint8_t (*)(void *const, const uint8_t, uint8_t))st7789_write_command;
    st7789_driver_instance->p_st7789_spi_instance->pf_st7789_write_data = (uint8_t (*)(void *const, uint8_t *, uint32_t))st7789_write_data;
    st7789_driver_instance->p_st7789_spi_instance->pf_st7789_write_simple_data = (uint8_t (*)(void *const, const uint8_t))st7789_write_simple_data;
    st7789_driver_instance->pf_draw_circle = (uint8_t (*)(void *const, uint16_t, uint16_t, uint8_t, uint16_t))st7789_draw_circle;
    st7789_driver_instance->pf_draw_image = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, const uint16_t *))st7789_draw_image;
    st7789_driver_instance->pf_draw_line = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_draw_line;
    st7789_driver_instance->pf_draw_pixel = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t))st7789_draw_pixel;
    st7789_driver_instance->pf_draw_pixel_4px = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t))st7789_draw_pixel_4px;
    st7789_driver_instance->pf_draw_rectangle = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_draw_rectangle;
    st7789_driver_instance->pf_fill = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_fill;
    st7789_driver_instance->pf_invert_colors = (uint8_t (*)(void *const, uint16_t))st7789_invert_colors;
    st7789_driver_instance->pf_write_char = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, font_def_t, 
                                             uint16_t, uint16_t))st7789_write_char;
    st7789_driver_instance->pf_write_string = (uint8_t (*)(void *const, uint16_t, uint16_t, const char *, 
                                               font_def_t, uint16_t, uint16_t))st7789_write_string;
    st7789_driver_instance->pf_draw_filled_circle = (uint8_t (*)(void *const, int16_t, int16_t, int16_t, uint16_t))st7789_draw_filled_circle;
    st7789_driver_instance->pf_draw_filled_rectangle = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_draw_filled_rectangle;
    st7789_driver_instance->pf_draw_filled_triangle = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_draw_filled_triangle;
    st7789_driver_instance->pf_draw_triangle = (uint8_t (*)(void *const, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t))st7789_draw_triangle;
    st7789_driver_instance->pf_tear_effect = (uint8_t (*)(void *const, uint8_t))st7789_tear_effect;
    st7789_driver_instance->pf_test_your_device = (uint8_t (*)(void *const))st7789_test_your_device;
    return 0;

}



