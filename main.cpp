#include "raylib.h"

int main(){
    //window dimentions
    const int windowWidth{512};
    const int windowHeight{380};

    //initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1}; //acceleration due to gravity (pixels/frame)/frame

    //rectange dimentions
    const int width = 50;
    const int height = 80;
    int posY{windowHeight - height}; //upper left corner of rectangle

    //velocity
    int velocity{0};
    const double jumpVelocity{-20.875};  // jump velocity

    // check for object in air 
    bool isInAir{};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //window drawing creation
        BeginDrawing();
        ClearBackground(WHITE);

        //GAME LOGIC  

        //gravity pull and ground check
        if (posY >= windowHeight - height){
            velocity = 0; // rectangle is on the ground
            isInAir = false;
        }
        else{
            velocity += gravity; // rectangle is in the air
            isInAir = true;
        }

        //detect key press for jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir){ 
            velocity += jumpVelocity;
        }
        
        posY += velocity; // updates rectange position

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        //stop drawing
        EndDrawing();
    }

    CloseWindow();
}