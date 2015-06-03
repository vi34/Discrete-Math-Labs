#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>
#include <fstream>

#define NAME "map"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 100000000;

long long n, tree[500000 * 4 + 1], mas[400000];

int oper(int a, int b) {
    if(b == INF)
        return a;
    if(a == INF)
        return b;
    if(mas[a] == 0)
        return a;
    else
        return b;
}

void build(long long a[], int v, int l, int r) {
    if (l == r)
        tree[v] = l;
    else {
        int mid = (l + r) / 2;
        build(a, v * 2, l, mid);
        build(a, v * 2 + 1, mid + 1, r);
        tree[v] = oper(tree[v * 2], tree[v * 2 + 1]);
    }
}

long long tsum(int v, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) {
        return tree[v];
    } else if(l > qr || r < ql ) {
        return INF;
    } else {
        int mid = (l + r) / 2;
        int rr = oper(tsum(v * 2, l, mid, ql, min(qr,mid)), tsum(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr));
        return rr;
    }
}

void tset(int v, int l, int r, int x, long long val) {
    if (l == r && r == x){
        tree[v] = l;
        mas[l] = val;
    }
    else {
        int mid = (l + r) / 2;
        if(x <= mid)
            tset(v * 2, l, mid, x, val);
        else
            tset(v * 2 + 1, mid + 1, r, x, val);
        tree[v] = oper(tree[v * 2], tree[v * 2 + 1]);
    }
}

int main ()
{
    
    ifstream in("parking.in");
    ofstream out("parking.out");
    int m;
    in >> n >> m;
    build(mas, 1, 0, n - 1);
    rep0(i, m) {
        string s;
        int a;
        in >> s >> a;
        a--;
        if(s == "enter") {
            int res =tsum(1, 0, n - 1, a, n - 1);
            if(mas[res])
                res = tsum(1, 0, n - 1, 0, a);
            tset(1, 0, n - 1, res, 1);
            out << res + 1 << endl;
        } else if( s == "exit") {
            tset(1, 0, n - 1, a, 0);
        }
        
    }
    
    return 0;
}
/// 1 2 3 4 5 6 7 8 9 0
/// 0 0 0 0 0 0 0 0 0 0