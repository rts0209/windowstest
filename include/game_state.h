#ifndef GAME_STATE_H
#define GAME_STATE_H

// =======================
// Math Types
// =======================
struct Vec2 {
    float x;
    float y;
};

struct rect {
    Vec2 pos;
    Vec2 size;
    Vec2 velocity;
    float rotation;
};



// =======================
// SHARED GAME VARIABLES
// =======================
extern rect player;
extern rect ground;

extern bool is_grounded;
extern bool is_jumping;
extern float delta_time;

#endif
