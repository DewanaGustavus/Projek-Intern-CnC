#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int tc;
    cin >> tc;
    while (tc--)
    {
        int X, N;
        string op;
        cin >> X >> N >> op;

        if (op == "AND" || op == "OR" || (N & 1))
        {
            for (int i = 0; i < N; i++)
            {
                cout << X;
                if (i < N - 1)
                    cout << ' ';
            }
            cout << '\n';
        }
        else
        {
            int p1, p2;
            if (X == 1)
                p1 = 2;
            else if (X == 1e9)
                p1 = X - 1;
            else
                p1 = 1;
            p2 = X ^ p1;
            cout << p1 << ' ' << p2;
            for (int i = 2; i < N; i++)
            {
                cout << ' ' << X;
            }
            cout << '\n';
        }
    }
}