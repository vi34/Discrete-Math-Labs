#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("search1.in");
    ofstream out("search1.out");

    string p1, t;
    in >> p1 >> t;
    string s = p1 + "#" + t;
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
    vector<int> answer;
    int pn = p1.size();
    for(int i = pn + 1; i < n; ++i) {
        if(p[i] == pn) {
            answer.push_back(i - 2 * pn + 1);
        }
    }
    out << answer.size() << endl;
    for(int i = 0; i < answer.size(); ++i)
        out << answer[i] << " ";
    return 0;
}