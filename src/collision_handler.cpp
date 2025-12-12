#include "collision_handler.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

// ✅ ONLY place these functions exist

void CheckForGround(rect& player, GLFWwindow* window, float dt) {
    if (is_jumping == false) {
        float real_ground_height = ground.pos.y + (ground.size.y / 2);

        printf("Player.pos.y is %.3f\n", player.pos.y);

        printf("Actual top starts at %.3f\n", real_ground_height);
        if (player.pos.y = ground.pos.y + (ground.size.y / 2) + (player.size.y)) {
            player.pos.y = ground.pos.y + (ground.size.y / 2)   + (player.size.y);
            player.velocity.y = 0.0f;
            is_grounded = true;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                is_jumping = true;
                is_grounded = false;
                player.velocity.y = 35.0f * dt; 
            }
            
            
        }
        if (player.pos.y + player.size.y / 2 > ground.pos.y + (ground.size.y / 2) + (player.size.y)) {
            is_grounded = false;
            is_jumping = true;
        }
    }
}

void CheckForGroundWhilstFalling() {
    if (is_jumping == true) {
        if (player.pos.y = ground.pos.y + (ground.size.y / 2) + (player.size.y)) {
            is_grounded = true;
            is_jumping = false;
        }
        /*
        if (player.pos.y < ground.pos.y + (ground.size.y / 2) + (player.size.y)) {
            player.pos.y = ground.pos.y + (ground.size.y / 2) + (player.size.y);
            is_grounded = true;
            is_jumping = false;
        }
        */
        if (player.pos.y > ground.pos.y + (ground.size.y / 2) + (player.size.y)) {
            is_grounded = false;
            is_jumping = true;
        }
    }
}

void Gravity(float dt) {
    const float gravity = -0.98;
    if (is_grounded == false) {
        player.velocity.y += gravity * dt;
    }
}

/*
If I check for is_jumping to be true then I 
can't check if the player is above the ground
maybe I don't set the pos?
Maybe I should just set the velocity to 0 right?
*/