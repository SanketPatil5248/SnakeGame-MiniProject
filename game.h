#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1     //defined this constants for directions to know the position of snake
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 60

void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void random(int&, int&);

#endif // GAME_H_INCLUDED
