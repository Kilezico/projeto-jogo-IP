#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "mapa.h"
#include "jogador.h"
#include "coins.h"
#include "phisica.h"

Plataforma novaPlataforma(Vector2 position, Texture2D *texturaPlat, Texture2D *texturaPlatFlor) 
{
    // Função que cria e retorna uma nova plataforma na altura position.y e num x perto de position.x
    int distanciaMin = 100;
    int distanciaMax = 400;
    // distanciaMin = distanciaMax = 0;
    Plataforma plat;
    plat.textura = GetRandomValue(1, 2) == 1 ? texturaPlat : texturaPlatFlor;
    plat.rect = (Rectangle){0, position.y, plat.textura->width / 3, plat.textura->height / 3};
    plat.hitbox = (EnvItem){(Rectangle){plat.rect.x + 10, plat.rect.y + 75, plat.rect.width - 20, 20}, 1};
    plat.velocidade = 0;

    // Randomiza a posição da plataforma
    float pos = position.x;
    if (pos < distanciaMax) pos += GetRandomValue(distanciaMin, distanciaMax);
    else if (pos > 1920 - distanciaMax - plat.hitbox.react.width) pos += GetRandomValue(-distanciaMax, -distanciaMin);
    else pos += pow(-1, GetRandomValue(1, 2)) * GetRandomValue(distanciaMin, distanciaMax);
    plat.rect.x = pos;
    plat.hitbox.react.x = pos + 5;

    // Cria a coin da plataforma
    Coin dindin;
    dindin.active = GetRandomValue(1, 8) == 1;
    dindin.position.x = plat.hitbox.react.x + plat.hitbox.react.width/2;
    dindin.position.y = plat.hitbox.react.y - 40;
    dindin.color = GOLD;
    plat.coin = dindin;

    return plat;
}

void criaPlataformas(Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor) // Cria as plataformas iniciais
{
    // Seria criar um número fixo de plataformas (plataformasTam) no começo do jogo
    // a partir do chão, ou seja, criar o próprio chão, e depois mais plataformasTam-1 plataformas.
    // chão
    plataformas[0] = (Plataforma){(EnvItem){(Rectangle){0, 0, 2000, 300}, 1}, (Rectangle){0, 0, 0, 0}, NULL, 0};
    // primeira plataforma em lugar aleátrio  
    plataformas[1] = novaPlataforma((Vector2) {GetRandomValue(300, 1600), -250}, texturaPlat, texturaPlatFlor);
    for (int i=2; i<plataformasTam; i++) {
        float altura = plataformas[i-1].rect.y - 120;
        plataformas[i] = novaPlataforma((Vector2) {plataformas[i-1].rect.x, altura}, texturaPlat, texturaPlatFlor);
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
    if (plataformaSaiu != -1) {
        Vector2 position;
        position.x = plataformas[maiorPlataforma].hitbox.react.x;
        position.y = plataformas[maiorPlataforma].rect.y - 120;
        plataformas[plataformaSaiu] = novaPlataforma(position, texturaPlat, texturaPlatFlor);
    }
}

void drawPlataforma(Plataforma *plataformas, int plataformasTam, Texture2D terra, Texture2D topo, Texture2D mosca)
{
    for (int i=0; i<plataformasTam; i++) {
        if (plataformas[i].textura != NULL) { // é uma vitória régia
            //DrawTexture(*plataformas[i].textura, plataformas[i].rect.x, plataformas[i].rect.y, WHITE);
            Rectangle source = (Rectangle){0, 0, plataformas[i].textura->width, plataformas[i].textura->height};
            DrawTexturePro(*plataformas[i].textura, source, plataformas[i].rect, (Vector2){0, 0}, 0, WHITE);
            DrawCoin(plataformas[i].coin, mosca);
            // desenha as hitboxes
            // DrawRectangleLinesEx(plataformas[i].hitbox.react, 2, RED);
        } else { // é o chão
            int tam = 16 * 5;
            for (int j=plataformas[i].hitbox.react.x; j<plataformas[i].hitbox.react.width; j+=tam) {
                for (int k=plataformas[i].hitbox.react.y; k<plataformas[i].hitbox.react.height; k+=tam) {
                    DrawTexturePro((k == 0) ? topo : terra, (Rectangle){0, 0, 16, 16}, (Rectangle){j, k-10, tam, tam}, (Vector2){0, 0}, 0, WHITE);
                }
            }
            // DrawRectangleRec(plataformas[i].hitbox.react, BROWN);
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
        if (distancia > 570) { // "Tenho que ir rápido". Vai chegar de volta a tela bem rápido
            agua->altura -= distancia * 0.008;
        } else { // Quando chegar na tela, vai um pouco mais lento
            agua->altura -= agua->velVertical;
            agua->velVertical += AGUA_ACCEL;
            if (agua->velVertical > AGUA_MAX_SPD) agua->velVertical = AGUA_MAX_SPD;
        }
    } else {
        agua->altura -= 5;        
    }
    // Aumenta a velocidade vertical (e horizontal) gradativamente
    // TODO - aumentar as velocidades  

    // Sobe também a altrua letal
    agua->alturaLetal = agua->altura + 110;
}