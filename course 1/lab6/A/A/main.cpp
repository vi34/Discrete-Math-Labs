#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "exam"
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
    int n, k;
    scanf("%d %d", &k, &n);
    long double answ = 0.0;
    rep0(i, k)
    {
        double p, m;
        scanf("%lf %lf", &p, &m);
        answ += (p/n) * (m / 100);
    }
    cout.precision(5);
    cout << answ;
    return 0;
}