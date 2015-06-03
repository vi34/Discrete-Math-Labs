#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "queuemin2"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

class Node {
 public:
    int v;
    Node* next;
    Node* prev;
};

Node* head = 0;
Node* tail = 0;
int size = 0;

void addF(Node* p){
    if(size == 0)
    {
        tail = p;
    }
    p->next = head;
    p->prev = 0;
    if(head != NULL)
        head->prev = p;
    head = p;
    size++;
}

void addB(Node* p){
    if(size == 0)
    {
        head = p;
    }
    p->next = 0;
    p->prev = tail;
    if(tail != NULL)
        tail->next = p;
    tail = p;
    size++;
}

int pop_b() {
    int result = 0;
    if(size > 0){
        result = tail->v;
        if(size > 1)
            tail->prev->next = 0;
        delete tail;
        tail = tail->prev;
        size--;
    }
    return result;
}

int pop_f() {
    int result = 0;
    if(size > 0){
        result = head->v;
        if(size > 1)
            head->next->prev = 0;
        delete head;
        head = head->next;
        size--;
    }
    return result;
}
int peek_b() {
    int result = 0;
    if(size > 0)
        result = tail->v;
    return result;
}
int peek_f() {
    int result = 0;
    if(size > 0)
        result = head->v;
    return result;
}

bool is_Empty() {
    return size == 0;
}


Node* create(int vv) {
    Node* n = new Node;
    n->next = 0;
    n->prev = 0;
    n->v = vv;
    return n;
}

int calcf(int x2, int x1, int a, int b, int c)
{
    int x;
    long long f = a * x2 + b * x1 + c;
    f = (f << 32);
    f = (f >> 32);
    if(f > (1 << 31) - 1) {
        f -= (1 << 32);
    } else if(f < -1 * (1 << 31)) {
        f += (1 << 32);
    }
    x = f;
    return x;
}

int main ()
{
    
    //freopen(NAME".in", "r", stdin);
    //freopen(NAME".out", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    int a, b, c;
    cin >> a >> b >> c;
    int x[k];
    int xp[3];
    int xf[3];
    rep0(i, k)
        scanf("%d", x + i);
    /*rep(i, k, n) {
        long long f = a * x[i - 2] + b * x[i - 1] + c;
        f = (f << 32);
        f = (f >> 32);
        if(f > (1 << 31) - 1) {
            f -= (1 << 32);
        } else if(f < -1 * (1 << 31)) {
            f += (1 << 32);
        }
        x[i] = f;
    }*/
    xf[0] = x[0];
    xf[1] = x[1];
    if(k > 1)
        xf[2] = x[2];
    else
        xf[2] = calcf(xf[0], xf[1], a, b, c);
    xp[0] = x[0];
    xp[1] = x[1];
    if(k > 1)
        xp[2] = x[2];
    else
        xp[2] = calcf(xp[0], xp[1], a, b, c);
    rep0(i, m - 1) {
        while(!is_Empty() && peek_f() > x[i])
            pop_f();
        addF(create(x[i]));
        if (i < k && i > 2) {
            xf[0] = xf[1];
            xf[1] = xf[2];
            xf[2] = x[i];
        } else if(i > k) {
            xf[0] = xf[1];
            xf[1] = xf[2];
            xf[2] = calcf(xf[0], xf[1], a, b, c);
        }
    }
    long long sum = 0;
    rep0(i,n - m + 1) {
        if (i + m - 1 < k && i + m - 1 > 2) {
            xf[0] = xf[1];
            xf[1] = xf[2];
            xf[2] = x[i];
            
        } else if(i > k) {
            xf[0] = xf[1];
            xf[1] = xf[2];
            xf[2] = calcf(xf[0], xf[1], a, b, c);
        }
        while(!is_Empty() && peek_f() > xf[2])
            pop_f();
        addF(create(xf[2]));
        sum += peek_b();
        if(!is_Empty() && peek_b() == x[i])
            pop_b();
    }
    cout << sum << endl;
    
    return 0;
}


/*
 2000000 15 5
 283471207 23947205 3
 17625384 939393931 1838388 912740247 290470294

*/