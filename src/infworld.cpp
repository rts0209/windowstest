#include "infworld.h"
#include "game_state.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void checkforoutterbounderies (rect &a, rect &b, GLFWwindow * window) {
    // CnG = ChunkNeedsGeneration.
    bool CnG = false;
    double gen_chunk;
    double chunk_coords = 0 & 0;
    if (a.pos.x > b.pos.x) {
        CnG = true;
        gen_chunk = a.pos.x, a.pos.z;
        //if (CnG == true && gen_chunk != NULL, NULL) {
        //    
        //}
    }
}

void converttochunkcoords (rect &a, rect &b, GLFWwindow * window) {
    chunkcoord_x = a.pos.x * 10.0f;

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        printf("X: %f\n", chunkcoord_x);
    }
}