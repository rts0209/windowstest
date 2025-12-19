#include "input_handler.h"
#include "collision_handler.h"
#include "game_state.h"
#include "player_movement.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void Integrate_Movement(rect& player, float dt) {
    player.pos.x += player.velocity.x * dt;
    player.pos.y += player.velocity.y * dt;
}
