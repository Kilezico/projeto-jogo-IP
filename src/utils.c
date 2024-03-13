#include "utilidades.h"

#include <raylib.h>
#include <math.h>

void DrawTextCenter(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontsize, float spacing, Color tint)
{
    Vector2 tamanho = MeasureTextEx(font, text, fontsize, spacing);
    DrawTextPro(font, text, (Vector2){position.x - tamanho.x/2.0f, position.y - tamanho.y/2.0f}, origin, rotation, fontsize, spacing, tint);
}

void DrawTextLines(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize)
{
    Vector2 txtSize = MeasureTextEx(font, txt, fontSize, spacing);

    for (float angle = 0.0f; angle < 2*PI; angle+=PI/16) {
        Vector2 outlinePos = {position.x + (cos(angle) * outlineSize), position.y + (sin(angle) * outlineSize)};
        DrawTextPro(font, txt, outlinePos, (Vector2){txtSize.x/2.0f, txtSize.y/2.0f},  rotation, fontSize, spacing, outline);
    }

    DrawTextPro(font, txt, position, (Vector2){txtSize.x/2.0f, txtSize.y/2.0f},  rotation, fontSize, spacing, tint);
}

void DrawTextLinesCorner(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize)
{
    for (float angle = 0.0f; angle < 2*PI; angle+=PI/16) {
        Vector2 outlinePos = {position.x + (cos(angle) * outlineSize), position.y + (sin(angle) * outlineSize)};
        DrawTextPro(font, txt, outlinePos, (Vector2){0, 0},  rotation, fontSize, spacing, outline);
    }

    DrawTextPro(font, txt, position, (Vector2){0, 0},  rotation, fontSize, spacing, tint);
}