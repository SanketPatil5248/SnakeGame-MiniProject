#include <GL/gl.h> //need to include opengl
#include <GL/glut.h>
#include "game.h"
#include <ctime> // used in random number func for knowing the the time.n also used to get time on your computer
#include <windows.h>

extern int score;

int gridX, gridY;
int snake_length = 5; //Initial length of snake at start of game
bool food= true;
int foodX, foodY;
short sDirection = RIGHT;
extern bool gameOver;

int posX[60]={20,20,20,20,20}, posY[60]={20,19,18,17,16};

void initGrid(int x, int y)//now to include grid on screen. Dimensions of grid is initialized by this function.
{
    gridX = x; //initialization
    gridY = y;
}



void unit(int, int); //unit function declaration.
void drawGrid()//now we create new function to draw grid.
{
   //unit(20,20); // used to draw single square on display window.
   //ALGORITHM TO DRAW MULTIPLE SQUARE UNITS or grid.
   for(int x=0; x<gridX; x++) // for x-coordinate
   {
       for(int y=0; y<gridY; y++) // for y-coordinate
       {
           unit(x,y);
       }
   }
}

void unit(int x, int y)//different function to draw single square unit.
{   //THIS WILL DRAW SIMPLE SQUARE OF ONE UNIT AT A POINT WHICH IS SUPPLIED TO IT WITH A DRAWGRID FUNCTION.
    //setting color and thickness of line.
    //glLineWidth(1.0); // this 2 functions used to draw grid lines with white color
    //glColor3f(1.0,1.0,1.0); //for white color intensity should be full that is 1.

    //add logic to check whether the box is at th edge in a grid on a displayed window.
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1)
    {
        glLineWidth(3.0); //this block of code executed for red colored border of the grid.
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0); // this block of code executed for the grid inside the red border.
        glColor3f(1.0,1.0,1.0);
    }

    glBegin(GL_LINE_LOOP); //loop of lines, first vertex and last vertex will be connected.
        glVertex2f(x,y);
        glVertex2f(x+1,y); //to create square of 1 unit we need to add one to its bottom left vertex point.
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void drawFood() //draw food at random place
{
    if(food) //if it is true
        random(foodX,foodY);
    food=false;
    glColor3f(1.0,0.0,0.0); // color of the food
    glRectf(foodX, foodY,foodX+1,foodY+1); //used to draw food.
}
void random(int &x, int &y) //takes to references for x and y co-ordinates.
{
    int _maxX = gridX-2; //this is the range for the random number.
    int _maxY  = gridY-2;
    int _min =1;
    srand(time(NULL)); //time in ctime header file
    x = _min + rand() % (_maxX - _min); //used this to get random number in required range.
    y = _min + rand() % (_maxY - _min);
}
void drawSnake()
{   //Animation used for a block from left to right.
    //glRectd(index,20,index+2,22); //used to draw rectangle.
    //index++;
    //if(index>40)
    //{
    //   index=0;
    //}
    for(int i = snake_length-1; i > 0; i--)
    {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }

    if(sDirection==UP)
        posY[0]++;
    else if(sDirection==DOWN)
        posY[0]--;
    else if(sDirection==RIGHT)
        posX[0]++;
    else if(sDirection==LEFT)
        posX[0]--;

    for(int i=0; i< snake_length ; i++)
    {
        // set snake head color to green from red
        if(i == 0)
            glColor3f(0.0,0.0,1.0);
        else
            glColor3f(0.0,1.0,0.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);//used to draw rectangle at center of screen.
    }

    //restriction to be given to snake using red wall
    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1)
        gameOver=true;
    if(posX[0]==foodX && posY[0]==foodY) //if snake goes on target then the food is redrawn at another random location.
    {
        score++;
        snake_length++;
        if(snake_length>MAX)
            snake_length=MAX; //snake will grow till 60 more blocks after this it will not grow.
        food=true;
    }
}
