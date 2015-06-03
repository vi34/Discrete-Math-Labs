#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <bitset>

using namespace std;

int n, m;

int main()
{
    freopen ("cycles.in", "r", stdin);
    freopen ("cycles.out", "w", stdout);
    cin >> n >> m;
    vector<pair <int, int> > w;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        w.push_back(make_pair(tmp, i));
    }
    sort(w.begin(), w.end());
    reverse(w.begin(), w.end());
    vector<bitset<20> > cycles;
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        bitset<20> tmp;
        for (int j = 0; j < k; j++)
        {
            int q;
            cin >> q;
            tmp.set(q - 1);
        }
        cycles.push_back(tmp);
    }
    long long answ = 0;
    bitset<20> a;
    for (int i = 0; i < w.size(); ++i) {
        a.set(w[i].second);
        bool indep = true;

        for (int j = 0; j < cycles.size(); ++j) {
            bool subset = true;
            for (int k = 0; k < 20; ++k) {
                if(cycles[j].test(k) && !a.test(k)) {
                    subset = false;
                    break;
                }
            }
            if (subset) {
                indep = false;
                break;
            }
        }

        if (indep) {
            answ += w[i].first;
        } else {
            a.set(w[i].second, 0);
        }
    }
    cout << answ;
    return 0;
}