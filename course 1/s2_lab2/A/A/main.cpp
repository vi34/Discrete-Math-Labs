#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "isheap"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;



int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    int n;
    cin >> n;
    int a[n];
    rep0(i, n)
        cin >> a[i];
    
    rep0(i, n) {
        if((i * 2 + 1 < n && a[2 * i + 1] < a[i]) || (i * 2 + 2 < n && a[2 * i + 2] < a[i]))
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}