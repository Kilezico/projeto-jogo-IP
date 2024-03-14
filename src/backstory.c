#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "telas.h"

typedef struct{
Texture2D image;
Rectangle proportionSquare;
Rectangle whereSquare;
}squareImages;

typedef struct{
const char *tale;
}writtenStory; //ponteiro que aponta para a string de texto que vai ficar em cada um dos quadrinhos

void DrawSTory(writtenStory verse, Font fonte){
    // DrawText(verse.tale, 650, 150, 65, WHITE);
    DrawTextEx(fonte, verse.tale, (Vector2){650, 150}, 65, 0, WHITE);
}

bool BackToMenuPressedBS(bool menuButton, Rectangle button) {
    if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        menuButton = true;
    } //checa se o cursor ta em cima do botão e se foi pressioanado
    return menuButton;
}

GameScreen backStoryDraw(GameScreen *screen, Font fonte)
{
    bool goBacktoMenu = false;
    
    //const int screenWidth = GetScreenWidth(); //tamanho da tela na horizontal
    //const int screenHeight = GetScreenHeight(); //tamanho da tela na vertical
    Color forestGreen = (Color){34, 139, 34, 255}; //cor para o fundo, não gostei do verde do raylib ai peguei essas coordenadas rgb na internet
    Color waterBlue = (Color){63, 145, 182, 255};
     
    squareImages One, Two, Three, Four, Five, Six, Seven, Eight;

    One.image = LoadTexture("assets/squareOne.PNG");
    One.proportionSquare = (Rectangle) { 0.0f, 0.0f, One.image.width, One.image.height };
    One.whereSquare = (Rectangle) { 635, 660, One.image.width * 0.6, One.image.height * 0.6 };

    Two.image = LoadTexture("assets/squareTwo.PNG");
    Two.proportionSquare = (Rectangle) { 0.0f, 0.0f, Two.image.width, Two.image.height };
    Two.whereSquare = (Rectangle) { 635, 635, Two.image.width * 0.6, Two.image.height * 0.6 };

    Three.image = LoadTexture("assets/squareThree.PNG");
    Three.proportionSquare = (Rectangle) { 0.0f, 0.0f, Three.image.width, Three.image.height };
    Three.whereSquare = (Rectangle) { 635, 660, Three.image.width * 0.7, Three.image.height * 0.7 };

    Four.image = LoadTexture("assets/squareFour.PNG");
    Four.proportionSquare = (Rectangle) { 0.0f, 0.0f, Four.image.width, Four.image.height };
    Four.whereSquare = (Rectangle) { 635, 660, Four.image.width * 0.85, Four.image.height * 0.85 };

    Five.image = LoadTexture("assets/squareFive.PNG");
    Five.proportionSquare = (Rectangle) { 0.0f, 0.0f, Five.image.width, Five.image.height };
    Five.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Six.image = LoadTexture("assets/squareSix.PNG");
    Six.proportionSquare = (Rectangle) { 0.0f, 0.0f, Six.image.width, Six.image.height };
    Six.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Seven.image = LoadTexture("assets/squareSeven.PNG");
    Seven.proportionSquare = (Rectangle) { 0.0f, 0.0f, Seven.image.width, Seven.image.height };
    Seven.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };

    Eight.image = LoadTexture("assets/squareEight.PNG");
    Eight.proportionSquare = (Rectangle) { 0.0f, 0.0f, Eight.image.width, Eight.image.height };
    Eight.whereSquare = (Rectangle) { 960, 540, 1920, 1080 };
    
    writtenStory taleOne, taleTwo, taleThree, taleFour, taleFive, taleSix, taleSeven, taleEight;
    //struct que pega o texto chamada para cada um dos quadrinhos

    taleOne.tale = "Era uma vez uma lagoa, com muita biodiversividade.\n\n\n\nLá moravam muitos sapinhos, mas entre eles estava\n\n\n\npara nascer um muito especial: Sapo-Sopa.";
    taleTwo.tale = "Sapo-Sopa nasceu e passou a viver muito feliz com\n\n\n\nseus irmãos girinos. Porém,\n\n\n\nalgo devastador estava prestes a ocorrer.";
    taleThree.tale = "Com o aumento do aquecimento global,\n\n\n\nas geleiras foram derretendo.\n\n\n\nFazendo assim o nível da água subir mais e mais.";
    taleFour.tale = "Na medida que cresceu,\n\n\n\nSapo-Sopa assistiu sua lagoa encher cada vez mais rápido.";
    taleFive.tale = "Até que um dia, a lagoa de Sapo-Sopa\n\n\n\nfoi invadida pelo mar, obrigando Sapo-Sopa a pular por aí,\n\n\n\nfugindo da água salgada (sal mata sapo).";
    taleSix.tale = "Agora, nosso querido sapo está fadado a pular\n\n\n\nde vitória-régia em vitória-régia pelo resto da sua vida,\n\n\n\npara fugir da seleção natural.";
    taleSeven.tale = "E para ter energia para continuar pulando,\n\n\n\nele fica sempre a procura de moscas para devorar.";
    taleEight.tale = "Ajude Sapo-Sopa a sobreviver os terríveis impactos dos\n\n\n\nseres humanos na Terra (e a comer muitas mosquinhas).";
    //texto

    int squareCount = 1; //começa no quadrinho 1

    // Mouse mosquinha
    Texture2D mosquinha = LoadTexture("assets/mosquinha.PNG");

    while (goBacktoMenu!=true)  
    {
        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)){
            squareCount++;
            if (squareCount > 8) squareCount = 1;
        } //passa o quadrinho quando o jogador aperta espaço
        
        BeginDrawing();

            ClearBackground(forestGreen);

            if(squareCount==1){ //mostra o quadrinho 1
                Vector2 origin = { One.whereSquare.width / 2, One.whereSquare.height / 2 };
                DrawTexturePro(One.image, One.proportionSquare, One.whereSquare, origin, 0.0f, WHITE);
                DrawSTory(taleOne, fonte);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
            }else if(squareCount==2){ //mostra o quadrinho 2
                Vector2 origin = { Two.whereSquare.width / 2, Two.whereSquare.height / 2 };
                DrawTexturePro(Two.image, Two.proportionSquare, Two.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleTwo, fonte);
            }else if(squareCount==3){ //mostra o quadrinho 3
                Vector2 origin = { Three.whereSquare.width / 2, Three.whereSquare.height / 2 };
                DrawTexturePro(Three.image, Three.proportionSquare, Three.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleThree, fonte);
            }else if(squareCount==4){ //mostra o quadrinho 4
                Vector2 origin = { Four.whereSquare.width / 2, Four.whereSquare.height / 2 };
                DrawTexturePro(Four.image, Four.proportionSquare, Four.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleFour, fonte);
            }else if(squareCount==5){ //mostra o quadrinho 5
                Vector2 origin = { Five.whereSquare.width / 2, Five.whereSquare.height / 2 };
                DrawTexturePro(Five.image, Five.proportionSquare, Five.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleFive, fonte);
            }else if(squareCount==6){ //mostra o quadrinho 6
                Vector2 origin = { Six.whereSquare.width / 2, Six.whereSquare.height / 2 };
                DrawTexturePro(Six.image, Six.proportionSquare, Six.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleSix, fonte);
            }else if(squareCount==7){ //mostra o quadrinho 7
                Vector2 origin = { Seven.whereSquare.width / 2, Seven.whereSquare.height / 2 };
                DrawTexturePro(Seven.image, Seven.proportionSquare, Seven.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para continuar...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleSeven, fonte);
            }else if(squareCount>=8){ //mostra o quadrinho 8
                Vector2 origin = { Eight.whereSquare.width / 2, Eight.whereSquare.height / 2 };
                DrawTexturePro(Eight.image, Eight.proportionSquare, Eight.whereSquare, origin, 0.0f, WHITE);
                DrawTextPro(fonte, "(Aperte ESPAÇO para rever a história...)", (Vector2) {38, GetScreenHeight()/1.1}, (Vector2) {0,0}, 0, 50 , 0 , ORANGE);
                DrawSTory(taleEight, fonte);
                Rectangle backToMenu = (Rectangle){ 20, 30, 450, 200 };
                DrawRectangleRec(backToMenu, waterBlue);
                // DrawText("sapo-sopa sobe", 25, 35, 50, BLACK);
                DrawTextEx(fonte, "menu", (Vector2){25, 35}, 50, 0, BLACK);
                goBacktoMenu = BackToMenuPressedBS(goBacktoMenu, backToMenu);
                if(goBacktoMenu==true){//vai fazer o while parar
                    *screen = MENUS;
                }
            }
            DrawTexturePro(mosquinha, (Rectangle){0, 0, mosquinha.width, mosquinha.height},
            (Rectangle){GetMousePosition().x, GetMousePosition().y, 40, 40}, (Vector2){20, 20}, 0, WHITE);

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
    UnloadTexture(mosquinha);

    return *screen;
}
