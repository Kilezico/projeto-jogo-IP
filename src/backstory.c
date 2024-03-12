#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
Texture2D image;
Rectangle proportionSquare;
Rectangle whereSquare;
}squareImages;

typedef struct{
const char *tale;
}writtenStory; //ponteiro que aponta para a string de texto que vai ficar em cada um dos quadrinhos

void DrawSTory(writtenStory verse){
    DrawText(verse.tale, 650, 150, 65, WHITE);
}

bool BacktToMenuPressed(bool menuButton, Rectangle button) {
    if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        menuButton = true;
    } //checa se o cursor ta em cima do botão e se foi pressioanado
    return menuButton;
}

GameScreen backStoryDraw(GameScreen screen)
{
    bool goBacktoMenu = false;
    
    const int screenWidth = 1920; //tamanho da tela na horizontal
    const int screenHeight = 1080; //tamanho da tela na vertical
    Color forestGreen = (Color){34, 139, 34, 255}; //cor para o fundo, não gostei do verde do raylib ai peguei essas coordenadas rgb na internet
    Color waterBlue = (Color){63, 145, 182, 255};
     
    SetTargetFPS(60);

    squareImages One, Two, Three, Four, Five, Six, Seven, Eight;

    One.image = LoadTexture("assets/squareOne.png");
    One.proportionSquare = (Rectangle) { 0.0f, 0.0f, One.image.width, One.image.height };
    One.whereSquare = (Rectangle) { 635, 660, One.image.width * 0.6, One.image.height * 0.6 };

    Two.image = LoadTexture("assets/squareTwo.png");
    Two.proportionSquare = (Rectangle) { 0.0f, 0.0f, Two.image.width, Two.image.height };
    Two.whereSquare = (Rectangle) { 635, 635, Two.image.width * 0.6, Two.image.height * 0.6 };

    Three.image = LoadTexture("assets/squareThree.png");
    Three.proportionSquare = (Rectangle) { 0.0f, 0.0f, Three.image.width, Three.image.height };
    Three.whereSquare = (Rectangle) { 635, 660, Three.image.width * 0.7, Three.image.height * 0.7 };

    Four.image = LoadTexture("assets/squareFour.png");
    Four.proportionSquare = (Rectangle) { 0.0f, 0.0f, Four.image.width, Four.image.height };
    Four.whereSquare = (Rectangle) { 635, 660, Four.image.width * 0.85, Four.image.height * 0.85 };

    Five.image = LoadTexture("assets/squareFive.png");
    Five.proportionSquare = (Rectangle) { 0.0f, 0.0f, Five.image.width, Five.image.height };
    Five.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Six.image = LoadTexture("assets/squareSix.png");
    Six.proportionSquare = (Rectangle) { 0.0f, 0.0f, Six.image.width, Six.image.height };
    Six.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Seven.image = LoadTexture("assets/squareSeven.png");
    Seven.proportionSquare = (Rectangle) { 0.0f, 0.0f, Seven.image.width, Seven.image.height };
    Seven.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Eight.image = LoadTexture("assets/squareEight.png");
    Eight.proportionSquare = (Rectangle) { 0.0f, 0.0f, Eight.image.width, Eight.image.height };
    Eight.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };
    
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

    while (goBacktoMenu!=true)  
    {
        if(IsKeyPressed(KEY_SPACE)){
            squareCount++;
        } //passa o quadrinho quando o jogador aperta espaço
        
        BeginDrawing();

            ClearBackground(forestGreen);

            if(squareCount==1){ //mostra o quadrinho 1
                Vector2 origin = { One.whereSquare.width / 2, One.whereSquare.height / 2 };
                DrawTexturePro(One.image, One.proportionSquare, One.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleOne);
            }else if(squareCount==2){ //mostra o quadrinho 2
                Vector2 origin = { Two.whereSquare.width / 2, Two.whereSquare.height / 2 };
                DrawTexturePro(Two.image, Two.proportionSquare, Two.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleTwo);
            }else if(squareCount==3){ //mostra o quadrinho 3
                Vector2 origin = { Three.whereSquare.width / 2, Three.whereSquare.height / 2 };
                DrawTexturePro(Three.image, Three.proportionSquare, Three.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleThree);
            }else if(squareCount==4){ //mostra o quadrinho 4
                Vector2 origin = { Four.whereSquare.width / 2, Four.whereSquare.height / 2 };
                DrawTexturePro(Four.image, Four.proportionSquare, Four.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleFour);
            }else if(squareCount==5){ //mostra o quadrinho 5
                Vector2 origin = { Five.whereSquare.width / 2, Five.whereSquare.height / 2 };
                DrawTexturePro(Five.image, Five.proportionSquare, Five.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleFive);
            }else if(squareCount==6){ //mostra o quadrinho 6
                Vector2 origin = { Six.whereSquare.width / 2, Six.whereSquare.height / 2 };
                DrawTexturePro(Six.image, Six.proportionSquare, Six.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleSix);
            }else if(squareCount==7){ //mostra o quadrinho 7
                Vector2 origin = { Seven.whereSquare.width / 2, Seven.whereSquare.height / 2 };
                DrawTexturePro(Seven.image, Seven.proportionSquare, Seven.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleSeven);
            }else if(squareCount==8){ //mostra o quadrinho 8
                Vector2 origin = { Eight.whereSquare.width / 2, Eight.whereSquare.height / 2 };
                DrawTexturePro(Eight.image, Eight.proportionSquare, Eight.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleEight);
                Rectangle backToMenu = (Rectangle){ 20, 30, 450, 200 };
                DrawRectangleRec(backToMenu, waterBlue);
                DrawText("sapo-sopa sobe", 25, 35, 50, BLACK);
                BacktToMenuPressed(goBacktoMenu, backToMenu);
                if(goBacktoMenu==true){//vai fazer o while parar
                    gameState = MENUS;
                }
            }

        EndDrawing();
    }

    UnloadTexture(One.image);
    UnloadTexture(Two.image);
    UnloadTexture(Three.image);
    UnloadTexture(Four.image);
    UnloadTexture(Five.image);
    UnloadTexture(Six.image);
    UnloadTexture(Seven.image);
    UnloadTexture(Eight.image);

    return screen;
}
