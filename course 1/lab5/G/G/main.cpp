#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long INF = 10000000000;

vector< vector <int> > m;
string s;
string rec(int l, int r)
{
    string tm = "";
    if(l == r)
        return tm + s[l];
    if(m[l][r] == 2)
    {
        
        if(r - l == 1)
            return tm + s[l] + s[r];
        return s[l] + rec(l + 1, r - 1) + s[r];
    }
    if(m[l][r] == 1)
        return rec(l + 1, r);
    return rec(l, r - 1);
}
int main ()
{
    
    freopen("palindrome.in", "r", stdin);
    freopen("palindrome.out", "w", stdout);
    cin >> s;
    int n = s.size();
    //int d[n][n];
    vector< vector <int> > d(n, vector<int>(n, 0));
    m.resize(n, vector<int>(n));
    for(int i = 0; i < s.size(); i++)
        d[i][i] = 1;
    for(int l = 1; l < s.size(); l++)
    {
        for(int i = 0; i < s.size() - l; i++)
        {
            int j = i + l;
            int a = d[i][j - 1];
            int b = d[i + 1][j];
            int c = 0;
            if(l == 1 && s[i] == s[j])
                c = 2;
            if(l > 1 && s[i] == s[j])
                c = d[i + 1][j - 1] + 2;
            
            if(a > b)
            {
                if(a > c)
                {
                    d[i][j] = a;
                    m[i][j] = 0;
                }
                else{
                    d[i][j] = c;
                    m[i][j] = 2;
                }
            }
            else{
                if(b > c)
                {
                    d[i][j] = b;
                    m[i][j] = 1;
                }else{
                    d[i][j] = c;
                    m[i][j] = 2;
                }
            }
        }
    }
    int answ = d[0][s.size() - 1];
    string ans = "";
    cout << answ << endl<< rec(0, s.size() - 1);
    
    return 0;
}