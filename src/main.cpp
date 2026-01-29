#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glad/glad.h"  // Must include GLAD BEFORE GLFW
#include <GLFW/glfw3.h>
#include <cstdio>  // For printf debug output
#include <iostream>
#include <cmath>
#include "game_state.h"

int height = 32;
int width = 32;
int pixels = width * height;
bool start_vertex = false;

bool CheckCollision(const rect& a, const rect& b) {
    return (a.pos.x < b.pos.x + b.size.x &&
            a.pos.x + a.size.x > b.pos.x &&
            a.pos.y < b.pos.y + b.size.y &&
            a.pos.y + a.size.y > b.pos.y);
}

    void DrawRect(const rect& r, float r_col, float g_col, float b_col) {
        glPushMatrix();
        glTranslatef(r.pos.x + r.size.x * 0.5f, r.pos.y + r.size.y * 0.5f, 0);
        glRotatef(r.rotation, 0, 0, 1);
        glTranslatef(-r.size.x * 0.5f, -r.size.y * 0.5f, 0);

        // start drawing quads
        glBegin(GL_QUADS);
            glColor3f(r_col, g_col, b_col);
            glVertex2f(0, 0);
            glVertex2f(r.size.x, 0);
            glVertex2f(r.size.x, r.size.y);
            glVertex2f(0, r.size.y);
        glEnd();

    glPopMatrix();
    }



int main(void) {
    glfwSwapInterval(1); // Enable VSync
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    printf("Starting program...\n");

    GLFWwindow* window;

    printf("Initializing GLFW...\n");
    if (!glfwInit()) {
        printf("GLFW init failed!\n");
        return -1;
    }

    printf("Creating window...\n");
    window = glfwCreateWindow(1200, 1200, "Huh. ", NULL, NULL);
    if (!window) {
        printf("Window creation failed!\n");
        glfwTerminate();
        return -1;
    }

    printf("Making context current...\n");
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // World Setup

     
    printf("Initializing GLAD...\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("GLAD load failed!\n");
        glfwTerminate();
        return -1;
    }

    printf("Loading icon...\n");
    int icon_width, icon_height, icon_channels;
    unsigned char* icon_pixels = stbi_load("C:/Users/nismo/Downloads/images.jpg", &icon_width, &icon_height, &icon_channels, 4);  // Changed to relative path
    if (!icon_pixels) {
        printf("Icon load failed! STB Error: %s\n", stbi_failure_reason());  // More debug info
        printf("Continuing without icon...\n");
    } else {
        printf("Icon loaded successfully: %dx%d\n", icon_width, icon_height);
        GLFWimage images[1];
        images[0].width = icon_width; 
        images[0].height = icon_height;
        images[0].pixels = icon_pixels;
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(icon_pixels);  // Free immediately after setting
    }

//  ------------------------------------------------------------------------------------------------------------
    printf("Entering main loop...\n");

    double lastTime = glfwGetTime();
    printf("%.f\n", lastTime);

    while (!glfwWindowShouldClose(window)) {
        

        double now = glfwGetTime();
        float dt = float(now - lastTime);
        lastTime = now;

        glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                //printf("ESC pressed, exiting...\n");
                glfwTerminate();
                return -1;
            }

        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        }
    
        // Rendering
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        DrawRect(ground, 0.2f, 0.9f, 0.3f);  // green ground    

        glfwSwapBuffers(window);
        }

        GLFW_RESIZABLE; // Approx 60 FPS
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
             

    printf("Exiting program...\n");
    glfwTerminate();
    return 0;
    }