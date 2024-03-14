#include "phisica.h"
#include "jogador.h"

#include <raylib.h>
#include <stdlib.h>

void UpdatePlayer(Player *player, Plataforma *plataformas, int plataformasLength, Agua agua, float delta) {
    player->andando = false;
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->position.x -= PLAYER_HOR_SPD*delta; // Tecla esquerda -> movimentacao para esquerda
        player->esquerda = true;
        player->andando = true;
    }
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->position.x += PLAYER_HOR_SPD*delta; // Tecla direita -> movimentacao para direita
        player->esquerda = false;
        player->andando = true;
    }
    // Funcao de pulo
    if (IsKeyPressed(KEY_SPACE)) {
        player->jumpBuffer = true;
        player->jumpBufferCount = 5;
    } else {
        player->jumpBufferCount--;
        if (player->jumpBufferCount < 0)
            player->jumpBuffer = false;
    }
    if(player->jumpBuffer && player->canJump){
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
        player->jumpBuffer = false;
        PlaySound(player->somPulo);
    }

    // Limites do mapa
    if(player->position.x < 0){
        player->position.x = 0;
    }
    if(player->position.x > 2000){
        player->position.x = 2000;
    }


    // Condicoes de pulo
    int hitObstacle = 0;
    
    for(int i= 0; i < plataformasLength; i++){
        EnvItem ei = plataformas[i].hitbox;
        Vector2 *p = &(player->position);
        
        if(ei.blocking && ei.react.x <= p->x && ei.react.x + ei.react.width >= p->x &&
        ei.react.y >= p->y && ei.react.y <= p->y + player->speed*delta){
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei.react.y;
        }
    }
    
    if(!hitObstacle){
        player->position.y += player->speed * delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;

    // Atualiza a hitbox
    player->hitbox.width = player->textura.width / 10;
    player->hitbox.height = player->textura.height / 10;
    player->hitbox.x = player->position.x - player->hitbox.width/2;
    player->hitbox.y = player->position.y - player->hitbox.height;

    // Atualiza a rotacao no sapo andando
    if (player->andando) {
        player->rotacao += player->rotacaoVel;
        if (abs(player->rotacao) > 10) player->rotacaoVel *= -1;
    } else 
        player->rotacao = 0;

    // Checa se morreu pela água
    if (player->position.y > agua.alturaLetal && player->vivo) {
        player->vivo = false;
        PlaySound(player->somMorte);
    }
}

void DrawPlayer(Player player){
    if (!player.canJump && player.speed < 0) {
        // Sapo está pulando e indo para cima!
        Rectangle destino = {0, 0, player.texturaPulo.width/5, player.texturaPulo.height/5};
        destino.x = player.position.x - destino.width/2;
        destino.y = player.position.y - destino.height/2 - 15;
        if (player.esquerda)
            DrawTexturePro(player.texturaPulo, (Rectangle){0, 0, player.texturaPulo.width, player.texturaPulo.height}, destino, (Vector2){0, 0}, 0, WHITE);
        else 
            DrawTexturePro(player.texturaPulo, (Rectangle){0, 0, -player.texturaPulo.width, player.texturaPulo.height}, destino, (Vector2){0, 0}, 0, WHITE);

    } else if (player.andando) {
        // Se tiver em movimento, faz ele balançar pra lá e pra cá
        Rectangle destino = {0, 0, player.textura.width/10, player.textura.height/10};
        Vector2 origem = {destino.width/2, destino.height/2}; // rotacionar com a origem no centro
        // ajusta posição para ir pro canto superior esquerdo. Por algum motivo, tá desenhando a textura no centro da posição dada.
        destino.x = player.position.x;
        destino.y = player.position.y - destino.height/2 + 10;
        if (!player.esquerda)
            DrawTexturePro(player.textura, (Rectangle){0, 0, player.textura.width, player.textura.height}, destino, origem, player.rotacao, WHITE);
        else 
            DrawTexturePro(player.textura, (Rectangle){0, 0, -player.textura.width, player.textura.height}, destino, origem, player.rotacao, WHITE);
    } else {
        // Está parado
        Rectangle destino = {0, 0, player.textura.width/10, player.textura.height/10};
        // ajusta posição para ir pro canto superior esquerdo
        destino.x = player.position.x - destino.width/2;
        destino.y = player.position.y - destino.height + 10;
        if (!player.esquerda)
            DrawTexturePro(player.textura, (Rectangle){0, 0, player.textura.width, player.textura.height}, destino, (Vector2){0, 0}, 0, WHITE);
        else 
            DrawTexturePro(player.textura, (Rectangle){0, 0, -player.textura.width, player.textura.height}, destino, (Vector2){0, 0}, 0, WHITE);
    }
    
    // Desenha a hitbox. Para propósitos de debugging.
    // DrawRectangleLinesEx(player.hitbox, 2, RED);
}

void UnloadPlayer(Player *player)
{
    UnloadSound(player->somMorte);
    UnloadSound(player->somPulo);
    UnloadTexture(player->textura);
    UnloadTexture(player->texturaPulo);
} 