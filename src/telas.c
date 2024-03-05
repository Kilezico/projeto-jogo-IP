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
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SKYBLUE);

    BeginMode2D(camera);
        drawAguaFundo(aguaLetal); // desenha fundo
        
        for(int i=1; i < plataformasTam; i++) DrawRectangleRec(plataformas[i].hitbox.react, BROWN); // desenha plataformas
        
        DrawPlayer(player); // desenha jogador
        
        // Desenha o chão com sprites de terra
        for (int i=0; i<ceil(plataformas[0].hitbox.react.width/80.0f); i++) {
            for (int j=0; j<ceil(plataformas[0].hitbox.react.height/80.0f); j++) {
                Rectangle src = {0, 0, 16, 16};
                Rectangle dest = {plataformas[0].hitbox.react.x + i*80, plataformas[0].hitbox.react.y + j*80 - 5, 80, 80};
                if (j==0) // linha 0, topo.
                    DrawTexturePro(topo, src, dest, (Vector2){0, 0}, 0, WHITE);
                else 
                    DrawTexturePro(terra, src, dest, (Vector2){0, 0}, 0, WHITE);
                    
            }
        }
        
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

void jogoUpdate(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam)
{
    float deltaTime = GetFrameTime();

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
        if (player->contMorte > GetFPS()*3) jogoReset(screen, camera, player, aguaLetal, plataformas, plataformasTam);
    }

    // Checa morte do jogador
    if (!player->vivo && *screen == JOGO) *screen = ENCHENTE;

    // Atualiza as info para camera
    UpdateCameraJump(camera, player, GetScreenWidth(), GetScreenHeight());
}

void jogoReset(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam) // Reseta as variáveis do jogo para começar de novo.
{
    // Pronto para começar de novo!
    *screen = JOGO;
    camera->zoom = 1.0f;
    camera->target.y = -400.0f;
    player->position = (Vector2){ 500, -50 };
    player->vivo = true;
    aguaLetal->altura = 500;
    aguaLetal->alturaLetal = 500;
    criaPlataformas(plataformas, plataformasTam);
}