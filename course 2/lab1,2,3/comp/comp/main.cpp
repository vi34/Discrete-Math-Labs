
//
//  main.cpp
//  topsort
//
//  Copyright (c) 2014 Р’РёРєС‚РѕСЂ РЁР°С‚СЂРѕРІ. All rights reserved.
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
#include <stack>

#define NAME "map"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

vector<int> color;
vector< vector<pair <int,int> > > g;
vector<int> up;
vector<int> answer;
vector<int> enter;
stack<int> st;
int t = 0;
int c = 1;

void dfs(int v, int parent)
{
    color[v] = 1;
    enter[v] = t++;
    up[v] = enter[v];
    int childrens = 0;
    bool point = true;
    for(int i = 0; i < g[v].size(); ++i)
    {
        int u = g[v][i].first;
        if(u == parent)
            continue;
        if(!color[u])
        {
            childrens++;
            if(v == parent && childrens > 1)
            {
                while (st.size() > 0) {
                    answer[st.top()] = c;
                    st.pop();
                }
                c++;
            }
            st.push(g[v][i].second);
            dfs(u,v);
            up[v] = min(up[u], up[v]);
            if(up[u] >= enter[v] && point && v != parent)
            {
                while (st.top() != g[v][i].second) {
                    answer[st.top()] = c;
                    st.pop();
                }
                answer[g[v][i].second] = c;
                st.pop();
                c++;
            }
        }
        else
        {
            up[v] = min(enter[u], up[v]);
            if(color[u] == 1)
                st.push(g[v][i].second);
        }

    }
    color[v] = 2;
}

int main ()
{

    ifstream in("biconv.in");
    ofstream out("biconv.out");
    int n,m;
    in >> n >> m;
    g.resize(n);
    up.resize(n);
    color.resize(n,0);
    enter.resize(n);
    answer.resize(m);
    for(int i = 0; i < m; ++i)
    {
        int a,b;
        in >> a >> b;
        g[a - 1].push_back(mp(b - 1, i));
        g[b - 1].push_back(mp(a - 1, i));
    }
    
    for(int i = 0; i < n; ++i)
    {
        if(!color[i])
        {
            dfs(i,i);
            if(st.size() != 0)
            {
                while(st.size() > 0)
                {
                    answer[st.top()] = c;
                    st.pop();
                }
                c++;
            }
        }
    }
    out << c - 1 << endl;

    rep0(i, m)
    {
        out << answer[i] << " ";
    }
    return 0;
}