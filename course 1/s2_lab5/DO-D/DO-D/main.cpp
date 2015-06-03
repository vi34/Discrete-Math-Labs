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

long long INF = 1000000000000000000;

long long n, tree[100000 * 5];
long long t_add[100000 * 5], t_set[100000 * 5];
bool t_setu[100000 * 5];

void build(long long a[], int v, int l, int r) {
    if (l == r) {
        tree[v] = a[l];
    } else {
        int mid = (l + r) / 2;
        build(a, v * 2, l, mid);
        build(a, v * 2 + 1, mid + 1, r);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

void push(int v) {
    if(v <= (100000 * 4 + 1) / 2){
        if(t_setu[v]) {
            t_set[v * 2] = t_set[v];
            tree[v * 2] = t_set[v];
            tree[v * 2 + 1] = t_set[v];
            t_set[v * 2 + 1] = t_set[v];
            t_setu[v * 2] = true;
            t_setu[v * 2 + 1] = true;
            t_setu[v] = false;
            t_add[v * 2] = 0;
            t_add[v * 2 + 1] = 0;
        } else if(t_add[v] != 0) {
            if(t_setu[v *2])
                push(v * 2);
            if(t_setu[v * 2 + 1])
                push(v * 2 + 1);
            t_add[v * 2] += t_add[v];
            t_add[v * 2 + 1] += t_add[v];
            tree[v * 2] += t_add[v];
            tree[v * 2 + 1] += t_add[v];
            t_add[v] = 0;
        }
    }
    
}

long long tmin(int v, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) {
        return tree[v];
    } else if(l > qr || r < ql ) {
        return INF;
    } else {
        int mid = (l + r) / 2;
        push(v);
        return min(tmin(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr), tmin(v * 2, l, mid, ql, min(qr,mid)));
    }
}


void tset(int v, int l, int r, int ql, int qr, long long val) {
    if(l == ql && r == qr) {
        t_set[v] = val;
        t_add[v] = 0;
        t_setu[v] = true;
        tree[v] = val;
        if(l == r)
            t_setu[v] = false;
    } else if(l > qr || r < ql ) {
    } else {
        int mid = (l + r) / 2;
        push(v);
        tset(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr, val);
        tset(v * 2, l, mid, ql, min(qr,mid), val);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

void tadd(int v, int l, int r, int ql, int qr, long long val) {
    if(l == ql && r == qr) {
        if(l == r)
            t_setu[v] = false;
        if(t_setu[v])
            push(v);
        t_add[v] += val;
        tree[v] += val;
    } else if(l > qr || r < ql ) {
    } else {
        int mid = (l + r) / 2;
        push(v);
        tadd(v * 2 + 1, mid + 1, r, max(ql, mid +1), qr, val);
        tadd(v * 2, l, mid, ql, min(qr,mid), val);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

int main ()
{
    
    ifstream in("rmq2.in");
    ofstream out("rmq2.out");
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
        if(s == "min") {
            out << tmin(1, 0, n - 1, a, b) << endl;
        } else if( s == "set") {
            long long c;
            in >> c;
            tset(1, 0, n - 1, a, b, c);
        } else if(s == "add") {
            long long c;
            in >> c;
            tadd(1, 0, n - 1, a, b, c);
        }
        
    }
    
    return 0;
}

/// 0 0 0 1 2 3 4