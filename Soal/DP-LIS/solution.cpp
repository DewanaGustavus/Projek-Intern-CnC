#include <bits/stdc++.h>

using namespace std;

bool sortcmp(vector <int> v1, vector <int> v2) {
    return (v1[0] < v2[0]);
}

int main() {
    vector <vector <int>> listBox;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        vector <int> tv;
        for (int j = 0; j < 3; j++) {
            int ti;
            cin >> ti;
            tv.push_back(ti);
        }
        listBox.push_back(tv);
    }

    sort(listBox.begin(), listBox.end(), sortcmp);

    vector <int> dp;

    for (int i = 0; i < n; i++) {
        int val = listBox[i][2];
        int m = 0;
        for (int j = 0; j < i; j++) {
            if (listBox[j][0] < listBox[i][0] && listBox[j][1] < listBox[i][1] && dp[j] > m) {
                m = dp[j];
            }
        }
        dp.push_back(val + m);
    }

    cout << dp[n - 1] << endl;
}
