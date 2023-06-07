all:
	gcc -o snakegame snake.c main.c -lncurses
run:
	./snakegame
