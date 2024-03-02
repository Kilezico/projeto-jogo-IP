#ifndef UTILIDADES_H 
#define UTILIDADES_H
// nao consegui usar "utils.h", já tá sendo usado no código do raylib
#include <raylib.h>

// Desenha um texto centralizado na posição dada
void DrawTextCenter(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontsize, float spacing, Color tint);

#endif