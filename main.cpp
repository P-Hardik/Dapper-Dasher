#include "raylib.h"

int main(){
    //window dimentions
    const int windowWidth{512};
    const int windowHeight{380};

    //initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1'000}; //acceleration due to gravity (pixels/sec)/sec

    //character properties, character's name is *Scarfy*
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //animation frame 
    int frame{};
    const float updateTime{1.0/12.0}; //amount of time we update the animation frame
    float runningTime{}; 

    //velocity
    int velocity{0};
    const int jumpVelocity{-600};  // jump velocity (pixels/second)

    // check if character is in air
    bool isInAir{};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //delta time (time since last frame)
        const float dT {GetFrameTime()}; 

        //window drawing creation
        BeginDrawing();
        ClearBackground(WHITE);

        //GAME LOGIC  

        //gravity pull and ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height){
            velocity = 0; // scarfy is on the ground
            isInAir = false;
        }
        else{
            velocity += (gravity * dT); // scarfy is in the air
            isInAir = true;
        }

        //detect key press for jump
        if (IsKeyPressed(KEY_SPACE) && !isInAir){ 
            velocity += jumpVelocity;
        }
        
        scarfyPos.y += (velocity * dT); // updates scarfy's position

        //update animation frame 
        runningTime += dT;

        if(runningTime >= updateTime){
            runningTime = 0;

            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5){
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}