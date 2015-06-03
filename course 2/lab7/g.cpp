#include <cstdio>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

const int SIZE = 26;

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
    vector<int> strnum;
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

void add(string s, int strnum)
{
    vertex* cur = root;
    for(int i = 0; i < s.length(); ++i)
    {
        char c = s[i] - 'a';
        if (cur->sons[c] == 0)
        {
            cur->sons[c] = new vertex();
            cur->sons[c]->sufflink = 0;
            cur->sons[c]->pchar = c;
            cur->sons[c]->parent = cur;
            cur->sons[c]->terminal = false;
        }
        cur = cur->sons[c];
    }
    cur->terminal = true;
    cur->strnum.push_back(strnum);

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

int main() {
    freopen("search4.in","r",stdin);
    freopen("search4.out","w",stdout);
    root = new vertex();
    root->sufflink = root;
    int n;
    scanf("%d\n", &n);
    string s;
    char buf[1000001];
    for(int i = 0; i < n; ++i)
    {
        scanf("%s\n",buf);
        s = (const char*) buf;
        add(s,i);
    }
    scanf("%s", buf);
    s = (const char*) buf;
    vector<bool> answ(n, false);
    vertex* cur = root;
    char c;


    for(int i = 0; i < s.length(); ++i)
    {
        c = s[i] - 'a';
        cur = go(cur,c);
        if(!cur->checked)
        {
            cur->checked = true;
            for(int j = 0; j < cur->strnum.size(); ++j)
                answ[cur->strnum[j]] = true;
            vertex* cur2 = go_up(cur);
            while(cur2 != root)
            {
                for(int j = 0; j < cur2->strnum.size(); ++j)
                    answ[cur2->strnum[j]] = true;
                cur2 = go_up(cur2);
            }
        }

    }
    for(int i = 0; i < n; ++i)
    {
        if(answ[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}