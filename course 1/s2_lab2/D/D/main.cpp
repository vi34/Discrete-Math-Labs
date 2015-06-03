#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "parking"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; ++i)
#define rep(i, l, r) for(int i = l; i < r; ++i)

using namespace std;

long long INF = 10000000000;

int p[300001];
int r[300001];
int col[300001];
int pr[300001];

void make(int i) {
    p[i] = i;
    r[i] = 0;
    pr[i] = i;
    col[i] = 0;
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
    }
}


int main ()
{
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    int n;
    cin >> n;
    rep0(i, n)
    make(i);
    rep0(i, n)
    {
        int t;
        cin >> t;
        t %= n;
        int ans = t;
        if(col[t] != 0)
        {
            ans = pr[get(t)];
            t = pr[get(t)];
            col[ans] = 1;
        } else {
            col[t] = 1;
        }
        int left = (t + n - 1) % n;
        int right = (t + 1) % n;
        if(col[right] != 0){
            pr[t] = pr[get(right)];
            unon(t, right);
        } else {
            pr[get(t)] = right;
        }
        if(col[left] != 0)
        {
            pr[get(left)] = pr[t];
            unon(t, left);
        }

        if(ans == 0)
            ans = n;
        cout << ans << " ";
    }
    return 0;
}