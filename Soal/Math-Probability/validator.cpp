#include <bits/stdc++.h>

using namespace std;
const double EPS = 1e-5;
const int EXIT_AC = 42;
const int EXIT_WA = 43;
int ac()
{
    exit(EXIT_AC);
    return 0;
}

int wa()
{
    exit(EXIT_WA);
    return 0;
}

int main(int argc, char *argv[])
{
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);

    double tc_ans;
    tc_out >> tc_ans;

    double con_ans;
    if (!(cin >> con_ans))
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