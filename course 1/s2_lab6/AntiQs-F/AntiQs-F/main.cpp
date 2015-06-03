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

int main ()
{
    ifstream in("antiqs.in");
    ofstream out("antiqs.out");
    int n;
    in >> n;
    vector<int> m(n + 1);
    int it1 = 2;
    int it2 = 1;
    int i = 1;
    rep(i, 1, n + 1)
        m[i] = i;
    while(it1 < (n + 1) / 2 + 1 && it1 + it2 <= n)
    {
        swap(m[it1],m[it1 + it2]);
        if(i % 2 == 1)
            it2++;
        else
            it1++;
        i++;
    }
    rep(i, 1, n + 1)
    {
        out << m[i] << " ";
    }
    return 0;
}