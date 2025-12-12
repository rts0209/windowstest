#include "game_state.h"

// =======================
// SHARED OBJECTS
// =======================
rect player = {
    { -0.05f, -0.5f },   // pos
    {  0.1f,   0.1f },   // size
    {  0.0f,   0.0f },   // velocity
    0.0f                  // rotation
};

rect ground = {
    { -1.0f, -1.0f },
    {  2.0f,  0.1f },
    {  0.0f,  0.0f },
    0.0f
};



// =======================
// SHARED VARIABLES
// =======================
bool is_grounded = false;
bool is_jumping = false;
float delta_time = 0.016f;
