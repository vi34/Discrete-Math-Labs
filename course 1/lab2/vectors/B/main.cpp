#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector <int> cur;
vector < vector <int> > answ;
long long num = 0;

void gen(int k)
{
    if(k < n-1)
    {
        cur[k] = 0;
        gen(k+1);
        if((k > 0 && cur[k-1] != 1) || k == 0)
        {
            cur[k] = 1;
            gen(k+1);
        }
    }
    else if(k == n-1)
    {
        cur[k] = 0;
        num++;
        answ.push_back(cur);
        if((k > 0 && cur[k-1] != 1) || k == 0)
        {
            cur[k] = 1;
            num++;
            answ.push_back(cur);
        }
    }
}

int main ()
{
    freopen("vectors.in","r",stdin);
    freopen("vectors.out","w",stdout);
    cin >> n;
    cur.resize(n);
    gen(0);
    cout << num << endl;
    for(long long i = 0; i < num; i++)
    {
        for(int j = 0; j < n; j++)
            cout << answ[i][j];
        cout << endl;
    }
    return 0;
}