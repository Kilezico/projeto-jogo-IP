#ifndef MAPA_H
#define MAPA_H
#include <raylib.h>

//variaveis da entidade do mapa
typedef struct{
    Rectangle react;
    int blocking;
} EnvItem;

typedef struct {
    EnvItem hitbox; // Para colisão com jogador
    Rectangle rect;
    Texture2D *textura; // Está como ponteiro para carregar a mesma textura apenas uma vez.
    Texture2D *textureFlor;
    float velocidade;
} Plataforma;

// Água do mar que sobe
typedef struct {
    float altura;
    Rectangle rect[3]; // Uma para cada camada da água
    Texture2D texturas[3];
    float vel[3];
    float velVertical;
    float alturaLetal; // Altura que não pode ficar abaixo pra não morrer
} Agua;

void criaPlataformas(Plataforma *plataformas, int plataformasTam); // Cria as plataformas iniciais
void updatePlataforma(Plataforma *plataformas, int plataformasTam); // Cria novas plataformas
void drawPlataforma(Plataforma *plataformas, int plataformasTam, Texture2D terra, Texture2D terraTopo);

void criaTexturasAgua(Agua *agua);
void drawAguaFundo(Agua agua);
void drawAguaFrente(Agua agua);
void updateAgua(Agua* agua, float alturaJogador, bool cabou);


#endif