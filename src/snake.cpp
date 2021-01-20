#include "snake.h"

#define SNAKE_HEAD '+'
#define SNAKE_TAIL 'o'
#define FRUIT '@'

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    for(int i = 4; i > 0; i--)
        snake.push_back(CPoint(2 + i, 2));

    timeout(400);
    srand(time(0));
    generateFruit();
}

void CSnake::paintPointsWindow(){
    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("|");
    gotoyx(geom.topleft.y - 1, geom.topleft.x + 1);
    if(points < 10)
        printl("POINTS:  %d", points);
    else
        printl("POINTS: %d", points);
    gotoyx(geom.topleft.y - 1, geom.topleft.x + 11);
    printl("|");
}

void CSnake::paintSpeedWindow(){
    if(speed != 5){
        gotoyx(geom.topleft.y - 1, geom.topleft.x + 27);
        printl("|");
        gotoyx(geom.topleft.y - 1, geom.topleft.x + 12);
        printl(" SPEED LEVEL: %d", speed);
    }
    else{
        gotoyx(geom.topleft.y - 1, geom.topleft.x + 29);
        printl("|");
        gotoyx(geom.topleft.y - 1, geom.topleft.x + 12);
        printl(" SPEED LEVEL: %s", "MAX");
    }
}

void CSnake::snakeDirection(int key){
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

void CSnake::snakeMovement(){
    switch(currentDirection){
            case right:
                snake.insert(snake.begin(), CPoint(snake[0].x + 1, snake[0].y));
                    
                if(snake[0].x == geom.size.x - 1)
                    snake[0] = CPoint(1, snake[0].y);
            break;
            case left:
                snake.insert(snake.begin(), CPoint(snake[0].x - 1, snake[0].y));
                
                if(snake[0].x == 0)
                    snake[0] = CPoint(geom.size.x - 2, snake[0].y);
            break;
            case up:
                snake.insert(snake.begin(), CPoint(snake[0].x, snake[0].y - 1));
                
                if(snake[0].y == 0)
                    snake[0] = CPoint(snake[0].x, geom.size.y - 2);
            break;
            case down:
                snake.insert(snake.begin(), CPoint(snake[0].x, snake[0].y + 1));
                
                if(snake[0].y == geom.size.y - 1)
                    snake[0] = CPoint(snake[0].x, 1);
            break;
        }
}

void CSnake::generateFruit(){
    while(1){
        fruit = CPoint(rand() % geom.size.x + 1, rand() % geom.size.y + 1);
    
        for(unsigned i = 0; i < snake.size(); i++){
            if(snake[i].x == fruit.x && snake[i].y == fruit.y)
                continue;
        }
        
        if(fruit.y >= (geom.size.y - 1) || fruit.x >= (geom.size.x - 1))
            continue;
            
        break;
    }
}

void CSnake::collision(){
    if(snake[0].x == fruit.x && snake[0].y == fruit.y){
        points++;
        if(points % 5 == 0 && speed < 5){
            delay -= 70;
            timeout(delay);
            speed++;
        }
        
        snake.push_back(CPoint(snake.back().x, snake.back().y));
        
        generateFruit();
    }
    
    for(unsigned i = 1; i < snake.size(); i++){
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            gameOver = true;
    }
}

void CSnake::restart(){
    while(snake.size() != 0)
        snake.pop_back();
    
    for(int i = 4; i > 0; i--)
        snake.push_back(CPoint(2 + i, 2));
    
    help = true;
    paused = false;
    gameOver = false;
    currentDirection = right;
    delay = 400;
    points = 0;
    speed = 1;
}

void CSnake::paint(){
    CFramedWindow::paint();
    if(!gameOver){
        paintPointsWindow();
        paintSpeedWindow();
    }
    else{
        gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
        printl("GAME OVER! Result:  %d", points);
    }
   
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
        printl("q - quit");
        gotoyx(geom.topleft.y + 9, geom.topleft.x + 5);
        printl("arrows - move snake or");
        gotoyx(geom.topleft.y + 10, geom.topleft.x + 5);
        printl("         screen when the game is paused");
    }
}

bool CSnake::handleEvent(int key){  
    tabPaused = false;

    switch(key){
        case 'H':
        case 'h':
            help = !help;
        break;
        case 'P':
        case 'p':
            paused = !paused;
        break;
        case 'R':
        case 'r':
            restart();
            return true;
        break;
        case '\t':
            if(!paused)
                tabPaused = true;
            return false;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_RIGHT:
        case KEY_LEFT:
            if(!paused && !help && !gameOver)
                snakeDirection(key);
        break;
        default:
        break;
    }
    
    if(gameOver)
        paused = true;
    
    if(paused || help){
        CFramedWindow::handleEvent(key);
        return true;
    }
       
    if(!help && !paused){
        snake.pop_back();

        snakeMovement();
    }
    
    collision();
    
    return true;
}
