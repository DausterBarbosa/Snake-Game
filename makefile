all:
	gcc -o snakeGame snake.c snakeGame.c -lglut -lGLU -lGL -lm
run:
	./snakeGame
