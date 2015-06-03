#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define NAME "matching"
#define mp make_pair
#define pb push_back

using namespace std;

long long INF = 10000000000;

vector< vector<pair<int, int> > > g;
vector <long long> a;
vector <long long> b;
int n;

void rec(int v)
{
    if(a[v] == -1)
    {
        a[v] = 0;
        b[v] = 0;
        int i = 0;
        while(i < g[v].size())
        {
            if(a[g[v][i].first] == -1)
            {
                int to = g[v][i].first;
                rec(to);
                b[v] += max(a[to], b[to]);
                a[v] = max(a[v], g[v][i].second + b[to] - max(a[to], b[to]));
            }
            i++;
        }
        a[v] += b[v];
    }
}

int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    cin >> n;
    g.resize(n);
    a.resize(n, -1);
    b.resize(n, -1);
    
    for(int i = 0; i < n - 1; i++)
    {
        int v, u, w;
        cin >> v >> u >> w;
        g[v - 1].pb(mp(u - 1,w));
        g[u - 1].pb(mp(v - 1,w));
    }
    rec(0);
    cout << max(a[0], b[0]);
    
    return 0;
    
}