//
//  main.cpp
//  topsort
//
//  Created by Виктор Шатров on 29.09.14.
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

vector<int> t;
vector< vector<int> > g;
vector<int> topsort;

void dfs(int v)
{
    t[v] = 1;
    for(int i = 0; i < g[v].size(); ++i)
    {
        int u = g[v][i];
        if(!t[u])
            dfs(u);
    }
    t[v] = 2;
    topsort.push_back(v);
}




int main ()
{

    ifstream in("hamiltonian.in");
    ofstream out("hamiltonian.out");
    int n,m;
    in >> n >> m;
    g.resize(n);
    t.resize(n,0);
    for(int i = 0; i < m; ++i)
    {
        int a, b;
        in >> a >> b;
        g[a - 1].push_back(b - 1);
    }

    for(int i = 0; i < n; ++i)
    {
        if(!t[i])
            dfs(i);
    }

    reverse(topsort.begin(), topsort.end());
    for(int i = 0; i < n - 1; i++)
    {
        int v = topsort[i];
        bool ok = false;
        for(int j = 0; j < g[v].size(); ++j)
        {
            if(g[v][j] == topsort[i + 1])
            {
                ok = true;
                break;
            }
        }
        if(!ok)
        {
            out << "NO";
            return 0;
        }
    }

    out << "YES";

    return 0;
}


