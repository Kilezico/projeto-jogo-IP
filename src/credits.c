#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "utilidades.h"
#include "telas.h"

#define BUTTON_WIDTH 840 //largura dos nomes
#define BUTTON_HEIGHT 120 //altura dos nomes

typedef struct {
    Rectangle credit;
    Color rectColor;
    Color nameColor;
    const char *name;
} nameCredit; //struct para os nomes dos integrantes do grupo

typedef struct {
    Color fullNameColor;
    const char *fullName;
    const char *role;
} nameCreditExpanded; //struct para oq aparece quado coloca o cursor em cima do nome

void DrawCreditButton(nameCredit student, Font fonte) {
    DrawRectangleRec(student.credit, student.rectColor);
    DrawTextLinesCorner(fonte, student.name, (Vector2){student.credit.x, student.credit.y}, 0, 120, 20, student.nameColor, BLACK, 4);
} //desenha os nomes na tela

void DrawExpandedCreditButton(nameCreditExpanded studentF, Font fonte) {
    // DrawText(studentF.fullName, 720, 360, 70, studentF.fullNameColor);
    DrawTextEx(fonte, studentF.fullName, (Vector2){720, 360}, 70, 0, studentF.fullNameColor);
    // DrawText(studentF.role, 770, 440, 50, studentF.fullNameColor);
    DrawTextEx(fonte, studentF.role, (Vector2){770, 440}, 50, 0, studentF.fullNameColor);
} //coloca mais informações, desenha o resto na tela quando o cursor esta no nome

bool BackToMenuPressedC(bool menuButton, Rectangle button) {
    if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        menuButton = true;
    } //checa se o cursor ta em cima do botão e se foi pressioanado
    return menuButton;
}

GameScreen creditsDraw(GameScreen *screen, Font fonte)
{
    bool goBacktoMenu = false;
    
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    Color grassGreen = (Color){74, 163, 26, 255}; //cor para os nomes das opções
    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu
    Color groundBrown = (Color){130, 68, 4, 255}; //cor do titulo/terra    
 
    Texture2D background = LoadTexture("assets/backGround.png");

    nameCredit Dyego; nameCredit Henrique; nameCredit Joao; nameCredit Luanna; nameCredit Clara;
    //struct q pega as informações para desenhar os nomes

    Dyego.credit = (Rectangle){ 70, screenHeight / 2 - (5*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    //define o retangulo que representa o lugar do nome, mesma coordenada x, mas y é diferente
    Dyego.name = "Dyego"; //nome de cada um dos integrantes
    Dyego.rectColor = polutedSky; //cor (igual ao fundo) do retangulo, não aparece
    Dyego.nameColor = groundBrown; //cor do nome quando o cursor não está em cima

    Henrique.credit = (Rectangle){ 70, 25 + screenHeight / 2 - (3*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    Henrique.name = "Henrique";
    Henrique.rectColor = polutedSky;
    Henrique.nameColor = groundBrown;

    Joao.credit = (Rectangle){ 70, 50 + screenHeight / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Joao.name = "João";
    Joao.rectColor = polutedSky;
    Joao.nameColor = groundBrown;

    Luanna.credit = (Rectangle){ 70, 75 + screenHeight / 2 + BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Luanna.name = "Luanna";
    Luanna.rectColor = polutedSky;
    Luanna.nameColor = groundBrown;
    
    Clara.credit = (Rectangle){ 70, 100 + screenHeight / 2 + 3*BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Clara.name = "Clara";
    Clara.rectColor = polutedSky;
    Clara.nameColor = groundBrown;

    nameCreditExpanded DyegoF; nameCreditExpanded HenriqueF; nameCreditExpanded JoaoF; nameCreditExpanded LuannaF; nameCreditExpanded ClaraF;
    //struct para as informações que aparecem quando o cursor está em cima de um nome
    
    DyegoF.fullNameColor = groundBrown;
    DyegoF.fullName = "Dyego Ferreira da Silva";
    DyegoF.role = "função do dyego";

    HenriqueF.fullNameColor = groundBrown;
    HenriqueF.fullName = "Henrique Alves Passos";
    HenriqueF.role = "função do henrique";

    JoaoF.fullNameColor = groundBrown;
    JoaoF.fullName = "João Victor Grangeiro Costa";
    JoaoF.role = "função do joão";

    LuannaF.fullNameColor = groundBrown;
    LuannaF.fullName = "Luanna Gomes Lucena";
    LuannaF.role = "função da luanna";

    ClaraF.fullNameColor = groundBrown;
    ClaraF.fullName = "Maria Clara Laranjeira Tenório";
    ClaraF.role = "função da clara";

    while (goBacktoMenu!=true)  
    {
        
        BeginDrawing();

            DrawTexture(background, 0, 0, WHITE);
            DrawTextLines(fonte, "sapos-sopa (grupo 7)", (Vector2){960, 120}, 0, 150, 20, WHITE, BLACK, 4); // titulo do jogo

            Rectangle backToMenu = (Rectangle){ 20, 30, 450, 200 };
            DrawRectangleRec(backToMenu, polutedSky);
            // DrawText("sapo-sopa sobe", 25, 35, 50, BLACK);
            DrawTextEx(fonte, "sapo-sopa sobe", (Vector2){25, 35}, 50, 0, BLACK);
            goBacktoMenu = BackToMenuPressedC(goBacktoMenu, backToMenu);
            if(goBacktoMenu==true){//vai fazer o while parar
                *screen = MENUS;
            }

            DrawCreditButton(Dyego, fonte);
            DrawCreditButton(Henrique, fonte);
            DrawCreditButton(Joao, fonte);
            DrawCreditButton(Luanna, fonte);
            DrawCreditButton(Clara, fonte);
            //desenha todos os nomes

            if (CheckCollisionPointRec(GetMousePosition(), Dyego.credit)){
                Dyego.rectColor = polutedSky;
                Dyego.nameColor = groundBrown;
                DrawExpandedCreditButton(DyegoF, fonte);
            } else{
                Dyego.rectColor = polutedSky;
                Dyego.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Henrique.credit)){
                Henrique.rectColor = polutedSky;
                Henrique.nameColor = groundBrown;
                DrawExpandedCreditButton(HenriqueF, fonte);
            } else {
                Henrique.rectColor = polutedSky;
                Henrique.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Joao.credit)){
                Joao.rectColor = polutedSky;
                Joao.nameColor = groundBrown;
                DrawExpandedCreditButton(JoaoF, fonte);
            } else{
                Joao.rectColor = polutedSky;
                Joao.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Luanna.credit)){
                Luanna.rectColor = polutedSky;
                Luanna.nameColor = groundBrown;
                DrawExpandedCreditButton(LuannaF, fonte);
            } else{
                Luanna.rectColor = polutedSky;
                Luanna.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Clara.credit)){
                Clara.rectColor = polutedSky;
                Clara.nameColor = groundBrown;
                DrawExpandedCreditButton(ClaraF, fonte);
            } else{
                Clara.rectColor = polutedSky;
                Clara.nameColor = grassGreen;
            } //verifica se o cursor está em cima de algum dos nomes, se estiver expande para as informações daquele e muda a cor
            
        EndDrawing();
    }

    UnloadTexture(background);

    return *screen;
}
