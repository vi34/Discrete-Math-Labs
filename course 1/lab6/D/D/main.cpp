#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "absmarkchain"
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
    int n, m;
    cin >> n >> m;
    vector< vector<long double> > rib(m, vector<long double>(3));
    bool pogl[n];
    rep0(i, m)
    {
        int a, b;
        long double p;
        cin >> a >> b >> p;
        a--;
        b--;
        if(a == b && p == 1)
            pogl[a] = true;
        else
            pogl[a] = false;
        rib[i][0] = a;
        rib[i][1] = b;
        rib[i][2] = p;
    }
    int count_p = 0;
    int count_np = 0;
    int pos[n];
    rep0(i, n)
    {
        if(pogl[i])
            pos[i] = count_p++;
        else
            pos[i] = count_np++;
    }
    long double r[n][n];
    long double q[n][n];
    memset(r, 0.0, n * n * sizeof(long double));
    memset(q, 0.0, n * n * sizeof(long double));
    rep0(i, m)
    {
        if(pogl[(int)rib[i][1]])
        {
            if(!pogl[(int)rib[i][0]])
                r[pos[(int)rib[i][0]]][pos[(int)rib[i][1]]] = rib[i][2];
        }
        else
            q[pos[(int)rib[i][0]]][pos[(int)rib[i][1]]] = rib[i][2];
    }
    vector< vector<long double> > E(n, vector<long double>(n, 0.0)), N(n, vector<long double>(n, 0.0));
    rep0(i, count_np)
    {
        E[i][i] = 1;
        N[i][i] = 1;
        rep0(j, count_np)
            E[i][j] -= q[i][j];
    }
    rep0(i, count_np)
    {
        if(E[i][i] != 1)
        {
            long double div = E[i][i];
            rep0(j, count_np)
            {
                E[i][j] /= div;
                N[i][j] /= div;
            }
        }
        rep0(j, count_np)
        {
            if(i != j)
            {
                long double div = E[j][i];
                rep0(k, count_np)
                {
                    E[j][k] -= div * E[i][k];
                    N[j][k] -= div * N[i][k];
                }
            }
        }
        
    }
    long double B[n][n];
    rep0(i, count_np)
        rep0(j, count_p)
        {
            B[i][j] = 0;
            rep0(k, count_np)
                B[i][j] += N[i][k] * r[k][j];
        }
    cout.precision(5);
    rep0(i, n)
    {
        long double p = 0;
        if(pogl[i])
        {
            rep0(j, count_np)
                p += B[j][pos[i]];
            p++;
            p /= n;
        }
        cout << p << endl;
    }
    
    return 0;
}