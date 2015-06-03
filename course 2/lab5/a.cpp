#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

vector< vector<int> > g;
vector<int> match;
vector<int> used;

int answer = 0;
bool dfs(int v)
{
    if(used[v])
        return false;
    used[v] = true;
    for(int i = 0; i < g[v].size(); ++i)
    {
        int u = g[v][i];
        if(match[u] == -1 || dfs(match[u]))
        {
            match[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream in("paths.in");
    ofstream out("paths.out");
    int n, m;
    in >> n >> m;
    g.resize(n);
    match.resize(n, -1);
    used.resize(n, 0);

    int a,b;
    for(int i = 0; i < m; ++i)
    {
        in >> a >> b;
        g[a - 1].push_back(b - 1);
    }

    for(int i = 0; i < n; ++i)
    {
        fill(used.begin(),used.end(),0);
        if(dfs(i))
            answer++;
    }

    out << n - answer;

    return 0;
}