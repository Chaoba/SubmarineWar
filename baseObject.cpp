#include <vector>
#include <iostream>
using namespace std;
class Point
{
public:
    int x, y;
    Point(int i, int j) : x(i), y(j)
    {
    }
    ~Point() {}
    Point operator+(const Point &b)
    {
        return Point(x + b.x, y + b.y);
    }
};

enum OBJECT_VALUE
{
    EMPTY = 0,
    CHESS = 1,
    DECORATION = 2,
};

class BaseObject
{
public:
    int width, height;
    Point leftTop;
    bool valid = false;
    BaseObject(int w, int h) : leftTop(Point(-1, -1)), width(w), height(h)
    {
    }
    bool addToBoard(vector<vector<int> > &board, Point position)
    {
        leftTop = position;
        return true;
    }
    ~BaseObject() {}
};