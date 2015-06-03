//
// Created by Виктор Шатров on 05/05/15.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n, w[2000], mt[2000], ans = 0, vertex_swap[2000];
vector <pair <int, vector <int> > > graph;
bool used[2000];
vector <int> g[2000];

bool dfs(int v)
{
    if (used[v])
    {
        return false;
    }
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
    {
        if (mt[g[v][i]] == -1 || dfs(mt[g[v][i]]))
        {
            mt[g[v][i]] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    freopen ("matching.in", "r", stdin);
    freopen ("matching.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        w[i] = tmp;
    }
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        vector <int> tmp_vec;
        for (int j = 0; j < tmp; j++)
        {
            int tmp_num;
            cin >> tmp_num;
            tmp_vec.push_back(tmp_num - 1);
        }
        tmp_vec.push_back(i);
        graph.push_back(make_pair(w[i], tmp_vec));
    }
    sort(graph.begin(), graph.end());
    reverse(graph.begin(), graph.end());
    for (int i = 0; i < n; i++)
    {
        vertex_swap[i] = graph[i].second.back();
        for (int j = 0; j < graph[i].second.size() - 1; j++)
        {
            g[i].push_back(graph[i].second[j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        mt[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            used[j] = false;
        }
        if (dfs(i))
        {
            ans++;
        }
    }
    vector <int> answer;
    answer.resize((unsigned long) n);
    for (int i = 0; i < n; i++)
    {
        if (mt[i] != -1)
        {
            answer[vertex_swap[mt[i]]] = i + 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << answer[i] << " ";
    }
    return 0;
}