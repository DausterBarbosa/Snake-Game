#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "stb_image.h"
#include "stb_truetype.h"
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "snake.h"
#include "fruit.h"

Fruit *fruit;

Snake *snake;

GLuint textureIDs[20];
GLuint bgID1, bgID2;
int gameState = 2;
char direcao = 'R';
int sprite = 0;
int delay = 120;
void resetGame()
{
  snake = criarSnake();
  fruit = criarFruta();
  direcao = 'R';
}

void screenUpdate(int value)
{
  if (value == 1)
  {
    comeuFruta(snake, fruit);
    int result = moverSnake(snake, direcao, -100, 100, 100, -100);

    if (result == 0)
      gameState = 0;

    glutPostRedisplay();
  }

  glutTimerFunc(delay, screenUpdate, gameState);
}

void loadBackground()
{
  int pattern = 0;

  for (int i = -100; i < 100; i += 10)
  {
    for (int j = -100; j < 100; j += 10)
    {
      if (pattern == 0)
      {
        glBindTexture(GL_TEXTURE_2D, textureIDs[15]);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(j, i);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(j + 10, i);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(j + 10, i + 10);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(j, i + 10);
        glEnd();
        pattern = 1;
      }
      else
      {
        glBindTexture(GL_TEXTURE_2D, textureIDs[16]);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(j, i);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(j + 10, i);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(j + 10, i + 10);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(j, i + 10);
        glEnd();
        pattern = 0;
      }
    }

    if (pattern == 1)
      pattern = 0;
    else
      pattern = 1;
  }
}

void loadTexture(const char *imagePath, int textureIndex)
{
  // Carrega a imagem usando o stb_image
  int width, height;
  unsigned char *data = stbi_load(imagePath, &width, &height, NULL, STBI_rgb_alpha);
  if (!data)
  {
    printf("Falha ao carregar a imagem\n");
    return;
  }

  // Gera o ID da textura
  glGenTextures(1, &textureIDs[textureIndex]);

  // Vincula a textura
  glBindTexture(GL_TEXTURE_2D, textureIDs[textureIndex]);

  // Configura os parâmetros de filtragem e repetição da textura
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  // Passa os dados da imagem para o OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  // Libera a memória dos dados da imagem
  stbi_image_free(data);
}

void loadTextureArray()
{
  loadTexture("assets/head_up.png", 0);
  loadTexture("assets/head_down.png", 1);
  loadTexture("assets/head_right.png", 2);
  loadTexture("assets/head_left.png", 3);
  loadTexture("assets/tail_up.png", 5);
  loadTexture("assets/tail_down.png", 6);
  loadTexture("assets/tail_right.png", 7);
  loadTexture("assets/tail_left.png", 8);
  loadTexture("assets/body_horizontal.png", 9);
  loadTexture("assets/body_vertical.png", 10);
  loadTexture("assets/body_bottomright.png", 11);
  loadTexture("assets/body_bottomleft.png", 12);
  loadTexture("assets/body_topright.png", 13);
  loadTexture("assets/body_topleft.png", 14);
  loadTexture("assets/bg_1.png", 15);
  loadTexture("assets/bg_2.png", 16);
  loadTexture("assets/apple.png", 17);
  loadTexture("assets/texto_morte.png", 18);
  loadTexture("assets/texto_pause.png", 19);
}

void keyboardHandle(unsigned char key, int x, int y)
{

  switch (key)
  {
  case 'w':
    direcao = controlaDirecao('T', direcao);
    break;
  case 's':
    direcao = controlaDirecao('D', direcao);
    break;
  case 'a':
    direcao = controlaDirecao('L', direcao);
    break;
  case 'd':
    direcao = controlaDirecao('R', direcao);
    break;

  case 'r':
    if (gameState == 0)
      gameState = 1;
    resetGame();
    glutPostRedisplay();
    break;

  case 'p':
    if (gameState == 2)
      gameState = 1;
    else if (gameState == 1)
      gameState = 2;

    glutPostRedisplay();
    break;

  default:
    break;
  }
}

void drawPauseText()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, textureIDs[19]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-60, 30);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(60, 30);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(60, 70);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-60, 70);
  glEnd();
}

void drawDeadText()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, textureIDs[18]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-60, 30);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(60, 30);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(60, 70);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-60, 70);
  glEnd();
}

void drawSnake()
{
  Snake *tmp = snake;

  do
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureIDs[tmp->sprite]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(tmp->quad.x1, tmp->quad.y1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(tmp->quad.x2, tmp->quad.y2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(tmp->quad.x3, tmp->quad.y3);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(tmp->quad.x4, tmp->quad.y4);
    glEnd();

    tmp = tmp->anterior;
  } while (tmp != NULL);
}

void drawGrid()
{
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(1.0f);

  glBegin(GL_LINES);
  for (int i = -100; i < 100; i += 10)
  {
    glVertex2f(100, i);
    glVertex2f(-100, i);
    glVertex2f(i, 100);
    glVertex2f(i, -100);
  }
  glEnd();

  glLineWidth(3.0f);
  glBegin(GL_LINES);
  glVertex2f(100, 0);
  glVertex2f(-100, 0);
  glVertex2f(0, 100);
  glVertex2f(0, -100);
  glEnd();
}

void drawFruit()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, textureIDs[17]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(fruit->x1, fruit->y1);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(fruit->x2, fruit->y2);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(fruit->x3, fruit->y3);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(fruit->x4, fruit->y4);
  glEnd();
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  // drawGrid();
  loadBackground();
  // drawSquare();
  // renderText(100.0f, 100.0f, "Hello, world!", 1.0f);
  drawSnake();
  drawFruit();
  if (gameState == 0)
    drawDeadText();

  if (gameState == 2)
    drawPauseText();

  glFlush();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  // configurando uma janela
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // glutInitWindowPosition(0,0);    // Set window position
  glutInitWindowSize(900, 900); // Set window size
  glutCreateWindow("Snake");

  glEnable(GL_TEXTURE_2D);

  // glClearColor(1.0, 1.0, 1.0, 0.0); // Set display window colour to white
  // delimitando orientacoes do cenário
  snake = criarSnake();
  fruit = criarFruta();
  loadTextureArray();
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

  // registro de funcao de callback
  glutKeyboardFunc(keyboardHandle);
  glutDisplayFunc(draw);

  // iniciando variaveis
  glClearColor(0.0, 1.0, 0.0, 0.0);
  glutTimerFunc(delay, screenUpdate, gameState);

  // loop de tratamento de eventos
  glutMainLoop();
  return EXIT_SUCCESS;
}
