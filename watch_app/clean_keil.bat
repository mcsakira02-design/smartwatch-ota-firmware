@echo off
echo 正在清理 Keil 编译生成的临时文件...

:: 删除常见的 Keil 编译输出文件
del /S /Q *.bak       2>nul
del /S /Q *.ddk       2>nul
del /S /Q *.edk       2>nul
del /S /Q *.lst       2>nul
del /S /Q *.lnp       2>nul
del /S /Q *.obj       2>nul
del /S /Q *.omf       2>nul
del /S /Q *.tmp       2>nul
del /S /Q *.tra       2>nul
del /S /Q *.dep       2>nul
del /S /Q *.crf       2>nul
del /S /Q *.o         2>nul
del /S /Q *.d         2>nul
del /S /Q *.axf       2>nul
del /S /Q *.iex       2>nul
del /S /Q *.htm       2>nul
::del /S /Q *.sct       2>nul
del /S /Q *.map       2>nul
del /S /Q *.bak       2>nul
del /S /Q *.uvguix.*  2>nul
del /S /Q *.uvoptx    2>nul
del /S /Q *.uvprojx   2>nul

:: 删除文件夹
rmdir /S /Q Objects   2>nul
rmdir /S /Q Listings  2>nul

echo Keil 编译文件清理完成！
pause