#include "submarineWar.cpp"
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void createQuestin(string s, int maxStep, int showLog, int findShortest)
{
    if (s.size() == 0)
        return;
    int index = s.find_first_of('.') + 1, x = 0, y = 0;
    if(index == -1){
        cout<<"Question format error."<<endl;
        return;
    }
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
            if (chesses[i][j] && !chesses[i][j]->addToBoard(board, {2 + i * 5, 2 + j * 5}, {0, 0}))
            {
                cout << "Add chess faild:" << i << "  " << j << endl;
                return;
            }
        }
    }
    // cout << "Add chesses succeed." << endl;
    vector<int> result = SubmarineWar(maxStep, showLog, findShortest).findPath(chesses, board);
    if (result.empty())
    {
        cout << "Can't find a path." << endl;
    }
    else
    {
        cout << result.size() << " steps:";
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
    cout << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "Please set questionNumm maxStep, showLog, findShortest, for example SubmarineWar 1 100 0 1" << endl;
        return 0;
    }
    int qeustionNum = stoi(argv[1]);
    int maxStep = stoi(argv[2]);
    int showLog = stoi(argv[3]);
    int findShortest = stoi(argv[4]);
    ifstream in("questions.txt");
    string filename;
    string line;

    if (in)
    {
        while (qeustionNum > 0 && getline(in, line))
        {
            qeustionNum--;
            createQuestin(line, maxStep, showLog, findShortest);
        }
    }
}
