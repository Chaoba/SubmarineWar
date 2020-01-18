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
    NONE = 0,
    CHESS = 1,
    DECORATION = 2,
};

enum POSITION
{
    LEFT_TOP = 0,
    RIGHT_TOP = 1,
    LEFT_BOTTOM = 2,
    RIGHT_BOTTOM = 3,
    LEFT_BORDER = 4,
    TOP_BORDER = 5,
    RIGHT_BORDER = 6,
    BOTTOM_BORDER = 7,
};
enum DERIECTION
{
    LEFT = 0,
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
};
enum CHESS_TYPE
{
    SUB_MARINE = 6,
    SMALL_MINE = 7,
    MIDDLE_MINE = 8,
    BIG_MINE = 9
};
class BaseObject
{
public:
    int width, height;
    Point leftTop, parent;
    bool valid = false;
    BaseObject(int w, int h) : leftTop(Point(-1, -1)), parent(Point(-1, -1)), width(w), height(h)
    {
    }
    virtual bool addToBoard(vector<vector<int>> &board, Point position, Point parentPosition)
    {
        // cout<<"Add to baord: "<<position.x<<"  "<<position.y<<endl;
        leftTop = position;
        parent = parentPosition;
        return true;
    }
    virtual bool removeFromBoard(vector<vector<int>> &board) = 0;

    virtual ~BaseObject() {}
};
