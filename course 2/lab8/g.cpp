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
long long n;
int n2;

struct node {
    long long l, r;
    long long depth = -1;
    long long vnum = -1;
    bool leaf1 = false;
    bool leaf2 = false;
    node *parent;
    node *suff_link;
    map<char,node*> next;
    bool term() {
        return ((r == n));
    }

    node(long long l, long long r, node* par = nullptr)
            : l(l), r(r), parent(par),suff_link(nullptr) {}
    long long len() { return r - l;}
    node* &get(char c) {
        if (!next.count(c)) next[c] = nullptr;
        return next[c];
    }


};

node* root;
pair<node*, long long> point;
long long m;

pair<node*, long long> walk(pair<node*, long long> p, long long l, long long r) {
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

node *split(pair<node*, long long> st) {
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

void add(long long k) {
    for (;;) {
        pair<node*, long long> next = walk(point, k, k + 1);
        if(next.first != nullptr) {
            point = next;
            return;
        }
        node* mid = split(point);
        node* leaf = new node(k, n, mid);
        if (k != n - 1) leaf->vnum = ++m;
        mid->get(s[k]) = leaf;
        point.first = get_slink(mid);
        point.second = point.first->len();
        if(mid == root) break;
    }
}

node* answ = nullptr;

void dfs(node *v, long long l) {
    if(v == nullptr)
    {
        cout << "ASFASFAF";
        return;
    }
    if(v->l < n2)
        v->leaf1 = true;
    else
        v->leaf2 = true;
    if (v != root && l == 0)
        v->depth = v->len();
    else
        v->depth = l + v->len();
    if(v->r == n)
        v->depth--;
    for (auto it = v->next.begin(); it != v->next.end(); it++) {
        if((*it).second->l != n - 1) {
            dfs((*it).second, v->depth);
            if ((*it).second->leaf1)
                v->leaf1 = true;
            if((*it).second->leaf2)
                v->leaf2 = true;
        }
        else {
            v->leaf2 = true;
        }
    }
    long long r = ((v->r == n) ? n - 1 : v->r);
    if ((answ == nullptr || (answ->depth < v->depth )) && v->leaf2 && v->leaf1)
        answ = v;
    if(v != root) {
        //cout << v->parent->vnum << " " << v->vnum << " " << v->l + 1 << " " << ((v->r == n) ? n - 1 : v->r) << " " << v->l2;
    }
    //cout << " " << v->leafs << endl;


}



int main() {
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);
    string s1,s2;
    cin >> s1 >> s2;
    s = s1;
    s += ('a' - 1);
    n2 = s.size();
    s += s2;
    s += ('a' - 2);
    n = s.size();
    m = 0;
    root = new node(-1,-1);
    root->vnum = ++m;
    point = make_pair(root,0);
    for(int i = 0; i < n; ++i)
        add(i);
    dfs(root, 0);
    long long r = ((answ->r == n) ? n - 1 : answ->r);
    long long answ_len = answ->depth;
    if(false){//answ_len * (long long)answ->leafs < n - 1) {
        cout << n - 1 << endl << n - 1 << endl;
        for(long long i = 0; i < n - 1; ++i) {
            cout << s[i] << " ";
        }
    } else {
        //cout << (long long)(answ_len * (long long)answ->leafs) << endl << answ_len << endl;
        for(long long i = r - answ_len; i < r; ++i) {
            cout << s[i];
        }
    }
    cout << endl;
    return 0;
}
