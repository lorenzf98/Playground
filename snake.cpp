//  snake.cpp
//  A classic SNAKE game written in C++ for macOS using NCURSES

#include <stdlib.h>
#include <ncurses.h>

bool gameOver;
const int width = 60, height = 30, maxL = 100;
int x, y, TargetX, TargetY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int TailX[maxL], TailY[maxL];
int nTail = 0;

void Init()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    TargetX = (rand() % width) + 2;
    TargetY = (rand() % height) + 2;
    score = 0;
}

void Draw()
{
    clear();
    mvprintw(0, 20, "CLASSICAL SNAKE GAME");
    mvprintw(y, x, "0"); // snake head
    mvprintw(TargetY, TargetX, "0");

    for (int i=2; i<height+1; i++){
        for (int j=0; j<width+1; j++){
            if (i == 2 || i == height){
                mvprintw(i, j, "#");
            }
            if (j == 0 || j == width){
                mvprintw(i, j, "#");
            }
            else {
                for (int k=0; k<nTail; k++){
                    if (TailX[k] == j && TailY[k] == i){
                        mvprintw(i, j, "o"); // draw trajectory ("tail")
                    }
                }
            }
        }
    }

    mvprintw(height+2, 0, "SCORE: %i", score);
    refresh();
}

void Input()
{
    keypad(stdscr, TRUE);
    halfdelay(1);

    int c = getch();

    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 99:
            gameOver = true;
            break;
    }
}

void Logic()
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;

    TailX[0] = x; // head of snake in front
    TailY[0] = y;

    for (int i=1; i<nTail; i++){ // create trajectory ("tail")
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x > width-1 || x < 1 || y > height-1 || y < 3){
        gameOver = true;
    }

    if (x == TargetX && y == TargetY){
        score++;
        TargetX = (rand() % width) + 2; // redraw start point
        TargetY = (rand() % height) + 2;
        nTail++;
    }

    for (int i=0; i<nTail; i++){
        if (TailX[i] == x && TailY[i] == y){
            gameOver = true;
        }
    }
}

int main()
{
    Init();

    while(!gameOver){
        Draw();
        Input();
        Logic();
    }

    getch();
    endwin();

    return 0;
}

