#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
const char *tale;
}writtenStory; //ponteiro que aponta para a string de texto que vai ficar em cada um dos quadrinhos

void DrawSquareOne(){
    Texture2D squareOne = LoadTexture("assets/squareOne.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareOne.width, squareOne.height };
    Rectangle whereSquare = { 265, 275, squareOne.width * 0.25, squareOne.height * 0.25 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareOne, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

//as imagens diferentes dos quadrinhos, funções diferentes pq elas tem tamanhos e proporcoes diferentes
void DrawSquareTwo(){
    Texture2D squareTwo = LoadTexture("assets/squareTwo.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareTwo.width, squareTwo.height };
    Rectangle whereSquare = { 265, 275, squareTwo.width * 0.25, squareTwo.height * 0.25 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareTwo, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareThree(){
    Texture2D squareThree = LoadTexture("assets/squareThree.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareThree.width, squareThree.height };
    Rectangle whereSquare = { 265, 275, squareThree.width * 0.3, squareThree.height * 0.3 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareThree, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareFour(){
    Texture2D squareFour = LoadTexture("assets/squareFour.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareFour.width, squareFour.height };
    Rectangle whereSquare = { 265, 275, squareFour.width * 0.35, squareFour.height * 0.35 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareFour, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareFive(){
    Texture2D squareFive = LoadTexture("assets/squareFive.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareFive.width, squareFive.height };
    Rectangle whereSquare = { 400, 225, 800, 450 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareFive, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareSix(){
    Texture2D squareSix = LoadTexture("assets/squareSix.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareSix.width, squareSix.height };
    Rectangle whereSquare = { 400, 225, 800, 450 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareSix, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareSeven(){
    Texture2D squareSeven = LoadTexture("assets/squareSeven.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareSeven.width, squareSeven.height };
    Rectangle whereSquare = { 400, 225, 800, 450 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareSeven, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSquareEight(){
    Texture2D squareEight = LoadTexture("assets/squareEight.png");
    Rectangle proportionSquare = { 0.0f, 0.0f, squareEight.width, squareEight.height };
    Rectangle whereSquare = { 400, 225, 800, 450 };
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(squareEight, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSTory(writtenStory verse){
    DrawText(verse.tale, 200, 80, 30, WHITE);
} //escrever os textos

void backStory()
{
    const int screenWidth = 800; //tamanho da tela na horizontal
    const int screenHeight = 450; //tamanho da tela na vertical
    Color forestGreen = (Color){34, 139, 34, 255}; //cor para o fundo, não gostei do verde do raylib ai peguei essas coordenadas rgb na internet

    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe backstory");

    Texture2D squareOne = LoadTexture("assets/squareOne.png");
    Texture2D squareTwo = LoadTexture("assets/squareTwo.png");
    Texture2D squareThree = LoadTexture("assets/squareThree.png");
    Texture2D squareFour = LoadTexture("assets/squareFour.png");
    Texture2D squareFive = LoadTexture("assets/squareFive.png");
    Texture2D squareSix = LoadTexture("assets/squareSix.png");
    Texture2D squareSeven = LoadTexture("assets/squareSeven.png");
    Texture2D squareEight = LoadTexture("assets/squareEight.png");
    //desenhos dos quadrinhos
     
    SetTargetFPS(60);

    writtenStory taleOne, taleTwo, taleThree, taleFour, taleFive, taleSix, taleSeven, taleEight;
    //struct que pega o texto chamada para cada um dos quadrinhos

    taleOne.tale = "historia no quadrinho 1";
    taleTwo.tale = "historia no quadrinho 2";
    taleThree.tale = "historia no quadrinho 3";
    taleFour.tale = "historia no quadrinho 4";
    taleFive.tale = "historia no quadrinho 5";
    taleSix.tale = "historia no quadrinho 6";
    taleSeven.tale = "historia no quadrinho 7";
    taleEight.tale = "historia no quadrinho 8";
    //texto

    int squareCount = 1; //começa no quadrinho 1

    while (!WindowShouldClose())  
    {
        if(IsKeyPressed(KEY_SPACE)){
            squareCount++;
        } //passa o quadrinho quando o jogador aperta espaço
        
        BeginDrawing();

            ClearBackground(forestGreen);

            //abre um quadro diferente, na sequencia
            if(squareCount==1){ //mostra o quadrinho 1
                DrawSquareOne();
                DrawSTory(taleOne);
            }else if(squareCount==2){ //mostra o quadrinho 2
                DrawSquareTwo();
                DrawSTory(taleTwo);
            }else if(squareCount==3){ //mostra o quadrinho 3
                DrawSquareThree();
                DrawSTory(taleThree);
            }else if(squareCount==4){ //mostra o quadrinho 4
                DrawSquareFour();
                DrawSTory(taleFour);
            }else if(squareCount==5){ //mostra o quadrinho 5
                DrawSquareFive();
                DrawSTory(taleFive);
            }else if(squareCount==6){ //mostra o quadrinho 6
                DrawSquareSix();
                DrawSTory(taleSix);
            }else if(squareCount==7){ //mostra o quadrinho 7
                DrawSquareSeven();
                DrawSTory(taleSeven);
            }else if(squareCount==8){ //mostra o quadrinho 8
                DrawSquareEight();
                DrawSTory(taleEight);
            }else{
                //voltar para o menu
            }

        EndDrawing();
    }

    CloseWindow(); 

    UnloadTexture(squareOne);
    UnloadTexture(squareTwo);
    UnloadTexture(squareThree);
    UnloadTexture(squareFour);
    UnloadTexture(squareFive);
    UnloadTexture(squareSix);
    UnloadTexture(squareSeven);
    UnloadTexture(squareEight);

}
