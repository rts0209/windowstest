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

REM Compile Sub Files...
echo Compiling %SRC_DIR%/Sub files...
g++ -c %SRC_DIR%/collision_handler.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o collision_handler.o
if errorlevel 1 goto error

g++ -c %SRC_DIR%/input_handler.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o input_handler.o
if errorlevel 1 goto error

g++ -c %SRC_DIR%/variable_updater.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o variable_updater.o
if errorlevel 1 goto error

g++ -c %SRC_DIR%/game_state.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o game_state.o
if errorlevel 1 goto error

g++ -c %SRC_DIR%/menu_handler.cpp -I %INCLUDE_DIR% -I %INCLUDE_DIR%/STB -I %INCLUDE_DIR%/glad -I %INCLUDE_DIR%/GLFW -I %INCLUDE_DIR%/KHR -o menu_handler.o
if errorlevel 1 goto error

REM Check for GLFW
if not exist %LIB_DIR%\libglfw3.a goto error

REM Link everything
echo Linking...
g++ main.o glad.o player_movement.o collision_handler.o input_handler.o variable_updater.o game_state.o menu_handler.o -L %LIB_DIR% -lglfw3 -lopengl32 -lgdi32 -o %BIN_DIR%/program.exe
if errorlevel 1 goto error

REM Cleanup
del main.o
del glad.o
del player_movement.o
del collision_handler.o
del input_handler.o
del variable_updater.o
del game_state.o
del menu_handler.o

echo Build successful!
pause
goto end

:error
echo Build failed!
pause

:end
