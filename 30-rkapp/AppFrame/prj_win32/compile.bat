@echo off
echo AppFrame build begin
rem 创建文件夹

call "%VS100COMNTOOLS%\vsvars32.bat"

echo build clean debug unicode vs2010
@devenv AppFrame.vcxproj /ReBuild "Unicode_Debug" /Out ..\..\..\10-common\version\CompileInfo\appframe_u_d_2010.txt

echo build clean release unicode vs2010
@devenv AppFrame.vcxproj /ReBuild "Unicode_Release" /Out ..\..\..\10-common\version\CompileInfo\appframe_u_r_2010.txt

rem 还原现场
call "%VS60COMNTOOLS%\vcvars32.bat"

echo AppFrame build end




