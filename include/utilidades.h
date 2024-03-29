#ifndef UTILIDADES_H 
#define UTILIDADES_H
// nao consegui usar "utils.h", já tá sendo usado no código do raylib
#include <raylib.h>

// Desenha um texto centralizado na posição dada
void DrawTextCenter(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontsize, float spacing, Color tint);

// Desenha Texto com borda
void DrawTextLines(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize);

void DrawTextLinesCorner(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize);

#endif