#include "input_handler.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void player_movements(rect& player, GLFWwindow* window, float dt) {
    
    const float speed = 3.0f;
    const float jump_strength = 15.0f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.velocity.x += speed * dt;
        printf("5%.f\n", player.velocity.x);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.velocity.x -= speed * dt;
        printf("5%.f\n", player.velocity.x);
    }
    /*
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && is_grounded == true) {
        player.velocity.y = jump_strength * dt;
        is_jumping = true;
        printf("Player Velocity: %.f\n", player.velocity.y);
        printf("Jumping?: %.i\n", is_jumping);
        
    }
    */
}