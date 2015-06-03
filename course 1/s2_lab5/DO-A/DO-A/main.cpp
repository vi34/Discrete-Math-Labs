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

long long n, tree[500000 * 4 + 1];

void build(long long a[], int v, int l, int r) {
    if (l == r)
        tree[v] = a[l];
    else {
        int mid = (l + r) / 2;
        build(a, v * 2, l, mid);
        build(a, v * 2 + 1, mid + 1, r);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

long long tsum(int v, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) {
        return tree[v];
    } else if(l > qr || r < ql ) {
        return 0;
    } else {
        int mid = (l + r) / 2;
        return tsum(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr) + tsum(v * 2, l, mid, ql, min(qr,mid));
    }
}

void tset(int v, int l, int r, int x, long long val) {
    if (l == r && r == x)
        tree[v] = val;
    else {
        int mid = (l + r) / 2;
        if(x <= mid)
            tset(v * 2, l, mid, x, val);
        else
            tset(v * 2 + 1, mid + 1, r, x, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

int main ()
{
    
    ifstream in("rsq.in");
    ofstream out("rsq.out");
    in >> n;
    long long a[n];
    rep0(i, n)
        in >> a[i];
    build(a, 1, 0, n - 1);
    while(in) {
        string s;
        long long a, b;
        in >> s >> a >> b;
        a--;
        b--;
        if(s == "sum") {
            out << tsum(1, 0, n - 1, a, b) << endl;
        } else if( s == "set") {
            tset(1, 0, n - 1, a, b + 1);
        }
        
    }
     
    return 0;
}

/// 0 0 0 1 2 3 4