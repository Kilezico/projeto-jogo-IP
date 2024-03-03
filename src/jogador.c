#include "phisica.h"
#include "jogador.h"

#include <raylib.h>

void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, Agua agua, float delta){
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        player->position.x -= PLAYER_HOR_SPD*delta; // Tecla esquerda -> movimentacao para esquerda
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        player->position.x += PLAYER_HOR_SPD*delta; // Tecla direita -> movimentacao para direita

    // Semelhante as funcoes acima mas com as teclas A(esquerda) e D(direita) controlando
    if(IsKeyDown(KEY_A)) player->position.x -= PLAYER_HOR_SPD*delta;
    if(IsKeyDown(KEY_D)) player->position.x += PLAYER_HOR_SPD*delta;

    // Funcao de pulo
    if(IsKeyDown(KEY_SPACE) && player->canJump){
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    // Limites do mapa
    if(player->position.x < 20){
        player->position.x = 20;
    }
    if(player->position.x > 2000){
        player->position.x = 2000;
    }


    // Condicoes de pulo
    int hitObstacle = 0;
    
    for(int i= 0; i < envItemsLength; i++){
        EnvItem *ei = envIntems + i;
        Vector2 *p = &(player->position);
        
        if(ei->blocking && ei->react.x <= p->x && ei->react.x + ei->react.width >= p->x &&
        ei->react.y >= p->y && ei->react.y <= p->y + player->speed*delta){
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->react.y;
        }
    }
    
    if(!hitObstacle){
        player->position.y += player->speed * delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;

    // Checa se morreu pela água
    if (player->position.y > agua.alturaLetal && player->vivo) {
        player->vivo = false;
        PlaySound(player->somMorte);
    }
}

void DrawPlayer(Player player){
    Rectangle playerRect = {player.position.x - 20, player.position.y - 40, 40, 40};
    DrawRectangleRec(playerRect, GREEN);
}

void UnloadPlayer(Player *player)
{
    UnloadSound(player->somMorte);
} 