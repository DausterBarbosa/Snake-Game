#ifndef __SNAKE__FRUIT
#define __SNAKE__FRUIT

#include "snake.h"

typedef struct fruit Fruit;

struct fruit
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

Fruit *criarFruta();

void comeuFruta(Snake *snake, Fruit *fruit);

#endif
