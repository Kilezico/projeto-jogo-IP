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

GameScreen howToDraw(GameScreen *screen)
{
    SetTargetFPS(60);
    bool goBacktoMenu = false;

    Texture2D background = LoadTexture("assets/backGround.png");
    Texture2D keyBoard = LoadTexture("assets/keyBoard.png");
    Texture2D AandD = LoadTexture("assets/AandD.png");
    Texture2D LandR = LoadTexture("assets/LandR.png");
    Texture2D spaceKey = LoadTexture("assets/spaceKey.png");

    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu

    while (goBacktoMenu!=true)
    {

        BeginDrawing();

            DrawTexture(background, 0, 0, WHITE);
    
            Rectangle backToMenu = (Rectangle){ 20, 30, 450, 200 };
            DrawRectangleRec(backToMenu, polutedSky);
            DrawText("sapo-sopa sobe", 25, 35, 50, BLACK);
            goBacktoMenu = BackToMenuPressedHT(goBacktoMenu, backToMenu);
            if(goBacktoMenu==true){//vai fazer o while parar
                *screen = MENUS;
            }
      
            Rectangle keyBoardProportions = { 0, 0, keyBoard.width, keyBoard.height };
            Rectangle keyBoardWhere = { 1440, 480, keyBoard.width*0.5, keyBoard.height*0.5 };
            DrawTexturePro(keyBoard, keyBoardProportions, keyBoardWhere, (Vector2){ 0, 0 }, 0, WHITE); //coloca a imagem do teclado
    
            Rectangle AandDProportions = { 0, 0, AandD.width, AandD.height };
            Rectangle AandDWhere = { 120, 1200, AandD.width*0.25, AandD.height*0.25 };
            DrawTexturePro(AandD, AandDProportions, AandDWhere, (Vector2){ 0, 0 }, 0, WHITE); //imagem das teclas a e d
    
            Rectangle LandRProportions = { 0, 0, LandR.width, LandR.height };
            Rectangle LandRWhere = { 140, 1200, LandR.width*0.25, LandR.height*0.25 };
            DrawTexturePro(LandR, LandRProportions, LandRWhere, (Vector2){ 0, 0 }, 0, WHITE); //imagem das teclas das setas
    
            Rectangle spaceKeyProportions = { 0, 0, spaceKey.width, spaceKey.height };
            Rectangle spaceKeyWhere = { 300, 1200, spaceKey.width*0.25, spaceKey.height*0.25 };
            DrawTexturePro(spaceKey, spaceKeyProportions, spaceKeyWhere, (Vector2){ 0, 0 }, 0, WHITE); //imagem da tecla espaço
    
            DrawText("Teclas necessárias:", 100, 70, 100, BLACK);
            DrawText("Como andar para os lados?", 120, 200, 50, BLACK);
            DrawText("Use as letras A e D, ou as setas do teclado", 120, 250, 25, BLACK);
            DrawText("Como pular?", 960, 480, 50, BLACK);
            DrawText("Aperte no botão de espaço", 960, 600, 25, BLACK); //textos que ficam na tela

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(keyBoard);
    UnloadTexture(AandD);
    UnloadTexture(LandR);
    UnloadTexture(spaceKey);

    return *screen;
}
