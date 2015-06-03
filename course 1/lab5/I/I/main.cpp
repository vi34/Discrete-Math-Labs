#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define NAME "salesman"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)

using namespace std;

long long INF = 10000000000;

vector< vector<pair<int, int> > > g;
vector <vector<long long > > d;
int n, m;
int mask;

long long rec(int mask, int curr)
{
    if(d[mask][curr] != INF)
        return d[mask][curr];
    
    rep0(i, g[curr].size())
    {
        int v = g[curr][i].first;
        int w = g[curr][i].second;
        if(mask & (1 << v))
        {
            d[mask][curr] = min(d[mask][curr], rec(mask - (1 << v),v) + w);
        }
    }
    return d[mask][curr];
}

int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    cin >> n >> m;
    g.resize(n);
    
    rep0(i, m)
    {
        int v, u, w;
        cin >> v >> u >> w;
        g[v - 1].pb(mp(u - 1,w));
        g[u - 1].pb(mp(v - 1,w));
    }
    long long answ = INF;
    rep0(i, n)
    {
        mask = (1 << (n)) - 1;
        mask -= (1 << i);
        d.resize(mask + 1, vector<long long>(n , INF));
        d[0][i] = 0;
        answ = min(answ, rec(mask, i));
    }
    if(answ == INF)
        cout << -1;
    else
        cout << answ;
    return 0;
    
}