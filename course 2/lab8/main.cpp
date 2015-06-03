#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string.h>

using namespace std;

const int SIZE = 26;

int n = 0;

struct vertex {
    vertex(){
        memset(sons, 0,SIZE* sizeof(vertex*));
        memset(go, 0,SIZE* sizeof(vertex*));
        up = 0;
        checked = false;
    }

    vertex* sons[SIZE];
    vertex* go[SIZE];
    vertex* parent;
    vertex* sufflink;
    vertex* up;
    int pchar;
    bool terminal;
    bool checked;
};

vertex* root;
vertex* go(vertex* v, char c);

vertex* get_sufflink(vertex* v)
{
    if(v->sufflink == 0)
    {
        if(v->parent == root)
            v->sufflink = root;
        else
            v->sufflink = go(get_sufflink(v->parent),v->pchar);
    }
    return v->sufflink;
}

vertex* go(vertex* v, char c)
{
    if(!v->go[c])
    {
        if(v->sons[c])
        {
            v->go[c] = v->sons[c];
        } else {
            v->go[c] = ((v == root) ? root: go(get_sufflink(v),c));
        }

    }
    return v->go[c];
}

void add(string s)
{
    vertex* cur = root;
    for(int i = 0; i < s.length(); ++i)
    {
        char c = s[i] - 'a';
        if (cur->sons[c] == 0)
        {
            cur->sons[c] = new vertex();
            n++;
            cur->sons[c]->sufflink = 0;
            cur->sons[c]->pchar = c;
            cur->sons[c]->parent = cur;
            cur->sons[c]->terminal = false;
        }
        cur = cur->sons[c];
    }
    cur->terminal = true;

}

vertex* go_up(vertex* v)
{
    if(v->up == 0)
    if(get_sufflink(v)->terminal)
    {
        v->up = get_sufflink(v);
    } else if(get_sufflink(v) == root) {
        v->up = root;
    } else {
        v->up = go_up(get_sufflink(v));
    }

    return v->up;
}

string s;

void dfs(vertex* v) {
    v->checked = true;
    int its = n;
    for(int i = 0; i < SIZE; ++i) {
        if(v->sons[i] != 0) {
            cout << its << " " << ++n << " " << (char)('a' + i) << endl;
            dfs(v->sons[i]);
        }
    }
}


int main() {
    freopen ("trie.in", "r", stdin);
    freopen ("trie.out", "w", stdout);
    root = new vertex();
    root->sufflink = root;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        add(s.substr(i));
    }
    cout << n + 1 << " " << n << endl;
    n = 1;
    dfs(root);
    return 0;
}