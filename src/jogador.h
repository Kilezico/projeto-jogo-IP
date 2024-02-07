#ifndef jogador
#define jogador
#include <raylib.h>

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    bool canJump;
} Player;

//variaveis da entidade
typedef struct{
    Rectangle react;
    int blocking;
    Color color;
} EnvItem;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, float delta); 


#endif