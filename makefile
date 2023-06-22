all:
	gcc -o snakeGame snake.c snakeGame.c fruit.c -lglut -lGLU -lGL -lm
run:
	./snakeGame
