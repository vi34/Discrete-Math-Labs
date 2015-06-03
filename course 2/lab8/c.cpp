//
// Created by Виктор Шатров on 05.04.15.
//

#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

string s;

struct node {
    int l, r;
    int vnum = -1;
    node *parent;
    node *suff_link;
    map<char,node*> next;

    node(int l, int r, node* par = nullptr)
            : l(l), r(r), parent(par),suff_link(nullptr) {}
    int len() { return r - l;}
    node* &get(char c) {
        if (!next.count(c)) next[c] = nullptr;
        return next[c];
    }


};

node* root;
int n;
pair<node*, int> point;
int m;

pair<node*, int> walk(pair<node*, int> p, int l, int r) {
    while (l < r) {
        if (p.second == p.first->len()) {
            p = make_pair(p.first->get(s[l]), 0);
            if (p.first == nullptr)
                return p;
        } else {
            if (s[p.first->l + p.second] != s[l])
                return make_pair(nullptr, -1);
            if (r - l < p.first->len() - p.second)
                return make_pair(p.first, p.second + r - l);
            l += p.first->len() - p.second;
            p.second = p.first->len();
        }
    }
    return p;
}

node *split(pair<node*, int> st) {
    if (st.second == st.first->len())
        return st.first;
    if (st.second == 0)
        return st.first->parent;

    node* par = st.first->parent;
    node* mid = new node(st.first->l,st.first->l + st.second, par);
    mid->vnum = ++m;
    par->get(s[st.first->l]) = mid;
    mid->get(s[st.first->l + st.second]) = st.first;
    st.first->parent = mid;
    st.first->l += st.second;
    return mid;

}

node *get_slink(node* v) {
    if (v->suff_link != nullptr) return v->suff_link;
    if (v->parent == nullptr) return root;
    node *to = get_slink(v->parent);
    return v->suff_link = split(walk(make_pair(to, to->len()), v->l + (v->parent == root), v->r));
}

void add(int k) {
    for (;;) {
        pair<node*, int> next = walk(point, k, k + 1);
        if(next.first != nullptr) {
            point = next;
            return;
        }
        node* mid = split(point);
        node* leaf = new node(k, n, mid);
        leaf->vnum = ++m;
        mid->get(s[k]) = leaf;
        point.first = get_slink(mid);
        point.second = point.first->len();
        if(mid == root) break;
    }
}

void dfs(node *v) {
    if(v == nullptr) return;
    if(v != root) {
        cout << v->parent->vnum << " " << v->vnum << " " << v->l + 1 << " " << v->r  << endl;
    }
    for (auto it = v->next.begin(); it != v->next.end(); it++) {
        dfs((*it).second);
    }

}



int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> s;
    n = s.size();
    m = 0;
    root = new node(-1,-1);
    root->vnum = ++m;
    point = make_pair(root,0);
    for(int i = 0; i < n; ++i)
        add(i);


    cout << m  << " " << m - 1 << endl;
    dfs(root);

    return 0;
}
