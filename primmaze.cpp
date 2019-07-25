#include "primmaze.h"

PrimMaze::PrimMaze(int sideLength)
{
    this->sideLength = sideLength;
    mazeLength = sideLength - 2;
    map = new int* [sideLength];//此处进行map行的动态初始化
    maze = new int* [sideLength - 1];
    pathmap = new int* [sideLength - 1];
    for (int i = 0; i < sideLength; i++)
    {
        map[i] = new int[sideLength];//动态初始化数组的列
        memset(map[i], 0, sideLength * sizeof(int));//由于memset只能初始化一维数组,所以在每动态初始化一列的时候填充
    }
    for (int i = 0; i < mazeLength; i++)
    {

        maze[i] = new int[mazeLength];
        pathmap[i] = new int[mazeLength];
        memset(maze[i], 0, mazeLength * sizeof(int));
        memset(pathmap[i], 0, mazeLength * sizeof(int));
    }
}

PrimMaze::~PrimMaze()
{

}

void PrimMaze::printmap()//打印地图
{

    //4右,5下,6左,7上
    for (int i = 0; i < mazeLength; i++)
    {
        for (int j = 0; j < mazeLength; j++)
        {
            if (maze[i][j] == 0)
            {
                cout << "  ";
            }
            else if (maze[i][j] == 1)
            {
                cout << "■";
            }
            else if (maze[i][j] == 2)
            {
                cout << "♀";
            }
            else if (maze[i][j] == 3)
            {
                cout << "×";
            }
            else if (maze[i][j] == 4)
            {
                cout << "↓";
            }
            else if (maze[i][j] == 5)
            {
                cout << "→";
            }
            else if (maze[i][j] == 6)
            {
                cout << "↑";
            }
            else if (maze[i][j] == 7)
            {
                cout << "←";
            }
        }
        cout << endl;
    }
}

void PrimMaze::createwall()//初始化整个二维数组为墙
{
    for (int i = 0; i < sideLength; i++)
    {
        map[0][i] = 1;
        map[sideLength - 1][i] = 1;
        map[i][0] = 1;
        map[i][sideLength - 1] = 1;
    }
}

void PrimMaze::createmaze()
{
    srand((unsigned int)time(NULL));
    pointNode seed(2, 2);
    pathvector.push_back(seed);

    //当墙队列为空时结束循环
    while (pathvector.size()) {
        //在墙队列中随机取一点
        int r = rand() % pathvector.size();
        int x = pathvector[r].getX();
        int y = pathvector[r].getY();

        //判读上下左右四个方向是否为路
        int count = 0;
        for (int i = x - 1; i < x + 2; i++) {
            for (int j = y - 1; j < y + 2; j++) {
                if (abs(x - i) + abs(y - j) == 1 && map[i][j] > 0) {
                    ++count;
                }
            }
        }

        if (count <= 1) {
            map[x][y] = 1;
            //在墙队列中插入新的墙
            for (int i = x - 1; i < x + 2; i++) {
                for (int j = y - 1; j < y + 2; j++) {
                    if (abs(x - i) + abs(y - j) == 1 && map[i][j] == 0) {
                        pointNode nowpoint(i, j);
                        pathvector.push_back(nowpoint);
                    }
                }
            }
        }

        //删除当前墙
        pathvector.erase(pathvector.begin() + r);
    }

    //设置迷宫进出口
    for (int i = sideLength - 3; i >= 0; i--) {
        if (map[i][sideLength - 3] == 1) {
            map[i][sideLength - 2] = 1;
            break;
        }
    }

    for (int i = 0; i < mazeLength; i++)
    {
        for (int j = 0; j < mazeLength; j++)
        {
            maze[i][j] = abs(map[i + 1][j + 1] - 1);
        }
    }
}

void PrimMaze::setStart(int x, int y)
{
    while (maze[x][y])
    {
        cout << "输入非法请重新输入:";
        cin >> x >> y;
    }
    startX = x;
    startY = y;
    maze[startX][startY] = 2;
}

void PrimMaze::calculationEnd()//计算终点
{
    for (int i = mazeLength - 1; i >= 0; i--)
    {
        if (maze[i][mazeLength - 1] == 0)
        {
            endX = i;
            endY = mazeLength - 1;
        }
    }

    maze[endX][endY] = 3;
}

bool PrimMaze::canGo(int x, int y)
{
    if (x < 0 && x > mazeLength)
    {
        return 0;
    }
    else if (y < 0 && y > mazeLength)
    {

    }
    else if (maze[x][y] == 1)
    {
        return 0;
    }
    else if (pathmap[x][y] == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void PrimMaze::BFScalculation()
{

    start = new point;
    start->x = startX, start->y = startY;
    shortqueue.push(start);
    pathmap[start->x][start->y] = 1;
    while (shortqueue.size())
    {
        point* nownode = shortqueue.front();
        shortqueue.pop();
        p = nownode;
        if (p->x == endX && p->y == endY)
        {
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            if (canGo(p->x + dx[i], p->y + dy[i]))
            {
                newnode = new point;
                newnode->x = p->x + dx[i];
                newnode->y = p->y + dy[i];
                newnode->dir = dir[i];
                newnode->parent = p;
                shortqueue.push(newnode);
                pathmap[newnode->x][newnode->y] = 1;
            }
        }
    }

    bfspathnode = p->parent;
}

void PrimMaze::print()
{
    for (int i = 0; i < mazeLength; i++)
    {
        for (int j = 0; j < mazeLength; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

