#ifndef VISAO
#define VISAO
#include <raylib.h>
#include "jogador.h"

void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraJump(Camera2D *camera, Player *player, int width, int height);

#endif