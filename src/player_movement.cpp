#include "player_movement.h"
#include <GLFW/glfw3.h>
#include <cstdio>


void updatePlayerMovement(rect& player, GLFWwindow* window, float dt)
{

    // Move The Player
    player.pos.x += player.velocity.x * dt;


    if (player.rotation >= 360 ^ player.rotation <= -360) {
        player.rotation = 360;
    }

    const float speed = 20.0f;


    if (player.velocity.x > 1.5 ^ player.velocity.x < -1.5) {
        if (player.velocity.x > 0) {
            player.velocity.x = 1.5;
        }

        if (player.velocity.x < 0) {
            player.velocity.x = -1.5;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.velocity.x += speed * dt;
        //player.rotation -= 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.velocity.x -= speed * dt;
        //player.rotation += 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        player.rotation += 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        player.rotation -= 1.0f;
    }

    /*
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && grounded == true) {
        player.velocity.y = 5.0f;
        grounded == false;
    }

    I think we'll handle jumping within the main file so variables are updated correctly, no
    */

    if (player.velocity.y > 0) {
        player.velocity.y -= 0.05f * dt;
    }

    if (player.velocity.x > 0) {
        player.velocity.x -= dt * 2.75f;
    }

    if (player.velocity.x < 0) {
        player.velocity.x += dt * 2.75f;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS == true) {
        player.velocity.y = dt * 0.3f;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
    printf("%.f\n", player.velocity.y);
        //printf("%.f\n", velocity.x);
    }
}

