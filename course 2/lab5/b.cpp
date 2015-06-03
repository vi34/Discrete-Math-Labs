#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 2000000000;

struct edge{
    int s, t, c, f;
    int rev;
};

int s = 0;
int t;
int n, m;

vector<int> d;
vector<edge> edges;
vector<vector<int> > g;
vector<int> ptr;
vector< vector<int> > answer;
vector<int> used;

int dfs(int u, int t, int c)
{
    if(u == t)
        return c;
    for(; ptr[u] < g[u].size(); ++ptr[u])
    {
        edge e = edges[g[u][ptr[u]]];
        if(e.c - e.f > 0 && d[e.t] == d[e.s] + 1)
        {
            int d = dfs(e.t, t, min(c,e.c - e.f));
            if(d > 0)
            {
                edges[g[u][ptr[u]]].f += d;
                edges[edges[g[u][ptr[u]]].rev].f -= d;
                return d;
            }
        }
    }
    return 0;
}

bool bfs()
{
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < g[u].size(); ++i)
        {
            edge e = edges[g[u][i]];
            if(e.c > e.f && d[e.t] == INF)
            {
                d[e.t] = d[u] + 1;
                q.push(e.t);
            }
        }
    }
    return d[t] != INF;

}

bool dfs2(int v)
{
   // used[v] = true;
    vector<int> answ;
    int fmin = INF;
    while(v != t && !used[v])
    {
        int i = 0;
        for(; i < g[v].size(); ++i)
            if(edges[g[v][i]].f > 0)
                break;
        if(i == g[v].size())
        {
            if(v == t)
                break;
            return false;
        }
        fmin = min(fmin, edges[g[v][i]].f);
        answ.push_back(g[v][i]);
        used[v] = true;
        v = edges[g[v][i]].t;
    }

    vector<int> pansw;
    int j = answ.size() - 1;
    while(edges[answ[j]].s != v && edges[answ[j]].s != s)
    {
        pansw.push_back(answ[j] / 2 + 1);
        edges[answ[j]].f -= fmin;
        j--;
    }
    pansw.push_back(answ[j] / 2 + 1);
    edges[answ[j]].f -= fmin;


    pansw.push_back(pansw.size());
    pansw.push_back(fmin);
    reverse(pansw.begin(), pansw.end());
    answer.push_back(pansw);
    return true;

}


int main() {
    ifstream in("decomposition.in");
    ofstream out("decomposition.out");
    in >> n >> m;
    d.resize(n);
    ptr.resize(n);
    g.resize(n);
    used.resize(n, 0);
    t = n - 1;

    for(int i = 0; i < m; ++i)
    {
        int a,b,c;
        in >> a >> b >> c;
        a--;
        b--;
        edge e {a, b, c, 0};
        edge re {b, a, 0, 0};
        e.rev = edges.size() + 1;
        re.rev = edges.size();
        edges.push_back(e);
        edges.push_back(re);
        g[a].push_back(re.rev);
        g[b].push_back(e.rev);
    }

    long long flow = 0;

    while(bfs())
    {
        int p;
        fill(ptr.begin(),ptr.end(),0);
        while(p = dfs(s, t, INF))
        {
            flow += p;
        }
    }

    for(int i = 0; i < n - 1; ++i)
    {
        while(dfs2(i))
        {
            fill(used.begin(), used.end(),0);
        }
    }

    out << answer.size() << endl;
    for(int i = 0; i < answer.size(); ++i)
    {
        for(int j = 0; j < answer[i].size(); ++j)
        {
            out << answer[i][j] << " ";
        }
        out << endl;
    }

    return 0;
}