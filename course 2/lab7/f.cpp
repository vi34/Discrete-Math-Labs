#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in("period.in");
    ofstream out("period.out");
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
    int ans = n - p[n - 1];
    out << ((n % ans == 0) ?  ans : n);


    return 0;
}