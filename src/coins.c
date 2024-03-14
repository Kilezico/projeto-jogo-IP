#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "jogador.h"
#include "coins.h"

// Função para criar uma moeda
Coin CreateCoin(Vector2 position, Color color) {
    Coin coin;
    coin.position = position;
    coin.active = true;
    coin.color = color;
    return coin;
}

// Função para desenhar uma moeda na tela
void DrawCoin(Coin coin) {
    if (coin.active) {
        DrawCircleV(coin.position, 10, coin.color);
    }
}

// Função para calcular a distância entre dois pontos
float CalculateDistance(Vector2 playerPosition, Vector2 coinPosition) {
    // Calcula as diferenças nas coordenadas x e y
    float dx = coinPosition.x - playerPosition.x;
    float dy = coinPosition.y - playerPosition.y;

    // Calcula a distância euclidiana usando o teorema de Pitágoras
    float distance = sqrtf(dx * dx + dy * dy);

    return distance;
}

// Função para verificar a colisão entre o jogador e uma moeda
bool CheckCoinCollision(Player player, Coin coin) {
    // Define o raio do jogador
    float playerRadius = 20.0f;

    // Calcula a distância entre o jogador e a moeda
    float distance = CalculateDistance(player.position, coin.position);

    // Se a distância for menor que a soma dos raios do jogador e da moeda, houve colisão
    return distance < playerRadius + 10; // 10 é o raio da moeda
}

// Função para coletar uma moeda
void CollectCoin(Coin *coin, Player *player) {
    coin->active = false;
    player->coinCount++;
}

/* (Alterações na main)

#include "coins.h"

int main(){
    //-------Inicializacao-------
    
    // Inicializa as moedas
    const int numCoins = 5;
    Coin coins[numCoins];
    for (int i = 0; i < numCoins; i++) {
        coins[i] = CreateCoin((Vector2){GetRandomValue(50, 750), GetRandomValue(50, 400)}, GOLD);
    }

    //------Loop principal------
    while(!WindowShouldClose()){
        
        // Verifica a colisão e coleta de moedas
        for (int i = 0; i < numCoins; i++) {
            if (CheckCoinCollision(player, coins[i])) {
                CollectCoin(&coins[i]);
            }
        }

        // Desenha na tela        
        BeginDrawing();

            // Desenha as moedas
            for (int i = 0; i < numCoins; i++) {
            DrawCoin(coins[i]);
            }
            
        EndDrawing();
    }

    return 0;
}

*/
    
    

