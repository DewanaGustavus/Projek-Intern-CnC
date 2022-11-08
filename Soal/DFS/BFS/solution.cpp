#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 2;

int visited[maxn][maxn] = {0};
int arr[maxn][maxn];
int n,m;
int maks = 0;
int temp_area = 0;
int movx[] = {1,1,1,0,0,-1,-1,-1};
int movy[] = {-1,0,1,1,-1,1,0,-1};


bool in_range(int j,int i)
{
    return j>=1 && j <= n && i >=1 && i <=m && arr[j][i] == 1;
}


void dfs(int j,int i)
{
    visited[j][i] = 1;
    temp_area++;

    for(int x = 0;x < 8;x++)
    {
        int newi = movx[x] + i;
        int newj = movy[x] + j;
        if(in_range(newj,newi) && !visited[newj][newi])
        {
            dfs(newj,newi);
        }
    }

}




int main()
{
    cin >> n >> m;

    for(int j =1;j <=n;j++)
    {
        for(int i = 1;i <=m;i++)
        {
            cin >> arr[j][i];
        }
    }

    // start dfs;

    for(int j = 1;j <=n;j++)
    {
        for(int i = 1;i <=m;i++)
        {
            if(!visited[j][i] && arr[j][i] == 1)
            {
                temp_area = 0;
                dfs(j,i);
                maks = max(maks,temp_area);
            }
        }
    }

    cout << maks;


    return 0;
}