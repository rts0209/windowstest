#ifndef GAME_STATE_H
#define GAME_STATE_H

// =======================
// Math Types
// =======================
struct Vec3 {
    float x;
    float y;
    float z;
};

struct rect {
    Vec3 pos;
    Vec3 size;
    Vec3 velocity;
    Vec3 rotation;
};



// =======================
// SHARED GAME VARIABLES
// =======================
extern rect parent;
extern rect cube;
extern rect ground;
extern rect target_cube_2;

extern bool is_grounded;
extern bool is_jumping;
extern bool menu_opened;
extern float delta_time;

#endif