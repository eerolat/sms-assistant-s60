@echo off
if "%1"=="" goto help

goto %1

:mbm
bmconv assist.lst
goto end

:saveico
copy assist.mbm \epoc32\release\wins\udeb\z\system\apps\assist\assist.mbm
copy assist.mbm \epoc32\data\z\system\apps\assist\assist.mbm
goto end

:all
call build mbm
call build saveico
goto end

:help
echo Use this to build and save parts of the AIF for SMS Assistant
echo build mbm	build the .mbm file
echo build saveico	save the icons with their projects
echo build all	do all steps in sequence

:end