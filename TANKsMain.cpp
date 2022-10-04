# Tanks
//TANKS
#include <iostream>
#include <cstring>
#include <windows.h>
#include <ctime>
//----------------------------
using namespace::std;


//----------------------------
#define width 80
#define height 25

#define field ' '
#define fbrick 176
#define fstone 206

#define DULOv 179
#define DULOh 205
#define TANKC 219
#define catter '#'

//----------------------------
typedef char hwmap [height][width];
//----------------------------
void SetCurPos(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


};
struct tMap
{
    hwmap map;
    void Clr()
    {
        memset(map, field, sizeof(map)-1);
    };
    void SetEnd()
    {
        map[height - 1][width-1] = '\0';
    };
    void Show()
    {
        SetCurPos(0,0);
        SetEnd();
        cout <<map[0];
    };


};
enum Tdir {Runn = 0, Rdown, Rleft, Rright};
POINT dirInc[] = {{0,-1}, {0,1}, {-1,0}, {1,0}};

class Ttank
{
    int x, y;
    int sX, sY;
public:
    Tdir dir;
    Ttank(int startX, int startY)
    {
        dir = Runn;
        sX = startX;
        sY = startY;
        SetToStart();
    };
    void Show(hwmap &map);
    void Move(char w, char s, char a, char d, char fire);
    void SetToStart()
    {
        x = sX; y = sY;
    };
    bool IsHoriz() {return (dir == Rright || dir == Rleft);}
    RECT GetRect() {RECT r = {x - 1, y - 1, x + 1, y + 1}; return r;}

};


tMap scr;
Ttank tank(40,11);


void Ttank::Show(hwmap &map)
{
    if(IsHoriz())
        for (int i = -1; i < 2; map[y + 1][x - i] = map[y + 1][x + i] = catter, i++);
    else
        for (int i = -1; i < 2; map[y - i][x - 1] = map[y + i][x + 1] = catter, i++);
    map[y][x] = TANKC;
    POINT dt = dirInc[dir];
    map[y + dt.y][x + dt.x] = IsHoriz() ? DULOh : DULOv;
}
RECT area = {2,2, width - 3, height - 3};
void Ttank::Move(char w, char s, char a, char d, char fire)
{
    char wsad[4] = {w, s, a, d};
    for (int i= 0; i < 4; i++)
        if (GetKeyState(wsad[i]) < 0) dir = (Tdir)i;
    POINT pt = dirInc[dir];
    Ttank old = *this;
    x += pt.x;
    y += pt.y;
    /*if(!IsCross(area, GetRect()))
        *this = old;*/

}

int main()
{
    do
    {
      tank[0].Move('W','S','A','D', VK_SPACE);
      tank[1].Move(38,40,37,39,13);


      scr.Clr();
      for (int i = 0; i < tankCnt; tank[i++].Show(scr.map));
      scr.Show();

    }
    while (GetKeyState(VK_ESCAPE) >= 0);





    return 0;
}
