#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "game_state.h"

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

    glTranslatef(r.pos.x, r.pos.y, r.pos.z);

    glRotatef(r.rotation.x, 1, 0, 0);
    glRotatef(r.rotation.y, 0, 1, 0);
    glRotatef(r.rotation.z, 0, 0, 1);

    float x = r.size.x;
    float y = r.size.y;
    float z = r.size.z;

    glBegin(GL_QUADS);

    // Front
    glColor3f(1,0,0);
    glVertex3f(0,0,z);
    glVertex3f(x,0,z);
    glVertex3f(x,y,z);
    glVertex3f(0,y,z);

    // Back
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,y,0);
    glVertex3f(x,y,0);
    glVertex3f(x,0,0);

    // Left
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,z);
    glVertex3f(0,y,z);
    glVertex3f(0,y,0);

    // Right
    glColor3f(1,1,0);
    glVertex3f(x,0,0);
    glVertex3f(x,y,0);
    glVertex3f(x,y,z);
    glVertex3f(x,0,z);

    // Top
    glColor3f(1,0,1);
    glVertex3f(0,y,0);
    glVertex3f(0,y,z);
    glVertex3f(x,y,z);
    glVertex3f(x,y,0);

    // Bottom
    glColor3f(0,1,1);
    glVertex3f(0,0,0);
    glVertex3f(x,0,0);
    glVertex3f(x,0,z);
    glVertex3f(0,0,z);

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
    cube.pos.x = 0;
    cube.pos.y = 0;
    cube.pos.z = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        /*
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cube.rotation.x += 0.25f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cube.rotation.x -= 0.25f;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cube.rotation.y += 0.25f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cube.rotation.y -= 0.25f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cube.pos.z -= 0.005f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cube.pos.z += 0.005f;

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            cube.pos.y += 0.005f;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            cube.pos.y -= 0.005f;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cube.pos.x -= 0.005f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cube.pos.x += 0.005f;

        */

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            parent.rotation.x = 0.0f;
            parent.rotation.y = 0.0f;
            parent.rotation.z = 0.0f;

        }

        cube.rotation.x = parent.rotation.x;
        cube.rotation.y = parent.rotation.y;
        cube.rotation.z = parent.rotation.z;
        ground.rotation.x = parent.rotation.x;
        ground.rotation.y = parent.rotation.y;
        ground.rotation.z = parent.rotation.z;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            ground.pos.z += -0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            cube.pos.z += 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cube.pos.x += 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cube.pos.x += -0.001f;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            parent.rotation.y += 0.05f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            parent.rotation.y += -0.05f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            parent.rotation.x += 0.05f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            parent.rotation.x += -0.05f;
        }

        

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate;
            return -1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        // Camera
        glTranslatef(-0.15f, -0.15f, -2.0f);

        DrawCube(cube);
        DrawCube(ground);
        //DrawCube(target_cube_2);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
