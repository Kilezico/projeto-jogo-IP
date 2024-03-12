#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
Texture2D image;
Rectangle proportionSquare
Rectangle whereSquare
}squareImages;

typedef struct{
const char *tale;
}writtenStory; //ponteiro que aponta para a string de texto que vai ficar em cada um dos quadrinhos

void DrawSquares(Texture2D image, Rectangle proportionSquare, Rectangle whereSquare){
    Vector2 origin = { whereSquare.width / 2, whereSquare.height / 2 };
    DrawTexturePro(image, proportionSquare, whereSquare, origin, 0.0f, WHITE);
}

void DrawSTory(writtenStory verse){
    DrawText(verse.tale, 650, 150, 65, WHITE);
}

int backStory(void)
{
    const int screenWidth = 1920; //tamanho da tela na horizontal
    const int screenHeight = 1080; //tamanho da tela na vertical
    Color forestGreen = (Color){34, 139, 34, 255}; //cor para o fundo, não gostei do verde do raylib ai peguei essas coordenadas rgb na internet

    InitWindow(screenWidth, screenHeight, "sapo-sopa sobe backstory");
     
    SetTargetFPS(60);

    squareImages One, Two, Three, Four, Five, Six, Seven, Eight;

    One.squareOne = LoadTexture("assets/squareOne.png");
    One.proportionSquare = { 0.0f, 0.0f, squareOne.width, squareOne.height };
    One.whereSquare = { 635, 660, squareOne.width * 0.6, squareOne.height * 0.6 };

    Two.squareTwo = LoadTexture("assets/squareTwo.png");
    Two.proportionSquare = { 0.0f, 0.0f, squareTwo.width, squareTwo.height };
    Two.whereSquare = { 635, 635, squareTwo.width * 0.6, squareTwo.height * 0.6 };

    Three.squareThree = LoadTexture("assets/squareThree.png");
    Three.proportionSquare = { 0.0f, 0.0f, squareThree.width, squareThree.height };
    Three.whereSquare = { 635, 660, squareThree.width * 0.7, squareThree.height * 0.7 };

    Four.squareFour = LoadTexture("assets/squareFour.png");
    Four.proportionSquare = { 0.0f, 0.0f, squareFour.width, squareFour.height };
    Four.whereSquare = { 635, 660, squareFour.width * 0.85, squareFour.height * 0.85 };

    Five.squareFive = LoadTexture("assets/squareFive.png");
    Five.proportionSquare = { 0.0f, 0.0f, squareFive.width, squareFive.height };
    Five.whereSquare = { 960, 540, 1920, 1080 };

    Six.squareSix = LoadTexture("assets/squareSix.png");
    Six.proportionSquare = { 0.0f, 0.0f, squareSix.width, squareSix.height };
    Six.whereSquare = { 960, 540, 1920, 1080 };

    Seven.squareSeven = LoadTexture("assets/squareSeven.png");
    Seven.proportionSquare = { 0.0f, 0.0f, squareSeven.width, squareSeven.height };
    Seven.whereSquare = { 960, 540, 1920, 1080 };

    Eight.squareEight = LoadTexture("assets/squareEight.png");
    Eight.proportionSquare = { 0.0f, 0.0f, squareEight.width, squareEight.height };
    Eight.whereSquare = { 960, 540, 1920, 1080 };

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

            if(squareCount==1){ //mostra o quadrinho 1
                DrawSquares(One.squareOne, One.proportionSquare, One.whereSquare);
                DrawSTory(taleOne);
            }else if(squareCount==2){ //mostra o quadrinho 2
                DrawSquares(Two.squareOne, Two.proportionSquare, Two.whereSquare);
                DrawSTory(taleTwo);
            }else if(squareCount==3){ //mostra o quadrinho 3
                DrawSquares(Three.squareOne, Three.proportionSquare, Three.whereSquare);
                DrawSTory(taleThree);
            }else if(squareCount==4){ //mostra o quadrinho 4
                DrawSquares(Four.squareOne, Four.proportionSquare, Four.whereSquare);
                DrawSTory(taleFour);
            }else if(squareCount==5){ //mostra o quadrinho 5
                DrawSquares(Five.squareOne, Five.proportionSquare, Five.whereSquare);
                DrawSTory(taleFive);
            }else if(squareCount==6){ //mostra o quadrinho 6
                DrawSquares(Six.squareOne, Six.proportionSquare, Six.whereSquare);
                DrawSTory(taleSix);
            }else if(squareCount==7){ //mostra o quadrinho 7
                DrawSquares(Seven.squareOne, Seven.proportionSquare, Seven.whereSquare);
                DrawSTory(taleSeven);
            }else if(squareCount==8){ //mostra o quadrinho 8
                DrawSquares(Eight.squareOne, Eight.proportionSquare, Eight.whereSquare);
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

    return 0;
}
