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
if errorlevel 1 goto error

REM Compile glad.c
echo Compiling %SRC_DIR%/glad.c...
g++ -c %SRC_DIR%/glad.c -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o glad.o
if errorlevel 1 goto error

REM Compile player_movement.cpp
echo Compiling %SRC_DIR%/player_movement.cpp...
g++ -c %SRC_DIR%/player_movement.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o player_movement.o
if errorlevel 1 goto error

REM Check for GLFW
if not exist %LIB_DIR%\libglfw3.a goto error

REM Link everything
echo Linking...
g++ main.o glad.o player_movement.o -L %LIB_DIR% -lglfw3 -lopengl32 -lgdi32 -o %BIN_DIR%/program.exe
if errorlevel 1 goto error

REM Cleanup
del main.o
del glad.o
del player_movement.o

echo Build successful!
pause
goto end

:error
echo Build failed!
pause

:end
