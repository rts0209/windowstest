#include "player_movement.h"
#include <GLFW/glfw3.h>
#include <cstdio>


void updatePlayerMovement(rect& player, GLFWwindow* window, float dt)
{
    rect ground = {{-1.0f, -0.9f}, {2.0f, 0.2f}};
    bool grounded = false;

    // Move The Player
    player.pos.x += player.velocity.x * dt;
    player.pos.y += player.velocity.y * dt;


    if (player.rotation >= 360 ^ player.rotation <= -360) {
        player.rotation = 360;
    }

    const float speed = 20.0f;
    float gravity = -9.8f;


        if (player.pos.y = ground.pos.y + ground.size.y / 2) {
            grounded = true;
        }
        else {
            grounded = false;
        }


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

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && grounded == true) {
        player.velocity.y = 5.0f;
        grounded == false;
        
    }

    if (player.velocity.y > 0 && grounded == false) {
        player.velocity.y -= 0.05f * dt;
    }

    if (player.velocity.x > 0) {
        player.velocity.x -= dt * 2.75f;
    }

    if (player.velocity.x < 0) {
        player.velocity.x += dt * 2.75f;
    }
}

