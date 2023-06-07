#ifndef __SNAKE__GAME
#define __SNAKE__GAME

typedef struct snake Snake;

struct snake{
	Snake* posterior;
	int sprite;
	int x;
	int y;
	Snake* anterior;
};

Snake* criarSnake();

char controlaDirecao(char direcaoNova, char direcaoAtual);

void moverSnake(Snake* snake, char direcaoAtual, int telaLargura, int telaAltura);

#endif
