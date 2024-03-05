#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "phisica.h"
#include "jogador.h"
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
    player.position = (Vector2){ 500, -50 }; // Vetor2 == Vetor 2D V(x,y)
    player.canJump = false;
    player.speed = 0;
    player.vivo = true;
    player.somMorte = LoadSound("assets/bolhas.mp3");
    player.somPulo = LoadSound("assets/pulo.mp3");

    // Plataformas
    int plataformasTam = 10;
    Plataforma plataformas[plataformasTam];
    plataformas[0] = (Plataforma){(EnvItem){(Rectangle){0, 0, 2000, 300}, 1}, (Rectangle){0, 0, 0, 0}, NULL, NULL};
    criaPlataformas(plataformas, plataformasTam);

    Texture2D texturaTerra = LoadTexture("assets/terra.png");
    Texture2D texturaTerraTopo = LoadTexture("assets/terra_topo.png");

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
    camera.target = (Vector2){960, -400};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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
                // Atualiza o jogo
                jogoUpdate(&gameplayState, &camera, &player, &aguaLetal, plataformas, plataformasTam);
            break;
            default: break;
        }
        // Desenha na tela        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (gameState) {
                case GAMEPLAY:
                    // Desenha o jogo
                    jogoDraw(gameplayState, camera, player, aguaLetal, plataformas, plataformasTam, poufonte, texturaTerra, texturaTerraTopo);
                break;
                default: break;
            }
        EndDrawing();
    }

    // Descarrega coisas da memória
    for (int i=0; i<3; i++)
        UnloadTexture(aguaLetal.texturas[i]);
    UnloadTexture(texturaTerra);
    UnloadTexture(texturaTerraTopo);
    
    UnloadPlayer(&player);

    UnloadFont(poufonte);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}