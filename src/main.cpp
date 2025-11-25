#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glad/glad.h"  // Must include GLAD BEFORE GLFW
#include <GLFW/glfw3.h>
#include <cstdio>  // For printf debug output
#include <iostream>
#include <cmath>
#include "player_movement.h"



rect player;

int wwidth, hheight;
float red;
float green;
float blue;
int height = 32;
int width = 32;
int pixels = width * height;
bool menu_bool = false;
bool menu_timeout = false;
bool box_spawned = false;
bool can_move = true;
bool start_vertex = false;

bool CheckCollision(const rect& a, const rect& b) {
    return (a.pos.x < b.pos.x + b.size.x &&
            a.pos.x + a.size.x > b.pos.x &&
            a.pos.y < b.pos.y + b.size.y &&
            a.pos.y + a.size.y > b.pos.y);
}

/*
void DrawRect(const rect& r, float r_col, float g_col, float b_col) {
    glBegin(GL_QUADS);
    glColor3f(r_col, g_col, b_col);
    glVertex2f(r.pos.x, r.pos.y);
    glVertex2f(r.pos.x + r.size.x, r.pos.y);
    glVertex2f(r.pos.x + r.size.x, r.pos.y + r.size.y);
    glVertex2f(r.pos.x, r.pos.y + r.size.y);
    glEnd();
}
*/

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


// If I need to delete everything from here



    struct constrect {
        float x, y;     // position
        float w, h;     // size
        float rot;      // rotation
    };



    /*
        Here we'll find the verticies of a normal rectangle and then adjust the collisions
        based around the rotation and positions of the box.

        I'm thinking about using a for loop to search for the lowest vertice on the box AFTER rotation
        I think we'll do a basic array to keep track of one item at a time. Once we find the LV I'll rewrite collisions.

        I'm going to use bounding boxes as a collider and find if more than 2 x, y values intersect then collision is true,
        I'll then write a calclation on how the boxes should respond based on angular velocity, mass, gravity, and speed.
        Those 4 values are the most important in this context, other important ones are WHERE they collide on terms of their
        own surfaces. Friction is also another important one, it would affect how much / far it rotates on a drastic angle.

        []----[]    * Track the corners and find the lowest one if the angle isn't 0 (If the angle is 0 find the bottom 2)
        |      |    * Initialize corners first as floating point values, ex: c1cp = 1.0f
        |      |    * Use a for loop to find the one that's the lowest in y value
        []----[]    *

        */

// DISABLE FOR NOW UNTIL I REDO THE FUCKING COLLISION
// !!!! WRITE A COLLISON CODE USING THE CODE AND ARRAYS YOU IDIOT !!!!
//*
    

    void GetCorners_TopLeftPos(const rect &a, Vec2 outCorners[4]) {



            // do I use a box.pos.x + box.size.x approach? Or track the literal verticies?
            //👍 well I think I'll learn array's whilst I'm at it.
            // initialize variables lol
            const float PI = 3.14159265358979323846f;   

            float hw = a.size.x * 0.5f; // half width / half x
            float hh = a.size.y * 0.5f; // half height / half y

            // cos and sin, How tf do these work?
            float rad = a.rotation * (PI / 180.0f);
            float c = cos(rad);
            float s = sin(rad);

            // initialize array
            float local_x[4] = { -hw, hw, hw, -hw };
            float local_y[4] = { -hh, -hh, hh, hh };

            float cx = a.pos.x + hw;
            float cy = a.pos.y + hh;


            // FOR LOOPS, kill me zawg
            for (int i = 0; i < 4; i++) {
                float rx = local_x[i] * c - local_y[i] * s;
                float ry = local_x[i] * s + local_y[i] * c;

                outCorners[i].x = cx + rx;
                outCorners[i].y = cy + ry;
            }
        // to here

    }

    int FindLowestVertex(const rect &a, Vec2 outCorners[4], Vec2 &lowestOut)
{
    GetCorners_TopLeftPos(a, outCorners);

    int lowestIdx = 0;
    lowestOut = outCorners[0];

    for (int i = 1; i < 4; ++i) {
        if (outCorners[i].y < lowestOut.y) {
            lowestOut = outCorners[i];
            lowestIdx = i;
        }
    }
    return lowestIdx;
}

//*

