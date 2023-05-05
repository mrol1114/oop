set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/invalid-columns-matrix.txt test-data/valid-matrix-1.txt > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/invalid-columns-rows.txt test-data/valid-matrix-1.txt > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/invalid-values-matrix.txt test-data/valid-matrix-1.txt > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data/valid-matrix-1.txt test-data/valid-matrix-2.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/out-12.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data/valid-float-matrix-1.txt test-data/valid-float-matrix-2.txt > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt test-data/out-float-12.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
