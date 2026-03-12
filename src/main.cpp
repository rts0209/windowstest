#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "game_state.h"
#include "input.h"
#include "infworld.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float fov = 70.0f;
    float aspect = (float)width / (float)height;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    float top = tan(fov * 3.14159265f / 360.0f) * nearPlane;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    glFrustum(left, right, bottom, top, nearPlane, farPlane);

    glMatrixMode(GL_MODELVIEW);
}

void DrawCube(const rect& r)
{
    glPushMatrix();

    // Move the object so its center is placed at world-space position.
    glTranslatef(r.pos.x, r.pos.y, r.pos.z);

    // Rotate around object-local origin (which is now the cube center).
    glRotatef(r.rotation.x, 1, 0, 0);
    glRotatef(r.rotation.y, 0, 1, 0);
    glRotatef(r.rotation.z, 0, 0, 1);

    // Centered half-extents, so local origin is exactly in the middle.
    const float hx = r.size.x * 0.5f;
    const float hy = r.size.y * 0.5f;
    const float hz = r.size.z * 0.5f;

    glBegin(GL_QUADS);

    // Front (+Z)
    glColor3f(1, 0, 0);
    glVertex3f(-hx, -hy, +hz);
    glVertex3f(+hx, -hy, +hz);
    glVertex3f(+hx, +hy, +hz);
    glVertex3f(-hx, +hy, +hz);

    // Back (-Z)
    glColor3f(0, 1, 0);
    glVertex3f(-hx, -hy, -hz);
    glVertex3f(-hx, +hy, -hz);
    glVertex3f(+hx, +hy, -hz);
    glVertex3f(+hx, -hy, -hz);

    // Left (-X)
    glColor3f(0, 0, 1);
    glVertex3f(-hx, -hy, -hz);
    glVertex3f(-hx, -hy, +hz);
    glVertex3f(-hx, +hy, +hz);
    glVertex3f(-hx, +hy, -hz);

    // Right (+X)
    glColor3f(1, 1, 0);
    glVertex3f(+hx, -hy, -hz);
    glVertex3f(+hx, +hy, -hz);
    glVertex3f(+hx, +hy, +hz);
    glVertex3f(+hx, -hy, +hz);

    // Top (+Y)
    glColor3f(1, 0, 1);
    glVertex3f(-hx, +hy, -hz);
    glVertex3f(-hx, +hy, +hz);
    glVertex3f(+hx, +hy, +hz);
    glVertex3f(+hx, +hy, -hz);

    // Bottom (-Y)
    glColor3f(0, 1, 1);
    glVertex3f(-hx, -hy, -hz);
    glVertex3f(+hx, -hy, -hz);
    glVertex3f(+hx, -hy, +hz);
    glVertex3f(-hx, -hy, +hz);

    glEnd();

    glPopMatrix();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1200, 1200, "3D Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Force projection setup once
    framebuffer_size_callback(window, 1200, 1200);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    parent.pos.x = 0.0f;
    parent.pos.y = 0.0f;
    parent.pos.z = 0.0f;
    parent.rotation.x = 0.0f;
    parent.rotation.y = 0.0f;
    parent.rotation.z = 0.0f;

    ground.pos.y = -0.8f;
    ground.pos.x = 0.0f;
    ground.size.x = 1.0f;
    ground.size.z = 1.0f;
    cube.pos.x = 0;
    cube.pos.y = 1.0f;
    cube.pos.z = 0;

    is_grounded = true;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();



        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            is_grounded = true;
            cube.velocity.x = 0.0f;
            cube.velocity.y = 0.0f;
            cube.velocity.z = 0.0f;
            cube.pos.x = 0.0f;
            cube.pos.y = 0.0f;
            cube.pos.z = 0.0f;

        }     

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate;
            return -1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        // Camera
        glTranslatef(-0.15f, -0.15f, -2.0f);

        converttochunkcoords(cube, ground, window);

        playerinputs(window);

        PositiontoVelocity(cube, window);

        check_for_ground(cube, ground);

        IsOnObject(cube, ground, window);
        
        groundedfunctions(cube, ground, window);

        DrawCube(cube);

        DrawCube(ground);


        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
