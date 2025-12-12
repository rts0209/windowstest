#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include "game_state.h"
#include <GLFW/glfw3.h>

void GroundCollision();
void CheckForGround(rect& player, GLFWwindow* window, float dt);
void Gravity(float dt);
void CheckForGroundWhilstFalling();

#endif
