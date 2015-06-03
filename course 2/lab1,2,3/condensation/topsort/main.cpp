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
#include <array>

#define NAME "map"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

vector<int> t;
vector< vector<int> > g;
vector< vector<int> > rg;
vector<int> topsort;
vector<int> answer;
array<int, 5> a;
int c = 1;

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

void dfs2(int v)
{
    t[v] = 1;
    for(int i = 0; i < rg[v].size(); ++i)
    {
        int u = rg[v][i];
        if(!t[u])
            dfs2(u);
    }
    t[v] = 2;
    answer[v] = c;
}


int main ()
{

    ifstream in("cond.in");
    ofstream out("cond.out");
    int n,m;
    in >> n >> m;
    g.resize(n);
    rg.resize(n);
    t.resize(n,0);
    answer.resize(n);
    for(int i = 0; i < m; ++i)
    {
        int a,b;
        in >> a >> b;
        g[a - 1].push_back(b - 1);
        rg[b - 1].push_back(a - 1);
    }

    for(int i = 0; i < n; ++i)
    {
        if(!t[i])
            dfs(i);
    }

    reverse(topsort.begin(), topsort.end());
    fill(t.begin(),t.end(),0);

    for(int i = 0; i < n; ++i)
    {
        if(!t[topsort[i]])
        {
            dfs2(topsort[i]);
            c++;
        }
    }

    out << c - 1 << endl;

    rep0(i,n)
    {
        out << answer[i] << " ";
    }
    return 0;
}


