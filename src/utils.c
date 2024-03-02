#include "utilidades.h"

#include <raylib.h>

void DrawTextCenter(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontsize, float spacing, Color tint)
{
    Vector2 tamanho = MeasureTextEx(font, text, fontsize, spacing);
    DrawTextPro(font, text, (Vector2){position.x - tamanho.x/2.0f, position.y - tamanho.y/2.0f}, origin, rotation, fontsize, spacing, tint);
}