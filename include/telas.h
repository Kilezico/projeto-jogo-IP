#ifndef TELAS_H
#define TELAS_H

#include "jogador.h"
#include "mapa.h"

// Para sinalizar o estado do jogo.
typedef enum {
    INTRO, JOGO, PAUSA, ENCHENTE, MORTE
} GameplayScreen;

// Telas do jogo
// Se precisar de mais alguma coisa pra printar na função, é só adicionar nos parâmetros
void jogoDraw(GameplayScreen screen, Camera2D camera, Player jogador, Agua aguaLetal, Plataforma *plataformas, int platformasTam, Font fonte, Texture2D t1, Texture2D t2);
void jogoUpdate(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam);
void jogoReset(GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam);

// Terá pelo menos duas funçãos (draw e update) para cada tela
void menuDraw();
void menuUpdate();

// ...

#endif