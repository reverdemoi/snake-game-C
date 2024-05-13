#include <stdio.h>
#include <windows.h>

const int width = 30;
const int height = 15;

char faceDir[50] = ">";
char *ptr = &faceDir[0];

int snakeCoords[2] = {8, 8};
int foodCoords[2] = {10, 10};

int score = 0;
char direction;

void generateFood() {
  int x = rand() % (width - 2);
  int y = rand() % (height - 2);

  foodCoords[0] = x + 1, foodCoords[1] = y + 1;
}

void drawCanvas() {
  // for (int i = 0; i < 50; i++) {
  //   printf("\n");
  // }

  printf("%i", score);
  for (int row = 1; row <= height; row++) {
    for (int col = 1; col <= width; col++) {
      // Draw boarder
      if (row == 1 || row == height) {
        printf("#");
        continue;
      } 
      // Draw snake
      else if (row == snakeCoords[1] && col == snakeCoords[0]) {
        printf("%c", *ptr);
      } 
      // Draw food
      else if (row == foodCoords[1] && col == foodCoords[0]) {
        printf("F");
      }
      // Draw boarder
      else if (col == 1 || col == width) {
        printf("#");
        continue;
      } 
      // Draw playable area
      else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void moveSnake(char direction) {
  switch(direction) {
    case 'w':
      snakeCoords[1]--;
      *ptr = '^';
      break;
    case's':
      snakeCoords[1]++;
      *ptr = 'v';
      break;
    case 'a':
      snakeCoords[0]--;
      *ptr = '<';
      break;
    case 'd':
      snakeCoords[0]++;
      *ptr = '>';
      break;
    default:
      break;
  } 

  // printf("%i, %i\n\n", snakeCoords[0], snakeCoords[1]);
  // printf("%i, %i\n\n", foodCoords[0], foodCoords[1]);
  if (snakeCoords[0] == foodCoords[0] && snakeCoords[1] == foodCoords[1]) {
    score++;
    generateFood();
  }
}

int main() {

  while (score != 5) {
    while(1) {
      drawCanvas();
      Sleep(300);

      // printf("%i", rand() % width);

      if (_kbhit()) {
          direction = _getch();
          printf("%c\n", direction);
      } else {
          direction = ' ';
      }

      moveSnake(direction);
    }
  }

  return 0;
}

/*

TODO

*** Fixa boarder collision
*** Lägg till en kropp på ormen som ökar vid äppleätande
*** Avsluta när specifierat score har uppnåtts

** Klura ut varför det printas dubbelt

*/
