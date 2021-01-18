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
    bool paused = false;
    bool help = true;
    
    enum direction { up, down, right, left };
    enum direction currentDirection = right;
public:
    CSnake(CRect r, char _c = ' ');
    void paint();
    bool handleEvent(int key);
    void snakeMovement(int key);
};

#endif
