#ifndef PRIMMAZE_H
#define PRIMMAZE_H
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <string.h>
using namespace std;

struct point
{
    int x;
    int y;
    int dir = 0;
    point* parent = NULL;//上一步的坐标
};

class pointNode
{
    public:
        pointNode();
        pointNode(int x, int y) : x(x), y(y) {}
        int getX() { return x; }
        int getY() { return y; }
    private:
        int x;
        int y;
};

class PrimMaze
{
    public:
        PrimMaze(int sideLength);
        ~PrimMaze();
        void printmap();
        void createwall();
        void createmaze();
        void setStart(int x, int y);
        void calculationEnd();
        bool canGo(int x, int y);
        void BFScalculation();
        void print();
        int** returnmaze() { return maze; }
        int** returnpathmaze() {return pathmap;}
        point *bfspathnode;
        point* returnpathnode() {return bfspathnode;}
        int returnmazelength(){return mazeLength;}
        int returnendX() {return endX;}
        int returnendY() {return endY;}
    private:
        int sideLength, mazeLength, startX, startY, endX, endY;
        int** map = NULL; //生成指针的指针数组
        int** maze = NULL, ** pathmap = NULL;
        point* p, * newnode, * start;
        int dx[4] = { 1, 0, -1, 0 };
        int dy[4] = { 0, 1, 0, -1 };
        int dir[4] = { 1, 2, 3, 4 };//1右,2下,3左,4上
        vector<pointNode> pathvector;
        queue<point*>shortqueue;
};


#endif // PRIMMAZE_H
