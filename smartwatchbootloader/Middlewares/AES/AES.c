
/*
  AES 加密  解密
  数据块  固定为16字节
  秘钥有   128bit（16字节）    192bit（24字节）    256bit（32字节）
  */

#include"string.h"
//#include "stdafx.h"
#include "aes.h"

//轮秘钥缓存   原始秘钥 + 多个子秘钥
static unsigned char Round_Key[256];

/*
* S-box transformation table    S盒数据  在字节代替中需要使用
*/
const unsigned char aes_s_box[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // a
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // b
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // c
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // d
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // e
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };// f


/*
* Inverse S-box transformation table   S盒的逆    在字节代替中需要使用
*/
const unsigned char  aes_inv_s_box[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };// f



//列混淆 计算矩阵  列混淆矩阵在左边 乘以明文    即列混淆矩阵的行乘以明文矩阵的列
const unsigned char aes_MixColumns[4][4] = {
	// 0     1     2      3      
	0x02, 0x03, 0x01, 0x01,  //0
	0x01, 0x02, 0x03, 0x01,  //1
	0x01, 0x01, 0x02, 0x03,  //2
	0x03, 0x01, 0x01, 0x02,  //3
};

//列混淆 计算矩阵的逆
const unsigned char aes_invMixColumns[4][4] = {
	// 0     1     2      3      
	0x0E, 0x0B, 0x0D, 0x09,  //0
	0x09, 0x0E, 0x0B, 0x0D,  //1
	0x0D, 0x09, 0x0E, 0x0B,  //2
	0x0B, 0x0D, 0x09, 0x0E,  //3
};

//轮常数  子秘钥G函数用到  后一个数据为 前一个数据在GF(28)域上乘2
const unsigned char aes_Rcon[14] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d };


//AES字节替代函数
void Aes_SubBytes(unsigned char *Byte_IN_OUT, unsigned int Len)
{
	unsigned char S_X, S_Y;
	unsigned int Count = 0;
	for (Count = 0; Count < Len; Count++)
	{
		S_X = Byte_IN_OUT[Count] >> 4;   //得到高4位的值
		S_Y = Byte_IN_OUT[Count] & 0x0f;
		Byte_IN_OUT[Count] = aes_s_box[S_X][S_Y];  //得到对应的值
	}
}
//AES 逆向字节替代函数
void Aes_invSubBytes(unsigned char *Byte_IN_OUT, unsigned int Len)
{
	unsigned char S_X, S_Y;
	unsigned int Count = 0;
	for (Count = 0; Count < Len; Count++)
	{
		S_X = Byte_IN_OUT[Count] >> 4;   //得到高4位的值
		S_Y = Byte_IN_OUT[Count] & 0x0f;
		Byte_IN_OUT[Count] = aes_inv_s_box[S_X][S_Y];  //得到对应的值
	}
}

//数组指定行左移 指定字节
//SrcInOut：  数组输入及结果输出 必须为16字节  且内部分解成4X4矩阵
//Rows：      数组第几行  0~3
//Number:     左移字节数  1~3
void ShiftByteNumRows(unsigned char *SrcInOut, unsigned char Rows, unsigned char Number)
{
	unsigned char Data[10];  //用于移位数据备份
	unsigned char Count;
	if ((Number > 10) || (Number == 0))
	{
		return;
	}
	for (Count = 0; Count < Number; Count++) //先把要左移溢出的数据备份  
	{
		Data[Count] = SrcInOut[Rows + 4 * Count];
	}
	for (Count = 0; Count < (4 - Number); Count++)  //把后面的数据左移
	{
		SrcInOut[Rows + 4 * Count] = SrcInOut[Rows + 4 * (Number + Count)];
	}
	for (Count = 0; Count < Number; Count++)  //把后面的数据左移
	{
		SrcInOut[Rows + 4 * ((4 - Number) + Count)] = Data[Count];
	}
}
//行移动
void Aes_ShiftRows(unsigned char *SrcInOut)
{
	//const unsigned char Shitftable[4] = { 0, 1, 2, 3 };
	//ShiftByteNumRows(SrcInOut, 4, 0);  //第一行不移位
	ShiftByteNumRows(SrcInOut, 1, 1);    //左移1个字节
	ShiftByteNumRows(SrcInOut, 2, 2);    //左移2个字节
	ShiftByteNumRows(SrcInOut, 3, 3);    //左移3个字节
}
//逆向行移动
void Aes_invShiftRows(unsigned char *SrcInOut)
{
	//const unsigned char Shitftable[4] = { 0, 1, 2, 3 };
	//ShiftByteNumRows(SrcInOut, 4, 0);  //第一行不移位
	ShiftByteNumRows(SrcInOut, 1, 3);    //之前左移1个字节 逆向则为左移3个字节
	ShiftByteNumRows(SrcInOut, 2, 2);    //左移2个字节     逆向则为左移2个字节
	ShiftByteNumRows(SrcInOut, 3, 1);    //左移3个字节     逆向则为左移1个字节
}

