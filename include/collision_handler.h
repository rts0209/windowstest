#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include "game_state.h"
#include <GLFW/glfw3.h>

void ResolveGroundCollision(rect& player);
void Apply_Gravity(float dt);

#endif
