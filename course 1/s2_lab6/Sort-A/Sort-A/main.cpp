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
int m[100000];
int tmp[100000];

void mergeM(int l, int r, int mid)
{
    int it1 = l;
    int it2 = mid + 1;
    int i = 0;
    while(it1 <= mid && it2 <= r)
    {
        if(m[it1] < m[it2])
        {
            tmp[i] = m[it1];
            it1++;
        }
        else
        {
            tmp[i] = m[it2];
            it2++;
        }
        i++;
    }
    while(it1 <= mid)
        tmp[i++] = m[it1++];
    while(it2 <= r)
        tmp[i++] = m[it2++];
    for(int j = 0; j < i; j++)
        m[l + j] = tmp[j];

}

void mSort(int l, int r)
{
    if(l + 1 < r)
    {
        int mid = (l + r)/ 2;
        mSort(l, mid);
        mSort(mid + 1, r);
        mergeM(l, r, mid);
    }
    else
    {
        if(m[r] < m[l])
            swap(m[l], m[r]);
    }
}

int main ()
{
    ifstream in("sort.in");
    ofstream out("sort.out");
    in >> n;
    for(int i = 0; i < n; i++)
        in >> m[i];
    mSort(0, n - 1);
    for(int i = 0; i < n; i++)
        out << m[i] << " ";
    return 0;
}