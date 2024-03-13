#ifndef COINS
#define COINS
#include <raylib.h>

#include "jogador.h"

// Estrutura de moeda
typedef struct {
    Vector2 position;
    bool active;
    Color color;
} Coin;

// Função para criar uma moeda
Coin CreateCoin(Vector2 position, Color color);

// Função para desenhar uma moeda na tela
void DrawCoin(Coin coin);

// Função para verificar a colisão entre o jogador e uma moeda
bool CheckCoinCollision(Player player, Coin coin);

// Função para coletar uma moeda
void CollectCoin(Coin *coin);

#endif