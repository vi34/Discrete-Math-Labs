#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector <long long> d;
vector <vector <int> > g;

long long calc(int v)
{
    if(d[v] == -1)
    {
        d[v] = 0;
        for(int i = 0; i < g[v].size(); i++)
        {
            d[v] += calc(g[v][i]);
            d[v] %= 1000000007;
        }
    }
    return d[v];
}

int main ()
{
    freopen("countpaths.in", "r", stdin);
    freopen("countpaths.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    d.resize(n, -1);
    g.resize(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[b - 1].push_back(a - 1);
    }
    d[0] = 1;
    cout << calc(n - 1);
    return 0;
}
