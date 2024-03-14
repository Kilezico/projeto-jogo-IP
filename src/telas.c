#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "telas.h"
#include "jogador.h"
#include "mapa.h"
#include "utilidades.h"
#include "visao.h"

// Telas do jogo
void jogoDraw(GameplayScreen screen, Camera2D camera, Player player, Agua aguaLetal, Plataforma *plataformas, int plataformasTam, Font fonte, Texture2D terra, Texture2D topo, Texture2D mosca)
{
    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), polutedSky);

    BeginMode2D(camera);
        drawAguaFundo(aguaLetal); // desenha fundo
        
        drawPlataforma(plataformas, plataformasTam, terra, topo, mosca); // desenha plataformas

        DrawPlayer(player); // desenha jogador
        
        drawAguaFrente(aguaLetal); // desenha frente
    EndMode2D();
    
    if (screen == JOGO) {
        DrawTexturePro(mosca, (Rectangle){0, 0, mosca.width, mosca.height}, (Rectangle){30, 30, 80, 80},
            (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(fonte, TextFormat("%d", player.coinCount), (Vector2){120, 34}, 70, 0, WHITE);
        DrawTexturePro(player.texturaPulo, (Rectangle){0, 0, -player.texturaPulo.width, player.texturaPulo.height},
            (Rectangle){1600, 25, 100, player.texturaPulo.height * 100 / player.texturaPulo.width}, (Vector2){0, 0}, 0, WHITE);
        DrawTextEx(fonte, TextFormat("%.02f", -player.maxHeight), (Vector2){1700, 34}, 70, 0, WHITE);
    }
    else if (screen == MORTE) {
        DrawTextCenter(fonte, "Game Over :(", (Vector2){960, 540}, (Vector2){0, 0}, 0, 150, 10, (Color){255, 0, 0, 255});
        DrawTextCenter(fonte, TextFormat("Você devourou %d mosca%s!!", player.coinCount, player.coinCount==1?"":"s"), (Vector2){960, 700}, (Vector2){0, 0}, 0, 70, 0, WHITE);
        DrawTextCenter(fonte, TextFormat("Você chegou até %.02f de altura!!!", -player.maxHeight), (Vector2){960, 850}, (Vector2){0, 0}, 0, 70, 0, WHITE);
    }

    // // Mostra a posicao do jogador
    // char positionStr[64];
    // sprintf(positionStr, "Posição do Jogador: [ X: %.02f, Y: %.02f ]", player.position.x, player.position.y);
    // DrawTextEx(fonte, positionStr, (Vector2){10, 40}, 40, 5, WHITE);
    

}

void jogoUpdate(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor, Music mMenu, Music mJogo)
{
    float deltaTime = GetFrameTime();

    if (*screen == JOGO) {
        UpdatePlayer(player, plataformas, plataformasTam, *aguaLetal, deltaTime);
        updateAgua(aguaLetal, player->position.y, false);
        updatePlataforma(plataformas, plataformasTam, texturaPlat, texturaPlatFlor, aguaLetal->alturaLetal);
        // Checa morte do jogador
        if (!player->vivo) {
            *screen = ENCHENTE;
            StopMusicStream(mJogo);
        }
    } else if (*screen == ENCHENTE) {
        // Quando morre, espera um pouco para a água subir bastante
        updateAgua(aguaLetal, player->position.y, true);
        if (aguaLetal->altura < camera->target.y - aguaLetal->texturas[0].width/2)
            *screen = MORTE; // Tela de Game Over
        player->contMorte = 0;
    } else if (*screen == MORTE) {
        // Fica nela por alguns segundos
        player->contMorte++;
        if (player->contMorte > GetFPS()*4) jogoReset(bigScreen, screen, camera, player, aguaLetal, plataformas, plataformasTam, texturaPlat, texturaPlatFlor, mMenu, mJogo);
    }

    // Atualiza as info para camera
    UpdateCameraJump(camera, player, GetScreenWidth(), GetScreenHeight());
}

// Reseta as variáveis do jogo para começar de novo.
void jogoReset(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor, Music mMenu, Music mJogo)
{
    // Pronto para começar de novo!
    *bigScreen = MENUS;
    *screen = JOGO; // aqui vai mudar eu acho, né
    camera->zoom = 1.0f;
    camera->target.y = -400.0f;
    player->position = (Vector2){ 500, -50 };
    player->maxHeight = 0;
    player->vivo = true;
    player->coinCount = 0;
    aguaLetal->altura = 1400;
    aguaLetal->alturaLetal = 1400;
    aguaLetal->velVertical = 1.0f;
    criaPlataformas(plataformas, plataformasTam, texturaPlat, texturaPlatFlor);
    PlayMusicStream(mMenu);
    StopMusicStream(mJogo);
}