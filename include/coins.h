#ifndef COINS
#define COINS
#include <raylib.h>

// Estrutura de moeda
typedef struct {
    Vector2 position;
    bool active;
    Color color;
} Coin;

// Função para criar uma moeda
Coin CreateCoin(Vector2 position, Color color);

// Função para desenhar uma moeda na tela
void DrawCoin(Coin coin, Texture2D mosca);

#endif
