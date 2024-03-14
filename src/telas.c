#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "telas.h"
#include "jogador.h"
#include "mapa.h"
#include "utilidades.h"
#include "visao.h"

// Telas do jogo
void jogoDraw(GameplayScreen screen, Camera2D camera, Player player, Agua aguaLetal, Plataforma *plataformas, int plataformasTam, Font fonte, Texture2D terra, Texture2D topo)
{
    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), polutedSky);

    BeginMode2D(camera);
        drawAguaFundo(aguaLetal); // desenha fundo
        
        drawPlataforma(plataformas, plataformasTam, terra, topo); // desenha plataformas

        DrawPlayer(player); // desenha jogador
        
        drawAguaFrente(aguaLetal); // desenha frente
    EndMode2D();
    

    if (screen == MORTE) {
        DrawTextCenter(fonte, "Game Over :(", (Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, (Vector2){0, 0}, 0, 100, 10, (Color){255, 0, 0, 255});
    }

        // Mostra a posicao do jogador
    char positionStr[64];
        sprintf(positionStr, "Posição do Jogador: [ X: %.02f, Y: %.02f ]", player.position.x, player.position.y);
        DrawTextEx(fonte, positionStr, (Vector2){10, 40}, 40, 5, WHITE);
    DrawTextEx(fonte, TextFormat("Velocidade da agua: %f", aguaLetal.velVertical), (Vector2){10, 80}, 40, 10, WHITE);
}

void jogoUpdate(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor)
{
    float deltaTime = GetFrameTime();

    if (*screen == JOGO) {
        UpdatePlayer(player, plataformas, plataformasTam, *aguaLetal, deltaTime);
        updateAgua(aguaLetal, player->position.y, false);
        updatePlataforma(plataformas, plataformasTam, texturaPlat, texturaPlatFlor, aguaLetal->alturaLetal);
    } else if (*screen == ENCHENTE) {
        // Quando morre, espera um pouco para a água subir bastante
        updateAgua(aguaLetal, player->position.y, true);
        if (aguaLetal->altura < camera->target.y - aguaLetal->texturas[0].width/2)
            *screen = MORTE; // Tela de Game Over
        player->contMorte = 0;
    } else if (*screen == MORTE) {
        // Fica nela por alguns segundos
        player->contMorte++;
        if (player->contMorte > GetFPS()*3) jogoReset(bigScreen, screen, camera, player, aguaLetal, plataformas, plataformasTam, texturaPlat, texturaPlatFlor);
    }

    // Checa morte do jogador
    if (!player->vivo && *screen == JOGO) *screen = ENCHENTE;

    // Atualiza as info para camera
    UpdateCameraJump(camera, player, GetScreenWidth(), GetScreenHeight());
}

void jogoReset(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor) // Reseta as variáveis do jogo para começar de novo.
{
    // Pronto para começar de novo!
    *bigScreen = MENUS;
    *screen = JOGO; // aqui vai mudar eu acho, né
    camera->zoom = 1.0f;
    camera->target.y = -400.0f;
    player->position = (Vector2){ 500, -50 };
    player->vivo = true;
    aguaLetal->altura = 1400;
    aguaLetal->alturaLetal = 1400;
    aguaLetal->velVertical = 1.0f;
    criaPlataformas(plataformas, plataformasTam, texturaPlat, texturaPlatFlor);
}