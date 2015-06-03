#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int n;

vector< vector<pair<int, int> > > g;
vector<int> match;
vector<int> used;


int min_rib;

bool dfs(int v, int border)
{
    if(used[v])
        return false;
    used[v] = true;
    for(int i = 0; i < n; ++i)
    {
        if(g[v][i].second <= border)
            continue;
        int u = i;

        if(match[u] == -1 || dfs(match[u], border))
        {
            match[u] = v;
            return true;
        }
    }
    return false;
}

bool kuhn(int border)
{
    min_rib = INF;
    int answ = 0;
    fill(match.begin(),match.end(),-1);

    for(int i = 0; i < n; ++i)
    {
        fill(used.begin(),used.end(),0);
        if(dfs(i, border))
            answ++;
    }

    if(answ == n)
        return true;
    else
        return false;
}

int main() {
    ifstream in("minimax.in");
    ofstream out("minimax.out");
    in >> n;
    g.resize(n, vector<pair<int,int> >(n));
    match.resize(n, -1);
    used.resize(n, 0);

    vector<pair<int,int> > edges(n * n);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
        {
            int cost;
            in >> cost;
            g[i][j].first = cost;
            edges[i * n + j] = make_pair(cost, i * n + j);
        }
    sort(edges.begin(), edges.end());
    for(int i = 0; i < edges.size(); ++i)
    {
        int ii, jj;
        ii = edges[i].second / n;
        jj = edges[i].second % n;
        g[ii][jj].second = i;
    }

    int l = 0;
    int r = edges.size() + 1;
    int m;
    while (l < r - 1)
    {
        m = (l + r) / 2;
        if(kuhn(m))
            l = m;
        else
            r = m;
    }

    out << edges[r].first;

    return 0;
}