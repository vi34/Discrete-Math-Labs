#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int INF = 1000000000;

vector< vector <long long> > m;
vector< vector <int> > s;
void rec(int l, int r)
{
    if(l == r)
        cout << "A";
    else
    {
        cout << "(";
        rec(l,s[l][r]);
        rec(s[l][r] + 1, r);
        cout << ")";
    }
}
int main ()
{
    
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    
    int n;
    cin >> n;
    int p[n + 1];
    cin >> p[0];
    m.resize(n, vector<long long>(n));
    s.resize(n, vector<int>(n));
    for(int i = 1; i < n; i++)
    {
        int tm;
        cin >> tm >> p[i];
    }
    cin >> p[n];
    for(int i = 0; i < n; i++)
        m[i][i] = 0;
    for(int l = 1; l < n; l++)
    {
        for(int i = 1; i <= n - l; i++)
        {
            int j = i - 1 + l;
            m[i - 1][j] = INF;
            for(int k = i - 1; k < j; k++)
            {
                long long tmp = m[i - 1][k] + m[k + 1][j] + p[i - 1] * p[j + 1] * p[k + 1];
                if(m[i - 1][j] > tmp)
                {
                    m[i - 1][j] = tmp;
                    s[i - 1][j] = k ;
                }
            }
            
        }
    }
    rec(0, n - 1);
    
    return 0;
}