#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "movetofront"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;



class Vertex {
public:
    int x, y, count;
    bool rev;
    Vertex* right;
    Vertex* left;
    
};

Vertex* root;

int Tcount (Vertex* v) {
    return v ? v->count : 0;
}

void update_count(Vertex* v) {
    if(v)
        v->count = Tcount(v->left) + Tcount(v->right) + 1;
}

Vertex* create(int x, int y, Vertex* left = NULL, Vertex* right = NULL) {
    Vertex* n = new Vertex;
    n->x = x;
    n->y = y;
    n->left = left;
    n->right = right;
    n->count = Tcount(n->left) + Tcount(n->right) + 1;
    return n;
}

void push(Vertex* v) {
    if(v && v->rev) {
        if(v->left)
            v->left->rev ^= true;
        if(v->right)
            v->right->rev ^= true;
        swap(v->left, v->right);
        v ->rev = false;
    }
}

void merge (Vertex* &v, Vertex* l, Vertex* r) {
    push(l);
    push(r);
    if(l == NULL)
        v = r;
    else if(r == NULL)
        v = l;
    else if(l->y > r->y) {
        merge(l->right,l->right, r);
        v = l;
    } else {
        merge(r->left, l, r->left);
        v = r;
    }
    update_count(v);
}

void split(Vertex* t, int x0, Vertex* &l, Vertex* &r, int sum = 0) {
    if(!t) {
        l = NULL;
        r = NULL;
        return;
    }
    push(t);
    int this_x = sum + Tcount(t->left);
    if(x0 <= this_x) {
        split(t->left, x0, l, t->left, sum);
        r = t;
    } else {
        split(t->right, x0, t->right, r, sum + Tcount(t->left) + 1);
        l = t;
    }
    update_count(t);
    
}

void Treverse (Vertex* v, int l, int r) {
    Vertex* v1 = 0;
    Vertex* v2 = 0;
    Vertex* v3 = 0;
    split(v, l , v1, v2);
    split(v2, r - l + 1, v2, v3);
    v2->rev ^= true;
    merge(v, v1, v2);
    merge(v, v, v3);
}

void insert (Vertex* &v, Vertex* n) {
	if (!v)
		v = n;
	else if (n->y > v->y) {
		split (v, n->x, n->left, n->right);
        v = n;
    }
	else if(n->x < v->x)
        insert (v->left, n);
    else
        insert (v->right, n);
    update_count(v);
}

void pr(Vertex* v) {
    if(!v)
        return;
    push(v);
    pr(v->left);
    printf("%d ", v->x);
    pr(v->right);
}



int main ()
{
    
    //freopen(NAME".in", "r", stdin);
    //freopen(NAME".out", "w", stdout);
    int n, m;
    cin >> n >> m;
    root = create(1, 0);
    rep(i,1, n) {
        insert(root, create(i + 1, rand()));
    }
    rep0(i, m) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        r--;
        if(l != 0) {
            Treverse(root, 0, r);
            Treverse(root, 0, r - l);
            Treverse(root, r - l + 1, r);
        }
    }
    pr(root);
    return 0;
}

