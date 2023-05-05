set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% dfgc > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 256 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% -1 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 255 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/255-out.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 0 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/0-out.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 6 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/6-out.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 155 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/155-out.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1