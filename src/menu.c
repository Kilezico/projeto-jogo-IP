#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utilidades.h"

#define BUTTON_WIDTH 450 //define a largura do botões
#define BUTTON_HEIGHT 110 //define a altura dos botões 

typedef struct {
    Rectangle button;
    Color rectColor;
    Color optionColor;
    const char *word;
    int fontSize;
} options; //struct pras informações de cada um dos cinco botões (jogar, backstory, como jogar, creditos e sair)

void DrawMenuButton(options choice) {

    DrawRectangleRec(choice.button, choice.rectColor);
    DrawText(choice.word, (int)choice.button.x + 20, (int)choice.button.y + 20, choice.fontSize, choice.optionColor);
} //desenha cada um dos botões com base nas informações da struct correspondente a opção (parametro)

bool checkOptionSelected(bool buttonClicked, options choice) {
    if (CheckCollisionPointRec(GetMousePosition(), choice.button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    { //checa se o cursor ta em cima do botão e se for pressioanado
        if(buttonClicked==true){
            buttonClicked = false;
        }else{
            buttonClicked = true;
        }
    }
    return buttonClicked;
} //checa se o botão fornecido no parametro foi clicado, caso sim torna buttonClicked verdade

int menu(void)
{
    const int screenWidth = 1920; //tamanho da tela na horizontal
    const int screenHeight = 1080; //tamanho da tela na vertical 
    Color grassGreen = (Color){74, 163, 26, 255}; //cor para os nomes das opções
    Color polutedSky = (Color){121, 144, 160, 255}; //cor do ceu
    Color groungBrown = (Color){130, 68, 4, 255}; //cor do titulo/terra
 
    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe menu screen");
    Texture2D background = LoadTexture("assets/backGround.png");
    Texture2D frogMenu = LoadTexture("assets/sapoComeMenu.png"); //desenho do sapo que fica no menu

    SetTargetFPS(60);

    options play; options gamePlay; options backStory; options exit; options creditPage;
    //struct que pega as informações dos botões

    play.button = (Rectangle){ screenWidth - (325 + BUTTON_WIDTH), screenHeight / 2 - (5*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    //define o retangulo que representa o botão, todos tem o mesmo tamanho mas a coordenada do eixo y muda, um em cima do outro
    play.rectColor = polutedSky; //cor do retengulo, igual a do fundo e igual para todos
    play.optionColor = groungBrown; //cor do texto, igual para todos
    play.word = "Jogar"; //texto q fica no botão, indica a opção
    play.fontSize = 65; //tamanho das letras

    gamePlay.button = (Rectangle){ screenWidth - (325 + BUTTON_WIDTH), 25 + screenHeight / 2 - (3*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    gamePlay.rectColor = polutedSky;
    gamePlay.optionColor = groungBrown;
    gamePlay.word = "Como jogar?";
    gamePlay.fontSize = 65;

    backStory.button = (Rectangle){ screenWidth - (325 + BUTTON_WIDTH), 50 + screenHeight / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    backStory.rectColor = polutedSky;
    backStory.optionColor = groungBrown;
    backStory.word = "Backstory";
    backStory.fontSize = 65;

    exit.button = (Rectangle){ screenWidth - (325 + BUTTON_WIDTH), 75 + screenHeight / 2 + BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    exit.rectColor = polutedSky;
    exit.optionColor = groungBrown;
    exit.word = "Sair :(";
    exit.fontSize = 65;

    creditPage.button = (Rectangle){ screenWidth - (325 + BUTTON_WIDTH), 100 + screenHeight / 2 + 3*BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    creditPage.rectColor = polutedSky;
    creditPage.optionColor = groungBrown;
    creditPage.word = "Creditos";
    creditPage.fontSize = 65;

    bool buttonPlayClicked = false, buttonGamePlayClicked = false, buttonBackStoryClicked = false, buttonExitClicked = false, buttonCreditPageClicked = false;
    //variavel booleana pra verificar se alguma opção foi selecionada, so muda e fica verdadeira caso seja, quando se torna true a tela muda

     while (!WindowShouldClose())  
    {

        BeginDrawing();

            DrawTexture(background, 0, 0, WHITE);
            DrawTextLines(GetFontDefault(), "sapo-sopa sobe", (Vector2){960, 120}, 0, 170, 20, grassGreen, BLACK, 4); // titulo do jogo
            
            Rectangle proportionFrogMenu = { 0.0f, 0.0f, frogMenu.width, frogMenu.height };
            //retangulo que vai definir a proporção da imagem do sapo, nesse caso pega o sapo todo
            // Define the destination rectangle for drawing
            Rectangle whereFrogMenu = { 625, 750, frogMenu.width * 0.5, frogMenu.height * 0.5 };
            //define onde deve ser desenhado e o seu tamanho (escala de 0.6)
            Vector2 origin = { whereFrogMenu.width / 2, whereFrogMenu.height / 2 };
            //define o centro da imagem como sua origem
            DrawTexturePro(frogMenu, proportionFrogMenu, whereFrogMenu, origin, 0.0f, WHITE);
            //modo de densenho que realisa os ajustes necessários para que fique no quadrando inferior esquerdo da tela

            DrawMenuButton(play);
            DrawMenuButton(gamePlay);
            DrawMenuButton(backStory);
            DrawMenuButton(exit);
            DrawMenuButton(creditPage);
            //desenha os botões na tela usando a função

            checkOptionSelected(buttonPlayClicked, play);
            checkOptionSelected(buttonGamePlayClicked, gamePlay);
            checkOptionSelected(buttonBackStoryClicked, backStory);
            checkOptionSelected(buttonExitClicked, exit);
            checkOptionSelected(buttonCreditPageClicked, creditPage);
            //checa em loop se algum foi clicado

            //ADICIONAR A TROCA DE TELA
            
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(frogMenu);
    CloseWindow(); 

    return 0;
}
