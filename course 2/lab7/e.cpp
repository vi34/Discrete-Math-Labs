#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>

using namespace std;

vector <int> z_func(const string s) {
    int n = s.length();
    vector<int> z(s.length(), 0);
    int l = 0;
    int r = 0;
    for(int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && (s[i + z[i]] == s[z[i]]))
        {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}


int main() {
    ifstream in("search3.in");
    ofstream out("search3.out");
    string p,t;
    in >> p >> t;
    vector<int> answ(0);
    vector<int> z = z_func(p + "#" + t);
    reverse(begin(p),end(p));
    reverse(begin(t),end(t));
    vector<int> z2 = z_func(p + "#" + t);

    int n = p.length() + 1;
    if(p.length() <= t.length())
        for(int i = 0; i < t.length() - p.length() + 1; ++i)
        {
            int k = z[i + n];
            k += z2[t.length() - i + 1];
            if(k >= p.length() - 1)
                answ.push_back(i + 1);
        }
    out << answ.size();
    out <<endl;
    for(int i = 0; i < answ.size(); ++i)
        out << answ[i] <<  " ";

    return 0;
}