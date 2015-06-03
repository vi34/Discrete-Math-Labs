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
int mas[40000000];

int kth(int l, int r, int k)
{
    while(true) {
        if(l == r)
            return mas[r];
        int mid;
        int pivot = r;
        pivot = mas[r];
        int i = l - 1;
        for(int j = l; j < r; j++)
            if(mas[j] < pivot)
            {
                i++;
                swap(mas[i], mas[j]);
            }
        swap(mas[i + 1], mas[r]);
        mid = i + 1;
        int pos = mid - l + 1;
        if(pos == k)
            return mas[mid];
        if(k < pos)
            r = mid - 1;
        else
        {
            k -= pos;
            l = mid + 1;
        }
    }
}

int main ()
{

    ifstream in("kth.in");
    ofstream out("kth.out");
    int a,b,c, k;
    in >> n >> k >> a >> b >> c >> mas[0] >> mas[1];
    rep(i, 2, n)
        mas[i] = mas[i - 2] * a + mas[i - 1] * b + c;
    out << kth(0, n - 1, k);
    return 0;
}