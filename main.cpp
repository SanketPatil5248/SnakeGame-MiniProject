#include <GL/gl.h>// header file for opengl
#include <GL/glut.h> //glut library used since it decreases lot of efforts and makes programming simple.
#include "game.h"
#include <stdlib.h>
#include <windows.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 10 //10 fps for each frame to be displayed, when snake moves forward by 1 unit then that frame to be displayed.

extern short sDirection;//gets access from "game.cpp" file for directions.
bool gameOver=false;//boolean declaration for game over which is by default false.

int score=0;

void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);//by default color is black i.e 0 intensity of all colors returns black
    initGrid(COLUMNS,ROWS);
}

int main(int argc , char **argv)
{
    glutInit(&argc, argv);//initialize the glut which takes to arguments
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);//gives double buffer window
    glutInitWindowSize(500,500);//initialize window size
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);// called when window is created
    glutTimerFunc(0,timer_callback,0);//registers callback which has to be triggered
    //glutKeyboardFunc(); //keyboard callback is triggered when user gives input using arrow/direction keys.
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();// used to call main function
    return 0;
}
int index = 0; //used to keep  track of position in animation
void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);// clears the buffer for each frame that is displayed
    drawGrid();//call drawgrid method before the buffers are swaped, i.e. drawn on every frame.
    drawSnake();
    drawFood();//reset position of food or draws food after drawing the snake.
    glutSwapBuffers();//swaps buffers using this function       //delay to FPS is added by this function.
    // after swaping the buffers the grid will be displayed.
    if(gameOver) //if it is true
    {
        char _score[10];
        itoa(score, _score, 10); //this function converts integer value to characters.
        char text[50]="Your Score: ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);//used to display messagebox that has been ended which is present in windows.h or glut.h header file.
        exit(0);
    }
}
void reshape_callback(int w, int h) //width and height of window when it is resized
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);//set viewport that covers entire window
    //setting up the orthographic projection or the coordinates
    glMatrixMode(GL_PROJECTION); //changed matrix mode to projection mode
    glLoadIdentity();//makes sure there are no changes made to the matrix
    //for 2D co-ordination system Orthographic projectiom is  used
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}
void timer_callback(int)
{   //new frame is displayed when each time timer_callback function is called.
    glutPostRedisplay();//it gives opengl a urge to call the display function
    glutTimerFunc(1000/FPS, timer_callback, 0);//aragument is in form of milliseconds
}

void keyboard_callback(int key, int, int)
{
    switch(key)
    {
        case GLUT_KEY_UP: //GLUT_KEY identifies the input from keyboard of which key is pressed.
            if(sDirection!=DOWN)
                sDirection=UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection!=UP)
                sDirection=DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection!=LEFT)
                sDirection=RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection!=RIGHT)
                sDirection=LEFT;
            break;
    }
}
