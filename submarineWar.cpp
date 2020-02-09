#include "chess.cpp"

class SubmarineWar
{
private:
    pair<int, int> moveDeriction[4] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
    int maxStep;
    int showLog;
    int findShortest;

public:
    SubmarineWar(int _maxStep, int _showLog, int _findShortest) : maxStep(_maxStep), showLog(_showLog), findShortest(_findShortest) {}
    ~SubmarineWar() = default;
    void printBoard(vector<vector<int>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if ((i - 4) % 5 == 0 && (j - 4) % 5 == 0)
                {
                    cout << "\033[32m" << board[i][j] << " \033[0m";
                }
                else
                {
                    cout << board[i][j] << " ";
                }
                if ((j - 1) % 5 == 0)
                {
                    cout << "\033[31m| \033[0m";
                }
            }

            cout << endl;
            if ((i - 1) % 5 == 0)
            {
                for (int j = 0; j < board[0].size() + 4; j++)
                {
                    cout << "\033[31m--\033[0m";
                }
                cout << endl;
            }
        }
    }

    vector<int> findPath(vector<vector<Chess *>> &chesses, vector<vector<int>> &board)
    {
        if(chesses.size() != 3 || chesses[0].size() != 3 || board.size() != 19 || board[0].size() != 19) {
            cout<<"chesses or board size error!"<<endl;
            return {};
        }

        if (showLog)
        {
            printBoard(board);
        }

        vector<int> path;
        vector<int> minPath;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {

                if (!chesses[i][j])
                {
                    if (showLog)
                    {
                        cout << "EMPTY is at " << i << " " << j << endl;
                    }
                    dfsFind(chesses, board, path, minPath, i, j);
                    if (!minPath.empty())
                    {
                        // cout << "Find a path" << endl;
                        return minPath;
                    }
                }
            }
        }
        return {};
    }

private:
    //(x,y) is the empty chess location.
    bool dfsFind(vector<vector<Chess *>> &chesses, vector<vector<int>> &board, vector<int> &path, vector<int> &minPath, int x, int y)
    {

        if (path.size() > maxStep)
        {
            return false;
        }

        for (int i = 0; i < 4; i++)
        {
            if ((!path.empty() && path.back() == i))
            {
                //The deriection last step comes from.
                continue;
            }
            int nextX = x + moveDeriction[i].first;
            int nextY = y + moveDeriction[i].second;
            if (nextX < 0 || nextX > 2 || nextY < 0 || nextY > 2)
            {
                continue;
            }
            if (showLog)
            {
                cout << "dfs find x:" << x << " y:" << y << "  nextX:" << nextX << "  nextY:" << nextY << "deriection:" << 3 - i << endl;
            }

            //1. Find a valid movable deriction.
            if (chesses[nextX][nextY]->canMove(board, DERIECTION(3 - i))) //Move to the current empty position.
            {
                if (showLog)
                {
                    cout << "can move:" << 3 - i << endl;
                    printBoard(board);
                }
                //2. Save the path.
                path.push_back(3 - i);

                //3. Remove this chess from board.
                chesses[nextX][nextY]->removeFromBoard(board);
                //4. Move this chess in chess array.
                chesses[x][y] = chesses[nextX][nextY];
                chesses[nextX][nextY] = nullptr;

                //5. Add this chess to the board with the target position.
                if (!chesses[x][y]->addToBoard(board, {2 + x * 5, 2 + y * 5}))
                {
                    cout << "add to board failed" << endl;
                    return false;
                }

                if (x == 2 && y == 1 && chesses[x][y]->chessType() == SUB_MARINE)
                {
                    if (chesses[x][y]->canMove(board, DOWN))
                    {
                        path.push_back(DOWN);
                        if (maxStep > path.size())
                        {
                            if (showLog)
                            {
                                cout << "find a path, size:" << path.size() << endl;
                            }
                            minPath = path;
                            maxStep = minPath.size();
                            if (!findShortest)
                            {
                                return true;
                            }
                        }
                        path.pop_back();
                    }
                }

                //6. Do dfs search.(nextX, nextY) shoule be empty chess.
                if (dfsFind(chesses, board, path, minPath, nextX, nextY))
                {
                    //find a path
                    if (!findShortest)
                    {
                        return true;
                    }
                }

                //7. Revert chess position
                chesses[x][y]->removeFromBoard(board);
                chesses[nextX][nextY] = chesses[x][y];
                chesses[x][y] = nullptr;
                if (!chesses[nextX][nextY]->addToBoard(board, {2 + nextX * 5, 2 + nextY * 5}))
                {
                    cout << "add to board failed" << endl;
                    return false;
                }

                path.pop_back();
            }
        }
        return false;
    }
};