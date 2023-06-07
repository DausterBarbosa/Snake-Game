#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "snake.h"

#define LINHAS 30
#define COLUNAS 60

void inicializaMatriz();
void adicionaSnakeNaMatriz();
void mostraMatriz();
void manipularMatriz();
int matriz[LINHAS][COLUNAS];

int main()
{
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  char direcaoAtual = 'R';

  Snake *snake = criarSnake();

  manipularMatriz(snake);

  while (1)
  {
    int tecla = getch();

    if (tecla == KEY_LEFT)
    {
      direcaoAtual = controlaDirecao('L', direcaoAtual);
    }
    else if (tecla == KEY_RIGHT)
    {
      direcaoAtual = controlaDirecao('R', direcaoAtual);
    }
    else if (tecla == KEY_UP)
    {
      direcaoAtual = controlaDirecao('T', direcaoAtual);
    }
    else if (tecla == KEY_DOWN)
    {
      direcaoAtual = controlaDirecao('D', direcaoAtual);
    }

    for (int x = 0; x < 90000000; x++)
      ;
    clear();
    moverSnake(snake, direcaoAtual, LINHAS, COLUNAS);
    manipularMatriz(snake);
  }
}

void manipularMatriz(Snake *snake)
{
  inicializaMatriz();
  adicionaSnakeNaMatriz(snake);
  mostraMatriz();
}

void inicializaMatriz()
{
  for (int x = 0; x < LINHAS; x++)
  {
    for (int y = 0; y < COLUNAS; y++)
    {
      matriz[x][y] = 0;
    }
  }
}

void adicionaSnakeNaMatriz(Snake *snake)
{
  while (snake->anterior != NULL)
  {
    matriz[snake->y][snake->x] = snake->sprite;

    snake = snake->anterior;
  }
}

void mostraMatriz()
{
  for (int x = 0; x < LINHAS; x++)
  {
    for (int y = 0; y < COLUNAS; y++)
    {
      printw("%d", matriz[x][y]);
    }
    printw("\n");
  }
}
