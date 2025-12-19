#include "input_handler.h"
#include "game_state.h"
#include <GLFW/glfw3.h>

void Handle_input(rect& player, GLFWwindow* window) {
    const float move_speed = 2.0f;
    const float jump_force = 1.25f;

    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.velocity.x += 0.005f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.velocity.x -= 0.005f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        player.rotation += 0.05f;
    }
    else {
        player.velocity.x = 0.0f;
    }

    if (player.velocity.x > move_speed) {
        player.velocity.x = move_speed;
    }

    if (player.velocity.x < -move_speed) {
        player.velocity.x = -move_speed;
    }

    // Jump (ONLY when grounded)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && is_grounded) {
        player.velocity.y = jump_force;
        is_grounded = false;
    }
}
