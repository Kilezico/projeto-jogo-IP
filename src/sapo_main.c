#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "phisica.h"
#include "jogador.h"
#include "visao.h"
#include "mapa.h"
#include "telas.h"

// Trocador de tela. Pode ser substituido se já tiver um no código do menu
typedef enum {
    GAMEPLAY
} GameScreen;

int main(){
    //-------Inicializacao-------

    InitWindow(0, 0, "Sapo Sopa Sobe");
    InitAudioDevice();

    // Tamanho da tela
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Coloca em tela cheia
    if (!IsWindowFullscreen())
        ToggleFullscreen();

    // Inicia as variaveis do jogador
    Player player = {0};
    player.position = (Vector2){ 1000, 1000 }; // Vetor2 == Vetor 2D V(x,y)
    player.canJump = false;
    player.speed = 0;
    player.vivo = true;
    player.somMorte = LoadSound("assets/bolhas.mp3");

    // Cria as entidades no mapa
    EnvItem envItems[] = {
        {{ 0, 0, 2560, 1440 }, 0, LIGHTGRAY },
        {{ 0, 1000, 2000, 400 }, 1, DARKGREEN },
        {{ 500, 860, 300, 10 }, 1, LIME },
        {{ 750, 750, 100, 10 }, 1, MAGENTA },
        {{ 820, 620, 100, 10 }, 1, GRAY },
        {{ 930, 475, 150, 10 }, 1, BROWN },
        {{ 1000, 400, 250, 10 }, 1, YELLOW }
    };

    Texture2D terra = LoadTexture("assets/terra.png");
    Texture2D terraTopo = LoadTexture("assets/terra_topo.png");
    

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    // Água que mata
    Agua aguaLetal = {};
    criaTexturasAgua(&aguaLetal);
    aguaLetal.altura = 1400;
    aguaLetal.alturaLetal = 1400;
    aguaLetal.vel[0] = 2.0f;
    aguaLetal.vel[1] = 1.5f;
    aguaLetal.vel[2] = 1.0f;
    aguaLetal.velVertical = 1.0f;

    // Inicia as variaveis de camera
    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Funcao que pega as informacoes das variaveis ao mesmo tempo para varias cameras
    void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
        // Por enqunto so tem uma
        UpdateCameraCenter,
        UpdateCameraJump
    };

    /* int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters)/sizeof(cameraUpdaters[0]); */


    GameplayScreen gameplayState = JOGO;
    GameScreen gameState = GAMEPLAY;

    SetTargetFPS(60); // Limite de fps

    // Só pra testar as fontes
    Font poufonte = LoadFontEx("assets/Pou.ttf", 50, 0, 256);

    //------Loop principal------
    while(!WindowShouldClose()){
        // Atualizações  
        switch (gameState) {
            case GAMEPLAY:
                jogoUpdate(&gameplayState, &camera, &player, &aguaLetal, envItems, envItemsLength);
            break;
            default: break;
        }
        // Atualiza as info para camera
        float deltaTime = GetFrameTime();
        cameraUpdaters[1](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);

        // Desenha na tela        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (gameState) {
                case GAMEPLAY:
                    // Desenha o jogo
                    jogoDraw(gameplayState, camera, player, aguaLetal, envItems, envItemsLength, poufonte, terra, terraTopo);
                break;
            }
        
        EndDrawing();
    }

    // Descarrega coisas da memória
    for (int i=0; i<3; i++)
        UnloadTexture(aguaLetal.texturas[i]);
    UnloadPlayer(&player);

    UnloadTexture(terra);
    UnloadTexture(terraTopo);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}