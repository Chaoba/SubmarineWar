#include "chess.cpp"
int main(int argc, char **argv)
{
    vector<vector<Chess>> chesses(3, vector<Chess>(3));
    vector<vector<int>> board(19, vector<int>(19, 0));
    chesses[0][0] = SmallMineChess(vector<POSITION>(1, LEFT_TOP));
    chesses[0][1] = MiddleMineChess(RIGHT_BORDER);
    chesses[0][2] = SmallMineChess(vector<POSITION>(1, RIGHT_TOP));
    POSITION small1[] = {LEFT_BOTTOM, RIGHT_BOTTOM};
    chesses[1][0] = SmallMineChess(vector<POSITION>(small1, small1 + sizeof(small1) / sizeof(POSITION)));
    POSITION small2[] = {LEFT_TOP, RIGHT_BOTTOM};
    chesses[1][1] = SmallMineChess(vector<POSITION>(small2, small2 + sizeof(small2) / sizeof(POSITION)));
    chesses[1][2] = SubMarine();
    chesses[2][0] = SmallMineChess(vector<POSITION>(1, LEFT_BOTTOM));
    chesses[2][1] = EmptyChess();
    chesses[2][1] = BigMineChess(RIGHT_BOTTOM);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!chesses[i][j].addToBoard(board, {2 + j * 5, 2 + i * 5}))
            {
                cout << "Add chess faild:" << i << "  " << j << endl;
            }
        }
    }
    cout<<"Add chesses succeed."<<endl;
}