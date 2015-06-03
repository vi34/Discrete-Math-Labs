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
    
    ifstream in("netcheck.in");
    ofstream out("netcheck.out");
    int n, m, k;
    in >> n >> m >> k;
    int comp[k][n][2];
    int rc[k];
    for(int i = 0; i < k; ++i)
    {
        in >> rc[i];
        rep0(j, rc[i])
        {
            in >> comp[i][j][0] >> comp[i][j][1];
            if(comp[i][j][0] > comp[i][j][1])
                swap(comp[i][j][0], comp[i][j][1]);
            comp[i][j][0]--;
            comp[i][j][1]--;
        }
    }
    for(int i = 0; i < (1 << n); ++i)
    {
        int res = i;
        for(int j = 0; j < k; j++)
        {
            for(int jj = 0; jj < rc[j]; ++jj)
            {
                if(((res & (1 << comp[j][jj][0])) < (res & (1 << comp[j][jj][1]))) && ((res & (1 << comp[j][jj][0])) == 0) )
                {
                    res += (1 << comp[j][jj][0]);
                    res -= (1 << comp[j][jj][1]);
                }
            }
        }
        bool zero = false;
        for(int j = n - 1; j >= 0; --j)
        {
            if((res & (1 << j)) == (1 << j))
            {
                if(!zero)
                    zero = true;
            }
            else if(zero)
            {
                out << "NO" << endl;
                return 0;
            }
        }
    }
    out << "YES";
    return 0;
}