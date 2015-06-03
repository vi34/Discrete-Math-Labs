#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>


using namespace std;


const long long INF = 8000000000000000000;


int main() {

    ifstream in ("planaritycheck2.in");
    ofstream out("planaritycheck.out");
    int t;
    in >> t;
    for(int num = 0; num < t; num++)
    {
        bool answer = true;
        string str;
        in >> str;
        int n = str.size();
        bitset<15> bits(str);
        if(n == 15)
        {

            if(bits.count() == 9)
            {
                vector <int> color(6, 0);
                color[0] = 1;
                bool nans = true;
                for(int i = 0; i < 5; i++)
                {
                    if(bits[15 - i] == 1)
                    {
                        if(color[1 + i] != -1)
                        {
                            if(color[1 + i] == color[0])
                                nans = false;
                        }
                        else
                        {
                            color[1 + i] = !color[0];
                        }
                    }
                }
                for(int i = 0; i < 4; i++)
                {
                    if(bits[15 - i - 5] == 1)
                    {
                        if(color[1 + i + 5] != -1)
                        {
                            if(color[1 + i + 5] == color[1])
                                nans = false;
                        }
                        else
                        {
                            color[1 + i + 5] = !color[1];
                        }
                    }
                }
                for(int i = 0; i < 3; i++)
                {
                    if(bits[15 - i - 9] == 1)
                    {
                        if(color[1 + i + 9] != -1)
                        {
                            if(color[1 + i + 9] == color[2])
                                nans = false;
                        }
                        else
                        {
                            color[1 + i + 9] = !color[2];
                        }
                    }
                }
                for(int i = 0; i < 2; i++)
                {
                    if(bits[15 - i - 12] == 1)
                    {
                        if(color[1 + i] != -1)
                        {
                            if(color[1 + i + 12] == color[3])
                                nans = false;
                        }
                        else
                        {
                            color[1 + i + 12] = !color[3];
                        }
                    }
                }
                if(bits[15 - 13] == 1)
                {
                    if(color[1] != -1)
                    {
                        if(color[1 + 13] == color[4])
                            nans = false;
                    }
                    else
                    {
                        color[1 + 13] = !color[4];
                    }
                }
                if(nans)
                    answer = false;


            }

            bitset<10> g;

            vector<int> vpath1{0,4,7,9,0,4,7,9,0,7,9,0,9,0,0};
            vector<int> vpath2{0,0,0,0,0,4,4,4,4,7,7,7,9,9,0};

            bitset<15> v1("000001111111111");
            bitset<15> v2("011110000111111");
            bitset<15> v3("101110111000111");
            bitset<15> v4("110111011011001");
            bitset<15> v5("111011101101010");
            bitset<15> v6("111101110110100");
            vector <bitset<15> > vars(6);
            vars[0] = v1;
            vars[1] = v2;
            vars[2] = v3;
            vars[3] = v4;
            vars[4] = v5;
            vars[5] = v6;
            for(int q = 0; q < 6; q++) {

                int j = 0;
                for (int i = 0; i < 15; ++i) {
                    if (vars[q][i])
                        g[j++] = bits[i];
                }
                string debug = g.to_string('0', '1');
                int kkk = bits.count();
                if ((bits.count() - g.count() == 2 )&& g.count() == 9) {
                    int a1 = -1;
                    int a2 = -1;
                    int dist = -1;
                    bool a1b = false;
                    for (int i = 0; i < 15; ++i) {
                        if (vars[q][i])
                            continue;

                        if (a1b) {
                            dist++;
                        }
                        if (bits[15 - i] == 1) {
                            if (!a1b) {
                                a1 = i;
                                a1b = true;
                            }
                            else {
                                a2 = i;
                                break;
                            }
                        }
                    }
                    if (a2 - a1 == dist + 1) {
                        g[10 - vpath1[a1] - dist + 1] = 1;
                    }
                    else {
                        g[10 - vpath2[a1] - dist + 1] = 1;
                    }
                }
                debug = g.to_string('0', '1');
                if (g.count() == 10) {
                    answer = false;
                }
            }


        }
        else
        {
            if(str == "1111111111")
                answer = false;
        }

        if(answer)
        {
            out << "YES" << endl;
        }
        else
        {
            out << "NO" << endl;
        }
    }
    return 0;
}