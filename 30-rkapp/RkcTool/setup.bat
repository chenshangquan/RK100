rem echo off
if not exist "..\..\10-common\version\release\win32\RkcTool" (
    mkdir "..\..\10-common\version\release\win32\RkcTool"
)


if exist "..\..\10-common\version\compileinfo\RkcTool_setup.txt" (
    del ..\..\10-common\version\compileinfo\RkcTool_setup.txt
)


if not exist "setup files" (
    mkdir "setup files"
)


rem 拷贝相应文件
if not exist "setup files\skin" (
    mkdir "setup files\skin"
)


copy /Y ..\..\10-common\version\release\win32\RkcTool\RkcTool.exe "setup files\RkcTool.exe"
copy /Y ..\..\10-common\version\release\win32\tftp\tftp.exe "setup files\tftp.exe"
copy /Y ..\..\10-common\version\release\win32\RkcTool\system.xml "setup files\system.xml"

xcopy "..\..\10-common\version\release\win32\RkcTool\skin\*.*" "setup files\skin\" /s /y /h


cd setup
call compile.bat %1
cd..

del /S /Q "setup files\*.*"

:end
