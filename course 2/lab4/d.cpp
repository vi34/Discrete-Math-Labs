#include <iostream>
#include <fstream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    ifstream in("euler.in");
    ofstream out("euler.out");
    int n;
    in >> n;
    vector<vector <int> > g(n, vector<int> (n, 0));
    vector<int> deg(n);
    int odd_cnt = 0;
    int num;
    int s, f;
    s = 0;
    for(int i = 0; i < n; ++i) {
        in >> num;
        deg[i] = num;
        if(num % 2 == 1)
        {
            odd_cnt++;
            s = f;
            f = i;
        }
        for(int j = 0; j < num; ++j)
        {
            int t;
            in >> t;

            g[i][t - 1]++;
        }
    }
    if(odd_cnt % 2 == 1)
    {
        out << -1;
        return 0;
    }
    if(odd_cnt == 2)
    {
        g[s][f]++;
        g[f][s]++;
        deg[f]++;
        deg[s]++;
    }

    stack<int> st;
    vector<int> answer;
    st.push(s);
    while(!st.empty())
    {
        int v = st.top();
        if(deg[v] == 0)
        {
            answer.push_back(v);
            st.pop();
        }
        else
        {
            for(int i = 0; i < n; ++i)
            {
                if(g[v][i])
                {
                    g[v][i]--;
                    g[i][v]--;
                    deg[v]--;
                    deg[i]--;
                    st.push(i);
                    break;
                }
            }
        }

    }

    if(odd_cnt == 2)
    {
        for(int i = 0; i < answer.size() - 1; ++i)
        {
            if(answer[i] == s && answer[i + 1] == f || answer[i] == f && answer[i + 1] == s)
            {
                vector <int> tmp;
                for(int j = i + 1; j < answer.size(); ++j)
                    tmp.push_back(answer[j]);
                for(int j = 1; j <= i; ++j)
                    tmp.push_back(answer[j]);
                answer = tmp;
                break;
            }
        }
    }

    out << answer.size() - 1 << endl;
    for(int i = 0; i < answer.size(); ++i)
    {
        out << answer[i] + 1 << " ";
    }

    return 0;
}