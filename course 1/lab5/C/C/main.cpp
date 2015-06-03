#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long INF = 10000000000; 

int main ()
{
    
    //freopen("lcs.in", "r", stdin);
    //freopen("lcs.out", "w", stdout);
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int m;
    cin >> m;
    int b[m];
    for(int i = 0; i < m; i++)
        cin >> b[i];
    
    int d[n + 1][m + 1];
    int p[n + 1][m + 1];
    for(int i = 0; i <= n; i++)
        d[i][0] = 0;
    for(int i = 0; i <= m; i++)
        d[0][i] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            if(a[i - 1] == b[j - 1])
            {
                d[i][j] = d[i - 1][j - 1] + 1;
                p[i][j] = 0;
            }
            else if(d[i - 1][j] > d[i][j - 1])
            {
                d[i][j] = d[i - 1][j];
                p[i][j] = 1;
            }
            else{
                d[i][j] = d[i][j - 1];
                p[i][j] = 2;
            }
        }
    int k = d[n][m];
    cout << k << endl;
    int i = n, j = m;
    vector <int> answ(k);
    while(i != 0 && j != 0)
    {
        if(p[i][j] == 0)
        {
            answ[--k] = a[i - 1];
            i--;
            j--;
        }
        else if(p[i][j] == 1)
            i--;
        else
            j--;
    }
    for(int i = 0; i < answ.size(); i++)
        cout << answ[i] << " ";
    
    return 0;
}

