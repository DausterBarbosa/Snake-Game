#define STB_IMAGE_IMPLEMENTATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "stb_image.h"
#include "snake.h"

Snake *snake;

GLuint textureIDs[18];
GLuint bgID1, bgID2;
char direcao = 'R';
int sprite = 0;
int delay = 180;

void screenUpdate(int value)
{
  moverSnake(snake, direcao, 200, 200);
  glutPostRedisplay();
  glutTimerFunc(delay, screenUpdate, 1);
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
}

void keyboardHandle(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    direcao = 'T';
    break;
  case 's':
    direcao = 'D';
    break;
  case 'a':
    direcao = 'L';
    break;
  case 'd':
    direcao = 'R';
    break;
  default:
    break;
  }
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

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  // drawGrid();
  loadBackground();
  // drawSquare();
  drawSnake();
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
  loadTextureArray();
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

  // registro de funcao de callback
  glutKeyboardFunc(keyboardHandle);
  glutDisplayFunc(draw);

  // iniciando variaveis
  glClearColor(0.0, 1.0, 0.0, 0.0);
  glutTimerFunc(delay, screenUpdate, 1);

  // loop de tratamento de eventos
  glutMainLoop();
  return EXIT_SUCCESS;
}