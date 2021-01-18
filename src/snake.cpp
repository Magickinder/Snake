#include "snake.h"

#define SNAKE_HEAD '*'
#define SNAKE_TAIL 'o'
#define FRUIT '@'

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    for(int i = 4; i > 0; i--)
        snake.push_back(CPoint(2 + i, 2));
        
    srand(time(0));
    fruit = CPoint(rand() % geom.size.x + 1, rand() % geom.size.y + 1);
}

void CSnake::snakeMovement(int key){
    if(key == KEY_UP){
        if(currentDirection == right || currentDirection == left)
            currentDirection = up;
    }
    else if(key == KEY_DOWN){
        if(currentDirection == right || currentDirection == left)
            currentDirection = down;
    }
    else if(key == KEY_RIGHT){
        if(currentDirection == up || currentDirection == down)
            currentDirection = right;
    }
    else if(key == KEY_LEFT){
        if(currentDirection == up || currentDirection == down)
            currentDirection = left;
    }
}

void CSnake::generateFruit(){
    while(1){
        fruit = CPoint(rand() % geom.size.x + 1, rand() % geom.size.y + 1);
    
        for(unsigned i = 0; i < snake.size(); i++){
            if(snake[i].x == fruit.x && snake[i].y == fruit.y)
                continue;
        }
        
        if(fruit.y >= geom.size.y - 1 || fruit.x >= geom.size.x - 1)
            continue;
            
        break;
    }
}

void CSnake::paint(){
    CFramedWindow::paint();
   
    for(vector<CPoint>::iterator i = snake.begin();
       i != snake.end(); i++){
            gotoyx((*i).y + geom.topleft.y, (*i).x + geom.topleft.x);
            if(i == snake.begin())
                printl("%c", SNAKE_HEAD);
            else
                printl("%c", SNAKE_TAIL);
    }
    
    gotoyx(geom.topleft.y + fruit.y, geom.topleft.x + fruit.x);
    printl("%c", FRUIT);
    
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
        case KEY_UP:
        case KEY_DOWN:
        case KEY_RIGHT:
        case KEY_LEFT:
            if(!paused && !help)
                snakeMovement(key);
        break;
        default:
        break;
    }
       
    if(!help && !paused){
        snake.pop_back();
        
        switch(currentDirection){
            case right:
                snake.insert(snake.begin(), CPoint(snake[0].x + 1, snake[0].y));
            break;
            case left:
                snake.insert(snake.begin(), CPoint(snake[0].x - 1, snake[0].y));
            break;
            case up:
                snake.insert(snake.begin(), CPoint(snake[0].x, snake[0].y - 1));
            break;
            case down:
                snake.insert(snake.begin(), CPoint(snake[0].x, snake[0].y + 1));
            break;
        }
    }
       
    if(paused || help){
        CFramedWindow::handleEvent(key);
        return true;
    }
    
    return true;
}
