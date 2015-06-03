#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("z.in");
    ofstream out("z.out");
    string s;
    in >> s;
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0;
    int r = 0;
    for(int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for(int i = 1; i < n; ++i)
        out << z[i] << " ";
    return 0;
}