#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "utilidades.h"
#include "telas.h"

bool BackToMenuPressedHT(bool menuButton, Rectangle button) {
    if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        menuButton = true;
    } //checa se o cursor ta em cima do botão e se foi pressioanado
    return menuButton;
}

GameScreen howToDraw(GameScreen *screen, Font fonte)
{
    SetTargetFPS(60);
    bool goBacktoMenu = false;

    Texture2D tutorial = LoadTexture("assets/tutorialFinal.png");

    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu

    while (goBacktoMenu!=true)
    {

        BeginDrawing();

            // DrawTexture(tutorial, 0, 0, WHITE);
            Rectangle source = {0, 0, tutorial.width, tutorial.height};
            Rectangle dest = {0, -1, 1921, 1081};
            DrawTexturePro(tutorial, source, dest, (Vector2){0, 0}, 0, WHITE);
    
            Rectangle backToMenu = (Rectangle){ 20, 30, 450, 200 };
            DrawRectangleRec(backToMenu, polutedSky);
            DrawTextEx(fonte, "menu", (Vector2){25, 35}, 50, 0, BLACK);
            goBacktoMenu = BackToMenuPressedHT(goBacktoMenu, backToMenu);
            if(goBacktoMenu==true){//vai fazer o while parar
                *screen = MENUS;
            }
    
            DrawTextEx(fonte, "Como pular?", (Vector2){120, 200}, 100, 0, BLACK);
            DrawTextEx(fonte, "Aperte no botão de espaço", (Vector2){120, 320}, 65, 0, BLACK);
            DrawTextEx(fonte, "Como andar para os lados?", (Vector2){960, 400}, 100, 0, BLACK);
            DrawTextEx(fonte, "Use as letras A e D,\n\n\nou as setas do teclado", (Vector2){960, 520}, 65, 0, BLACK); //textos que ficam na tela
            
        EndDrawing();
    }

    UnloadTexture(tutorial);

    return *screen;
}
