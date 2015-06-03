#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <queue>


using namespace std;

const int INF = 1000000000;

struct edge{
    int s, t, c, v, f;
    int rev;
};

vector<pair<int, int> > match;
vector<int> used;
vector<vector<pair<int, int> > > g2;
vector<int> answer;
int n, s = 0, t;


bool dfs(int v)
{
    if(used[v])
        return false;
    used[v] = true;
    for(int i = 0; i < g2[v].size(); ++i)
        if(g2[v][i].second)
        {
            int u = g2[v][i].first;
            if(match[u].first == -1 || dfs(match[u].first))
            {
                match[u] = make_pair(v, i);
                return true;
            }
        }
    return false;
}

void kuhn()
{
    fill(match.begin(),match.end(), make_pair(-1, -1));

    for(int i = 0; i < n; ++i)
    {
        fill(used.begin(),used.end(),0);
        dfs(i);
    }

    for(int i = 0; i < n; ++i)
    {
        answer[match[i].first] = i;
        g2[match[i].first][match[i].second].second = 0;

    }
}



int main() {
    ifstream in("multiassignment.in");
    ofstream out("multiassignment.out");
    int k;
    in >> n >> k;
    t = 2 * n + 1;
    int n1 = n;
    answer.resize(n1);
    used.resize(n1);
    match.resize(n1);

    long long answ = 0;

    vector<vector<edge> > g(2*n + 2);
    g2.resize(n1);

    vector<edge> edges;
    for(int i = 1; i <= n; ++i)
    {
        edge e{0,i,k,0,0};
        e.rev = g[i].size();
        edges.push_back(e);
        edge re{i,0,0,0,0};
        re.rev = g[0].size();
        g[0].push_back(e);
        g[i].push_back(re);

    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            int v;
            in >> v;
            edge e{i,n + j,1,v,0};
            e.rev = g[n + j].size();
            edges.push_back(e);
            edge re{n + j,i,0,-v,0};
            re.rev = g[i].size();
            g[i].push_back(e);
            g[n + j].push_back(re);
        }

    for(int i = 1; i <= n; ++i)
    {
        edge e{i + n,t,k,0,0};
        e.rev = g[t].size();
        edges.push_back(e);
        edge re{t,n + i,0,0,0};
        re.rev = g[n + i].size();
        g[n + i].push_back(e);
        g[t].push_back(re);
    }

    n = 2*n + 2;

    vector<long long> potential(n, INF);

    potential[s] = 0;

    for(int i = 0; i < n - 1; ++i)
        for(int j = 0; j < edges.size(); ++j)
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

    for(int i = 1; i <= n1; ++i)
    {
        for(int j = 0; j < g[i].size(); j++)
        {
            if(g[i][j].f != 1)
                continue;
            g2[i - 1].push_back(make_pair(g[i][j].t - n1 - 1, 1));
        }
    }

    out << answ << endl;
    n = n1;

    for(int i = 0; i < k; ++i)
    {
        kuhn();
        for(int j = 0; j < n; ++j)
            out << answer[j] + 1 << " ";
        out << endl;
    }

    return 0;
}

