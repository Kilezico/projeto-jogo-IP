#ifndef TELAS_H
#define TELAS_H

#include "jogador.h"
#include "mapa.h"

// Telas do jogo
// Se precisar de mais alguma coisa pra printar na função, é só adicionar nos parâmetros
void jogoDraw(Camera2D camera, Player jogador, Agua aguaLetal, EnvItem *plataformas, int platformasTam, Font fonte);
void jogoUpdate(Camera2D *camera, Player *player, Agua *aguaLetal, EnvItem *plataformas, int plataformasTam);
void jogoReset();

// Terá pelo menos duas funçãos (draw e update) para cada tela
void menuDraw();
void menuUpdate();

// ...

#endif