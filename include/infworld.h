#ifndef INFWORLD_H
#define INFWORLD_H


#include "infworld.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void checkforoutterbounderies (rect &a, rect &b, GLFWwindow * window);

void converttochunkcoords (rect &a, rect &b, GLFWwindow * window);

#endif