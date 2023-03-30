#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;
enum dir { stop = 0, Left = 1, upLeft = 2, dwonleft = 3, Rigth = 4, upRight = 5, dwonRight = 6 };
class CBall
{
private:
    int x, y, originalX, originalY;
    dir direction;
public:
    CBall(int posX, int posY)
    {
        x = posX;
        y = posY;
        originalX = posX;
        originalY = posY;
        direction =  stop ;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    dir getDiretion()
    {
        return direction;
    }
    void changedirection(dir d)
    {
        direction = d;
    }
    void randomDirection()
    {
        srand(time(0));
        direction = (dir)(rand() % (6 - 1 + 1) + 1);
    }
    void move()
    {
        switch (direction)
        {
        case stop:
            break;
        case Left:
            x--;
            break;
        case upLeft:
            x--; y--;
            break;
        case dwonleft:
            x--; y++;
            break;
        case Rigth:
            x++;
            break;
        case upRight:
            x++; y--;
            break;
        case dwonRight:
            x++; y++;
            break;
        default:
            break;
        }
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = stop;
    }
};
class racket
{
private:
    int x, y, originalX, originalY;
public:
    racket(int posX,int posY)
    {
        x = originalX = posX;
        y = originalY = posY;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
    }
    void moveUp()
    {
        y--;
    }
    void moveDwon()
    {
        y++;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};
class gameSetting
{
private:
    int width, height, score1, score2;
    char up1, up2, dwon1, dwon2;
    CBall* ball;
    racket* player1;
    racket* player2;
    bool game;
public:
    gameSetting(int w, int h)
    {
        width = w;
        height = h;
        score1 = score2 = 0;
        ball = new CBall(width / 2, height / 2);
        player1 = new racket(2, height / 2 - 2);
        player2 = new racket(width - 1, height / 2 - 2);
        up1 = 'w'; up2 = 'i';
        dwon1 = 's'; dwon2 = 'k';
        game = false;
    }
    void scorUp(racket* player)
    {
        if (player == player1)
        {
            score1++;
        }
        if (player == player2)
        {
            score2++;
        }
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        system("cls");
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();
        for (int i = 1; i <= height; i++)
        {
            for (int j = 1; j <= width; j++)
            {
                //map
                if (i == 1 || i == height || j == 1 || j == width)
                    cout << "*";
                //ball
                else if (i == ballY && j == ballX)
                    cout << "O";
                //player1
                else if (i == player1Y && j == player1X)
                    cout << "#";
                else if (i == player1Y + 1 && j == player1X)
                    cout << "#";
                else if (i == player1Y + 2 && j == player1X)
                    cout << "#";
                else if (i == player1Y + 3 && j == player1X)
                    cout << "#";
                else if (i == player1Y + 4 && j == player1X)
                    cout << "#";
                //player2
                else if (i == player2Y && j == player2X)
                    cout << "#";
                else if (i == player2Y + 1 && j == player2X)
                    cout << "#";
                else if (i == player2Y + 2 && j == player2X)
                    cout << "#";
                else if (i == player2Y + 3 && j == player2X)
                    cout << "#";
                else if (i == player2Y + 4 && j == player2X)
                    cout << "#";
                //space
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "score1 : " << score1 << endl;
        cout << "score2 : " << score2 << endl;
    }
    void Input()
    {
        ball->move();
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();
        if (_kbhit())
        {
            char c = _getch();
            if (c == up1)
            {
                if (player1Y > 1)
                    player1->moveUp();
            }
            else if (c == dwon1)
            {
                if (player1Y + 4 < height)
                    player1->moveDwon();
            }
            if (c == up2)
            {
                if (player2Y > 1)
                    player2->moveUp();
            }
            else if (c == dwon2)
            {
                if (player2Y + 4 < height)
                    player2->moveDwon();
            }
            else if(ball->getDiretion() == stop)
            {
                ball->randomDirection();
            }
        }

    }
    void Logic()
    {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();
        //racket1
        for (int i = 0; i < 5; i++)
        {
            if (ballX == player1X + 1 && ballY == player1Y + i)
            {
                ball->changedirection((dir)(rand() % (6 - 4 + 1) + 4));
            }
        }
        //racket2
        for (int i = 0; i < 5; i++)
        {
            if (ballX == player2X - 1 && ballY == player2Y + i);
            ball->changedirection((dir)(rand() % (3- 1 + 1) + 1));
        }
        //scoreUp
        if (ballX == 1)
            scorUp(player2);
        else if (ballX == width)
            scorUp(player1);
        //bottom wall
        if (ballY == height - 1)
            ball->changedirection(ball->getDiretion() == dwonRight ? upRight : upLeft);
        //top wall
        if (ballY == 1)
            ball->changedirection(ball->getDiretion() == upRight ? dwonRight : dwonleft);
    }
    void Run()
    {
        while (!game)
        {
            Draw();
            Input();
            Logic();
            Sleep(50);
        }
    }
    ~gameSetting()
    {
        delete ball, player1, player2;
    }
};
int main()
{
    gameSetting g(40, 20);
    g.Run();
}
