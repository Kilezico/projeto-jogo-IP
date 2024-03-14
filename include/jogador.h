#ifndef JOGADOR
#define JOGADOR
#include <raylib.h>
#include "mapa.h"

// Variaveis do jogador
typedef struct{
    Vector2 position;
    float speed;
    float rotacao, rotacaoVel;
    bool canJump;
    bool vivo;
    bool esquerda; // se está apontado para esquerda ou direita
    bool andando;
    bool jumpBuffer;
    int jumpBufferCount;

    Rectangle hitbox;
    Texture2D textura;
    Texture2D texturaPulo;

    int contMorte; // Contador para morte
    Sound somMorte;
    Sound somPulo;
} Player;


// Funcao dos movimentos do jogador
void UpdatePlayer(Player *player, Plataforma *plataformas, int plataformasLength, Agua agua, float delta); 

// Funcao pra desenhar o jogador
void DrawPlayer(Player player);

// Função para desinicializar as texturas e sons do player
void UnloadPlayer(Player *player);

#endif