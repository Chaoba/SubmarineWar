#include "submarineWar.cpp"
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void createQuestin(string s)
{
    if (s.size() == 0)
        return;
    int index = 0, x = 0, y = 0;
    vector<vector<Chess *>> chesses(3, vector<Chess *>(3));
    vector<vector<int>> board(19, vector<int>(19, 0));

    while (index < s.size())
    {
        // cout<<"Add chesses:"<<s[index]<<endl;
        switch (s[index])
        {
        case 'T':
            // cout << "Create submarine." << endl;
            chesses[x][y] = new SubMarine();
            index += 2;
            break;
        case 'E':
            index += 2;
            break;
        case 'S':
        {
            vector<POSITION> mines;
            index++;

            while (index < s.size() && s[index] != ',')
            {
                mines.push_back(POSITION(s[index] - '0'));
                index++;
            }
            index++;
            // cout << "Create SmallMineChess. " << mines.size() << endl;
            chesses[x][y] = new SmallMineChess(mines);
        }
        break;
        case 'M':
            index++;
            // cout << "Create MiddleMineChess." << endl;

            chesses[x][y] = new MiddleMineChess(POSITION(s[index] - '0'));
            index += 2;
            break;
        case 'B':
            index++;
            // cout << "Create BigMineChess." << endl;

            chesses[x][y] = new BigMineChess(POSITION(s[index] - '0'));
            index += 2;
            break;
        default:
            cout << "default" << endl;
        }

        y++;
        if (y > 2)
        {
            x++;
            y = 0;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // cout << chesses[i][j]->chessType() << endl;
            // printBoard(board);
            if (chesses[i][j] && !chesses[i][j]->addToBoard(board, {2 + i * 5, 2 + j * 5},{0,0}))
            {
                cout << "Add chess faild:" << i << "  " << j << endl;
                return;
            }
        }
    }
    // cout << "Add chesses succeed." << endl;
    vector<int> result = SubmarineWar().findPath(chesses, board);
    if (result.empty())
    {
        cout << "Can't find a path." << endl;
    }
    else
    {
        cout<<result.size();
        for (auto i : result)
        {
            switch (i)
            {
            case 0:
                cout << " ← ";
                break;
            case 1:
                cout << " ↑ ";
                break;
            case 2:
                cout << " ↓ ";
                break;
            default:
                cout << " → ";
            }
        }
    }
    cout<<endl;
}

int main()
{

    ifstream in("questions.txt");
    string filename;
    string line;

    if (in)
    {
        while (getline(in, line))
        {
            // cout << line << endl;
            createQuestin(line);
        }
    }
}
