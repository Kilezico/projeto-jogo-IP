#include <raylib.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int mein() { // Mudei pra mein pra não ter duas mains e dar erro
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(0, 0, "raylib [core] example - mouse input");
    if (!IsWindowFullscreen()) ToggleFullscreen();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const float W2 = screenWidth / 2.0f;
    const float H2 = screenHeight / 2.0f;

    Texture bixoTex = LoadTexture("assets/kn.png");
    Rectangle bixoSrc = {0.0f, 0.0f, (float) bixoTex.width/3, (float) bixoTex.height};
    float bixoScale = 3.0f;
    Rectangle bixoDest = {W2, H2, bixoSrc.width * bixoScale, bixoSrc.height * bixoScale};
    Vector2 bixoOrig = {bixoDest.width/2, bixoDest.height/2};
    bool mostraBixo = false;
    int bixoFrame = 0, bixoStep = 4;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mostraBixo = true;
        else {
            mostraBixo = false;
            bixoFrame = 0;
        }
        
        bixoFrame++;
        bixoSrc.x = (bixoFrame / bixoStep) % 3 * bixoSrc.width;
    
        BeginDrawing();

        DrawText("Clique mouse :)", 500, 100, 30, GRAY);

        ClearBackground(RAYWHITE);

        if (mostraBixo) DrawTexturePro(bixoTex, bixoSrc, bixoDest, bixoOrig, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(bixoTex);

    CloseWindow();


    return 0;
}
