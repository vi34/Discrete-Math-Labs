#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main ()
{
    freopen("huffman.in","r",stdin);
    freopen("huffman.out","w",stdout);
    
    int n;
    cin >> n;
    priority_queue <long long> q;
    long long answ = 0;
    
    for (int i = 0; i < n; i++)
    {
        long long p;
        cin >> p;
        q.push(-p);
    }
    
    while (q.size() > 1) {
        long long tmp = 0;
        tmp += q.top();
        q.pop();
        tmp += q.top();
        q.pop();
        q.push(tmp);
        answ += tmp;
    }
    
    cout << -answ;
    return 0;
}

