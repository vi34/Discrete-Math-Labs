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

int n;
int mas[100000];

pair<int, int> binSearch(int l, int r, int x)
{
    int l0 = l, r0 = r;
    pair<int, int> ans;
    while(r > l + 1)
    {
        int mid = (l + r) / 2;
        if(mas[mid] >= x)
            r = mid;
        else
            l = mid;
    }
    ans.first = (r < n && mas[r] == x) ? r + 1 : -1;
    r = r0;
    l = l0;
    while(r > l + 1)
    {
        int mid = (l + r) / 2;
        if(mas[mid] > x)
            r = mid;
        else
            l = mid;
    }
    ans.second = (l < n && mas[l] == x) ? l + 1 : -1;
    return ans;
}

int main ()
{
    
    ifstream in("binsearch.in");
    ofstream out("binsearch.out");
    int m;
    in >> n;
    rep0(i, n)
        in >> mas[i];
    in >> m;
    rep0(i, m)
    {
        int q;
        in >> q;
        pair<int, int> a = binSearch(-1, n, q);
        out << a.first << " " << a.second << endl;
    }
    return 0;
}