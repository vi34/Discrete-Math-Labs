#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <set>


using namespace std;

const int INF = 1000000000;

struct point {
    int x;
    int y;
};


int main() {
    ifstream in("spantree.in");
    ofstream out("spantree.out");
    int n;
    in >> n;
    point points[n];
    for(int i = 0; i < n; ++i)
    {
        in >> points[i].x >> points[i].y;
    }
    vector<double> d(n + 1, INF);
    vector<bool> used(n, false);
    d[0] = 0;
    int min_v = 0;
    double answer = 0;
    for(int j = 0; j < n; ++j)
    {
        int p = min_v;
        answer += d[p];
        used[p] = true;
        min_v = n;
        for(int i = 0; i < n; i++)
        {
            if(used[i])
                continue;
            double dist = sqrt((points[i].x - points[p].x)*(points[i].x - points[p].x) + (points[i].y - points[p].y)*(points[i].y - points[p].y));
            if(dist < d[i])
            {
                d[i] = dist;
            }
            if(d[i] < d[min_v])
                min_v = i;
        }
    }
    out.precision(15);
    out << answer;

    return 0;
}