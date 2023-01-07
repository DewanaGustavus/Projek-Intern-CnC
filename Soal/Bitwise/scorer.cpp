#include <bits/stdc++.h>

using namespace std;
const double EPS = 1e-5;
int ac()
{
    cout << "AC" << endl;
    return 0;
}

int wa()
{
    cout << "WA" << endl;
    return 0;
}

int main(int argc, char *argv[])
{
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);

    int tc;
    string s_tc;
    getline(tc_in, s_tc);
    tc = atoi(s_tc.c_str());

    for (int i = 0; i < tc; i++)
    {
        string s_in, s_out;
        getline(tc_in, s_in);
        getline(con_out, s_out);
        stringstream str_in(s_in);
        stringstream str_out(s_out);

        int N, X;
        string op;
        str_in >> X >> N >> op;

        int total = 0;
        if (!(str_out >> total))
            return wa();

        int temp;
        for (int i = 1; i < N; i++)
        {
            if (!(str_out >> temp))
                return wa();
            if (temp < 1 || temp > 1e9)
                return wa();

            if (op == "AND")
                total &= temp;
            else if (op == "OR")
                total |= temp;
            else if (op == "XOR")
                total ^= temp;
        }
        if (str_out >> temp)
            return wa();
        if (total != X)
            return wa();
    }
    return ac();
}
