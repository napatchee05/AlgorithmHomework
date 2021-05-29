#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<int> G[1000];
int board[1000][1000];
set<int> specialPoint;
bool used[1000];
queue<vector<int> > q;
int myC;

void printVector(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

bool contain(vector<int> &v, int x)
{
    return find(v.begin(), v.end(), x) != v.end();
}

int lastPos(vector<int> &v)
{
    return v[v.size() - 1];
}

void clearCantReach()
{
    queue<vector<int> > newq;
    while (!q.empty())
    {
        vector<int> fr = q.front();
        q.pop();
        int last = lastPos(fr);
        if (specialPoint.find(last) != specialPoint.end())
        {
            newq.push(fr);
        }
    }
    q = newq;
}

void pathWalk(vector<int> path)
{
    int lastPos = path[path.size() - 1];
    path.push_back(-1);
    for (int i = 0; i < G[lastPos].size(); i++)
    {
        int v = G[lastPos][i];
        if (!contain(path, v))
        {
            path.pop_back();
            path.push_back(v);
            q.push(path);
            myC++;
        }
    }
}

int main()
{
    cout << "Enter Row and Column (R,C)\n";
    int r, c;
    cin >> r >> c;
    int n = r * c;

    for (int i = 0; i <= r + 1; i++)
    {
        board[i][0] = 9;
        board[i][c + 1] = 9;
    }

    for (int i = 0; i <= c + 1; i++)
    {
        board[0][i] = 9;
        board[r + 1][i] = 9;
    }

    cout << "Enter your Special Point (r,c)\n";
    for (int i = 0; i < 3; i++)
    {
        int a, b;
        cin >> a >> b;
        board[a][b] = 2;
    }

    board[1][2] = 1;

    // for (int i = 0; i <= r + 1; i++)
    // {
    //     for (int j = 0; j <= c + 1; j++)
    //     {
    //         cout << board[i][j];
    //     }
    //     cout << "\n";
    // }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            int idx = (i - 1) * c + j;
            if (board[i][j] == 2)
                specialPoint.insert(idx);
            if (board[i - 1][j] != 9 && board[i - 1][j] != 1)
                G[idx].push_back(idx - c);
            if (board[i][j - 1] != 9 && board[i][j - 1] != 1)
                G[idx].push_back(idx - 1);
            if (board[i][j + 1] != 9 && board[i][j + 1] != 1)
                G[idx].push_back(idx + 1);
            if (board[i + 1][j] != 9 && board[i + 1][j] != 1)
                G[idx].push_back(idx + c);
        }
    }

    vector<int> v;
    v.push_back(1);
    pathWalk(v);
    myC = 1;

    for (int i = 1; i <= 3; i++)
    {
        while (q.front().size() != i * n / 4)
        {
            v = q.front();
            q.pop();
            pathWalk(v);
        }
        clearCantReach();
    }

    if (r >= 2 && c >= 2)
    {
        G[2 + c].push_back(2);
    }

    if (r >= 1 && c >= 3)
    {
        G[3].push_back(2);
    }

    specialPoint.insert(2);

    while (q.front().size() != n)
    {
        v = q.front();
        q.pop();
        pathWalk(v);
    }

    clearCantReach();

    cout << "Amount of Possible Path : " << q.size() << "\n";

    while (!q.empty())
    {
        cout << "path : ";
        printVector(q.front());
        q.pop();
    }

    cout << "Number of node : " << myC << "\n";
}
