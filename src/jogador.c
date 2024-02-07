#include "phisica.h"
#include "jogador.h"
void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, float delta){
    if(IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta; // Tecla esquerda -> movimentacao para esquerda
    if(IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta; // Tecla direita -> movimentacao para direita

    // Semelhante as funcoes acima mas com as teclas A(esquerda) e D(direita) controlando
    if(IsKeyDown(KEY_A)) player->position.x -= PLAYER_HOR_SPD*delta;
    if(IsKeyDown(KEY_D)) player->position.x += PLAYER_HOR_SPD*delta;
}