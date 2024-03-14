#ifndef JOGADOR
#define JOGADOR
#include <raylib.h>
#include "mapa.h"

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    float rotacao, rotacaoVel;
    float maxHeight;
    bool canJump;
    bool vivo;
    bool esquerda; // se está apontado para esquerda ou direita
    bool andando;
    bool jumpBuffer;
    int jumpBufferCount;

    Rectangle hitbox;
    Texture2D textura;
    Texture2D texturaPulo;

    int contMorte;
    Sound somMorte;
    Sound somPulo;

    int coinCount;
} Player;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, Plataforma *plataformas, int plataformasLength, Agua agua, float delta); 

// Funcao pra desenhar o jogador
void DrawPlayer(Player player);

// Função para desinicializar as texturas e sons do player
void UnloadPlayer(Player *player);

// Função para verificar a colisão entre o jogador e uma moeda
bool CheckCoinCollision(Player player, Coin coin);

// Função para coletar uma moeda
void CollectCoin(Coin *coin, Player *player);


#endif
