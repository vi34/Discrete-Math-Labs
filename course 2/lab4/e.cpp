
#include <iostream>
#include <fstream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;

const int INF = 2000000000;

vector <int> used;
vector <int> topsort;
bool used2[2000];

void dfs(int v,vector< vector<pair<int, int> > > &e)
{
    used[v] = true;
    for(int i = 0; i < e[v].size(); ++i)
    {
        int to = e[v][i].first;
        if(used[to])
            continue;
        dfs(to, e);
    }
    topsort.push_back(v);
}

void dfs2(int v,vector< vector<pair<int, int> > > &e,vector<int> &answer, int c)
{
    used[v] = true;
    for(int i = 0; i < e[v].size(); ++i)
    {
        int to = e[v][i].first;
        if(used[to])
            continue;
        dfs2(to, e, answer,c);
    }
    answer[v] = c;
}

bool exist_path(int root, vector< vector<pair<int, int> > > &e)
{
    used.resize(e.size());
    fill(used.begin(),used.end(), 0);
    bool answ = true;
    dfs(root,e);
    for(int i = 0; i < e.size(); ++i)
    {
        if(!used[i])
        {
            answ = false;
            dfs(i, e);
        }
    }
    return answ;

}

void dfs8(int v, vector <vector <pair <int, int> > > &edges)
{
    used2[v] = true;
    for (int i = 0; i < edges[v].size(); i++)
    {
        if (!used2[edges[v][i].first])
        {
            dfs8(edges[v][i].first, edges);
        }
    }
}

pair<int, vector <int> > condensation(vector< vector<pair<int, int> > > &e)
{
    vector<int> cond(e.size());
    reverse(topsort.begin(), topsort.end());
    used.resize(e.size(), false);
    fill(used.begin(),used.end(), 0);
    int c = 0;
    for(int i = 0; i < e.size(); ++i)
    {
        if(!used[topsort[i]])
        {
            dfs2(topsort[i],e,cond,c);
            c++;
        }
    }
    return make_pair(c, cond);
}

long long mst(int root, vector< vector<pair<int, int> > > &e)
{
    long long res = 0;
    int n = e.size();
    vector<int> min_e(n, INF);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < e[i].size(); ++j)
        {
            int to = e[i][j].first;
            min_e[to] = min(min_e[to], e[i][j].second);
        }
    for(int i = 0; i < n; ++i)
        if(i != root)
            res += min_e[i];

    vector< vector<pair<int, int> > > zero_edges(n);
    vector< vector<pair<int, int> > > rev_zero_edges(n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < e[i].size(); ++j)
        {
            int to = e[i][j].first;
            if(e[i][j].second == min_e[to])
            {
                zero_edges[i].push_back(make_pair(to, 0));
                rev_zero_edges[to].push_back(make_pair(i, 0));
            }
            e[i][j].second -= min_e[to];                // ?
        }
    dfs8(root, zero_edges);
    bool fl = true;
    for (int i = 0; i < n; i++)
    {
        if (!used2[i])
        {
            fl = false;
        }
    }
    if (fl)
    {
        return res;
    }
    topsort.clear();
    exist_path(root, zero_edges);
    //if(exist_path(root, zero_edges))
    //{
    //    return res;
    //}
    pair<int, vector <int> > p = condensation(rev_zero_edges);
    vector<int> cond = p.second;
    int cond_count = p.first;

    vector< vector<pair<int, int> > > new_edges(cond_count);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < e[i].size(); ++j)
        {
            int to = e[i][j].first;
            if(cond[i] != cond[to])
            {
                new_edges[cond[i]].push_back(make_pair(cond[to],e[i][j].second));
            }
        }
    res += mst(cond[root], new_edges);

    return res;
}


int main() {
    ifstream in("chinese.in");
    ofstream out("chinese.out");
    int n, m;
    in >> n >> m;
    vector< vector<pair<int, int> > > g(n);
    for(int i = 0; i < m; ++i)
    {
        int a, b, w;
        in >> a >> b >> w;
        g[a - 1].push_back(make_pair(b - 1,  w));
    }
    if(exist_path(0, g))
    {
        out << "YES" << endl << mst(0, g);

    }
    else
        out << "NO";

    return 0;
}