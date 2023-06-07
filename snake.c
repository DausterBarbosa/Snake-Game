#include <stdlib.h>

#include "snake.h"

Snake *criarSnake()
{
  int sprites[] = {2, 9, 9, 8};

  Snake *head = NULL;

  Snake *tmp = NULL;

  for (int x = 0; x <= 4; x++)
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

  while (snake->anterior != NULL)
  {
    snake = snake->anterior;

    tmpQuad2 = snake->quad;
    snake->quad = tmpQuad1;

    tmpQuad1 = tmpQuad2;
  }
}

void moverSnake(Snake *snake, /*Fruta* fruta,*/ char direcaoAtual, int telaLargura, int telaAltura)
{
  atualizaPosicaoSnake(snake, direcaoAtual);
}
