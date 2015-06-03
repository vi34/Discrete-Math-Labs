#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <map>

#define NAME "set"
#define mp make_pair
#define pb push_back
#define rep0(i, n) for(int i = 0; i < n; i++)
#define rep(i, l, r) for(int i = l; i < r; i++)

using namespace std;

long long INF = 10000000000;

class Node {
public:
    int value;
    Node* left;
    Node* right;
    
};

Node hashh[21000];

void insert(int x) {
    int key = abs(x % 20011);
    if(hashh[key].left == NULL) {
        hashh[key].value = x;
        hashh[key].left = &hashh[key];
        hashh[key].right = NULL;
    } else {
        Node *a = &hashh[key];
        while(a->right != NULL) {
            if(a->value == x)
                return;
            a = a->right;
        }
        if(a->value == x)
            return;
        Node* n = new Node();
        n->value = x;
        n->left = a;
        n->right = NULL;
        a->right = n;
    }
    return;
}

bool exists(int x) {
    int key = abs(x % 20011);
    if(hashh[key].left != NULL) {
        Node *a = &hashh[key];
        while(a->right != NULL) {
            if(a->value == x)
                return true;
            a = a->right;
        }
        if(a->value == x)
            return true;
    }
    return false;
}

void del(int x) {
    int key = abs(x % 20011);
    if(hashh[key].left != NULL) {
        Node *a = &hashh[key];
        while(a->right != NULL) {
            if(a->value == x)
                break;
            a = a->right;
        }
        if(a->value == x) {
            if(a->right == NULL) {
                if(a->left == a) {
                    a->left = NULL;
                    return;
                }
                a->left->right = NULL;
                a->left = NULL;
                delete a;
            } else {
                if(a->left == a) {
                    a ->value = a->right->value;
                    delete a->right;
                    if(a->right->right != NULL) {
                        a->right->right->left = a;
                        a->right = a->right->right;
                        
                    }else {
                        a->right = NULL;
                    }
                    return;
                }
                a->right->left = a->left;
                a->left->right = a->right;
                delete a;
            }
        }
        
    }
    return;
}

int main ()
{
    
    //freopen(NAME".in", "r", stdin);
    //freopen(NAME".out", "w", stdout);
    ifstream in ("set.in");
    ofstream out ("set.out");
    while (in) {
        string s;
        int x;
        in >> s >> x;
        if(s == "insert")
            insert(x);
        else if(s == "exists")
        {
            if(exists(x))
                out << "true" << endl;
            else
                out << "false" << endl;
        }
        else
            del(x);
        
    }
    
    return 0;
}
