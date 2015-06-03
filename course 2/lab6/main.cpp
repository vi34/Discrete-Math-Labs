#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

const int INF = 1000000000;

int main() {
    ifstream in("assignment.in");
    ofstream out("assignment.out");
    int n;
    in >> n;
    int a[n][n];
    int cost = 0;
    vector<int> pi(n, 0),pj(n, 0), match(n,-1);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            in >> a[i][j];

    for(int i = 0; i < n; ++i)
    {
        vector<int> used(n, false);
        vector<int> prev(n, -1);
        vector<int> min_j(n, INF);
        int cur_i = i;
        int cur_j = -1, j;

        while(cur_i != -1)
        {
            j = -1;
            int d = INF;
            for(int k = 0; k < n; ++k)
            {
                if(!used[k])
                {
                    int value = a[cur_i][k] - pi[cur_i] -pj[k];
                    if(value < min_j[k])
                    {
                        min_j[k] = value;
                        prev[k] = cur_j;
                    }
                    if(min_j[k] < d || j == -1)
                    {
                        d = min_j[k];
                        j = k;
                    }
                }
            }

            for(int k = 0; k < n; ++k)
            {
                if(used[k])
                {
                    pi[match[k]] += d;
                    pj[k] -= d;
                }
                else
                {
                    min_j[k] -= d;
                }

            }
            cost += d;

            pi[i] += d;

            used[j] = true;
            cur_j = j;
            cur_i = match[j];
        }

        for(; prev[j] != -1; j = prev[j])
        {
            match[j] = match[prev[j]];
        }
        match[j] = i;
    }


    out << cost << endl;
    for(int i = 0; i < n; ++i)
        out << match[i] + 1 << " " << i + 1 << endl;


    return 0;
}