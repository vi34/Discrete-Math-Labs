
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector <int> cur;
bool cont = true;

void gen(int p, int balance, int prev)
{
    if(cont)
    {
        if(balance == n)
        {
            printf("%d=%d",n,cur[0]);
            for(int i = 1; i < p; i++)
                printf("+%d",cur[i]);
            cout << endl;
            cont = false;
            return;
        }
        for(int i = prev; i <= n - balance; i++)
        {
            cur[p] = i;
            gen(p+1, balance+i, i);
        }
    }
}

int main ()
{
    //freopen("nextpartition.in", "r", stdin);
    //freopen("nextpartition.out", "w", stdout);
    scanf("%d",&n);
    char c;
    vector <int> sum(n,0);
    int s = 0;
    int i = 0;
    cur.resize(n);
    while(s < n)
    {
        int tmp;
        scanf("%c%d",&c,&tmp);
        cur[i] = tmp;
        s += cur[i]; 
        sum[i] = s;
        i++;
    }
    i-= 2;
    if(cur[0] == n)
        cout << "No solution";
    else
    {
            int balance = (i > 0) ? sum[i - 1] : 0;
            if(cur[i] == cur[i+1])
            {
                cur[i] *= 2;
                gen(i + 1, balance + cur[i], cur[i]);
            }
            else if(cur[i] == cur[i+1] - 1)
            {
                cur[i] *= 2;
                cur[i]++;
                gen(i + 1, balance + cur[i], cur[i]);
            }
            else{
                for(int j = cur[i] + 1; j <= n - balance; j++)
                {
                    cur[i] = j;
                    gen(i + 1, balance + j, j);
                    if(!cont)
                    {
                        break;
                    }
                }
            }
    }
    return 0;
}