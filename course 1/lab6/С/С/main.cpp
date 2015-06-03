#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "lottery"
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
    int n, m;
    long double E = 0.0;
    long double pr = 1.0;
    int prb = 0;
    cin >> n >> m;
    rep0(i, m)
    {
        double a, b;
        scanf("%lf %lf", &a, &b);
        long double p = (a - 1) / a;
        E += (n - prb) * p * pr;
        pr *= (1.0 / a);
        prb = b;
    }
    E += (n - prb) * pr;
    cout.precision(13);
    cout << E;
    return 0;
}