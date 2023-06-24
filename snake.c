#include <stdlib.h>

#include <stdio.h>

#include "snake.h"

Snake *criarSnake()
{
  int sprites[] = {2, 9, 8};

  Snake *head = NULL;

  Snake *tmp = NULL;

  for (int x = 0; x < 3; x++)
  {

    Snake *cell = (Snake *)malloc(sizeof(Snake));

    if (head == NULL)
    {
      cell->posterior = NULL;
      cell->sprite = sprites[x];
      cell->quad.x1 = 0;
      cell->quad.y1 = 0;
      cell->quad.x2 = 10;
      cell->quad.y2 = 0;
      cell->quad.x3 = 10;
      cell->quad.y3 = 10;
      cell->quad.x4 = 0;
      cell->quad.y4 = 10;
      cell->anterior = NULL;

      head = cell;
      tmp = head;
    }
    else
    {
      tmp->anterior = cell;
      cell->posterior = tmp;
      cell->sprite = sprites[x];

      cell->quad.x1 = tmp->quad.x1 - 10;
      cell->quad.x2 = tmp->quad.x2 - 10;
      cell->quad.x3 = tmp->quad.x3 - 10;
      cell->quad.x4 = tmp->quad.x4 - 10;
      cell->quad.y1 = tmp->quad.y1;
      cell->quad.y2 = tmp->quad.y2;
      cell->quad.y3 = tmp->quad.y3;
      cell->quad.y4 = tmp->quad.y4;
      cell->anterior = NULL;

      tmp = cell;
    }
  }

  return head;
}

char controlaDirecao(char direcaoNova, char direcaoAtual)
{
  if (direcaoNova == 'R' && direcaoAtual != 'L')
    direcaoAtual = 'R';
  else if (direcaoNova == 'L' && direcaoAtual != 'R')
    direcaoAtual = 'L';
  else if (direcaoNova == 'T' && direcaoAtual != 'D')
    direcaoAtual = 'T';
  else if (direcaoNova == 'D' && direcaoAtual != 'T')
    direcaoAtual = 'D';

  return direcaoAtual;
}

void atualizaPosicaoSnake(Snake *snake, char direcaoAtual)
{
  int coordx = 0, coordy = 0;
  int count = 1;

  Snake *secondBody = snake->anterior;

  if (direcaoAtual == 'T')
    coordy = +10;
  else if (direcaoAtual == 'D')
    coordy = -10;
  else if (direcaoAtual == 'R')
    coordx = +10;
  else if (direcaoAtual == 'L')
    coordx = -10;

  SnakeQuad tmpQuad1 = snake->quad;

  SnakeQuad tmpQuad2;

  snake->quad.x1 += coordx;
  snake->quad.x2 += coordx;
  snake->quad.x3 += coordx;
  snake->quad.x4 += coordx;
  snake->quad.y1 += coordy;
  snake->quad.y2 += coordy;
  snake->quad.y3 += coordy;
  snake->quad.y4 += coordy;

  switch (direcaoAtual)
  {
  case 'T':
    snake->sprite = 1;
    break;

  case 'D':
    snake->sprite = 0;
    break;

  case 'L':
    snake->sprite = 3;
    break;

  case 'R':
    snake->sprite = 2;
    break;

  default:
    break;
  }

  while (snake->anterior != NULL)
  {
    snake = snake->anterior;

    tmpQuad2 = snake->quad;
    snake->quad = tmpQuad1;

    tmpQuad1 = tmpQuad2;
  }

  do
  {
    atualizaSprite(secondBody);
    secondBody = secondBody->anterior;
  } while (secondBody != NULL);
}

int verificaAutoColisao(Snake* snake){
	Snake* head = snake;
	Snake* body = head->anterior;

	do{
		if(head->quad.x1 == body->quad.x1 && head->quad.x2 == body->quad.x2 && head->quad.x3 == body->quad.x3 && head->quad.x4 == body->quad.x4 &&
		head->quad.y1 == body->quad.y1 && head->quad.y2 == body->quad.y2 && head->quad.y3 == body->quad.y3 && head->quad.y4 == body->quad.y4){
			return 0;
		}

		body = body->anterior;
	}while(body->anterior != NULL);

	return 1;
}

int moverSnake(Snake *snake, /*Fruta* fruta,*/ char direcaoAtual, int telaEsquerda, int telaDireita, int telaSuperior, int telaInferior)
{
  Snake *head = snake;
  atualizaPosicaoSnake(snake, direcaoAtual);

  if(verificaAutoColisao(snake) == 0){
	return 0;
  }

  if (head->quad.x2 >= telaDireita + 1 || head->quad.x1 <= telaEsquerda - 1)
    return 0;

  if (head->quad.y1 >= telaSuperior || head->quad.y1 <= telaInferior - 1)
    return 0;

  return 1;
}

void atualizaSprite(Snake *snake)
{

  char posicaoAnterior, posicaoPosterior;

  if (snake->anterior != NULL && snake->quad.x1 > snake->anterior->quad.x1)
    posicaoAnterior = 'L';

  if (snake->anterior != NULL && snake->quad.x1 < snake->anterior->quad.x1)
    posicaoAnterior = 'R';

  if (snake->anterior != NULL && snake->quad.y1 > snake->anterior->quad.y1)
    posicaoAnterior = 'D';

  if (snake->anterior != NULL && snake->quad.y1 < snake->anterior->quad.y1)
    posicaoAnterior = 'T';

  if (snake->quad.x1 > snake->posterior->quad.x1)
    posicaoPosterior = 'L';

  if (snake->quad.x1 < snake->posterior->quad.x1)
    posicaoPosterior = 'R';

  if (snake->quad.y1 > snake->posterior->quad.y1)
    posicaoPosterior = 'D';

  if (snake->quad.y1 < snake->posterior->quad.y1)
    posicaoPosterior = 'T';

  if (snake->anterior != NULL)
  {
    if (posicaoAnterior == 'T' && posicaoPosterior == 'L')
      snake->sprite = 12;

    if (posicaoAnterior == 'L' && posicaoPosterior == 'T')
      snake->sprite = 12;

    if (posicaoAnterior == 'T' && posicaoPosterior == 'R')
      snake->sprite = 11;

    if (posicaoAnterior == 'R' && posicaoPosterior == 'T')
      snake->sprite = 11;

    if (posicaoAnterior == 'D' && posicaoPosterior == 'L')
      snake->sprite = 14;

    if (posicaoAnterior == 'L' && posicaoPosterior == 'D')
      snake->sprite = 14;

    if (posicaoAnterior == 'D' && posicaoPosterior == 'R')
      snake->sprite = 13;

    if (posicaoAnterior == 'R' && posicaoPosterior == 'D')
      snake->sprite = 13;

    if (posicaoAnterior == 'D' && posicaoPosterior == 'T')
      snake->sprite = 10;

    if (posicaoAnterior == 'T' && posicaoPosterior == 'D')
      snake->sprite = 10;

    if (posicaoAnterior == 'L' && posicaoPosterior == 'R')
      snake->sprite = 9;

    if (posicaoAnterior == 'R' && posicaoPosterior == 'L')
      snake->sprite = 9;
  }
  else
  {
    if (posicaoPosterior == 'T')
      snake->sprite = 5;

    if (posicaoPosterior == 'D')
      snake->sprite = 6;

    if (posicaoPosterior == 'L')
      snake->sprite = 7;

    if (posicaoPosterior == 'R')
      snake->sprite = 8;
  }
}
