#include "raylib.h"
#include <string>
using namespace std;

int main(){
    //window dimentions
    const int windowWidth{512};
    const int windowHeight{380};

    //initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1'000}; //acceleration due to gravity (pixels/sec)/sec

    // nebula variables, nebula is the *obstacle*
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8.f, nebula.height/8.f};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    
    //nebula x velocity (pixels/sec)
    int nebVel{-200};       

    //nebula animation frame
    int nebFrame{};
    const float nebUpdateTime{1.0/16.0};
    float nebRunningTime{};

    //character properties, character's name is *Scarfy*
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0.0, 0.0, scarfy.width/6.f, scarfy.height/1.f};   //(float) or (n).f
    Vector2 scarfyPos{(windowWidth/2 - scarfyRec.width/2), (windowHeight - scarfyRec.height)};

    //Scarfy animation frame 
    int frame{};
    const float updateTime{1.0/12.0}; //amount of time we update the animation frame
    float runningTime{1.0/12.0}; 

    //velocity
    int velocity{0};
    const float jumpVelocity{-569.3181818};  //(600) jump velocity (pixels/second)

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
        
        //update nebula position
        nebPos.x += (nebVel * dT);
        
        // updates scarfy's position
        scarfyPos.y += (velocity * dT); 
        
        //update scarfy (character) animation frames 
        if(!isInAir){
            runningTime += dT;

            if(runningTime >= updateTime){
                runningTime = 0.0;

                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5){
                    frame = 0;
                }
            }
        }

        //Update nebula (obstacle) animation
        nebRunningTime += dT; //adds delta time to run time
        
        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;

            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7){
                nebFrame = 0;  
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        //Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Draw FPS
        DrawFPS(10, 10);

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}