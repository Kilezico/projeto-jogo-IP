#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
    //const char *role;
    Texture2D frogPersonal;
} nameCreditExpanded; //struct para oq aparece quado coloca o cursor em cima do nome

void DrawCreditButton(nameCredit student) {
    DrawRectangleRec(student.credit, student.rectColor);
    DrawText(student.name, (int)student.credit.x + 25, (int)student.credit.y + 25, 120, student.nameColor);
} //desenha os nomes na tela

void DrawExpandedCreditButton(nameCreditExpanded studentF) {
    DrawText(studentF.fullName, 720, 360, 70, studentF.fullNameColor);
} //colocar mais coisa, desenha o resto na tela quando o cursor esta no nome

int credits(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    Color grassGreen = (Color){74, 163, 26, 255}; //cor para os nomes das opções
    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu
    Color groungBrown = (Color){130, 68, 4, 255}; //cor do titulo/terra    
 
    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe credits screen");
    Texture2D background = LoadTexture("assets/backGround.png");

    SetTargetFPS(60);

    nameCredit Dyego; nameCredit Henrique; nameCredit Joao; nameCredit Luanna; nameCredit Clara;
    //struct q pega as informações para desenhar os nomes

    Dyego.credit = (Rectangle){ 70, 25 + screenHeight / 2 - (5*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    //define o retangulo que representa o lugar do nome, mesma coordenada x, mas y é diferente
    Dyego.name = "Dyego"; //nome de cada um dos integrantes
    Dyego.rectColor = polutedSky; //cor (igual ao fundo) do retangulo, não aparece
    Dyego.nameColor = groungBrown; //cor do nome quando o cursor não está em cima

    Henrique.credit = (Rectangle){ 70, 50 + screenHeight / 2 - (3*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    Henrique.name = "Henrique";
    Henrique.rectColor = polutedSky;
    Henrique.nameColor = groungBrown;

    Joao.credit = (Rectangle){ 70, 75 + screenHeight / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Joao.name = "João";
    Joao.rectColor = polutedSky;
    Joao.nameColor = groungBrown;

    Luanna.credit = (Rectangle){ 70, 100 + screenHeight / 2 + BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Luanna.name = "Luanna";
    Luanna.rectColor = polutedSky;
    Luanna.nameColor = groungBrown;
    
    Clara.credit = (Rectangle){ 70, 125 + screenHeight / 2 + 3*BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Clara.name = "Clara";
    Clara.rectColor = polutedSky;
    Clara.nameColor = groungBrown;

    nameCreditExpanded DyegoF; nameCreditExpanded HenriqueF; nameCreditExpanded JoaoF; nameCreditExpanded LuannaF; nameCreditExpanded ClaraF;
    //struct para as informações que aparecem quando o cursor está em cima de um nome
    
    DyegoF.fullNameColor = groungBrown;
    DyegoF.fullName = "Dyego Ferreira da Silva";

    HenriqueF.fullNameColor = groungBrown;
    HenriqueF.fullName = "Henrique Alves Passos";

    JoaoF.fullNameColor = groungBrown;
    JoaoF.fullName = "João Victor Grangeiro Costa";

    LuannaF.fullNameColor = groungBrown;
    LuannaF.fullName = "Luanna Gomes Lucena";

    ClaraF.fullNameColor = groungBrown;
    ClaraF.fullName = "Maria Clara Laranjeira Tenório";

    while (!WindowShouldClose())  
    {
        
        BeginDrawing();

            DrawTexture(background, 0, 0, WHITE);
            DrawText("sapos-sopa (grupo 7)", 275, 50, 170, WHITE); //titulo do jogo

            DrawCreditButton(Dyego);
            DrawCreditButton(Henrique);
            DrawCreditButton(Joao);
            DrawCreditButton(Luanna);
            DrawCreditButton(Clara);
            //desenha todos os nomes

            if (CheckCollisionPointRec(GetMousePosition(), Dyego.credit)){
                Dyego.rectColor = polutedSky;
                Dyego.nameColor = groungBrown;
                DrawExpandedCreditButton(DyegoF);
            } else{
                Dyego.rectColor = polutedSky;
                Dyego.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Henrique.credit)){
                Henrique.rectColor = polutedSky;
                Henrique.nameColor = groungBrown;
                DrawExpandedCreditButton(HenriqueF);
            } else {
                Henrique.rectColor = polutedSky;
                Henrique.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Joao.credit)){
                Joao.rectColor = polutedSky;
                Joao.nameColor = groungBrown;
                DrawExpandedCreditButton(JoaoF);
            } else{
                Joao.rectColor = polutedSky;
                Joao.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Luanna.credit)){
                Luanna.rectColor = polutedSky;
                Luanna.nameColor = groungBrown;
                DrawExpandedCreditButton(LuannaF);
            } else{
                Luanna.rectColor = polutedSky;
                Luanna.nameColor = grassGreen;
            }
            if(CheckCollisionPointRec(GetMousePosition(), Clara.credit)){
                Clara.rectColor = polutedSky;
                Clara.nameColor = groungBrown;
                DrawExpandedCreditButton(ClaraF);
            } else{
                Clara.rectColor = polutedSky;
                Clara.nameColor = grassGreen;
            } //verifica se o cursor está em cima de algum dos nomes, se estiver expande para as informações daquele e muda a cor
            
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow(); 


    return 0;
}
