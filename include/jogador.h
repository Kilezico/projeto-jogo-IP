#ifndef JOGADOR
#define JOGADOR
#include <raylib.h>

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    bool canJump;
} Player;

//variaveis da entidade do mapa
typedef struct{
    Rectangle react;
    int blocking;
    Color color;
} EnvItem;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, float delta); 

// Funcao pra desenhar o jogador
void DrawPlayer(Player player);

#endif