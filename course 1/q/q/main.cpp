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

int x[30000000];

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
        Node* tmp = tail;
        tail = tail->prev;
        delete tmp;
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
        Node* tmp = head;
        head = head->next;
        delete tmp;
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

int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    int a, b, c;
    cin >> a >> b >> c;
    rep0(i, k)
    scanf("%d", x + i);
    rep(i, k, n) {
        long long f = a * x[i - 2] + b * x[i - 1] + c;
        f = (f << 32);
        f = (f >> 32);
        if(f > (1 << 31) - 1) {
            f -= (1 << 32);
        } else if(f < -1 * (1 << 31)) {
            f += (1 << 32);
        }
        x[i] = f;
    }
    rep0(i, m - 1) {
        while(!is_Empty() && peek_f() > x[i])
            pop_f();
        Node* nn = new Node;
        nn->next = 0;
        nn->prev = 0;
        nn->v = x[i];
        addF(nn);
    }
    
    long long sum = 0;
    rep0(i,n - m + 1) {
        while(!is_Empty() && peek_f() > x[i + m - 1])
            pop_f();
        Node* nn = new Node;
        nn->next = 0;
        nn->prev = 0;
        nn->v = x[i + m - 1];
        addF(nn);
        sum += peek_b();
        if(!is_Empty() && peek_b() == x[i])
            pop_b();
    }
    
    cout << sum << endl;
    
    return 0;
}

/*
 30000000 15 5
 283471207 23947205 3
 17625384 939393931 1838388 912740247 290470294
*/