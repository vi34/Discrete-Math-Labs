#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "shooter"
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
    int n, m, k;
    cin >> n >> m >> k;
    long double b = 0.0, pbk;
    long double a = (1.0 / n);
    rep0(i, n)
    {
        double p, pq;
        scanf("%lf", &p);
        pq = 1 - p;
        long double pi = pq;
        rep0(j, m - 1)
            pi *= pq;
        if(i == k - 1)
            pbk = pi;
        b += pi * a;
    }
    long double ans = (pbk * a) / b;
    cout.precision(13);
    cout << ans;
    return 0;
}