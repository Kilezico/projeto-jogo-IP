#include <raylib.h>
#include <stdio.h>

#include "telas.h"
#include "jogador.h"
#include "mapa.h"
#include "utilidades.h"

// Telas do jogo
void jogoDraw(GameplayScreen screen, Camera2D camera, Player player, Agua aguaLetal, EnvItem *plataformas, int plataformasTam, Font fonte)
{
    DrawRectangleRec(plataformas[0].react, plataformas[0].color);

    BeginMode2D(camera);
        drawAguaFundo(aguaLetal); // desenha fundo
        for(int i=1; i < plataformasTam; i++) DrawRectangleRec(plataformas[i].react, plataformas[i].color); // desenha plataformas
        DrawPlayer(player); // desenha jogador
        drawAguaFrente(aguaLetal); // desenha frente
    EndMode2D();
    

    if (screen == MORTE) {
        // DrawTextEx(fonte, "Game Over :(", (Vector2){GetScreenWidth()/2-200, GetScreenHeight()/2-20}, 40, 10, RED);
        DrawTextCenter(fonte, "Game Over :(", (Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, (Vector2){0, 0}, 0, 40, 10, (Color){255, 0, 0, 255});
    }

        // Mostra a posicao do jogador
    char positionStr[64];
        sprintf(positionStr, "Posição do Jogador: [ X: %.02f, Y: %.02f ]", player.position.x, player.position.y);
        DrawTextEx(fonte, positionStr, (Vector2){10, 40}, 40, 5, WHITE);
}

void jogoUpdate(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, EnvItem *plataformas, int plataformasTam)
{
    float deltaTime = GetFrameTime();
    camera->zoom += ((float) GetMouseWheelMove()*0.05f);
    if(camera->zoom > 3.0f) camera->zoom = 3.0f;
    else if(camera->zoom < 0.3f) camera->zoom = 0.3f;

    if (*screen == JOGO) {
        UpdatePlayer(player, plataformas, plataformasTam, *aguaLetal, deltaTime);
        updateAgua(aguaLetal, player->position.y, false);
    } else if (*screen == ENCHENTE) {
        // Quando morre, espera um pouco para a água subir bastante
        updateAgua(aguaLetal, player->position.y, true);
        if (aguaLetal->altura < camera->target.y - aguaLetal->texturas[0].width/2)
            *screen = MORTE; // Tela de Game Over
        player->contMorte = 0;
    } else if (*screen == MORTE) {
        // Fica nela por alguns segundos
        player->contMorte++;
        if (player->contMorte > GetFPS()*3) jogoReset(screen, camera, player, aguaLetal);
    }


    // Atualiza as info para camera
    //cameraUpdaters[0](camera, player, plataformas, plataformasTam, deltaTime, GetScreenWidth(), GetScreenHeight());

    // Checa morte do jogador
    if (!player->vivo && *screen == JOGO) *screen = ENCHENTE;
}

void jogoReset(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal) // Reseta as variáveis do jogo para começar de novo.
{
    *screen = JOGO;
    camera->zoom = 1.0f;
    player->position = (Vector2){ 1000, 1000 };
    player->vivo = true;
    aguaLetal->altura = 1400;
    aguaLetal->alturaLetal = 1400;
}