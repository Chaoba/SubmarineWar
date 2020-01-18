#include "square.cpp"
class Decoration : public Square
{
public:
    Decoration(int width, int height) : Square(width, height)
    {
    }
    virtual ~Decoration() {}

    bool canMove(vector<vector<int>> &board, DERIECTION deriction)
    {
        // cout << "canMove:" << deriction << "  leftop.x:" << leftTop.x << "  y:" << leftTop.y << endl;
        for (int move = 1; move <= 5; move++)
        {
            // cout << "Move:" << move << endl;
            switch (deriction)
            {
            case UP:
                // cout << "Check up" << endl;
                for (int i = leftTop.x, j = leftTop.y; j < leftTop.y + width; j++)
                {
                    if (i - move < 0 || board[i - move][j] == DECORATION)
                    {
                        return false;
                    }
                }
                break;
            case DOWN:
                // cout << "Check Down" << endl;

                for (int i = leftTop.x + height - 1, j = leftTop.y; j < leftTop.y + width; j++)
                {
                    if (i + move >= 19 || board[i + move][j] == DECORATION)
                    {
                        return false;
                    }
                }
                break;
            case LEFT:
                // cout << "Check Left" << endl;

                for (int i = leftTop.x, j = leftTop.y; i < leftTop.x + height; i++)
                {
                    if (j - move < 0 || board[i][j - move] == DECORATION)
                    {
                        return false;
                    }
                }
                break;
            case RIGHT:
                // cout << "Check Right" << endl;

                for (int i = leftTop.x, j = leftTop.y + width - 1; i < leftTop.x + height; i++)
                {
                    // cout << i << "==== " << j + move << " ==== " << board[i][j + move] << endl;
                    if (j + move >= 19 || board[i][j + move] == DECORATION)
                    {
                        return false;
                    }
                }
                break;
            }
        }
        return true;
    }

    virtual bool removeFromBoard(vector<vector<int>> &board) override
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int x = leftTop.x + i;
                int y = leftTop.y + j;
                if (board[x][y] == DECORATION)
                {
                    board[x][y] = NONE;
                }
            }
        }
        return true;
    }

    virtual bool addToBoard(vector<vector<int>> &board, Point position, Point parentPosition) override
    {
        Square::addToBoard(board, position, parentPosition);
        // cout << "decoration add to board, leftTop.x:" << leftTop.x << "  y:" << leftTop.y << "  width:" << width << "  height:" << height << endl;
        if (position.x < 0 || position.x > 19 || position.y < 0 || position.y > 19)
        {
            return false;
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int x = leftTop.x + i;
                int y = leftTop.y + j;
                if (board[x][y] == DECORATION)
                {
                    //Confilct with other decoration
                    cout << "board x:" << x << " y:" << y << " is ocupied by DECORATION" << endl;
                    valid = false;
                    return false;
                }
                else
                {
                    board[x][y] = DECORATION;
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
class Clip : public Decoration
{
public:
    Clip() : Decoration(1, 1)
    {
    }
    ~Clip() {}
};