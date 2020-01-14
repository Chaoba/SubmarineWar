#include "baseObject.cpp"
class Decoration : public BaseObject
{
public:
    Decoration(int width, int height) : BaseObject(width, height)
    {
    }
    ~Decoration() {}

    bool addToBoard(vector<vector<int> > &board, Point position)
    {
        BaseObject::addToBoard(board, position);
        for (int i = leftTop.x; i < width; i++)
        {
            for (int j = leftTop.y; j < height; j++)
            {
                if (board[i][j] == DECORATION)
                {
                    //Confilct with other decoration
                    cout<<"board i:"<<i<<" j:"<<j<<" is ocupied by DECORATION"<<endl;
                    valid = false;
                    return false;
                }
                else
                {
                    board[i][j] = DECORATION;
                }
            }
        }
        return true;
    }
};

class SmallMine : public Decoration
{
public:
    SmallMine() : Decoration(2, 2)
    {
    }
    ~SmallMine() {}
};

class MiddleMine : public Decoration
{
public:
    MiddleMine() : Decoration(2, 3)
    {
    }
    MiddleMine(bool horizental) : Decoration(3, 2)
    {
    }
    ~MiddleMine() {}
};

class BigMine : public Decoration
{
public:
    BigMine() : Decoration(3, 3)
    {
    }
    ~BigMine() {}
};

class Propeller : public Decoration
{
public:
    Propeller() : Decoration(2, 2)
    {
    }
    ~Propeller() {}
};