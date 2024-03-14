#include "visao.h"
#include "jogador.h"

// Camera Centralizada com o jogador
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = player->position;

    camera->zoom += ((float) GetMouseWheelMove()*0.05f);
    if(camera->zoom > 3.0f) camera->zoom = 3.0f;
    else if(camera->zoom < 0.3f) camera->zoom = 0.3f;
}

// Camera que atualiza quando o jogador pisa na plataforma
void UpdateCameraJump(Camera2D *camera, Player *player, int width, int height)
{
    if (camera->target.y > player->position.y) camera->target.y = player->position.y;

    camera->zoom += ((float) GetMouseWheelMove()*0.05f);
    if(camera->zoom > 1.0f) camera->zoom = 1.0f;
    else if(camera->zoom < 0.5f) camera->zoom = 0.5f;
}