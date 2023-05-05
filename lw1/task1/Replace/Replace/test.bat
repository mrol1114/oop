set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/empty.txt test-data/empty.txt 1 11 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/fox.txt %TEMP%\out.txt bird cat > null
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/fox.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data/fox.txt %TEMP%\out.txt dog cat > null
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/fox-replace-dog-with-cat.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data/empty.txt %TEMP%\out.txt 1 11 > null
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/empty-replace-1-11.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data/numbers.txt %TEMP%\out.txt 123 123123 > null
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/numbers-replace-123-with-123123.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data/numbers.txt %TEMP%\out.txt 1231234 aa > null
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/numbers-replace-1231234-with-aa.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1