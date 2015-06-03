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

long long INF = 10000000000;

struct matrix {
    int a, b, c, d;
};

long long r, n;
matrix tree[200000 * 4 + 1];

matrix mult(matrix a, matrix b) {
    matrix res;
    res.a = (a.a * b.a + a.b * b.c) % r;
    res.b = (a.a * b.b + a.b * b.d) % r;
    res.c = (a.c * b.a + a.d * b.c) % r;
    res.d = (a.c * b.b + a.d * b.d) % r;
    return res;
}

void build(matrix a[], int v, int l, int r) {
    if (l == r)
        tree[v] = a[l];
    else {
        int mid = (l + r) / 2;
        build(a, v * 2, l, mid);
        build(a, v * 2 + 1, mid + 1, r);
        tree[v] = mult(tree[v * 2] , tree[v * 2 + 1]);
    }
}

matrix tsum(int v, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) {
        return tree[v];
    } else if(l > qr || r < ql ) {
        matrix e;
        e.a = 1;
        e.b = 0;
        e.c = 0;
        e.d = 1;
        return e;
    } else {
        int mid = (l + r) / 2;
        return mult(tsum(v * 2, l, mid, ql, min(qr,mid)), tsum(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr));
    }
}

int main ()
{
    
    ifstream in("crypto.in");
    ofstream out("crypto.out");
    int m;
    in >> r >> n >> m;
    matrix a[n];
    rep0(i, n){
        in >> a[i].a >> a[i].b >> a[i].c >> a[i].d;
    }
    
    build(a, 1, 0, n - 1);
    rep0(i, m) {
        long long a, b;
        in >> a >> b;
        a--;
        b--;
        matrix res =tsum(1, 0, n - 1, a, b);
        out << res.a << " " << res.b << endl;
        out << res.c << " " << res.d << endl;
        out << endl;
        
    }
    return 0;
}

/// 0 0 0 1 2 3 4

