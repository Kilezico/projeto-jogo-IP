#include <raylib.h>

#include "phisica.h"
#include "jogador.h"
#include "visao.h"
#include "mapa.h"

int main(){
    //-----Inicializacao-------

    InitWindow(0, 0, "Sapo Sopa Sobe Sobrio");

    // Tamanho da tela
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Coloca em tela cheia
    if (!IsWindowFullscreen())
        ToggleFullscreen();

    // Inicia as variaveis do jogador
    Player player = {0};
    player.position = (Vector2){ 1000, 720 }; // Vetor2 == Vetor 2D V(x,y)
    player.canJump = false;
    player.speed = 0;

    // Cria as entidades no mapa
    EnvItem envItems[] = {
        {{ 0, 0, 2560, 1440 }, 0, LIGHTGRAY },
        {{ 0, 1000, 2000, 300 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    // Inicia as variaveis de camera
    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Funcao que pega as informacoes das variaveis ao mesmo tempo para varias cameras
    void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
        // Por enqunto so tem uma
        UpdateCameraCenter
    }; 

    /* int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters)/sizeof(cameraUpdaters[0]); */

    SetTargetFPS(60); // Limite de fps

    
    //------Loop principal------
    while(!WindowShouldClose()){
        // Atualizações  
        float deltaTime = GetFrameTime();
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);


        camera.zoom += ((float) GetMouseWheelMove()*0.05f);
        if(camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if(camera.zoom < 0.3f) camera.zoom = 0.3f;

        // Volta para a posicao inicial
        if(IsKeyPressed(KEY_R)){
            camera.zoom = 1.0f;
            player.position = (Vector2){ 1000, 720};
        }

        // Atualiza as info para camera
        cameraUpdaters[0](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);


        // Desenho na tela        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Desenha o jogador
        BeginMode2D(camera);
            for(int i=0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].react, envItems[i].color);
            DrawPlayer(player);

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}