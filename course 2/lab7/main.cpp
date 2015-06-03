#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in("prefix.in");
    ofstream out("prefix.out");
    string s;
    in >> s;
    int n = s.size();
    int p[n];
    p[0] = 0;
    for(int i = 1; i < n; ++i) {
        int k = p[i - 1];
        while(k > 0 && s[i] != s[k])
            k = p[k - 1];
        if(s[k] == s[i])
            ++k;
        p[i] = k;
    }
    for(int i = 0; i < n; ++i)
        out << p[i] << " ";
    return 0;
}