#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "glad/glad.h"  // Must include GLAD BEFORE GLFW
#include <GLFW/glfw3.h>
#include <cstdio>  // For printf debug output
#include <iostream>

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


struct Vec2 {
    float x, y;
};

struct rect {
    Vec2 pos;
    Vec2 size;
    float rotation = 0.0f;
};

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

    void FindLowestVertex() {
        /*
        Here we'll find the verticies of a normal rectangle and then adjust the collisions
        based around the rotation and positions of the box.

        I'm thinking about using a for loop to search for the lowest vertice on the box AFTER rotation
        I think we'll do a basic array to keep track of one item at a time. Once we find the LV I'll rewrite collisions.

        I'm going to use bounding boxes as a collider and find if more than 2 x, y values intersect then collision is true,
        I'll then write a calclation on how the boxes should respond based on angular velocity, mass, gravity, and speed.
        Those 4 values are the most important in this context, other important ones are WHERE they collide on terms of their
        own surfaces. Friction is also another important one, it would affect how much / far it rotates on a drastic angle.

        */
    }
    





int main(void) {
    glfwSwapInterval(1); // Enable VSync
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    


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

    while (!glfwWindowShouldClose(window)) {
        glfwWaitEventsTimeout(0.016);

        // Movement
    if(can_move == true) {

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        player.rotation += 1.0f;  // degrees per frame
        }


        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            velocity.x -= 0.0025f;
            printf("%.2f\n", velocity.x);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            velocity.x += 0.0025f;
            printf("%.2f\n", velocity.x);
        }
    }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && grounded) {
            velocity.y = 0.05f; // Jump
        }
        
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            // Spawn Box
            box.pos.x = player.pos.x;
            box.pos.y = 0 + (player.pos.y + 0.08f);
            box_velocity.y = velocity.y + 0.05f; 
            box_spawned = true;
            box_grounded = false;
            can_move = true;
            box.size.x = 0.1f, box.size.y = 0.1f;
            
            
        }

            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
                seal_spawned = true;
                printf("arf arf or whatever a seal says\n");
                seal.pos.x = 0.0f;
                seal.pos.y = 0.01f;
                seal_velocity.y = 0.04f;
            } 

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                printf("ESC pressed, exiting...\n");
                glfwTerminate();
                return -1;
            }

            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                menu_bool = true;
                printf("E pressed, opening menu...\n");
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
            if (box_spawned == true) {
                DrawRect(box, 0.2f, 0.2f, 0.8f);
            }

            if (seal_spawned == true) {
                DrawRect(seal, 0.4f, 0.9f, 0.4f);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();

                if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && menu_bool == true) {
                    printf("Q pressed, closing menu...\n");
                    menu_bool = false;
            
        }

            continue; // Skip rest of loop
    }

        // Gravity
        if(seal_spawned == true) {
            seal_velocity.y += gravity;
            seal.pos.y += seal_velocity.y;
            seal.pos.x += seal_velocity.x;

            if (CheckCollision(seal, ground)) {
                seal.pos.y = ground.pos.y + ground.size.y;
                seal_velocity.y = seal_velocity.y * -0.9f; // Bounce with damping
            }
        }

        if(box_spawned == true) {

            box_velocity.y += gravity;
            box.pos.x += box_velocity.x;
            box.pos.y += box_velocity.y;

            /*
            velocity.y += gravity;
            player.pos.x += velocity.x;
            player.pos.y += velocity.y;
            */

            if (box_velocity.x >= 0.001 &&  box_velocity.x <= -0.001) {
                box_velocity.x = 0;
            }

            box.pos.x += box_velocity.x;
            if (box_grounded == true && !box_velocity.x == 0) {
                if(box_velocity.x > 0) {
                    box_velocity.x -= 0.001f;
                }
                if(box_velocity.x < 0) {
                    box_velocity.x += 0.001f;
                }
            }

            if (box_velocity.x > 0 && box_grounded == false) {
                if(box_velocity.x > 0) {
                    box_velocity.x -= 0.001f;
                }
                if(box_velocity.x < 0 && box_grounded == false) {
                    box_velocity.x += 0.001f;
                }
            }
        }
        
            // Reset velocity to 0 if it's stuck at 0.01

            if (velocity.x <= 0.001 && velocity.x >= -0.001) {
                velocity.x = 0;
            }    

            //add friction and a max velocity to the player
        if (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
            // max velocity
            if (velocity.x >= 0.02 || velocity.x <= -0.02) {
                if (velocity.x > 0.02) {
                    velocity.x = 0.02;
                }
                if (velocity.x < -0.02) {
                    velocity.x = -0.02;
                }
            }

            // friction
            if (!velocity.x == 0 && grounded == true) {
                if (velocity.x > 0) {
                    velocity.x -= 0.001f;
                }
                if (velocity.x < 0) {
                    velocity.x += 0.001f;
                }
            }           
        }
        
        //give the box friction so it's not on ice
        if (!box_velocity.x == 0 && box_grounded == true) {
            if (box_velocity.x > 0) {
                box_velocity.x -= 0.002f;
            }
            if (box_velocity.x < 0) {
                box_velocity.x += 0.002f;
        }

        // now prevent it from being really tiny
        if (box_velocity.x <= 0.001 && box_velocity.x >= -0.001) {
                box_velocity.x = 0;
            }  
        }
        
        if(box_grounded == false) {
            box.pos.y += box_velocity.y;
        }
        
        velocity.y += gravity;
        player.pos.y += velocity.y;
        player.pos.x += velocity.x;

        if(box_grounded == true) {
            box_velocity.y = 0;
        }

        if (player.rotation >= 90) {
            player.rotation = 0;
        }

        // Collision
        if (CheckCollision(player, ground)) {
            ground.pos.y + ground.size.y + (player.rotation / 1000);
            velocity.y = 0;
            grounded = true;
        } else {
            grounded = false;
        }

        // Box Collison With Ground
        if (CheckCollision(box, ground)) {
            box.pos.y = ground.pos.y + ground.size.y;
            box_velocity.y = 0;
            box_grounded = true;
            can_move = true;
        } else {
            box_grounded = false;
        }



        /*
        How tf do we fix this error with the bouncing bug due to rotation.
        We can either check vertex collisions and then match them with the ground
        We can check collisions based on the verticies positions and then find the one closest with the ground,
        this can also be used to check for better box collisions and rotations as well.



        */

        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            // Reset Player and Box
            player.pos.x = -0.05f;
            player.pos.y = -0.5f;
            velocity.x = 0;
            velocity.y = 0;
            box.pos.x = 0.1f;
            box.pos.y = -0.1f;
            box_velocity.x = 0;
            box_velocity.y = 0;
            box_spawned = false;
            can_move = true;
        }

