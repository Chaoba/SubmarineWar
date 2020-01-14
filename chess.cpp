#include "decoration.cpp"

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
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};
class Chess : public BaseObject
{
public:
    vector<pair<Decoration, Point>> decorations;
    Chess() : BaseObject(5, 5)
    {
    }
    bool addToBoard(vector<vector<int>> &board, Point position)
    {
        BaseObject::addToBoard(board, position);
        //Add current chess to board.
        for (int i = leftTop.x; i < width; i++)
        {
            for (int j = leftTop.y; j < height; j++)
            {
                if (board[i][j] == CHESS)
                {
                    //Confilct with other CHESS
                    cout<<"board i:"<<i<<" j:"<<j<<" is ocupied by CHESS"<<endl;
                    valid = false;
                    return valid;
                }
                else
                {
                    board[i][j] = CHESS;
                }
            }
        }

        //Add chess decorations.
        for (auto decoration : decorations)
        {
            if (!decoration.first.addToBoard(board, position + decoration.second))
            {
                cout<<"add decoration failed"<<endl;
                valid = false;
                return false;
            }
        }
        return true;
    }
    ~Chess()
    {
    }
};

class SubMarine : public Chess
{
public:
    SubMarine() : Chess()
    {
        //Add two propellers on top left and top right.
        decorations.push_back({Propeller(), {leftTop.x - 2, leftTop.y}});
        decorations.push_back({Propeller(), {leftTop.x + width, leftTop.y}});
    }
    ~SubMarine() {}
};

class SmallMineChess : public Chess
{
public:
    SmallMineChess(vector<POSITION> positions) : Chess()
    {
        for (auto position : positions)
        {
            if (position > RIGHT_BOTTOM)
            {
                cout << "SmallMine must on four corners!" << endl;
                valid = false;
                return;
            }

            switch (position)
            {
            case LEFT_TOP:
                decorations.push_back({SmallMine(), leftTop});
                break;
            case RIGHT_TOP:
                decorations.push_back({SmallMine(), {leftTop.x - 2, leftTop.y}});
                break;
            case LEFT_BOTTOM:
                decorations.push_back({SmallMine(), {leftTop.x, leftTop.y + height - 2}});
                break;
            case RIGHT_BOTTOM:
                decorations.push_back({SmallMine(), {leftTop.x + width - 2, leftTop.y + height - 2}});
                break;
            }
        }
    }
    ~SmallMineChess() {}
};

class MiddleMineChess : public Chess
{
public:
    MiddleMineChess(POSITION position) : Chess()
    {

        if (position < RIGHT_BOTTOM)
        {
            cout << "MiddleMine must on four borders!" << endl;
            valid = false;
            return;
        }

        switch (position)
        {
        case LEFT_BORDER:
            decorations.push_back({MiddleMine(), {leftTop.x - 1, leftTop.y + 1}});
            break;
        case TOP_BORDER:
            decorations.push_back({MiddleMine(true), {leftTop.x + 1, leftTop.y - 1}});
            break;
        case RIGHT_BORDER:
            decorations.push_back({MiddleMine(), {leftTop.x + width - 1, leftTop.y + 1}});
            break;
        case BOTTOM_BORDER:
            decorations.push_back({MiddleMine(true), {leftTop.x + width - 1, leftTop.y + height + 1}});
            break;
        }
    }
    ~MiddleMineChess() {}
};

class BigMineChess : public Chess
{
public:
    BigMineChess(POSITION position) : Chess()
    {
        if (position > RIGHT_BOTTOM)
        {
            cout << "BigMine must on four corners!" << endl;
            valid = false;
            return;
        }

        switch (position)
        {
        case LEFT_TOP:
            decorations.push_back({BigMine(), {leftTop.x - 2, leftTop.y - 2}});
            break;
        case RIGHT_TOP:
            decorations.push_back({BigMine(), {leftTop.x + width - 1, leftTop.y - 2}});
            break;
        case LEFT_BOTTOM:
            decorations.push_back({BigMine(), {leftTop.x - 2, leftTop.y + height - 1}});
            break;
        case RIGHT_BOTTOM:
            decorations.push_back({BigMine(), {leftTop.x + width - 1, leftTop.y + height - 1}});
            break;
        }
    }
    ~BigMineChess() {}
};

class EmptyChess : public Chess
{
};