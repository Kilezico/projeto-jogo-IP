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
    Vector2 position;
    Rectangle rect[3]; // Uma para cada camada do parallax
    Texture2D texturas[3];
    float vel[3];
} Agua;

void criaTexturasAgua(Agua *agua);

void drawAgua(Agua agua);

void updateAgua(Agua* agua, int speedAgua);


#endif