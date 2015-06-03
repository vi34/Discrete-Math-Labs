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

class Node {
public:
    string dat;
    string value;
    Node* left;
    Node* right;
    
};

Node hashh[21000];

void insert(string x, string y) {
    int key = 0;
    int p = 3;
    rep0(i, x.length()) {
        key += (x[i] - 'A') * p;
        p *= 3;
        key %= 20011;
    }
    key = abs(key);
    if(hashh[key].left == NULL) {
        hashh[key].value = x;
        hashh[key].dat = y;
        Node *b = &hashh[key];
        hashh[key].left = b;
        hashh[key].right = NULL;
    } else {
        Node *a = &hashh[key];
        while(a->right != NULL) {
            if(a->value == x) {
                a->dat = y;
                return;
            }
            a = a->right;
        }
        if(a->value == x)
        {
            a->dat = y;
            return;
        }
        Node* n = new Node();
        n->value = x;
        n->left = a;
        n->dat = y;
        n->right = NULL;
        a->right = n;
    }
    return;
}

string gett(string x) {
    int key = 0;
    int p = 3;
    rep0(i, x.length()) {
        key += (x[i] - 'A') * p;
        p *= 3;
        key %= 20011;
    }
    key = abs(key);
    if(hashh[key].left != NULL) {
        Node *a = &hashh[key];
        while(a->right != NULL) {
            if(a->value == x)
                return a->dat;
            a = a->right;
        }
        if(a->value == x)
            return a->dat;
    }
    return "none";
}

void del(string x) {
    int key = 0;
    int p = 3;
    rep0(i, x.length()) {
        key += (x[i] - 'A') * p;
        p *= 3;
        key %= 20011;
    }
    key = abs(key);
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
                    a->dat = a->right->dat;
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
    ifstream in("map.in");
    ofstream out("map.out");
    while(in) {
        string s;
        string x, y;
        in >> s >> x;
        if(s == "put")
        {
            in >> y;
            insert(x,y);
        }
        else if(s == "get")
        {
            string t = gett(x);
            out << t << endl;
        }
        else
            del(x);
        
    }
    
    return 0;
}