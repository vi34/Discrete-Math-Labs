#include <iostream>
#include <fstream>
#include <queue>
#include <cstdio>
#include <algorithm>


using namespace std;

const int INF = 1000000000;

vector<int> p;
vector<int> r;

int get(int v)
{
    if(p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void union_set(int a, int b)
{
    a = get(a);
    b = get(b);
    if(a != b) {
        if(r[a] > r[b])
            swap(a,b);
        p[a] = b;
        if(r[a] == r[b])
            r[b]++;
        return;
    }

    p[a] = b;
}


int main() {
    ifstream in("spantree2.in");
    ofstream out("spantree2.out");
    int n, m;
    in >> n >> m;
    p.resize(n);
    r.resize(n, 0);
    for(int i = 0; i < n; ++i)
        p[i] = i;
    
    vector<pair<int, pair<int, int> > > edges(m);
    int a, b, w;
    for(int i = 0; i < m; ++i)
    {
        in >> a >> b >> w;
        edges[i] = make_pair(w, make_pair(a - 1, b - 1));

    }
    sort(edges.begin(), edges.end());
    int answer = 0;
    for(int i = 0; i < m; ++i)
    {
        a = edges[i].second.first;
        b = edges[i].second.second;
        w = edges[i].first;
        if(get(a) != get(b))
        {
            answer += w;
            union_set(a, b);
        }

    }
    out << answer;
    return 0;
}