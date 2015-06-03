#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long INF = 10000000000; 

int main ()
{
    
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    int n;
    cin >> n;
    long long a[n];
    vector <int> di(n + 1);
    vector <int> p(n, -1);
    vector <long long> d(n + 1, INF);
    d[0] = -INF;
    di[0] = -1;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        int j = (int)(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        if(d[j - 1] < a[i] && a[i] < d[j])
        {
            d[j] = a[i];
            di[j] = i;
            if(j > 0)
                p[i] = di[j - 1];
            else
                p[i] = -1;
        }
    }
    int k = (int)(upper_bound(d.begin(), d.end(), INF - 1) - d.begin());
    cout << --k << endl;
    vector <int> answ(k);
    int cont = 0;
    k = di[k];
    while(k != -1)
    {
        answ[cont] = a[k];
        cont++;
        k = p[k];
        
    }
    for(int i = cont - 1; i >= 0; i--)
    {
            cout << answ[i] << " ";
    }
    return 0;
}

