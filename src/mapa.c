#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "mapa.h"
#include "jogador.h"

Plataforma novaPlataforma(Vector2 position, Texture2D *texturaPlat, Texture2D *texturaPlatFlor) 
{
    // Função que cria e retorna uma nova plataforma na altura position.y e num x perto de position.x
    int distanciaMin = 150;
    int distanciaMax = 300;
    Plataforma plat;
    plat.textura = GetRandomValue(1, 2) == 1 ? texturaPlat : texturaPlatFlor;
    plat.rect = (Rectangle){0, position.y, plat.textura->width / 3, plat.textura->height / 3};
    plat.hitbox = (EnvItem){(Rectangle){plat.rect.x + 10, plat.rect.y + 75, plat.rect.width - 30, 20}, 1};
    plat.velocidade = 0;
    
    // Randomiza a posição da plataforma
    float pos = position.x;
    if (pos < 2*distanciaMax) pos += GetRandomValue(distanciaMin, distanciaMax);
    else if (pos > 1920 - 2*distanciaMax - plat.hitbox.react.width) pos += GetRandomValue(-distanciaMax, -distanciaMin);
    else pos += pow(-1, GetRandomValue(1, 2)) * GetRandomValue(distanciaMin, distanciaMax);
    plat.rect.x = pos;
    plat.hitbox.react.x = pos + 10;
    return plat;
}

void criaPlataformas(Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor) // Cria as plataformas iniciais
{
    // Seria criar um número fixo de plataformas (plataformasTam) no começo do jogo
    // a partir do chão, ou seja, criar o próprio chão, e depois mais plataformasTam-1 plataformas.
    plataformas[0] = (Plataforma){(EnvItem){(Rectangle){0, 0, 2000, 300}, 1}, (Rectangle){0, 0, 0, 0}, NULL, 0};

    plataformas[1] = novaPlataforma((Vector2) {GetRandomValue(0, 1920), -50 - 140}, texturaPlat, texturaPlatFlor);
    for (int i=2; i<plataformasTam; i++) {
        plataformas[i] = novaPlataforma((Vector2) {plataformas[i-1].hitbox.react.x + plataformas[i-1].hitbox.react.width/2, -50 - 140*i}, texturaPlat, texturaPlatFlor);
    }
}

void updatePlataforma(Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor, float alturaAgua) // Cria novas plataformas e também move elas (se necessário)
{
    // Para criar novas plataformas, uma boa ideia seria verificar as plataformas que estão
    // dentro da água, e substituílas por novas, acima da tela, que vão entrar na tela na medida
    // que o sapo pular, já que a água não desce.
    int maiorPlataforma = -1, plataformaSaiu = -1;
    for (int i=0; i<plataformasTam; i++) {
        if (!i || plataformas[i].rect.y < plataformas[maiorPlataforma].rect.y)
            maiorPlataforma = i;
        if (plataformas[i].rect.y > alturaAgua) plataformaSaiu = i;
    }
    // Sim, só cria uma plataforma nova por frame, mas isso não deve se tornar um problema
    Vector2 position;
    position.x = plataformas[maiorPlataforma].hitbox.react.x + plataformas[maiorPlataforma].hitbox.react.width/2;
    position.y = plataformas[maiorPlataforma].rect.y - 144;
    plataformas[plataformaSaiu] = novaPlataforma(position, texturaPlat, texturaPlatFlor);
}

void drawPlataforma(Plataforma *plataformas, int plataformasTam)
{
    for (int i=0; i<plataformasTam; i++) {
        if (plataformas[i].textura != NULL) { // é uma vitória régia
            //DrawTexture(*plataformas[i].textura, plataformas[i].rect.x, plataformas[i].rect.y, WHITE);
            Rectangle source = (Rectangle){0, 0, plataformas[i].textura->width, plataformas[i].textura->height};
            DrawTexturePro(*plataformas[i].textura, source, plataformas[i].rect, (Vector2){0, 0}, 0, WHITE);
            //DrawRectangleLinesEx(plataformas[i].hitbox.react, 2, RED);
        } else { // é o chão
            DrawRectangleRec(plataformas[i].hitbox.react, BROWN);
        }
    }
}


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
            agua->velVertical += 0.0004f;
            if (agua->velVertical > 2.5f) agua->velVertical = 2.5f;
        }
    } else {
        agua->altura -= 5;        
    }
    // Aumenta a velocidade vertical (e horizontal) gradativamente
    // TODO - aumentar as velocidades  

    // Sobe também a altrua letal
    agua->alturaLetal = agua->altura + 110;
}