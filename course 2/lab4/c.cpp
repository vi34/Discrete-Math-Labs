#include <iostream>
#include <fstream>
#include <queue>
#include <cstdio>
#include <algorithm>


using namespace std;

const long long INF = 100000000000000000;

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
    ifstream in("mindiff.in");
    ofstream out("mindiff.out");
    int n, m;
    in >> n >> m;
    p.resize(n);
    r.resize(n, 0);


    vector<pair<long long, pair<int, int> > > edges(m);
    int a, b;
    long long w;
    for(int i = 0; i < m; ++i)
    {
        in >> a >> b >> w;
        edges[i] = make_pair(w, make_pair(a - 1, b - 1));

    }
    sort(edges.begin(), edges.end());
    long long answer = INF;
    long long min_r;
    for(int j = 0; j < m; ++j)
    {
        r.resize(n, 0);
        for(int i = 0; i < n; ++i)
            p[i] = i;
        min_r = edges[j].first;
        int count = 0;
        for(int i = j; i < m; ++i)
        {
            a = edges[i].second.first;
            b = edges[i].second.second;
            w = edges[i].first;
            if(get(a) != get(b))
            {
                count++;
                if(count == n - 1)
                    answer = min(answer, abs(w - min_r));
                union_set(a, b);
            }

        }
    }
    if(answer != INF)
    {
        out << "YES" << endl << answer;
    }
    else
        out << "NO";
    return 0;
}