int main(void) {
    glfwSwapInterval(1); // Enable VSync
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    player.pos = {0, 0};
    player.size = {50, 50};
    player.rotation = 0;

    printf("Starting program...\n");
    red = 0.1f;
    green = 0.3f;
    blue = 0.7f;

    GLFWwindow* window;

    printf("Initializing GLFW...\n");
    if (!glfwInit()) {
        printf("GLFW init failed!\n");
        return -1;
    }

    printf("Creating window...\n");
    window = glfwCreateWindow(1200, 1200, "Hello World✔ ", NULL, NULL);
    if (!window) {
        printf("Window creation failed!\n");
        glfwTerminate();
        return -1;
    }

    printf("Making context current...\n");
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // World Setup
    rect ground = {{-1.0f, -0.9f}, {2.0f, 0.2f}};
    rect player = {{-0.05f, -0.5f}, {0.1f, 0.1f}};
    rect menu = {{-0.3f, -0.3f}, {0.6f, 0.6f}};
    rect box = {{0.1f, -0.1f}, {0.1f, 0.1f}};
    rect seal = {{0.7f, 0.7f}, {0.3f, 0.1f}};


    box.rotation = 0;
    player.rotation = 0;

    Vec2 velocity = {0.0f, 0.0f};
    Vec2 box_velocity = {0.0f, 0.0f};
    Vec2 seal_velocity = {0.0f, 0.0f};
    const float gravity = -0.002f;

    bool grounded = false;
    bool box_grounded = false;
    bool on_box = false;
    bool on_player = false;
    bool seal_spawned = false;

    float cx = player.pos.x + player.size.x * 0.5f;
    float cy = player.pos.y + player.size.y * 0.5f;

 
    printf("Initializing GLAD...\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("GLAD load failed!\n");
        glfwTerminate();
        return -1;
    }

    printf("Loading icon...\n");
    int icon_width, icon_height, icon_channels;
    unsigned char* icon_pixels = stbi_load("C:/Users/nismo/Downloads/asdwasd.jfif", &icon_width, &icon_height, &icon_channels, 4);  // Changed to relative path
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

         updatePlayerMovement(player, window, dt);

        player.pos.y += velocity.y * dt;

        if (velocity.y > 0) {
            velocity.y * gravity;
        }


            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                //printf("ESC pressed, exiting...\n");
                glfwTerminate();
                return -1;
            }

            
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                menu_bool = true;
                //printf("E pressed, opening menu...\n");
                menu.pos.x = -0.95f;
                menu.pos.y = -0.35f;
                menu.size.y = 1.25f;
                printf("%.2f\n", box.pos.x);
                printf("%.2f\n", box.pos.y);
            }

        if (menu_bool) {
            // Render menu
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            DrawRect(menu, 0.5f, 0.5f, 0.5f);
            DrawRect(ground, 0.2f, 0.9f, 0.3f);
            DrawRect(player, 0.8f, 0.2f, 0.2f); 
        //  DrawRect(seal, 0.4f, 0.9f, 0.4f); Example Draw 


            glfwSwapBuffers(window);
            glfwPollEvents();

                if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && menu_bool == true) {
                    //printf("Q pressed, closing menu...\n");
                    menu_bool = false;
            
        }

            continue; // Skip rest of loop
    }



    // This section is forcing the cube to stick to the ground so it can't jump.
    // So how the hell do I fix this?
    // Can't use an if grounded statement since there's an else grounded in there.
    // When I disabled plyr.pos.y += pen; the player's top got stuck under ground?
    // So maybe I should track the bottom verticies instead of the top left?
    // Honestly how the hell should I do this? I do want it so if a box is a little off the edge on top
    // it falls and then tips over. That'd be nice. But in the mean time, I need to fix this stupid bug
    // Because this line is breaking it "player.pos.y += penetration;", maybe delete it or find a new approach
    // To execute the same code? I really should do this based off of the bottom 2 verticies.
    //
    //
    //
    //

        



    // Only check for ground collision when the player is MOVING DOWN
    /*
        if (velocity.y < 0.0f) 
            {
            if (lowest.y < groundTopY)
            {
                float penetration = groundTopY - lowest.y;

                // Correct position (landing)
                player.pos.y += penetration;

                // Stop falling
                velocity.y = 0.0f;
                grounded = true;
            }
        else 
            {
                grounded = false;
        }
    }
    */

    float groundTopY = ground.pos.y + ground.size.y;
    float playerBottomY = player.pos.y + player.size.y;

        Vec2 corners[4];
        Vec2 lowest;
        int idx = FindLowestVertex(player, corners, lowest);
        float penetration = groundTopY - lowest.y;
        // maybe rewrite this float section of code?



    if (player.rotation = 0) {
        if (velocity.y = 0.0f) {
            if (lowest.y < groundTopY) {
        
                player.pos.y += penetration;

                velocity.y = 0.0f;
                grounded = true;
            }
                else {
                    grounded = false;
                }
        }
    }
        else {
            if (velocity.y < 0.0f) {
                player.pos.y += penetration;
                velocity.y = 0.0f;
                grounded = true;
            }
        }

    if (player.pos.y > ground.pos.y) {
        grounded = false;
        }

    if (player.pos.y = ground.pos.y + (ground.size.y / 2)) {
        velocity.y = 0.0f;
        grounded = true;
        player.pos.y = player.pos.  y + (ground.size.y / 2);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && grounded == true) {
        player.pos.y = groundTopY + playerBottomY;
        velocity.y += 0.3f;
        grounded = false;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        printf("%.f\n", velocity.y);
        //printf("%.f\n", velocity.x);
    }


        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            // Reset Player and Box
            player.pos.x = -0.05f;
            player.pos.y = -0.5f;
            velocity.x = 0;
            velocity.y = 0;
            box.pos.x = 0.3f;
            box.pos.y = -0.1f;
            box_velocity.x = 0;
            box_velocity.y = 0;
            box_spawned = false;
            can_move = true;
        }

        // Rendering
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        DrawRect(ground, 0.2f, 0.9f, 0.3f);  // green ground    
        DrawRect(player, 0.8f, 0.2f, 0.2f);  // red player  
        if (box_spawned == true) {
            DrawRect(box, 0.2f, 0.2f, 0.8f);
        }   // blue box
        if (seal_spawned == true) {
                DrawRect(seal, 0.44f, 0.44f, 0.4f);
            }

        

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
