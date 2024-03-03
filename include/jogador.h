#ifndef JOGADOR
#define JOGADOR
#include <raylib.h>
#include "mapa.h"

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    bool canJump;
    bool vivo;

    int contMorte; // Contador para morte
    Sound somMorte;
} Player;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, EnvItem *envIntems, int envItemsLength, Agua agua, float delta); 

// Funcao pra desenhar o jogador
void DrawPlayer(Player player);

// Função para desinicializar as texturas e sons do player
void UnloadPlayer(Player *player);

#endif