//  Copyright (c) 2014 Виктор Шатров. All rights reserved.
//

#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>
#include <fstream>

#define NAME "map"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

vector<int> color;
vector< vector< int> > g;
vector<bool> visited;
bool answer = true;

void dfs(int v, int c)
{
    visited[v] = true;
    color[v] = c;
    for(int i = 0; i < g[v].size(); ++i)
    {
        int u = g[v][i];
        if(!visited[u])
        {
            dfs(u,!c);
        }
        else if(color[u] == color[v])
        {
            answer = false;
            break;
        }

    }
}

int main ()
{

    ifstream in("bipartite.in");
    ofstream out("bipartite.out");
    int n,m;
    in >> n >> m;
    g.resize(n);
    visited.resize(n, false);
    color.resize(n,0);
    for(int i = 0; i < m; ++i)
    {
        int a,b;
        in >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    for(int i = 0; i < n; ++i)
    {
        if(!visited[i])
        {
            dfs(i,0);
        }
    }
    if(answer)
        out << "YES";
    else
        out << "NO";
    return 0;
}


