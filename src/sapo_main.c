#include <raylib.h>
#include "phisica.h"
#include "jogador.h"

int main(){
    //-----Inicializacao-------

    // Tamanho da tela
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Sapo Sopa Sobe Sobrio");

    // Coloca em tela cheia
    if (!IsWindowFullscreen())
        ToggleFullscreen();

    // Inicia as variaveis do jogador
    Player player = {0};
    player.position = (Vector2){ 400, 350 }; // Vetor2 == Vetor 2D V(x,y)
    player.canJump = false;
    player.speed = 0;
    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };
    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    
    //------Loop principal------
    while(!WindowShouldClose()){
        // Atualizações  
        float deltaTime = GetFrameTime();
        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        // Desenho na tela

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    return 0;
}