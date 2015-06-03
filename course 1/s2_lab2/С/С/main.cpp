#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "priorityqueue"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

pair <int, long long> heap[10000000];
int size = 0;


void sift_down (int i) {
    int left, right;
    if(i * 2 + 1 < size)
        left = heap[i * 2 + 1].first;
    else
        left = INF;
    if(i * 2 + 2 < size)
        right = heap[i * 2 + 2].first;
    else
        right = INF;
    if(right <= left && i * 2 + 2 < size && heap[i].first > heap[i * 2 + 2].first)
    {
        swap(heap[i], heap[i * 2 + 2]);
        sift_down(i * 2 + 2);
    }
    if(i * 2 + 1 < size && heap[i].first > heap[i * 2 + 1].first)
    {
        swap(heap[i], heap[i * 2 + 1]);
        sift_down(i * 2 + 1);
    }
    return;
}

void sift_up(int i) {
    if (i == 0)
        return;
    if(heap[i].first < heap[i/2].first)
    {
        swap(heap[i], heap[i/2]);
        sift_up(i / 2);
    }
    return;
}

void push(pair<int, int> p)
{
    heap[size] = p;
    sift_up(size++);
}

int extract_min()
{
    int m = heap[0].first;
    heap[0] = heap[size - 1];
    --size;
    sift_down(0);
    return m;
}

void decrease_key(long long op, int n)
{
    rep0(i, size)
    {
        if(heap[i].second == op)
        {
            int old = heap[i].first;
            heap[i].first = n;
            if(old > n)
                sift_up(i);
            else
                sift_down(i);
            break;
        }
    }
    return;
}


int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    long long oper = 1;
    while(!feof(stdin))
    {
        string s;
        cin >> s;
        if(s == "push")
        {
            int a;
            cin >> a;
            push(mp(a,oper));
        }else if(s == "extract-min")
        {
            if(size > 0)
                cout << extract_min() << endl;
            else
                cout << "*" << endl;
        }
        else if(s == "decrease-key")
        {
            long long a;
            int b;
            cin >> a >> b;
            decrease_key(a, b);
        }
        oper++;
    }
    
    return 0;
}