#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "phisica.h"
#include "jogador.h"
#include "mapa.h"
#include "telas.h"

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
    player.position = (Vector2){ 500, -50 }; // Vetor2 == Vetor 2D V(x,y)
    player.canJump = false;
    player.speed = 0;
    player.rotacaoVel = 2;
    player.vivo = true;
    player.somMorte = LoadSound("assets/bolhas.mp3");
    player.somPulo = LoadSound("assets/pulo.mp3");
    player.textura = LoadTexture("assets/frogSitting.PNG");
    player.texturaPulo = LoadTexture("assets/frogJumping.PNG");
    player.esquerda = false;
    player.coinCount = 0;

    // Plataformas
    int plataformasTam = 20;
    Plataforma plataformas[plataformasTam];
    Texture2D texturaPlataforma = LoadTexture("assets/plataforma.png");
    Texture2D texturaPlataformaFlor = LoadTexture("assets/plataforma_flor.png");
    criaPlataformas(plataformas, plataformasTam, &texturaPlataforma, &texturaPlataformaFlor);
    Texture2D terra = LoadTexture("assets/terra.png");
    Texture2D terraTopo = LoadTexture("assets/terra_topo.png");

    // Água que mata
    Agua aguaLetal = {};
    criaTexturasAgua(&aguaLetal);
    aguaLetal.altura = 1400;
    aguaLetal.alturaLetal = 1400;
    aguaLetal.vel[0] = 2.0f;
    aguaLetal.vel[1] = 1.5f;
    aguaLetal.vel[2] = 1.0f;
    aguaLetal.velVertical = AGUA_START_SPD;

    // Inicia as variaveis de camera
    Camera2D camera = {0};
    camera.target = (Vector2){960, -400};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Estados para mudança de janela
    GameplayScreen gameplayState = JOGO;
    GameScreen gameState = MENUS;


    // Alce (Moose)
    Texture2D mosquinha = LoadTexture("assets/mosquinha.PNG");
    HideCursor();

    SetTargetFPS(60); // Limite de fps

    // Fonte
    Font fonteMenu = LoadFontEx("assets/fonteMenu.ttf", 300, 0, 256);

    bool running = true;
    //------Loop principal------
    while(!WindowShouldClose() && running){
        // Atualizações  
        switch (gameState) {
            case GAMEPLAY:
                // Atualiza o jogo
                jogoUpdate(&gameState, &gameplayState, &camera, &player, &aguaLetal, plataformas, plataformasTam, &texturaPlataforma, &texturaPlataformaFlor);
            break;
            default: break;
        }
        // Desenha na tela        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (gameState) {
                case GAMEPLAY:
                    // Desenha o jogo
                    jogoDraw(gameplayState, camera, player, aguaLetal, plataformas, plataformasTam, fonteMenu, terra, terraTopo, mosquinha);
                break;
                case MENUS:
                    menuDraw(&gameState, fonteMenu);
                break;
                case HOWTO:
                    howToDraw(&gameState, fonteMenu);
                break;
                case STORY:
                    backStoryDraw(&gameState, fonteMenu);
                break;
                case EXIT:
                    running = false;
                break;
                case CREDITS:
                    creditsDraw(&gameState, fonteMenu);
                break;
                default: running = false; break;
            }
            DrawTexturePro(mosquinha, (Rectangle){0, 0, mosquinha.width, mosquinha.height},
            (Rectangle){GetMousePosition().x, GetMousePosition().y, 40, 40}, (Vector2){20, 20}, 0, WHITE);
        EndDrawing();
    }

    // Descarrega coisas da memória
    for (int i=0; i<3; i++)
        UnloadTexture(aguaLetal.texturas[i]);

    UnloadTexture(texturaPlataforma);
    UnloadTexture(texturaPlataformaFlor);
    UnloadTexture(terra);
    UnloadTexture(terraTopo);
    UnloadTexture(mosquinha);

    UnloadPlayer(&player);

    UnloadFont(fonteMenu);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
