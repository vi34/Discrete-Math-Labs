#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "bst"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

const int RED = 0;
const int BLACK = 1;
long long INF = 10000000000;

class Vertex {
public:
    int v;
    int color;
    Vertex* parent;
    Vertex* right;
    Vertex* left;
};

Vertex* Nil;
Vertex* create(int vv) {
    Vertex* v = new Vertex;
    v->color = RED;
    v->parent = Nil;
    v->right = Nil;
    v->left = Nil;
    v->v = vv;
    return v;
}


Vertex* root = 0;
Vertex* Sparent = 0;
int Sdir = 0;
int size = 0;


void Right_Rotate(Vertex* v) {
    Vertex* r = v->left;
    if(v != root) {
        Vertex* p = v->parent;
        if(v == p->left)
            p->left = r;
        else
            p->right = r;
        r->parent = p;
    } else {
        r->parent = Nil;
        root = r;
    }
    v->left = r->right;
    if(v->left != Nil)
        v->left->parent = v;
    v->parent = r;
    r->right = v;
    
}

void Left_Rotate(Vertex* v) {
    Vertex* r = v->right;
    if(v != root) {
        Vertex* p = v->parent;
        if(v == p->right)
            p->right = r;
        else
            p->left = r;
        r->parent = p;
    } else {
        r->parent = Nil;
        root = r;
    }
    v->right = r->left;
    if(v->right != Nil)
        v->right->parent = v;
    v->parent = r;
    r->left = v;
}

void Tfix(Vertex* v) {
    while (v->parent->color == RED) {
        if (v->parent->parent->left == v->parent) {
            Vertex* y = v->parent->parent->right;
            if(y->color == RED) {
                y->color = BLACK;
                v->parent->color = BLACK;
                v->parent->parent->color = RED;
                v = v->parent->parent;
            } else {
                if(v->parent->right == v) {
                    v = v->parent;
                    Left_Rotate(v);
                }
                v->parent->color = BLACK;
                v->parent->parent->color = RED;
                Right_Rotate(v->parent->parent);
            }
        } else {
            Vertex* y = v->parent->parent->left;
            if(y->color == RED) {
                y->color = BLACK;
                v->parent->color = BLACK;
                v->parent->parent->color = RED;
                v = v->parent->parent;
            } else {
                if(v->parent->left == v) {
                    v = v->parent;
                    Right_Rotate(v);
                }
                v->parent->color = BLACK;
                v->parent->parent->color = RED;
                Left_Rotate(v->parent->parent);
            }
        }
        
    }
    root->color = BLACK;
}

void Tinsert(Vertex* curr, Vertex* v){
    if(root == Nil) {
        root = v;
        v->parent = Nil;
        v->color = BLACK;
        return;
    }
    if(curr->v == v->v){
        return;
    }
    if(curr->v > v->v) {
        if(curr->left == Nil)
        {
            curr->left = v;
            v->parent = curr;
            Tfix(v);
        }
        else
            Tinsert(curr->left, v);
    } else {
        if(curr->right == Nil)
        {
            curr->right = v;
            v->parent = curr;
            Tfix(v);
        }
        else
            Tinsert(curr->right, v);
    }
}


Vertex* Tsearch(Vertex* curr, int x){
    if(curr == root)
        Sparent = root;
    if(curr == Nil || curr->v == x){
        return curr;
    }
    if(curr->v > x) {
        if(curr->left == Nil)
        {
            Sparent = curr;
            Sdir = 0;
        }
        return Tsearch(curr->left, x);
    } else {
        if(curr->right == Nil){
            Sparent = curr;
            Sdir = 1;
        }
        return Tsearch(curr->right, x);
    }
    
}

Vertex* minimum(Vertex* v){
    if(v->left == Nil)
        return v;
    return minimum(v->left);
}

Vertex* maximum(Vertex* v){
    if(v->right == Nil)
        return v;
    return maximum(v->right);
}

Vertex* Tnext(Vertex* v){
    if(v != Nil && v->right != Nil)
        return minimum(v->right);
    Vertex* p;
    if(v == Nil)
        p = Sparent;
    else
        p = v->parent;
    while (p != Nil && ((v == Nil && Sdir)|| (v != Nil && v == p->right))){
        v = p;
        p = p->parent;
    }
    return p;
}

Vertex* Tprev(Vertex* v){
    if(v != Nil && v->left != Nil)
        return maximum(v->left);
    Vertex* p;
    if(v == Nil)
        p = Sparent;
    else
        p = v->parent;
    while (p != Nil && ((v == Nil && !Sdir)|| (v != Nil && v == p->left))){
        v = p;
        p = p->parent;
    }
    return p;
}

void Tdel_fix(Vertex* v) {
    while(v != root && v->color == BLACK) {
        if(v == v->parent->right) {
            Vertex* w = v->parent->left;
            if(w->color == RED) {
                w->color = BLACK;
                v->parent->color = RED;
                Right_Rotate(v->parent);
                w = v->parent->left;
            }
            if(w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                v = v->parent;
            } else {
                if(w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(w);
                    w = v->parent->left;
                }
                w->color = v->parent->color;
                v->parent->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(v->parent);
                v = root;
            }
        } else {
            Vertex* w = v->parent->right;
            if(w->color == RED) {
                w->color = BLACK;
                v->parent->color = RED;
                Left_Rotate(v->parent);
                w = v->parent->right;
            }
            if(w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                v = v->parent;
            } else {
                if(w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(w);
                    w = v->parent->right;
                }
                w->color = v->parent->color;
                v->parent->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(v->parent);
                v = root;
            }
        }
    }
    v->color = BLACK;
}

void  Tdel(Vertex* v) {
    if(v != Nil){
        Vertex* y;
        if(v->right == Nil || v->left == Nil)
            y = v;
        else
            y = Tnext(v);
        Vertex* x;
        if(y->left != Nil)
            x = y->left;
        else
            x = y->right;
        x->parent = y->parent;
        if(y->parent == Nil)
            root = x;
        else if(y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        if(y != v) {
            v->v = y->v;
        }
        if(y->color == BLACK)
            Tdel_fix(x);
        delete y;
    }
    
}

int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    Nil = new Vertex;
    Nil->color = BLACK;
    Nil->parent = Nil;
    root = Nil;
    while (!feof(stdin)) {
        string s;
        int par;
        cin >> s >> par;
        if(s == "insert"){
            Tinsert(root, create(par));
        }
        else if(s == "exists") {
            if(Tsearch(root, par) != Nil)
                cout << "true" << endl;
            else
                cout << "false" << endl;
        } else if(s == "next") {
            Vertex* n = Tnext(Tsearch(root, par));
            if(n == Nil)
                cout << "none" << endl;
            else
                cout << n->v << endl;
        }
        else if(s == "prev") {
            Vertex* n = Tprev(Tsearch(root, par));
            if(n == Nil)
                cout << "none" << endl;
            else
                cout << n->v << endl;
        }
        else {
            Tdel(Tsearch(root, par));
        }
    }
    
    return 0;
}

