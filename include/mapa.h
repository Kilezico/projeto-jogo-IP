#ifndef MAPA_H
#define MAPA_H
#include <raylib.h>

//variaveis da entidade do mapa
typedef struct{
    Rectangle react;
    int blocking;
    Color color;
} EnvItem;

// Água do mar que sobe
typedef struct {
    float altura;
    Rectangle rect[3]; // Uma para cada camada da água
    Texture2D texturas[3];
    float vel[3];
    float velVertical;
    float alturaLetal; // Altura que não pode ficar abaixo pra não morrer
} Agua;

void criaTexturasAgua(Agua *agua);
void drawAguaFundo(Agua agua);
void drawAguaFrente(Agua agua);
void updateAgua(Agua* agua, float alturaJogador, bool cabou);


#endif