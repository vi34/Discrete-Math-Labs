
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long INF = 10000000000;

int main ()
{
    
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    int v[n], c[n];
    int d[n + 1][m + 1];
    for(int i = 0; i < n; i++)
        cin >> v[i];
    for(int i = 0; i < n; i++)
    {
        cin >> c[i];
        d[i][0] = 0;
    }
    d[n][0] = 0;
    for(int i = 0; i <= m; i++)
        d[0][i] = 0;
    
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= m; j++)
            if(j >= v[i - 1])
                d[i][j] = max(d[i - 1][j], d[i - 1][j - v[i - 1]] + c[i - 1]);
            else
                d[i][j] = d[i - 1][j];
    
    
    vector <int> answ;
    int i = n, j = m;
    int count = 0;
    while(d[i][j] != 0)
    {
        if(d[i - 1][j] == d[i][j])
            i--;
        else
        {
            count++;
            answ.push_back(i);
            j -= v[i - 1];
            i--;
        }
    }
    reverse(answ.begin(), answ.end());
    cout << count << endl;
    for(int l = 0; l < answ.size(); l++)
    {
        printf("%d ", answ[l]);
    }
    return 0;
}