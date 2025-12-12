#include "input_handler.h"
#include "collision_handler.h"
#include "game_state.h"
#include "player_movement.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void Update_Player(rect& player, GLFWwindow* window, float dt) {
    player.pos.y += player.velocity.y * dt;
    player.pos.x += player.velocity.x * dt;

    if (player.velocity.x > 2.0f) {
        player.velocity.x = 2.0f;
    }

    if (player.velocity.x < -2.0f) {
        player.velocity.x = -2.0f;
    }

    if (player.velocity.x != 0) {
        if (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS ) {
            if (player.velocity.x > 0) {
                player.velocity.x -= 0.005f;
            }
            if (player.velocity.x < 0) {
                player.velocity.x += 0.005f;
            }
        }
    }
}