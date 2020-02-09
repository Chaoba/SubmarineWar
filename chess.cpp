#include "decoration.cpp"

class Chess : public Square
{
public:
    vector<pair<Decoration *, Point>> decorations;
    Chess() : Square(5, 5) {}

    virtual CHESS_TYPE chessType() = 0;

    bool sameRow(Point &a, Point &b)
    {
        return a.x == b.x;
    }

    bool sameCol(Point &a, Point &b)
    {
        return a.y == b.y;
    }

    bool canMove(vector<vector<int>> &board, DERIECTION deriction)
    {
        if (decorations.size() == 3)
        { // Check the clip of submarine chess.
            auto clip = decorations[1].first;
            if (deriction == DOWN && clip->leftTop.x == 16 && clip->leftTop.y == 9)
            {
                //Skip the check for clip in the exit position for down deriction.
            }
            else
            {
                if (!clip->canMove(board, deriction))
                    return false;
            }
        }

        auto front = decorations.front().first;
        auto back = decorations.back().first;

        if (decorations.size() == 1)
        {
            return front->canMove(board, deriction);
        }
        else
        {
            auto frontLeftTop = front->leftTop;
            auto backLeftTop = back->leftTop;
            //Check for the situations that two decorations are in the same line and deriction.
            switch (deriction)
            {
            case UP:
                if (sameCol(frontLeftTop, backLeftTop))
                {
                    //For up, we only need to check the upper one.
                    return (frontLeftTop.x < backLeftTop.x ? front : back)
                        ->canMove(board, deriction);
                }
                break;
            case DOWN:
                if (sameCol(frontLeftTop, backLeftTop))
                {
                    //For down, we only need to check the lowwer one.
                    return (frontLeftTop.x > backLeftTop.x ? front : back)
                        ->canMove(board, deriction);
                }
                break;
            case LEFT:
                if (sameRow(frontLeftTop, backLeftTop))
                {
                    //For left, we only need to check the lefter one.
                    return (frontLeftTop.y < backLeftTop.y ? front : back)
                        ->canMove(board, deriction);
                }
                break;
            case RIGHT:
                if (sameRow(frontLeftTop, backLeftTop))
                {
                    //For right, we only need to check the righter one.
                    return (frontLeftTop.y > backLeftTop.y ? front : back)
                        ->canMove(board, deriction);
                }
                break;
            default:
                break;
            }
        }
        return (front->canMove(board, deriction) && back->canMove(board, deriction));
    }

    virtual bool removeFromBoard(vector<vector<int>> &board) override
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int x = leftTop.x + i;
                int y = leftTop.y + j;
                if (board[x][y] == CHESS || board[x][y] == chessType())
                {
                    board[x][y] = NONE;
                }
            }
        }

        //Add chess decorations.
        for (auto decoration : decorations)
        {
            decoration.first->removeFromBoard(board);
        }
        return true;
    }

    virtual bool addToBoard(vector<vector<int>> &board, Point position) override
    {
        Square::addToBoard(board, position);
        // cout << chessType() << "chess add to board" << endl;
        if (position.x < 0 || position.x > 19 || position.y < 0 || position.y > 19)
        {
            return false;
        }
        //Add current chess to board.
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int x = leftTop.x + i;
                int y = leftTop.y + j;
                if (board[x][y] == CHESS)
                {
                    //Confilct with other CHESS
                    cout << "board x:" << x << " y:" << y << " is ocupied by CHESS" << endl;
                    valid = false;
                    return valid;
                }
                else if (board[x][y] == DECORATION)
                {
                    continue;
                }
                else
                {
                    board[x][y] = CHESS;
                }
            }
        }
        board[leftTop.x + 2][leftTop.y + 2] = chessType();
        //Add chess decorations.
        for (auto decoration : decorations)
        {
            if (!decoration.first->addToBoard(board, position + decoration.second))
            {
                cout << "add decoration failed" << endl;
                valid = false;
                return false;
            }
        }
        return true;
    }

    virtual ~Chess()
    {
        for (auto decoration : decorations)
        {
            delete decoration.first;
        }
    }
};

class SubMarine : public Chess
{
public:
    SubMarine() : Chess()
    {
        //Add two propellers on top left and top right.
        decorations.push_back({new Propeller(), {0, -2}});
        decorations.push_back({new Clip(), {4, 2}});
        decorations.push_back({new Propeller(), {0, width}});
    }
    ~SubMarine() {}
    CHESS_TYPE chessType() override
    {
        return SUB_MARINE;
    }
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
                decorations.push_back({new SmallMine(), {0, 0}});
                break;
            case RIGHT_TOP:
                decorations.push_back({new SmallMine(), {0, width - 2}});
                break;
            case LEFT_BOTTOM:
                decorations.push_back({new SmallMine(), {height - 2, 0}});
                break;
            case RIGHT_BOTTOM:
                decorations.push_back({new SmallMine(), {height - 2, width - 2}});
                break;
            default:
                cout << "wrong position" << position << endl;
            }
        }
    }

    ~SmallMineChess() {}
    CHESS_TYPE chessType() override
    {
        return SMALL_MINE;
    }
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
            decorations.push_back({new MiddleMine(), {1, -1}});
            break;
        case TOP_BORDER:
            decorations.push_back({new MiddleMine(true), {-1, 1}});
            break;
        case RIGHT_BORDER:
            decorations.push_back({new MiddleMine(), {1, width - 1}});
            break;
        case BOTTOM_BORDER:
            decorations.push_back({new MiddleMine(true), {height - 1, 1}});
            break;
        default:
            cout << "wrong position" << position << endl;
        }
    }
    ~MiddleMineChess() {}
    CHESS_TYPE chessType() override
    {
        return MIDDLE_MINE;
    }
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
            decorations.push_back({new BigMine(), {-2, -2}});
            break;
        case RIGHT_TOP:
            decorations.push_back({new BigMine(), {-2, width - 1}});
            break;
        case LEFT_BOTTOM:
            decorations.push_back({new BigMine(), {width - 1, -2}});
            break;
        case RIGHT_BOTTOM:
            decorations.push_back({new BigMine(), {height - 1, width - 1}});
            break;
        default:
            cout << "wrong position" << position << endl;
        }
    }
    ~BigMineChess() {}
    CHESS_TYPE chessType() override
    {
        return BIG_MINE;
    }
};