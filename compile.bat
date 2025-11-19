@echo off
REM Clean previous builds
if exist *.o del *.o
if exist bin\program.exe del bin\program.exe

REM Set directories
set SRC_DIR=src
set INCLUDE_DIR=include
set LIB_DIR=lib
set BIN_DIR=bin

REM Ensure bin directory exists
if not exist %BIN_DIR% mkdir %BIN_DIR%

REM Compile main.cpp
echo Compiling %SRC_DIR%/main.cpp...
g++ -c %SRC_DIR%/main.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o main.o
if errorlevel 1 (
    echo Compilation failed for main.cpp!
    goto error
)

REM Compile glad.c
echo Compiling %SRC_DIR%/glad.c...
g++ -c %SRC_DIR%/glad.c -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o glad.o
if errorlevel 1 (
    echo Compilation failed for glad.c!
    goto error
)

REM Check if GLFW library exists
if not exist %LIB_DIR%\libglfw3.a (
    echo Error: %LIB_DIR%\libglfw3.a not found! Ensure GLFW is properly installed.
    goto error
)

REM Link object files explicitly
echo Linking main.o and glad.o...
g++ main.o glad.o -L %LIB_DIR% -lglfw3 -lopengl32 -lgdi32 -o %BIN_DIR%/program.exe
if errorlevel 1 (
    echo Linking failed!
    goto error
)

REM Verify the exe was created
if exist %BIN_DIR%/program.exe (
    echo Build successful! Executable created at %BIN_DIR%/program.exe
    REM Clean up temporary object files after success
    del main.o glad.o
    echo Cleaned up temporary .o files.
) else (
    echo Error: Executable not found after linking!
    goto error
)

REM Copy required DLLs to bin
if exist %LIB_DIR%\glfw3.dll (
    copy %LIB_DIR%\glfw3.dll %BIN_DIR%\
    echo Copied glfw3.dll to %BIN_DIR%
) else (
    echo Warning: glfw3.dll not found in %LIB_DIR%. Ensure it's there for runtime.
)

echo Build process finished.
pause
goto end

:error
echo Build failed! Check the output above for details.
pause

:end