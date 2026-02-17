#include "game_state.h"

// =======================
// SHARED OBJECTS
// =======================
rect cube = {
    {  0.0f, 0.0f,  0.0f },   // pos
    {  0.2f,   0.2f,  0.2f },   // size | LENGTH, HEIGHT, DEPTH
    {  0.0f,   0.0f,  0.0f },   // velocity
    {  0.0f,  0.0f,  0.0f  } // Rotation
};

rect ground = {
    {  0.0f, 0.0f,  0.0f },   // pos
    {  1.0f,   0.8f,  1.0f },   // size | LENGTH, HEIGHT, DEPTH
    {  0.0f,   0.0f,  0.0f },   // velocity
    {  0.0f,  0.0f,  0.0f  } // Rotation
};

rect target_cube_2 = {
    {  0.0f, 0.0f,  0.0f },   // pos
    {  0.2f,   0.2f,  0.2f },   // size | LENGTH, HEIGHT, DEPTH
    {  0.0f,   0.0f,  0.0f },   // velocity
    {  0.0f,  0.0f,  0.0f  } // Rotation
};

rect parent = {
    {  0.0f, 0.0f,  0.0f },   // pos
    {  0.0f,   0.0f,  0.0f },   // size | LENGTH, HEIGHT, DEPTH
    {  0.0f,   0.0f,  0.0f },   // velocity
    {  0.0f,  0.0f,  0.0f  } // Rotation
};



// =======================
// SHARED VARIABLES
// =======================
bool is_grounded = false;
bool is_jumping = false;
bool menu_opened = false;
float delta_time = 0.016f;