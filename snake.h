#ifndef __SNAKE__GAME
#define __SNAKE__GAME

typedef struct snakeQuad SnakeQuad;

struct snakeQuad
{
  int x1;
  int y1;
  int x2;
  int y2;
  int x3;
  int y3;
  int x4;
  int y4;
};

typedef struct snake Snake;

struct snake
{
  Snake *posterior;
  int sprite;
  char direcao;
  SnakeQuad quad;
  Snake *anterior;
};

Snake *criarSnake();

char controlaDirecao(char direcaoNova, char direcaoAtual);

void moverSnake(Snake *snake, char direcaoAtual, int telaLargura, int telaAltura);

void atualizaSprite(Snake *snake);
#endif
