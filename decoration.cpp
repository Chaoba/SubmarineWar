#include "baseObject.cpp"
class Decoration : BaseObject
{
public:
    Decoration(vector<vector<int>> &board, Point leftTop, int width, int height) : BaseObject(board, leftTop, width, height)
    {
        for (int i = leftTop.x; i < width; i++)
        {
            for (int j = leftTop.y; j < height; j++)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = 1;
                }
            }
        }
    }
    ~Decoration() noexcept {}
};

class SmallMine : Decoration
{
public:
    SmallMine(vector<vector<int>> &board, Point leftTop) : Decoration(board, leftTop, 2, 2)
    {
    }
    ~SmallMine() noexcept {}
};

class MiddleMine : Decoration
{
public:
    MiddleMine(vector<vector<int>> &board, Point leftTop) : Decoration(board, leftTop, 2, 3)
    {
    }
    MiddleMine(vector<vector<int>> &board, Point leftTop, bool horizental) : Decoration(board, leftTop, 3, 2)
    {
    }
    ~MiddleMine() noexcept {}
};

class BigMine : Decoration
{
public:
    BigMine(vector<vector<int>> &board, Point leftTop) : Decoration(board, leftTop, 3, 3)
    {
    }
    ~BigMine() noexcept {}
};

class Propeller : Decoration
{
public:
    Propeller(vector<vector<int>> &board, Point leftTop) : Decoration(board, leftTop, 2, 2)
    {
    }
    ~Propeller() noexcept {}
};