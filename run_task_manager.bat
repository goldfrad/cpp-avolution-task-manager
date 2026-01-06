@echo off
echo Building Task Manager...
C:\mingw64\bin\g++.exe -g main.cpp src/Task.cpp src/TaskRepository.cpp src/TaskService.cpp src/ConsoleUI.cpp -o main.exe

if %errorlevel% equ 0 (
    echo Build successful! Starting Task Manager...
    echo.
    main.exe
) else (
    echo Build failed!
)

pause