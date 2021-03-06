#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <cstdlib>
#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <list>
#include <vector>

using namespace std;

class CSnake:public CFramedWindow
{
    vector <CPoint> snake;
    CPoint fruit;
    bool paused = false, tabPaused = false;
    bool help = true;
    bool gameOver = false;
    unsigned points = 0, speed = 1, delay = 400;
    
    enum direction { up, down, right, left };
    enum direction currentDirection = right;
public:
    CSnake(CRect r, char _c = ' ');
    void paint();
    void paintPointsWindow();
    void paintSpeedWindow();
    bool handleEvent(int key);
    void snakeDirection(int key);
    void snakeMovement();
    void generateFruit();
    void collision();
    void restart();
    
    unsigned getDelay(){
        return delay;
    }
};

#endif
