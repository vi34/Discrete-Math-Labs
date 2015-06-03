#include <iostream>
#include <set>
#include <cstdio>
#include <unordered_set>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    int n;
    cin >> n;
    set<int> s;
    vector<pair<int,int> > tasks(n);
    for (int i = 0; i < n; ++i) {
        int d, w;
        cin >> d >> w;
        tasks[i] = make_pair(-w, d);
        s.insert(i + 1);
    }

    sort(tasks.begin(), tasks.end());

    long long answ = 0;

    for (int i = 0; i < tasks.size(); ++i) {
        int time = tasks[i].second;
        auto it = s.lower_bound(time);
        if(*it == time) {
            s.erase(time);
        } else {
            if(it == s.end()) {
                s.erase((--s.end()));
            } else if (it == s.begin()){
                answ +=  -tasks[i].first;
                s.erase((--s.end()));
            } else {
                s.erase(--it);
            }

        }

    }

    cout << answ;
    return 0;
}