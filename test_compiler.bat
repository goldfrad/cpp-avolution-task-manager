@echo off
echo Testing C++ compiler...
echo.

echo Checking for g++...
g++ --version
if %errorlevel% equ 0 (
    echo g++ found! Compiling with MinGW...
    g++ -g main.cpp -o main.exe
    if %errorlevel% equ 0 (
        echo Compilation successful! Running program...
        main.exe
    ) else (
        echo Compilation failed!
    )
) else (
    echo g++ not found. Checking for MSVC...
    cl
    if %errorlevel% equ 0 (
        echo MSVC found! Compiling with cl...
        cl /EHsc /Fe:main.exe main.cpp
        if %errorlevel% equ 0 (
            echo Compilation successful! Running program...
            main.exe
        ) else (
            echo Compilation failed!
        )
    ) else (
        echo No C++ compiler found!
        echo Please install MinGW-w64 from https://winlibs.com/
        echo Or install Visual Studio with C++ support
    )
)

pause