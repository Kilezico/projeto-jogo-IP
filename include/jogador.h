#ifndef JOGADOR
#define JOGADOR
#include <raylib.h>
#include "mapa.h"

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    bool canJump;
} Player;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, float delta); 

// Funcao pra desenhar o jogador
void DrawPlayer(Player player);

#endif