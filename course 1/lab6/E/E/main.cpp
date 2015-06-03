#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "markchain"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;



int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    int n;
    cin >> n;
    vector< vector<long double> > m(n, vector<long double>(n));
    rep0(i, n)
        rep0(j, n)
            cin >> m[i][j];
    rep0(num, 7)
    {
        vector< vector<long double> > t = m;
        rep0(i, n)
            rep0(j, n)
            {
                m[i][j] = 0;
                rep0(k, n)
                    m[i][j] +=t[i][k] * t[k][j];
            }
    }
    cout.precision(4);
    rep0(i, n)
        cout << m[0][i] << endl;
    
    return 0;
}