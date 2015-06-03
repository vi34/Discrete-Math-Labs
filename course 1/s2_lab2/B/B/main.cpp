#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "dsu"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; ++i)
#define rep(i, l, r) for(int i = l; i < r; ++i)

using namespace std;

long long INF = 10000000000;

int p[100001];
int r[100001];
int ma[100001];
int mi[100001];
int col[100001];

void make(int i) {
    p[i] = i;
    r[i] = 0;
    ma[i] = i;
    mi[i] = i;
    col[i] = 1;
}

int get(int n) {
    if(p[n] == n)
        return n;
    else
        return p[n] = get(p[n]);
}

void unon(int a, int b) {
    a = get(a);
    b = get(b);
    if(a != b) {
        if(r[a] > r[b])
            swap(a, b);
        p[a] = b;
        
        if(r[a] == r[b]) {
            ++r[b];
        }
        if(ma[b] < ma[a])
            ma[b] = ma[a];
        col[b] += col[a];
        if(mi[b] > mi[a])
            mi[b] = mi[a];
    }
    
}


int main ()
{
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    int n;
    cin >> n;
    rep0(i, n + 1)
        make(i);
    while(!feof(stdin)) {
        string s;
        cin >> s;
        int a, b;
        if(s == "union") {
            cin >> a >> b;
            unon(a, b);
        }
        else if (s == "get") {
            cin >> a;
            a = get(a);
            cout << mi[a] <<" "<< ma[a] << " " << col[a] << endl;
        }
    }
    
    return 0;
}