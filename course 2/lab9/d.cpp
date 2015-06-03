#include <iostream>
#include <set>
#include <cstdio>
#include <unordered_set>
#include <bitset>

using namespace std;


bool first_ax = false;
bool second_ax = true;
bool third_ax = true;

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    unordered_set<bitset<10> > s;
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        bitset<10> bitset_tmp;
        int elem;
        for (int j = 0; j < k; ++j) {
            cin >> elem;
            bitset_tmp.set(elem - 1);
        }
        s.insert(bitset_tmp);
    }

    for (auto it = begin(s); it != end(s); ++it) {
        if (!it->any()) {
            first_ax = true;
            continue;
        }
        bitset<10> tmp = *it;
        for (int i = 0; i < 10; ++i) {
            if (it->test(i)) {
                tmp.set(i, 0);
                if (s.find(tmp) == end(s)) {
                    second_ax = false;
                    break;
                }
                tmp.set(i, 1);
            }
        }
        for (auto it2 = begin(s); it2 != end(s); ++it2) {
            if (it2->count() >= it->count())
                continue;
            tmp = *it2;
            bool found = false;
            for (int i = 0; i < 10; ++i) {
                if (!tmp.test(i) && it->test(i)) {
                    tmp.set(i, 1);
                    if (s.find(tmp) != end(s)) {
                        found = true;
                        break;
                    }
                    tmp.set(i, 0);

                }
            }
            if (!found) {
                third_ax = false;
                break;
            }
        }

    }
    if (first_ax && second_ax && third_ax)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}