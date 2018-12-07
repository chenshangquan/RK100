echo off
echo RckTool.exe build begin


if not exist "debug" (
	mkdir "debug"
)
if not exist "release" (
	mkdir "release"
)


if exist "..\..\..\10-common\version\debug\win32\RckTool" (
rmdir /s/q "..\..\..\10-common\version\debug\win32\RckTool"
)
if not exist "..\..\..\10-common\version\debug\win32\RkcTool" (
	mkdir "..\..\..\10-common\version\debug\win32\RkcTool"
)

if exist "..\..\..\10-common\version\release\win32\RkcTool" (
rmdir /s/q "..\..\..\10-common\version\release\win32\RkcTool"
)
if not exist "..\..\..\10-common\version\release\win32\RkcTool" (
	mkdir "..\..\..\10-common\version\release\win32\RkcTool"
)



call "%VS100COMNTOOLS%\vsvars32.bat"
echo build clean debug vs2010
@devenv RkcTool.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\CompileInfo\RkcTool_d.txt

echo build clean release vs2010
@devenv RkcTool.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\CompileInfo\RkcTool_r.txt

rem 还原现场
call "%VS60COMNTOOLS%\vcvars32.bat"



copy /Y Debug\RkcTool.exe ..\..\..\10-common\version\debug\win32\RkcTool\RkcTool.exe
copy /Y Release\RkcTool.exe ..\..\..\10-common\version\release\win32\RkcTool\RkcTool.exe

copy /Y ..\..\..\10-common\version\release\win32\tftp\tftp.exe ..\..\..\10-common\version\release\win32\RkcTool\tftp.exe

rem pdb调试文件
copy /Y Release\RkcTool.pdb ..\..\..\10-common\version\release\win32\RkcTool\RkcTool.pdb

if not exist "..\..\..\10-common\version\release\win32\RkcTool\skin" (
	mkdir "..\..\..\10-common\version\release\win32\RkcTool\skin"
)

copy /Y system.xml ..\..\..\10-common\version\debug\win32\RkcTool\system.xml
copy /Y system.xml  ..\..\..\10-common\version\release\win32\RkcTool\system.xml 

xcopy  skin\*.* ..\..\..\10-common\version\release\win32\RkcTool\skin /y /k /s 
copy /Y Release\RkcTool.map ..\..\..\10-common\version\release\win32\RkcTool\RkcTool.map

echo build RkcTool.exe over
echo on
