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
void jogoDraw(GameplayScreen screen, Camera2D camera, Player jogador, Agua aguaLetal, Plataforma *plataformas, int platformasTam, Font fonte);
void jogoUpdate(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor);
void jogoReset(GameScreen *bigScreen, GameplayScreen *screen, Camera2D *camera, Player *player, Agua *aguaLetal, Plataforma *plataformas, int plataformasTam, Texture2D *texturaPlat, Texture2D *texturaPlatFlor);

GameScreen menuDraw(GameScreen *screen);
GameScreen backStoryDraw(GameScreen *screen);
GameScreen creditsDraw(GameScreen *screen);
GameScreen howToDraw(GameScreen *screen);

#endif