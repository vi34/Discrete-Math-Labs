#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

struct edge{
    int s, t, c, v, f;
    int rev;
};

int s = 0, t;

const int INF = 1000000000;

int main() {
    ifstream in("mincost.in");
    ofstream out("mincost.out");
    int n, m;
    in >> n >> m;
    t = n - 1;

    long long answ = 0;

    vector<vector<edge> > g(n);
    vector<edge> edges;
    for(int i = 0; i < m; ++i)
    {
        int a,b,c,v;
        in >> a >> b >> c >> v;
        a--;
        b--;
        edge e{a,b,c,v,0};
        e.rev = g[b].size();
        edges.push_back(e);
        edge re{b,a,0,-v,0};
        re.rev = g[a].size();
        g[a].push_back(e);
        g[b].push_back(re);
    }

    vector<long long> potential(n, INF);

    potential[s] = 0;

    for(int i = 0; i < n - 1; ++i)
        for(int j = 0; j < m; ++j)
                if(potential[edges[j].s] < INF)
                    potential[edges[j].t] = min(potential[edges[j].t], potential[edges[j].s] + edges[j].v);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < g[i].size(); ++j)
        {
           g[i][j].v += potential[g[i][j].s] - potential[g[i][j].t];
        }


    bool path_exists = true;

    while(path_exists)
    {
        priority_queue<pair <long long, int> > q;
        vector<long long> d(n,INF);
        vector<pair<int, int> > prev(n);
        prev[0] = make_pair(-1, -1);
        d[0] = 0;
        q.push(make_pair(0, 0));
        while(!q.empty())
        {
            int v = q.top().second;
            long long td = q.top().first;
            q.pop();
            if(-td == d[v])
            {
                for(int i = 0; i < g[v].size(); ++i)
                {
                    edge &e = g[v][i];
                    if(e.f == e.c)
                        continue;
                    int to = e.t;
                    if(d[v] + e.v < d[to])
                    {
                        d[to] = d[v] + e.v;
                        prev[to] = make_pair(v, i);
                        q.push(make_pair(-d[to], to));
                    }
                }
            }
        }
        if(d[t] == INF)
        {
            path_exists = false;
            break;
        }

        int v = t;
        int flow = INF;
        while(v != s)
        {
            edge &e = g[prev[v].first][prev[v].second];
            flow = min(flow, e.c - e.f);
            v = prev[v].first;
        }
        v = t;

        answ += flow * (d[t] + potential[t] - potential[s]);
        while(v != s)
        {
            edge &e = g[prev[v].first][prev[v].second];
            edge &re = g[e.t][e.rev];

            e.f += flow;
            re.f -= flow;
            v = prev[v].first;
        }

    }
    out << answ;


    return 0;
}