//========================================================================
//=======================Player, Box Collision============================
//========================================================================

        // Box on Player collsion
        if (box.pos.y > player.pos.y) {
            if (CheckCollision(player, box)) {
                on_player = true;
                box.pos.y = player.pos.y + box.size.y;
                box_velocity.y = 0;
                box_velocity.x = velocity.x / 2;
                //printf("%.2f\n", box_velocity.x);
                //printf("%.2f\n", velocity.x);
                if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && on_player == true) {
                    box_velocity.y = 0.045f; // Jump
                    box_velocity.x = velocity.x / 2 ;
                    velocity.y -= 0.02f;
                    on_player = false;
                }
            }       
        }

            if (CheckCollision(player, box)) {
                if (player.pos.x < box.pos.x && box_grounded == true && grounded == true) {
                    box_velocity.x = (velocity.x / 2) + 0.001;
                }
                if (player.pos.x > box.pos.x && box_grounded == true && grounded == true) {
                    box_velocity.x = (velocity.x / 2) - 0.001;
                }
            }

        if (CheckCollision(player, box)) {
            // Player is ON box
            if  (player.pos.y > box.pos.y) {
                box_velocity.x += velocity.x / 10;
                player.pos.y = box.pos.y + player.size.y;
                velocity.y = 0;
                grounded = true;
                //velocity.x = box_velocity.x / 2;
                can_move = false;
            }
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
        glfwPollEvents();        

    printf("Exiting program...\n");
    glfwTerminate();
    return 0;
    }
