#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long INF = 10000000000;

int main ()
{
    
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
    string s,t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    int d[2][m + 1];
    for(int i = 0; i <= 1; i++)
        d[i][0] = i;
    for(int i = 0; i <= m; i++)
        d[0][i] = i;
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            d[i % 2][0] = i;
            int pr = 1;
            if(s[i - 1] == t[j - 1])
                pr = 0;
            d[i % 2][j] = min(d[(i - 1) % 2][j] + 1, min(d[i % 2][j - 1] + 1, d[(i - 1) % 2][j - 1]+ pr) );
        }
    cout << d[n % 2][m];
    return 0;
}