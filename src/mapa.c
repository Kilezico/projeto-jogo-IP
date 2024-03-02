#include <raylib.h>
#include <stdlib.h>

#include "mapa.h"
#include "jogador.h"

void criaTexturasAgua(Agua *agua) {
    int largura = GetScreenWidth() + 40;
    int altura = 1000;
    int raio = largura / 40;
    Image agua1 = GenImageColor(largura, 2*altura, WHITE);
    Image grad1 = GenImageGradientLinear(largura, altura, 0, (Color){5, 167, 242, 255}, (Color){0, 0, 255, 255});
    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua1, raio + 2*raio*i, 0, raio + 5, (Color){0});
        ImageDrawCircle(&grad1, raio + 2*raio*i, 0, raio + 7, (Color){0});
    }
    ImageDraw(&agua1, grad1, (Rectangle){0, 0, largura, altura}, (Rectangle){0, 0, largura, altura}, WHITE);
    ImageDrawRectangle(&grad1, 0, 0, largura, altura, (Color){0, 0, 255, 255});
    ImageDraw(&agua1, grad1, (Rectangle){0, 0, largura, altura}, (Rectangle){0, altura, largura, altura}, WHITE);
    
    // Faz essa textura da frente ser bem longa pra baixo pra cobrir a tela quando o jogador morrer.
    agua->texturas[0] = LoadTextureFromImage(agua1);

    Image agua2 = GenImageColor(largura, altura, WHITE);
    Image grad2 = GenImageGradientLinear(largura, altura, 0, (Color){5, 116, 242, 255}, (Color){0, 0, 255, 255});

    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua2, raio + 2*raio*i, 0, raio + 5, (Color){0});
        ImageDrawCircle(&grad2, raio + 2*raio*i, 0, raio + 7, (Color){0});
    }
    ImageDraw(&agua2, grad2, (Rectangle){0, 0, largura, altura}, (Rectangle){0, 0, largura, altura}, WHITE);
    
    agua->texturas[1] = LoadTextureFromImage(agua2);

    Image agua3 = GenImageColor(largura, altura, WHITE);
    Image grad3 = GenImageGradientLinear(largura, altura, 0, (Color){5, 60, 242, 255}, (Color){0, 0, 255, 255});

    for (int i=0; i<largura/raio*2; i++) {
        ImageDrawCircle(&agua3, raio + 2*raio*i, 0, raio + 5, (Color){0});
        ImageDrawCircle(&grad3, raio + 2*raio*i, 0, raio + 7, (Color){0});
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

void drawAguaFundo(Agua agua) {
    for (int i=2; i>=0; i--) {
        DrawTexturePro(
            agua.texturas[i], (Rectangle){0, 0, agua.texturas[i].width, agua.texturas[i].height},
            agua.rect[i], (Vector2){0}, 0, WHITE);
        DrawTexturePro(
            agua.texturas[i], (Rectangle){0, 0, agua.texturas[i].width, agua.texturas[i].height},
            (Rectangle){agua.rect[i].x - agua.rect[i].width, agua.rect[i].y, agua.rect[i].width, agua.rect[i].height},
            (Vector2){0}, 0, WHITE);
    }
}

void drawAguaFrente(Agua agua)
{
    DrawTexturePro(
        agua.texturas[0], (Rectangle){0, 0, agua.texturas[0].width, agua.texturas[0].height},
        agua.rect[0], (Vector2){0}, 0, WHITE);
    DrawTexturePro(
        agua.texturas[0], (Rectangle){0, 0, agua.texturas[0].width, agua.texturas[0].height},
        (Rectangle){agua.rect[0].x - agua.rect[0].width, agua.rect[0].y, agua.rect[0].width, agua.rect[0].height},
        (Vector2){0}, 0, WHITE);
}

void updateAgua(Agua* agua, float alturaJogador, bool cabou) {
    // Atualiza os retângulos em relação à posição
    for (int i=0; i<3; i++) {
        agua->rect[i].x += agua->vel[i];
        agua->rect[i].y = agua->altura - i*45;
        agua->rect[i].width = agua->texturas[i].width;
        agua->rect[i].height = agua->texturas[i].height;

        if (agua->rect[i].x >= agua->rect[i].width)
            agua->rect[i].x = 0;
    }
    
    // Faz a água subir
    if (!cabou) {
        float distancia = abs(alturaJogador - agua->altura);
        if (distancia > 480) { // "Tenho que ir rápido". Vai chegar de volta a tela bem rápido
            agua->altura -= distancia * 0.006;
        } else { // Quando chegar na tela, vai um pouco mais lento
            agua->altura -= agua->velVertical;
        }
    } else {
        agua->altura -= 5;        
    }
    // Aumenta a velocidade vertical (e horizontal) gradativamente
    // TODO - aumentar as velocidades  

    // Sobe também a altrua letal
    agua->alturaLetal = agua->altura + 110;
}