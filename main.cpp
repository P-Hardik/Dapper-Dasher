#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(){
    //window dimensions

    const int windowDimensions[2] = {512, 380};

    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData{ 
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f}, // Rectangle rec
        {(float)windowDimensions[0], (float)windowDimensions[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/16.0, // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8.f, nebula.height/8.f},
        {(float)windowDimensions[0] + 300, (float)windowDimensions[1] - nebula.height/8},
        0,
        1.0/32.0, //smaller fraction = the faster animations 
        0.0
    };

    AnimData nebulae[] {nebData, neb2Data};
    //nebulae[0]
    //nebulae[1]

    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0.0, 0.0, scarfy.width/6.f, (float)scarfy.height}, //Rectangle rec
        {windowDimensions[0]/2.f - scarfyData.rec.width/2.f, windowDimensions[1] - scarfyData.rec.height}, // Vector2pos
        0, // int frame
        1.0/12.0, //float updateTime
        0.0, //float runningTime
    };

    // is the rectanlge in the air?
    bool isInAir{};

    // jump velocity (pixels/second)
    const float jumpVel{-569.30};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height){
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }else{
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVel;
        }

        // update nebula position
        nebulae[0].pos.x += nebVel * dT;

        // update the second nebula's position
        nebulae[1].pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy's animation frame
        if (!isInAir){
            // update running time
            scarfyData.runningTime += dT;

            if (scarfyData.runningTime >= scarfyData.updateTime){
                scarfyData.runningTime = 0.0;

                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;

                if (scarfyData.frame > 5){
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula animation frame
        nebulae[0].runningTime += dT;

        if (nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;

            if (nebulae[0].frame > 7){ 
                nebulae[0].frame = 0;
            }
        }

        // update nebula2 animation frame
        nebulae[1].runningTime += dT;

        if (nebulae[1].runningTime >= nebulae[1].updateTime){
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;

            if (nebulae[1].frame > 7){ 
                nebulae[1].frame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        // draw the second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}