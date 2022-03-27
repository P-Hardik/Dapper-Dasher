#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
};

AnimData updateAnimData (AnimData data, float deltaTime, int maxFrame){
    //update running time 
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.0;

        //update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame){
            data.frame = 0.0;
        }   
    }
    return data;
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

    //amount of the nebula
    const int nebNum{10};

    // Animation Data for nebula
    AnimData nebulae[nebNum] {};

    for (int i = 0; i < nebNum; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8.f;
        nebulae[i].rec.height = nebula.height/8.f;
        nebulae[i].pos.x = (float)windowDimensions[0] + (i * 300); //for distance between each
        nebulae[i].pos.y = (float)windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    };

    const int nebulaeMaxFrames = 7;

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

    const int scarfyMaxFrames = 5;

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
        if (isOnGround(scarfyData, windowDimensions[1])){
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

        // update each nebula's position from lots of nebulae
        for (int i = 0; i < nebNum; i++){
            nebulae[i].pos.x += nebVel * dT;
        };

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy's animation frame 
        if (!isInAir){
            scarfyData = updateAnimData(scarfyData, dT, scarfyMaxFrames);
        }

        // update nebula animation frame
        for (int i = 0; i < nebNum; i++){
            // update nebula animation frame
            nebulae[i] = updateAnimData(nebulae[i], dT, nebulaeMaxFrames);
        };

        // draw each of the lots of nebulae
        for (int i = 0; i < nebNum; i++){
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, RAYWHITE);
        };

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawing
        EndDrawing();

        //Displays real-time FPS
        DrawFPS(10, 10); 
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}