//计算两个数在GF（28）域上的乘法
unsigned char  Get_Calculate_GF28(unsigned char data0, unsigned char data1)
{
	unsigned char Val = 0;
	unsigned char Count = 0;
	//把被乘数分成单独bit位或成的结果  比如  0x03*0x14 =0x03*00010100 =0x03*0x04 ^ 0x03*0x10  =((0x03*2)*2) ^ .... =  0x0c ^.... 
	for (Count = 0; Count < 8; Count++)
	{
		if (data1 & 0x01)  //判断当前
		{
			Val ^= data0;
		}
		data0 = (data0 << 1) ^ ((data0 & 0x80) ? 0x1b : 0); //每循环一次乘法的值变成两倍
		data1 >>= 1; //扫描下一位
	}
	return Val;
}
//列混淆
void Aes_MixColumns(unsigned char *SrcInOut)
{
	unsigned char Data_buff[4];  //一列数据备份
	unsigned char Calculate_val[4];   //计算后的值
	unsigned char Count; //列计数
	for (Count = 0; Count < 4; Count++)  //4 列
	{
		memcpy(Data_buff, &SrcInOut[Count * 4], 4); //拷贝一列的数据
		//执行 GF（28）域上的乘法
		Calculate_val[0] = Get_Calculate_GF28(Data_buff[0], aes_MixColumns[0][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_MixColumns[0][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_MixColumns[0][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_MixColumns[0][3]);

		Calculate_val[1] = Get_Calculate_GF28(Data_buff[0], aes_MixColumns[1][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_MixColumns[1][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_MixColumns[1][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_MixColumns[1][3]);

		Calculate_val[2] = Get_Calculate_GF28(Data_buff[0], aes_MixColumns[2][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_MixColumns[2][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_MixColumns[2][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_MixColumns[2][3]);

		Calculate_val[3] = Get_Calculate_GF28(Data_buff[0], aes_MixColumns[3][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_MixColumns[3][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_MixColumns[3][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_MixColumns[3][3]);

		memcpy(&SrcInOut[Count * 4], Calculate_val, 4); //拷贝结果
	}
}

//逆向列混淆
void Aes_invMixColumns(unsigned char *SrcInOut)
{
	unsigned char Data_buff[4];  //一列数据备份
	unsigned char Calculate_val[4];   //计算后的值
	unsigned char Count; //列计数
	for (Count = 0; Count < 4; Count++)  //4 列
	{
		memcpy(Data_buff, &SrcInOut[Count * 4], 4); //拷贝一列的数据
		//执行 GF（28）域上的乘法
		Calculate_val[0] = Get_Calculate_GF28(Data_buff[0], aes_invMixColumns[0][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_invMixColumns[0][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_invMixColumns[0][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_invMixColumns[0][3]);

		Calculate_val[1] = Get_Calculate_GF28(Data_buff[0], aes_invMixColumns[1][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_invMixColumns[1][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_invMixColumns[1][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_invMixColumns[1][3]);

		Calculate_val[2] = Get_Calculate_GF28(Data_buff[0], aes_invMixColumns[2][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_invMixColumns[2][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_invMixColumns[2][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_invMixColumns[2][3]);

		Calculate_val[3] = Get_Calculate_GF28(Data_buff[0], aes_invMixColumns[3][0]) ^ Get_Calculate_GF28(Data_buff[1], aes_invMixColumns[3][1]) ^ \
			Get_Calculate_GF28(Data_buff[2], aes_invMixColumns[3][2]) ^ Get_Calculate_GF28(Data_buff[3], aes_invMixColumns[3][3]);

		memcpy(&SrcInOut[Count * 4], Calculate_val, 4); //拷贝结果
	}
}

//AES 秘钥扩展中 的G函数
//先移位  再S盒替代  再与轮常数 异或
void Aes_G_function(unsigned char *Wjbuff_IN_OUT, unsigned char Count_j)
{
	unsigned char temp;
	//左移1个字节
	temp = Wjbuff_IN_OUT[0];
	memcpy(Wjbuff_IN_OUT, &Wjbuff_IN_OUT[1], 3);
	Wjbuff_IN_OUT[3] = temp;
	Aes_SubBytes(Wjbuff_IN_OUT, 4);       //S盒替换

	Wjbuff_IN_OUT[0] ^= aes_Rcon[Count_j];  //与常数轮 异或
	Wjbuff_IN_OUT[1] ^= 0x00;
	Wjbuff_IN_OUT[2] ^= 0x00;
	Wjbuff_IN_OUT[3] ^= 0x00;
}

void Aes_Bytes_Xor(unsigned char *Byte_IO, unsigned char *Byte_I, unsigned int Len)
{
	while (Len--)
	{
		*Byte_IO ^= *Byte_I;
		Byte_IO++;
		Byte_I++;
	}
}

//秘钥扩展
//KeySize: 秘钥大小 单位：字节  只能为16  24  32 
void Key_Schedule(unsigned char *KeyData_In, unsigned char KeySize)
{
	unsigned char Datatemp[4];
	unsigned char Datatemp0[4]; //计算的结果
	unsigned char Count;
	unsigned char Round_Count;  //轮计数  最大为14*4 = 56
	if (KeySize == 16)   //如果秘钥为16字节
	{
		Round_Count = 10;  //填充轮数
	}
	else if (KeySize == 24)
	{
		Round_Count = 12;  //填充轮数
	}
	else if (KeySize == 32)
	{
		Round_Count = 14;  //填充轮数
	}
	else //错误情况
	{
		return;
	}
	//拷贝原始秘钥 最后一列数据
	memcpy(Datatemp0, &KeyData_In[KeySize - 4], 4);
	//每轮需要一个子秘钥   每个子秘钥16字节  每次循环产生4个字节   即循环4次才产生一个字节秘钥  
	//当原始秘钥大于16字节时  多余16字节的数据为子秘钥数据   比如24字节秘钥  则原始秘钥中的后8个字节即为第一个子秘钥的前8个字节数据    32字节秘钥的后16字节数据 为第一个子秘钥数据
	//数量 * 4 则为原始秘钥不填充字节情况   但是当原始大于16字节时  需要考虑原始秘钥用于填充子秘钥情况
	for (Count = 0; Count < (Round_Count * 4 - ((KeySize - 16) / 8) * 2)/*减去原始秘钥填充子秘钥数据长度*/; Count++)
	{
		//列数如果为4或者6或者8的整数倍（取决于秘钥大小）  需要执行G函数   其它列只需要与对应列异或 及原秘钥矩阵列 与计算结果矩阵列异或
		if ((Count % (KeySize / 4)) == 0) //轮数为4的倍数  则其值 Wi = W(i-4) ^ G( W(i-1) )
		{
			Aes_G_function(Datatemp0, Count / (KeySize / 4));     //执行G函数  执行的结果保存在原数组中
		}
		else
		{
			//测试发现 上次计算的结果即为需要异或的数据  固没有重新读取数据
			if (((Count % (KeySize / 4)) == 4) && (KeySize == 32))  //在32字节秘钥下  如果当前轮数为4的倍数  则要经过一次S盒替代
			{
				Aes_SubBytes(Datatemp0, 4);       //S盒替换
			}
		}
		memcpy(Datatemp, &KeyData_In[Count * 4], 4); //得到指定一列的数据 
		Aes_Bytes_Xor(Datatemp0, Datatemp, 4);  //把两列数据异或
		memcpy(&KeyData_In[KeySize + Count * 4], Datatemp0, 4);  //拷贝结果
	}
}

//创建轮秘钥 128bit 秘钥 为10个子秘钥   192bit秘钥为   12个子秘钥   256bit为14个子秘钥    每个子秘钥固定为16    
//KeyByteSize: 秘钥字节数    只能为 16  24  32 
void Aes_Key_Schedule_Create(unsigned char *KeyData, unsigned char KeyByteSize)
{
	memcpy(Round_Key, KeyData, KeyByteSize); //把原始秘钥拷贝    拷贝到全局变量
	//开始根据原始秘钥扩展 子秘钥
	Key_Schedule(Round_Key, KeyByteSize);  //产生轮秘钥
}



//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key128bit:        秘钥  128bit  16字节
void Aes_IV_key128bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key128bit)
{
	unsigned char Count;
	if (key128bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT != NULL)  //如果有向量输入  则密文先与向量异或
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);
	}
	Aes_Key_Schedule_Create(key128bit, 16); //生成轮秘钥   共11轮  长度为 16字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[0], 16); //把第0轮秘钥与明文异或
	for (Count = 1; Count < 10; Count++)  //运行9轮 第10没有列混淆  固单独处理
	{
		Aes_SubBytes(State_IN_OUT, 16);  //字节替代
		Aes_ShiftRows(State_IN_OUT); //行移位
		Aes_MixColumns(State_IN_OUT);//列混淆
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
	}
	//第10轮----------------------------
	Aes_SubBytes(State_IN_OUT, 16);  //字节替代
	Aes_ShiftRows(State_IN_OUT); //行移位
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[16 * Count], 16);     //异或轮秘钥
	if (IV_IN_OUT != NULL)  //把密文拷贝到向量
	{
		memcpy(IV_IN_OUT, State_IN_OUT,16);
	}
}

//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key128bit:        秘钥  128bit  16字节
void Aes_IV_key128bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key128bit)
{
	unsigned char Count;
	unsigned char Temp[16];  //原密文数据缓存
	if (key128bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT!=NULL)
	{
		memcpy(Temp, State_IN_OUT, 16);  //拷贝原始密文
	}
	Aes_Key_Schedule_Create(key128bit, 16); //生成轮秘钥   共11轮  长度为 16字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[10 * 16], 16); //把第10轮秘钥与密文文异或
	Aes_invShiftRows(State_IN_OUT);       //逆向行移位
	Aes_invSubBytes(State_IN_OUT, 16);    //逆向字节替代
	for (Count = 9; Count > 0; Count--)  //运行9轮 第10没有列混淆  固单独处理
	{
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
		Aes_invMixColumns(State_IN_OUT);    //逆向列混淆
		Aes_invShiftRows(State_IN_OUT);     //逆向行移位
		Aes_invSubBytes(State_IN_OUT, 16);  //逆向字节替代	
	}
	//第10轮----------------------------
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[16 * Count], 16);     //异或轮秘钥  此处异或为原始秘钥
	if (IV_IN_OUT != NULL)
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);  //解密后的结果与向量异或
		memcpy(IV_IN_OUT, Temp, 16);  //拷贝原始密文到向量缓存
	}
}




//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key192bit:        秘钥  192bit  24字节
void Aes_IV_key192bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key192bit)
{
	unsigned char Count;
	if (key192bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT != NULL)  //如果有向量输入  则密文先与向量异或
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);
	}
	Aes_Key_Schedule_Create(key192bit, 24); //生成轮秘钥   共11轮  长度为 24字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[0], 16); //把第0轮秘钥与明文异或
	for (Count = 1; Count < 12; Count++)  //运行11轮 第12没有列混淆  固单独处理
	{
		Aes_SubBytes(State_IN_OUT, 16);  //字节替代
		Aes_ShiftRows(State_IN_OUT); //行移位
		Aes_MixColumns(State_IN_OUT);//列混淆
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
	}
	//第10轮----------------------------
	Aes_SubBytes(State_IN_OUT, 16);  //字节替代
	Aes_ShiftRows(State_IN_OUT); //行移位
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //异或轮秘钥
	if (IV_IN_OUT != NULL)  //把密文拷贝到向量
	{
		memcpy(IV_IN_OUT, State_IN_OUT, 16);
	}
}

//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key192bit:        秘钥  192bit  24字节
void Aes_IV_key192bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key192bit)
{
	unsigned char Count;
	unsigned char Temp[16];  //原密文数据缓存
	if (key192bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT != NULL)
	{
		memcpy(Temp, State_IN_OUT, 16);  //拷贝原始密文
	}
	Aes_Key_Schedule_Create(key192bit, 24); //生成轮秘钥   共12轮  长度为 24字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[12 * 16], 16); //把第12轮秘钥与密文文异或
	Aes_invShiftRows(State_IN_OUT);       //逆向行移位
	Aes_invSubBytes(State_IN_OUT, 16);    //逆向字节替代
	for (Count = 11; Count > 0; Count--)  //运行11轮 第12没有列混淆  固单独处理
	{
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
		Aes_invMixColumns(State_IN_OUT);    //逆向列混淆
		Aes_invShiftRows(State_IN_OUT);     //逆向行移位
		Aes_invSubBytes(State_IN_OUT, 16);  //逆向字节替代	
	}
	//第12轮----------------------------
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[16 * Count], 16);     //异或轮秘钥  此处异或为原始秘钥
	if (IV_IN_OUT != NULL)
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);  //解密后的结果与向量异或
		memcpy(IV_IN_OUT, Temp, 16);  //拷贝原始密文到向量缓存
	}
}


//AES加密  16字节一个数据块
//IV_IN_OUT:        向量输入  密文输出
//State_IN_OUT：    明文输入  密文输出
//key256bit:        秘钥  256bit  32字节
void Aes_IV_key256bit_Encrypt(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key256bit)
{
	unsigned char Count;
	if (key256bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT != NULL)  //如果有向量输入  则密文先与向量异或
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);
	}
	Aes_Key_Schedule_Create(key256bit, 32); //生成轮秘钥   共14轮  长度为 32字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[0], 16); //把第0轮秘钥与明文异或
	for (Count = 1; Count < 14; Count++)  //运行13轮 第14没有列混淆  固单独处理
	{
		Aes_SubBytes(State_IN_OUT, 16);  //字节替代
		Aes_ShiftRows(State_IN_OUT); //行移位
		Aes_MixColumns(State_IN_OUT);//列混淆
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
	}
	//第14轮----------------------------
	Aes_SubBytes(State_IN_OUT, 16);  //字节替代
	Aes_ShiftRows(State_IN_OUT); //行移位
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //异或轮秘钥
	if (IV_IN_OUT != NULL)  //把密文拷贝到向量
	{
		memcpy(IV_IN_OUT, State_IN_OUT, 16);
	}
}

//AES解密  16字节一个数据块
//IV_IN_OUT:        向量输入  原密文输出
//State_IN_OUT：    密文输入  明文输出
//key256bit:        秘钥  256bit  32字节
void Aes_IV_key256bit_Decode(unsigned char *IV_IN_OUT, unsigned char *State_IN_OUT, unsigned char *key256bit)
{
	unsigned char Count;
	unsigned char Temp[16];  //原密文数据缓存
	if (key256bit == NULL)
	{
		return;
	}
	if (IV_IN_OUT != NULL)
	{
		memcpy(Temp, State_IN_OUT, 16);  //拷贝原始密文
	}
	Aes_Key_Schedule_Create(key256bit, 32); //生成轮秘钥   共11轮  长度为 32字节
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[14 * 16], 16); //把第14轮秘钥与密文文异或
	Aes_invShiftRows(State_IN_OUT);       //逆向行移位
	Aes_invSubBytes(State_IN_OUT, 16);    //逆向字节替代
	for (Count = 13; Count > 0; Count--)  //运行13轮 第14没有列混淆  固单独处理
	{
		Aes_Bytes_Xor(State_IN_OUT, &Round_Key[Count * 16], 16);     //与轮秘钥异或
		Aes_invMixColumns(State_IN_OUT);    //逆向列混淆
		Aes_invShiftRows(State_IN_OUT);     //逆向行移位
		Aes_invSubBytes(State_IN_OUT, 16);  //逆向字节替代	
	}
	//第14轮----------------------------
	Aes_Bytes_Xor(State_IN_OUT, &Round_Key[16 * Count], 16);     //异或轮秘钥  此处异或为原始秘钥
	if (IV_IN_OUT != NULL)
	{
		Aes_Bytes_Xor(State_IN_OUT, IV_IN_OUT, 16);  //解密后的结果与向量异或
		memcpy(IV_IN_OUT, Temp, 16);  //拷贝原始密文到向量缓存
	}
}



//int main(void)
//{
//	unsigned char Temp[16]={0x2B,0XA3,0xDE,0xB4,0x2B,0x0E,0x8A,0xCB,0xD7,0x02,0x65,0x74,0x96,0x23,0xD8,0x25};  //原密文数据缓存
//	unsigned char IV[16]={0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32};  
//	unsigned char Key[32]={0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32,0x31,0X32};  //原密文数据缓存
//	Aes_IV_key256bit_Decode(IV,Temp,Key);
//	for(int i=0;i<16;i++)
//	{
//		printf("%02x ",Temp[i]);	
//	}
//	
// } 





