#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BUTTON_WIDTH 200 //tamanho dos botões (horizontal) 
#define BUTTON_HEIGHT 50 //tamanho dos botões (vertical) 

typedef struct {
    Rectangle button;
    Color rectColor;
    Color optionColor;
    const char *word;
    int fontSize;
} options; //struct pras informações de cada um dos cinco botões (jogar, backstory, como jogar, creditos e sair)

void DrawMenuButton(options choice) {

    DrawRectangleRec(choice.button, choice.rectColor);
    DrawText(choice.word, (int)choice.button.x + 10, (int)choice.button.y + 10, choice.fontSize, choice.optionColor);
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

void menu()
{
    const int screenWidth = 800; //tamanho da tela na horizontal
    const int screenHeight = 450; //tamanho da tela na vertical 
    Color forestGreen = (Color){34, 139, 34, 255}; //cor para os nomes das opções
 
    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe menu screen");
    Texture2D frogMenu = LoadTexture("assets/sapoComeMenu.png"); //desenho do sapo que fica no menu

    SetTargetFPS(60);

    options play; options gamePlay; options backStory; options exit; options creditPage;
    //struct que pega as informações dos botões

    play.button = (Rectangle){ screenWidth - (80 + BUTTON_WIDTH), screenHeight / 2 - (5*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    //define o retangulo que representa o botão, todos tem o mesmo tamanho mas a coordenada do eixo y muda, um em cima do outro
    play.rectColor = SKYBLUE; //cor do retengulo, igual a do fundo e igual para todos
    play.optionColor = forestGreen; //cor do texto, igual para todos
    play.word = "Jogar"; //texto q fica no botão, indica a opção
    play.fontSize = 30; //tamanho das letras

    gamePlay.button = (Rectangle){ screenWidth - (80 + BUTTON_WIDTH), 10 + screenHeight / 2 - (3*BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
    gamePlay.rectColor = SKYBLUE;
    gamePlay.optionColor = forestGreen;
    gamePlay.word = "Como jogar?";
    gamePlay.fontSize = 30;

    backStory.button = (Rectangle){ screenWidth - (80 + BUTTON_WIDTH), 20 + screenHeight / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    backStory.rectColor = SKYBLUE;
    backStory.optionColor = forestGreen;
    backStory.word = "Backstory";
    backStory.fontSize = 30;

    exit.button = (Rectangle){ screenWidth - (80 + BUTTON_WIDTH), 30 + screenHeight / 2 + BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    exit.rectColor = SKYBLUE;
    exit.optionColor = forestGreen;
    exit.word = "Sair :(";
    exit.fontSize = 30;

    creditPage.button = (Rectangle){ screenWidth - (80 + BUTTON_WIDTH), 40 + screenHeight / 2 + 3*BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    creditPage.rectColor = SKYBLUE;
    creditPage.optionColor = forestGreen;
    creditPage.word = "Creditos";
    creditPage.fontSize = 30;

    bool buttonPlayClicked = false, buttonGamePlayClicked = false, buttonBackStoryClicked = false, buttonExitClicked = false, buttonCreditPageClicked = false;
    //variavel booleana pra verificar se alguma opção foi selecionada, so muda e fica verdadeira caso seja, quando se torna true a tela muda

     while (!WindowShouldClose())  
    {

        BeginDrawing();

            ClearBackground(SKYBLUE);
            DrawText("sapo-sopa sobe", 115, 15, 70, forestGreen); //titulo do jogo
            
            Rectangle proportionFrogMenu = { 0.0f, 0.0f, frogMenu.width, frogMenu.height };
            //retangulo que vai definir a proporção da imagem do sapo, nesse caso pega o sapo todo
            // Define the destination rectangle for drawing
            Rectangle whereFrogMenu = { 265, 275, frogMenu.width * 0.25, frogMenu.height * 0.25 };
            //define onde deve ser desenhado e o seu tamanho (escala de 0.25)
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

    UnloadTexture(frogMenu);
    CloseWindow(); 
}
