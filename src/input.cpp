#include "input.h"
#include "game_state.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void check_for_ground(rect &a, rect &b) {
    float Top_A = a.pos.y + (a.size.y / 2);
    float Bottom_A = a.pos.y - (a.size.y / 2);
    float Top_B = b.pos.y + (b.size.y / 2);
    float Bottom_B = b.pos.y - (b.size.y / 2);

    if (Bottom_A <= Top_B) {
        is_grounded = true;
    }
    else {
        is_grounded = false;
    }

    if (Bottom_A < Top_B) {
        is_bottom_below = true;
    }
    else {
        is_bottom_below = false;
    }
}

void groundedfunctions(rect& a, rect& b, GLFWwindow *window) {
    float gravity = -0.00001f;
    float Bottom_A = a.pos.y - (a.size.y / 2);
    float Top_B = b.pos.y + (b.size.y / 2);

    if (is_grounded) {
        a.velocity.y = 0.0f;
        if (is_bottom_below == false) {
            a.pos.y = Top_B + (a.size.y / 2);
        }
        

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            a.velocity.y = 0.005f;
            is_grounded = false;
        }
    }
    else {
        is_grounded = false;
        a.velocity.y += gravity;
    }
}

void playerinputs(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            cube.velocity.z += -0.00002f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            cube.velocity.z += 0.00002f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cube.velocity.x += 0.00002f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cube.velocity.x += -0.00002f;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            cube.pos.x += 0.002f;
            ground.pos.x += 0.002f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            cube.pos.x += -0.002f;
            ground.pos.x += -0.002f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            cube.pos.z += 0.002f;
            ground.pos.z += 0.002f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            cube.pos.z += -0.002f;
            ground.pos.z += -0.002f;
        }
        
}

void IsOnObject(rect &a, rect& b, GLFWwindow *window) {
    if (a.pos.x - a.size.x / 2 > b.pos.x + b.size.x / 2) {
        is_grounded = false;
        is_bottom_below = false;
        //printf("[Positive X] Off of Edge. \n");
    }
    else if (a.pos.x + a.size.x / 2 < b.pos.x - b.size.x / 2) {
        //printf("[Negative X] Off of Edge. \n");
        is_grounded = false;
        is_bottom_below = false;
    }

    if (a.pos.z - a.size.z / 2 > b.pos.z + b.size.z / 2) {
        //printf("[Positive Z] Off of Edge. \n");
        is_grounded = false;
        is_bottom_below = false;
    }
    else if (a.pos.z + a.size.z / 2 < b.pos.z - b.size.z / 2) {
        //printf("[Negative Z] Off of Edge. \n");
        is_grounded = false;
        is_bottom_below = false;
    }
}

void PositiontoVelocity(rect &a, GLFWwindow* window) {
    a.pos.x += a.velocity.x;
    a.pos.y += a.velocity.y;
    a.pos.z += a.velocity.z;

    float vx = a.velocity.x;
    float vz = a.velocity.z;

    float friction = 0.00001f;
    float stopThreshold = 0.00005f;
    float max_speed = 0.00035f;

    if (glfwGetKey(window, GLFW_KEY_D || GLFW_KEY_A) != GLFW_PRESS) {
        if (vx > 0) {
            a.velocity.x += friction * -1;
        }
        else if (vx < 0) {
            a.velocity.x += friction;
        }

        if (vz > 0) {
            a.velocity.z += friction * -1;
        }
        else if (vz < 0) {
            a.velocity.z += friction;
        }
    }
    else {
        if (vx > max_speed) {
            a.velocity.x = max_speed;
        }
        else if (vx < max_speed) {
            a.velocity.x = max_speed *-1;
        }

        if (vz > max_speed) {
            a.velocity.z = max_speed;
        }
        else if (vz < max_speed) {
            a.velocity.z = max_speed *-1;
        }
    }
}
