#include "collision_handler.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

// ✅ ONLY place these functions exist

void ResolveGroundCollision(rect& player) {
    float groundTop = ground.pos.y + ground.size.y / 2.0f;
    float playerBottom = player.pos.y - player.size.y;

    // Only collide if falling
    if (playerBottom <= groundTop && player.velocity.y <= 0.0f) {
        player.pos.y = groundTop + player.size.y;
        player.velocity.y = 0.0f;
        is_grounded = true;
    }
}

void Apply_Gravity(float dt) {
    const float gravity = -1.5f;

    if (!is_grounded) {
        player.velocity.y += gravity * dt;
    }
}

/*
If I check for is_jumping to be true then I 
can't check if the player is above the ground
maybe I don't set the pos?
Maybe I should just set the velocity to 0 right?
*/