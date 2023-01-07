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

    double tc_ans;
    tc_out >> tc_ans;

    double con_ans;
    if (!(con_out >> con_ans))
    {
        return wa();
    }

    if (abs(tc_ans - con_ans) < EPS)
    {
        return ac();
    }
    else
    {
        return wa();
    }
}