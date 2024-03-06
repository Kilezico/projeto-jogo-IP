#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BUTTON_WIDTH 350 //defines the standard size of the buttons (horizontal) //MUDAR
#define BUTTON_HEIGHT 50 //defines the standard size of the buttons (vertical) //MUDAR

typedef struct {
    Rectangle credit;
    Color rectColor;
    Color nameColor;
    const char *name;
} nameCredit; //struct para os nomes dos integrantes do grupo

typedef struct {
    Color fullNameColor;
    const char *fullName;
    //const char *role;
    Texture2D frogPersonal;
} nameCreditExpanded; //struct para oq aparece quado coloca o cursor em cima do nome

void DrawCreditButton(nameCredit student) {
    DrawRectangleRec(student.credit, student.rectColor);
    DrawText(student.name, (int)student.credit.x + 10, (int)student.credit.y + 10, 50, student.nameColor);
} //desenha os nomes na tela

void DrawExpandedCreditButton(nameCreditExpanded studentF) {
    DrawText(studentF.fullName, 300, 150, 30, studentF.fullNameColor);
} //colocar mais coisa, desenha o resto na tela quando o cursor esta no nome

void credits()
{
    const int screenWidth = 800; //MUDAR
    const int screenHeight = 450;
    Color forestGreen = (Color){34, 139, 34, 255};
    
 
    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe credits screen");

    SetTargetFPS(60);

    nameCredit Dyego; nameCredit Henrique; nameCredit Joao; nameCredit Luanna; nameCredit Clara;
    //struct q pega as informações para desenhar os nomes

    Dyego.credit = (Rectangle){ 30, 10 + screenHeight / 2 - (5*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    //define o retangulo que representa o lugar do nome, mesma coordenada x, mas y é diferente
    Dyego.name = "Dyego"; //nome de cada um dos integrantes
    Dyego.rectColor = SKYBLUE; //cor (igual ao fundo) do retangulo, não aparece
    Dyego.nameColor = forestGreen; //cor do nome quando o cursor não está em cima

    Henrique.credit = (Rectangle){ 30, 20 + screenHeight / 2 - (3*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    Henrique.name = "Henrique";
    Henrique.rectColor = SKYBLUE;
    Henrique.nameColor = forestGreen;

    Joao.credit = (Rectangle){ 30, 30 + screenHeight / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Joao.name = "João";
    Joao.rectColor = SKYBLUE;
    Joao.nameColor = forestGreen;

    Luanna.credit = (Rectangle){ 30, 40 + screenHeight / 2 + BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Luanna.name = "Luanna";
    Luanna.rectColor = SKYBLUE;
    Luanna.nameColor = forestGreen;
    
    Clara.credit = (Rectangle){ 30, 50 + screenHeight / 2 + 3*BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Clara.name = "Clara";
    Clara.rectColor = SKYBLUE;
    Clara.nameColor = forestGreen;

    nameCreditExpanded DyegoF; nameCreditExpanded HenriqueF; nameCreditExpanded JoaoF; nameCreditExpanded LuannaF; nameCreditExpanded ClaraF;
    //struct para as informações que aparecem quando o cursor está em cima de um nome
    
    DyegoF.fullNameColor = forestGreen;
    DyegoF.fullName = "Dyego Ferreira da Silva";

    HenriqueF.fullNameColor = forestGreen;
    HenriqueF.fullName = "Henrique Alves Passos";

    JoaoF.fullNameColor = forestGreen;
    JoaoF.fullName = "João Victor Grangeiro Costa";

    LuannaF.fullNameColor = forestGreen;
    LuannaF.fullName = "Luanna Gomes Lucena";

    ClaraF.fullNameColor = forestGreen;
    ClaraF.fullName = "Maria Clara Laranjeira Tenório";

    while (!WindowShouldClose())  
    {
        
        BeginDrawing();


            ClearBackground(SKYBLUE);
            DrawText("sapo-sopa sobe", 115, 20, 70, WHITE); //titulo do jogo

            DrawCreditButton(Dyego);
            DrawCreditButton(Henrique);
            DrawCreditButton(Joao);
            DrawCreditButton(Luanna);
            DrawCreditButton(Clara);
            //desenha todos os nomes

            if (CheckCollisionPointRec(GetMousePosition(), Dyego.credit)){
                Dyego.rectColor = SKYBLUE;
                Dyego.nameColor = forestGreen;
                DrawExpandedCreditButton(DyegoF);
            } else{
                Dyego.rectColor = SKYBLUE;
                Dyego.nameColor = WHITE;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Henrique.credit)){
                Henrique.rectColor = SKYBLUE;
                Henrique.nameColor = forestGreen;
                DrawExpandedCreditButton(HenriqueF);
            } else {
                Henrique.rectColor = SKYBLUE;
                Henrique.nameColor = WHITE;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Joao.credit)){
                Joao.rectColor = SKYBLUE;
                Joao.nameColor = forestGreen;
                DrawExpandedCreditButton(JoaoF);
            } else{
                Joao.rectColor = SKYBLUE;
                Joao.nameColor = WHITE;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Luanna.credit)){
                Luanna.rectColor = SKYBLUE;
                Luanna.nameColor = forestGreen;
                DrawExpandedCreditButton(LuannaF);
            } else{
                Luanna.rectColor = SKYBLUE;
                Luanna.nameColor = WHITE;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Clara.credit)){
                Clara.rectColor = SKYBLUE;
                Clara.nameColor = forestGreen;
                DrawExpandedCreditButton(ClaraF);
            } else{
                Clara.rectColor = SKYBLUE;
                Clara.nameColor = WHITE;
            } //verifica se o cursor está em cima de algum dos nomes, se estiver expande para as informações daquele e muda a cor
            
        EndDrawing();
    }

    CloseWindow(); 
}
