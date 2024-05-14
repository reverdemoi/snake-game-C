#include <stdio.h>
#include <windows.h>

const int width = 30;
const int height = 15;

char faceDir[50] = ">";
char *ptr = &faceDir[0];

int snakeCoords[2] = {8, 8};
int foodCoords[2] = {10, 10};

typedef struct {
  int x;
  int y;
  char dir;
} SnakeLength;

SnakeLength snakeLength[10][3] = {{8, 8, 'd'}};

char direction;
int score = 1;
int counter = 1;

void reset() {
  snakeCoords[0] = 8;
  snakeCoords[1] = 8;
  SnakeLength snakeLength[10][3] = {{8, 8, 'd'}};
}

int gen(int length) {
  // Generating new coords inside playable area
  while (1) {
    int pos = rand() % (length - 2);

    if (pos <= 1 || pos >= length - 1) {
      // printf("FAILED TO GENERATE NEW APPLE COORDS, TRYING AGAIN");
      continue;
    } else {
      // printf("NEW APPLE COORDS");
      return pos;
    }
  }
}

void generateFood() {
  int x = gen(width); 
  int y = gen(height);

  foodCoords[0] = x + 1, foodCoords[1] = y + 1;
}

void drawCanvas() {
  system("cls");

  printf("Apple coords: %i, %i\n", foodCoords[0], foodCoords[1]);
  printf("Snake coords: %i, %i\n", snakeCoords[0], snakeCoords[1]);


  // printf("%i", score);
  for (int row = 1; row <= height; row++) {
    for (int col = 1; col <= width; col++) {
      // Draw boarder
      if (row == 1 || row == height) {
        printf("#");
        continue;
      } 
      // Draw snake head
      else if (row == snakeCoords[1] && col == snakeCoords[0]) {
        printf("%c", *ptr);
        continue;
      } 
      
      // Draw food
      else if (row == foodCoords[1] && col == foodCoords[0]) {
        printf("F");
        continue;
      }
      // Draw boarder
      else if (col == 1 || col == width) {
        printf("#");
        continue;
      } 
        
      // Draw snake body 
      for (int p = 0; p <= counter; p++) {
        if (col == snakeLength[p][0].x && row == snakeLength[p][1].y) {
          if (snakeLength[p][2].dir == 'w' || snakeLength[p][2].dir =='s') {
            printf("|");
          } else if (snakeLength[p][2].dir == 'a' || snakeLength[p][2].dir == 'd') {
            printf("-");
          }
          goto next;
        }
      }

      printf(" ");

      next:
        continue;
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

  // Add snake body parts
  counter++;
  snakeLength[counter][0].x = snakeCoords[0], snakeLength[counter][1].y = snakeCoords[1], snakeLength[counter][2].dir = direction;

  // Limit size of snake body
  if (counter > score) {
    for (int i = 0; i < counter; i++) {
      snakeLength[i][0].x = snakeLength[i + 1][0].x;
      snakeLength[i][1].y = snakeLength[i + 1][1].y;
      snakeLength[i][2].dir = snakeLength[i + 1][2].dir;
    }
    counter--;
  }

  // Check for whether snake is eating apple

  // printf("%i, %i", snakeLength[counter][0], snakeLength[counter][1]);

  // printf("%i, %i\n\n", snakeCoords[0], snakeCoords[1]);
  // printf("%i, %i\n\n", foodCoords[0], foodCoords[1]);
  if (snakeCoords[0] == foodCoords[0] && snakeCoords[1] == foodCoords[1]) {
    score++;
    generateFood();
  }
 
}

int main() {
  while(1) {
    drawCanvas();
    Sleep(300);

    // printf("%i", rand() % width);

    if (_kbhit()) {
        direction = _getch();
        // printf("%c\n", direction);
    }

    // Check for boarder collision
    if (snakeCoords[0] == 1 || snakeCoords[1] == width ||
        snakeCoords[1] == 1 || snakeCoords[1] == height) {
      printf("You loose!");      
      break;
    }

    moveSnake(direction);
    if (score == 10) {
      printf("You win!");
      break;
    }
  }

  return 0;
}

/*

TODO

*** Fixa boarder collision
*** Avsluta när specifierat score har uppnåtts

*/
