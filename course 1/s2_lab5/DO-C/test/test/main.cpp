#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>
#include <fstream>

#define NAME "map"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

int main ()
{
    
    //ifstream in("linkedmap.in");
    //ofstream out("linkedmap.out");
    ifstream in ("/Users/vi34/Desktop/programming/ITMO/labs/test.in");
    ofstream out("/Users/vi34/Desktop/programming/ITMO/labs/test.out");

    int bs = 0;
    int cs = 0;

    int ma[100];
    int ma2[100];

    rep0(i, 100) {
        ma[i] = 100 - i;
        ma2[i] = 100 - i;
    }
    rep0(i, 100) {
        cout << ma[i] << "  ";
    }
    cout << endl << endl;
    rep0(i, 100) {
        cout << ma2[i] << "  ";
    }

    
    return 0;
}