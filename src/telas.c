#include "telas.h"
#include "jogador.h"
#include "mapa.h"

#include <raylib.h>
#include <stdio.h>

// Telas do jogo
void jogoDraw(Camera2D camera, Player player, Agua aguaLetal, EnvItem *plataformas, int plataformasTam, Font fonte)
{
    BeginMode2D(camera);
        DrawRectangleRec(plataformas[0].react, plataformas[0].color);
        drawAguaFundo(aguaLetal); // desenha fundo
        for(int i=1; i < plataformasTam; i++) DrawRectangleRec(plataformas[i].react, plataformas[i].color); // desenha plataformas
        DrawPlayer(player); // desenha jogador
        drawAguaFrente(aguaLetal); // desenha frente
    EndMode2D();

        // Mostra a posicao do jogador
    char positionStr[64];
        sprintf(positionStr, "Posição do Jogador: [ X: %.02f, Y: %.02f ]", player.position.x, player.position.y);
        DrawTextEx(fonte, positionStr, (Vector2){10, 40}, 50, 5, WHITE);
}

void jogoUpdate(Camera2D *camera, Player *player, Agua *aguaLetal, EnvItem *plataformas, int plataformasTam)
{
    float deltaTime = GetFrameTime();
    UpdatePlayer(player, plataformas, plataformasTam, *aguaLetal, deltaTime);


    camera->zoom += ((float) GetMouseWheelMove()*0.05f);
    if(camera->zoom > 3.0f) camera->zoom = 3.0f;
    else if(camera->zoom < 0.3f) camera->zoom = 0.3f;

    // // Volta para a posicao inicial
    // if(IsKeyPressed(KEY_R)){
    //     camera->zoom = 1.0f;
    //     player->position = (Vector2){ 1000, 1000 };
    //     aguaLetal->altura = 1400;
    // }

    updateAgua(aguaLetal);

    // Atualiza as info para camera
    //cameraUpdaters[0](camera, player, plataformas, plataformasTam, deltaTime, GetScreenWidth(), GetScreenHeight());

    // Checa morte do jogador
    if (!player->vivo) jogoReset(camera, player, aguaLetal);
}

void jogoReset(Camera2D *camera, Player *player, Agua *aguaLetal) // Reseta as variáveis do jogo para começar de novo.
{
    camera->zoom = 1.0f;
    player->position = (Vector2){ 1000, 1000 };
    player->vivo = true;
    aguaLetal->altura = 1400;
}