#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <map>

#define NAME "bstsimple"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

class Vertex {
public:
    int v;
    Vertex* parent;
    Vertex* right;
    Vertex* left;
};

Vertex* root = 0;
Vertex* Sparent = 0;
int Sdir = 0;
int size = 0;

void Tinsert(Vertex* curr, Vertex* v){
    if(root == 0) {
        root = v;
        v->parent = 0;
        return;
    }
    if(curr->v == v->v){
        return;
    }
    if(curr->v > v->v) {
        if(curr->left == 0)
        {
            curr->left = v;
            v->parent = curr;
        }
        else
            Tinsert(curr->left, v);
    } else {
        if(curr->right == 0)
        {
            curr->right = v;
            v->parent = curr;
        }
        else
            Tinsert(curr->right, v);
    }
}

Vertex* Tsearch(Vertex* curr, int x){
    if(curr == root)
        Sparent = root;
    if(curr == 0 || curr->v == x){
        return curr;
    }
    if(curr->v > x) {
        if(curr->left == 0)
        {
            Sparent = curr;
            Sdir = 0;
        }
        return Tsearch(curr->left, x);
    } else {
        if(curr->right == 0){
            Sparent = curr;
            Sdir = 1;
        }
        return Tsearch(curr->right, x);
    }
    
}

Vertex* minimum(Vertex* v){
    if(v->left == 0)
        return v;
    return minimum(v->left);
}

Vertex* maximum(Vertex* v){
    if(v->right == 0)
        return v;
    return maximum(v->right);
}

Vertex* Tnext(Vertex* v){
    if(v != 0 && v->right != 0)
        return minimum(v->right);
    Vertex* p;
    if(v == 0)
        p = Sparent;
    else
        p = v->parent;
    while (p != 0 && ((v == 0 && Sdir)|| (v != 0 && v == p->right))){
        v = p;
        p = p->parent;
    }
    return p;
}

Vertex* Tprev(Vertex* v){
    if(v != 0 && v->left != 0)
        return maximum(v->left);
    Vertex* p;
    if(v == 0)
        p = Sparent;
    else
        p = v->parent;
    while (p != 0 && ((v == 0 && !Sdir)|| (v != 0 && v == p->left))){
        v = p;
        p = p->parent;
    }
    return p;
}

void  Tdel(Vertex* v) {
    if(v != 0){
        if(v->right == 0)
        {
                if(v == root)
                {
                    root = v->left;
                    if(v->left != 0)
                        v->left->parent = 0;
                }
                else if(v == v->parent->left)
                {
                    v->parent->left = v->left;
                    if(v->left != 0)
                        v->left->parent = v->parent;
                }
                else {
                    v->parent->right = v->left;
                    if(v->left != 0)
                        v->left->parent = v->parent;
                }
            //v = 0;
            delete v;
            v = NULL;
            
        } else if(v->left == 0) {
            if(v == root) {
                root = v->right;
                v->right->parent = 0;
            }
            else if(v == v->parent->left)
            {
                v->parent->left = v->right;
                v->right->parent = v->parent;
            }
            else {
                v->parent->right = v->right;
                v->right->parent = v->parent;
            }
            //v = 0;
            delete v;
            v = NULL;
        } else {
            Vertex* n = Tnext(v);
            v->v = n->v;
            //n = 0;
            delete n;
            n = NULL;
        }
    }
}

Vertex* create(int vv) {
    Vertex* v = new Vertex;
    v->parent = 0;
    v->right = 0;
    v->left = 0;
    v->v = vv;
    return v;
}

int main ()
{
    
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
    while (!feof(stdin)) {
        string s;
        int par;
        cin >> s >> par;
        if(s == "insert"){
            Tinsert(root, create(par));
        }
        else if(s == "exists") {
            if(Tsearch(root, par) != 0)
                cout << "true" << endl;
            else
                cout << "false" << endl;
        } else if(s == "next") {
            Vertex* n = Tnext(Tsearch(root, par));
            if(n == 0)
                cout << "none" << endl;
            else
                cout << n->v << endl;
        }
        else if(s == "prev") {
            Vertex* n = Tprev(Tsearch(root, par));
            if(n == 0)
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


/*
 insert 2
 insert 5
 insert 3
 exists 2
 exists 4
 next 4
 prev 4
 exists 5
 delete 5
 exists 5
 next 4
 prev 4
 insert 5
 next 4
 insert 5
 delete 5
 delete 5
 delete 5
 exists 5
 next 4
 insert 5
 next 4
 
 
 insert 2
 insert 3
 insert 4
 insert 110
 next 2
 next 3
 next 4
 delete 3
 next 2
 delete 4
 next 2
 insert 3
 delete 3
 delete 3
 delete 3
 next 2
 insert 3
 next 2
 prev 3
 prev 2
 delete 2
 delete 110
 next 3
 prev 3
 delete 3
 prev 3
 next 3
 exists 110
 next 3
 exists 110
 next 3
 next 4
 prev 111
 next 109
 next 110
 
 
 
 insert 1
 next 1
 delete 1
 next 1
 prev 1
 insert 2
 next 1
 delete 2
 next 1
 next 2
 
 
 
 set& set::operator=(set other)
 {
 root = new vertex();
 if (other.root->left != 0)
 {
 try
 {
 root->left = new vertex(root, other.root -> left);
 }
 catch(...)
 {
 delete root;
 throw;
 }
 }
 else
 {
 root -> left = 0;
 }
 ssize = other.ssize;
 return *this;
 }

 */

