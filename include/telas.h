#ifndef TELAS_H
#define TELAS_H

#include "jogador.h"
#include "mapa.h"

// Para sinalizar o estado do jogo.
typedef enum {
    JOGO, PAUSA, ENCHENTE, MORTE
} GameplayScreen;

// Trocador de tela
typedef enum {
    GAMEPLAY, MENUS, HOWTO, STORY, CREDITS, EXIT
} GameScreen;

// Telas do jogo
// Se precisar de mais alguma coisa pra printar na função, é só adicionar nos parâmetros
void jogoDraw(GameplayScreen screen, Camera2D camera, Player jogador, Agua aguaLetal, Plataforma *plataformas, int platformasTam, Font fonte, Texture2D terra, Texture2D terraTopo, Texture2D mosca);
void jogoUpdate(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor, Music mMenu, Music mJogo);
void jogoReset(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor, Music mMenu, Music mJogo);

GameScreen menuDraw(GameScreen *screen, Font fonte, Music mMenu, Music mJogo);
GameScreen backStoryDraw(GameScreen *screen, Font fonte);
GameScreen creditsDraw(GameScreen *screen, Font fonte);
GameScreen howToDraw(GameScreen *screen, Font fonte);

#endif