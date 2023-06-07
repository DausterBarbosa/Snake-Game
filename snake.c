#include <stdlib.h>

#include "snake.h"

Snake* criarSnake(){
	int sprites[] = {1, 2, 2, 3};

	Snake* head = NULL;

	Snake* tmp = NULL;

	for(int x = 0; x <= 4; x++){
		Snake* cell = (Snake*) malloc(sizeof(Snake));

		if(head == NULL){
			cell->posterior = NULL;
			cell->sprite = sprites[x];
			cell->x = 9;
			cell->y = 3;
			cell->anterior = NULL;

			head = cell;
			tmp = head;
		}
		else{
			tmp->anterior = cell;
			cell->posterior = tmp;
			cell->sprite = sprites[x];
			cell->x = tmp->x - 1;
			cell->y = tmp->y;
			cell->anterior = NULL;

			tmp = cell;
		}
	}

	return head;
}

char controlaDirecao(char direcaoNova, char direcaoAtual){
	if(direcaoNova == 'R' && direcaoAtual != 'L') direcaoAtual = 'R';
	else if(direcaoNova == 'L' && direcaoAtual != 'R') direcaoAtual = 'L';
	else if(direcaoNova == 'T' && direcaoAtual != 'D') direcaoAtual = 'T';
	else if(direcaoNova == 'D' && direcaoAtual != 'T') direcaoAtual = 'D';

	return direcaoAtual;
}

void atualizaPosicaoSnake(Snake* snake, char direcaoAtual){
	int coordx = 0, coordy = 0;

	if(direcaoAtual == 'T') coordy = -1;
	else if(direcaoAtual == 'D') coordy = 1;
	else if(direcaoAtual == 'R') coordx = 1;
	else if(direcaoAtual == 'L') coordx = -1;

	int tmpX1 = snake->x;
	int tmpY1 = snake->y;

	int tmpX2, tmpY2;

	snake->x += coordx;
	snake->y += coordy;

	while(snake->anterior != NULL){
		snake = snake->anterior;

		tmpX2 = snake->x;
		tmpY2 = snake->y;

		snake->x = tmpX1;
		snake->y = tmpY1;

		tmpX1 = tmpX2;
		tmpY1 = tmpY2;
	}
}

void moverSnake(Snake* snake, /*Fruta* fruta,*/char direcaoAtual, int telaLargura, int telaAltura){
	atualizaPosicaoSnake(snake, direcaoAtual);
}
