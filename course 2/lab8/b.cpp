//
// Created by Виктор Шатров on 02.04.15.
//

#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 27;

string s;

int main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);

    cin >> s;
    s += 'a' - 1;
    int n = s.size();
    int a[n];
    vector<int> color(n), count(max(SIZE,n));
    fill(begin(count), end(count), 0);
    for (int i = 0; i < n; ++i) {
        count[s[i] - 'a' + 1]++;
    }
    for (int i = 1; i < SIZE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = 0; i < n; ++i) {
        a[--count[s[i] - 'a' + 1]] = i;
    }

    int colors = 1;
    color[a[0]] = 0;

    for (int i = 1; i < n; ++i) {
        if (s[a[i]] != s[a[i - 1]])
            colors++;
        color[a[i]] = colors - 1;
    }

    vector<int> cn(n, 0), an(n, 0);
    for (int k = 0; (1 << k) < n; ++k) {

        for (int i = 0; i < n; ++i) {
            an[i] = (n + a[i] - (1 << k)) % n;
        }
        fill(begin(count), end(count), 0);
        for (int i = 0; i < n; ++i) {
            ++count[color[an[i]]];
        }
        for (int i = 1; i < colors; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            a[--count[color[an[i]]]] = an[i];
        }

        colors = 1;
        cn[a[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (!(color[a[i]] == color[a[i - 1]] && (color[(a[i] + (1<<k)) % n] == color[(a[i - 1] + (1 << k)) % n])))
                colors++;
            cn[a[i]] = colors - 1;
        }
        for (int i = 0; i < n; ++i) {
            color[i] = cn[i];
        }
    }

    for (int i = 1; i < s.size(); ++i)
        cout << a[i] + 1 << " ";

    return 0;
}