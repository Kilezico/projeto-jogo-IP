#include <raylib.h>

#include "mapa.h"
#include "jogador.h"

void criaTexturasAgua(Agua *agua) {
    int largura = GetScreenWidth();
    int altura = 500;
    int raio = largura / 40;
    Image agua1 = GenImageColor(largura, altura, WHITE);
    Image grad1 = GenImageGradientLinear(largura, altura, 0, (Color){5, 167, 242, 255}, (Color){5, 60, 242, 255});
    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua1, raio + 2*raio*i, 0, raio, (Color){0});
        ImageDrawCircle(&grad1, raio + 2*raio*i, 0, raio + 2, (Color){0});
    }
    ImageDraw(&agua1, grad1, (Rectangle){0, 0, largura, altura}, (Rectangle){0, 0, largura, altura}, WHITE);
    
    agua->texturas[0] = LoadTextureFromImage(agua1);

    Image agua2 = GenImageColor(largura, altura, WHITE);
    Image grad2 = GenImageGradientLinear(largura, altura, 0, (Color){5, 116, 242, 255}, (Color){0, 0, 255, 255});

    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua2, raio + 2*raio*i, 0, raio, (Color){0});
        ImageDrawCircle(&grad2, raio + 2*raio*i, 0, raio + 2, (Color){0});
    }
    ImageDraw(&agua2, grad2, (Rectangle){0, 0, largura, altura}, (Rectangle){0, 0, largura, altura}, WHITE);
    
    agua->texturas[1] = LoadTextureFromImage(agua2);

    Image agua3 = GenImageColor(largura, altura, WHITE);
    Image grad3 = GenImageGradientLinear(largura, altura, 0, (Color){5, 60, 242, 255}, (Color){0, 0, 255, 255});

    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua3, raio + 2*raio*i, 0, raio, (Color){0});
        ImageDrawCircle(&grad3, raio + 2*raio*i, 0, raio + 2, (Color){0});
    }
    ImageDraw(&agua3, grad3, (Rectangle){0, 0, largura, altura}, (Rectangle){0, 0, largura, altura}, WHITE);
    
    agua->texturas[2] = LoadTextureFromImage(agua3);

    

    UnloadImage(agua1);
    UnloadImage(grad1);
    UnloadImage(agua2);
    UnloadImage(grad2);
    UnloadImage(agua3);
    UnloadImage(grad3);
}

void drawAgua(Agua agua) {
    for (int i=3; i>=0; i--) {
        DrawTexturePro(
            agua.texturas[i], (Rectangle){0, 0, agua.texturas[i].width, agua.texturas[i].height},
            agua.rect[i], (Vector2){0}, 0, WHITE);
        DrawTexturePro(
            agua.texturas[i], (Rectangle){0, 0, agua.texturas[i].width, agua.texturas[i].height},
            (Rectangle){agua.rect[i].x - agua.rect[i].width, agua.rect[i].y, agua.rect[i].width, agua.rect[i].height},
            (Vector2){0}, 0, WHITE);
        
    }
}

void updateAgua(Agua* agua, int speedAgua) {
    // Atualiza os retângulos em relação à posição
    for (int i=0; i<3; i++) {
        agua->rect[i].x += agua->vel[i];
        agua->rect[i].y = agua->position.y - i*45;
        agua->rect[i].width = agua->texturas[i].width;
        agua->rect[i].height = agua->texturas[i].height;

        if (agua->rect[i].x >= agua->rect[i].width)
            agua->rect[i].x = 0;
    }

    
    // Faz a água subir
    for(int h=0; h < speedAgua; h++){
        agua->position.y--;
    }
}