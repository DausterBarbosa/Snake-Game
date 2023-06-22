#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "fruit.h"

Fruit* criarFruta(){
	Fruit* fruit = (Fruit*) malloc(sizeof(Fruit));

	srand(time(NULL));

	fruit->x1 = (rand() % 20 - 10) * 10;
	fruit->y1 = (rand() % 20 - 10) * 10;
	fruit->x2 = fruit->x1 + 10;
	fruit->y2 = fruit->y1;
	fruit->x3 = fruit->x1 + 10;
	fruit->y3 = fruit->y1 + 10;
	fruit->x4 = fruit->x1;
	fruit->y4 = fruit->y1 + 10;

	return fruit;
}

void atualizarFruta(Fruit* fruit){
	fruit->x1 = (rand() % 20 - 10) * 10;
	fruit->y1 = (rand() % 20 - 10) * 10;
	fruit->x2 = fruit->x1 + 10;
	fruit->y2 = fruit->y1;
	fruit->x3 = fruit->x1 + 10;
	fruit->y3 = fruit->y1 + 10;
	fruit->x4 = fruit->x1;
	fruit->y4 = fruit->y1 + 10;
}

void aumentarSnake(Snake* snake, Fruit* fruit){
	Snake* newCell = (Snake*) malloc(sizeof(Snake));

	newCell->quad.x1 = snake->quad.x1;
	newCell->quad.y1 = snake->quad.y1;
	newCell->quad.x2 = snake->quad.x2;
	newCell->quad.y2 = snake->quad.y2;
	newCell->quad.x3 = snake->quad.x3;
	newCell->quad.y3 = snake->quad.y3;
	newCell->quad.x4 = snake->quad.x4;
	newCell->quad.y4 = snake->quad.y4;

	newCell->sprite = 9;

	snake->quad.x1 = fruit->x1;
	snake->quad.y1 = fruit->y1;
	snake->quad.x2 = fruit->x2;
	snake->quad.y2 = fruit->y2;
	snake->quad.x3 = fruit->x3;
	snake->quad.y3 = fruit->y3;
	snake->quad.x4 = fruit->x4;
	snake->quad.y4 = fruit->y4;

	snake->anterior->posterior = newCell;
	newCell->anterior = snake->anterior;
	newCell->posterior = snake;
	snake->anterior = newCell;
}

void comeuFruta(Snake* snake, Fruit* fruit){
	if(snake->quad.x1 == fruit->x1 &&  snake->quad.x2  == fruit->x2 && snake->quad.x3  == fruit->x3
	&& snake->quad.x4  == fruit->x4 && snake->quad.y1  == fruit->y1 && snake->quad.y2  == fruit->y2
	&& snake->quad.y3  == fruit->y3 && snake->quad.y4 == fruit->y4){
		aumentarSnake(snake, fruit);
		atualizarFruta(fruit);
	}
}
