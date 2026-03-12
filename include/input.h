#ifndef INPUT_H
#define INPUT_H

#include "game_state.h"
#include <GLFW/glfw3.h>

void check_for_ground(rect &a, rect &b);
void groundedfunctions(rect& a, rect& b, GLFWwindow* window);
void IsOnObject(rect &a, rect& b, GLFWwindow *window);
void playerinputs(GLFWwindow* window);
void PositiontoVelocity(rect& a, GLFWwindow* window);

#endif