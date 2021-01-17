#include "snake.h"

#define SNAKE_HEAD '>'
#define SNAKE_TAIL '-'

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    for(int i = 0; i < 4; i++)
        //snake.push_back(CPoint(15 - i, 10));
        snake.push_back(CPoint(geom.topleft.x + 2 + i, geom.topleft.y + 2));
}

void CSnake::paint(){
    CFramedWindow::paint();
    
    //Update snake coordinates when snake screen is moved
    for(unsigned i = 0; i < snake.size(); i++){
        snake[i].x = geom.topleft.x + 2 + i;
        snake[i].y = geom.topleft.y + 2;
    }
   
    for(vector<CPoint>::iterator i = snake.begin();
       i != snake.end(); i++){
            gotoyx((*i).y, (*i).x);
            if(i == snake.end() - 1)
                printl("%c", SNAKE_HEAD);
            else
                printl("%c", SNAKE_TAIL);
    }
    
    if(help){
        gotoyx(geom.topleft.y + 5, geom.topleft.x + 5);
        printl("h - help");
        gotoyx(geom.topleft.y + 6, geom.topleft.x + 5);
        printl("p - toggle on/off pause");
        gotoyx(geom.topleft.y + 7, geom.topleft.x + 5);
        printl("r - restart game");
        gotoyx(geom.topleft.y + 8, geom.topleft.x + 5);
        printl("esc - quit");
        gotoyx(geom.topleft.y + 9, geom.topleft.x + 5);
        printl("arrows - move snake or");
        gotoyx(geom.topleft.y + 10, geom.topleft.x + 5);
        printl("         screen when the game is paused");
    }
}

bool CSnake::handleEvent(int key){
    switch(key){
        case 'h':
            help = !help;
        break;
        case 'p':
            paused = !paused;
        break;
        case '\t':
            paused = true;
            return false;
        default:
        break;
    }
    
    if(paused || help){
        CFramedWindow::handleEvent(key);
        return true;
    }
    
    return true;
}
