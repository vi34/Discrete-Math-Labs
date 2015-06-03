#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <fstream>

using namespace std;

long double y[200], y2[200], f1, f2, h = 0.1;

void init(int r, long double x)
{
    f1 = y[r] * y[r] + y2[r] * y2[r];
    f2 = (y[r] * y2[r]);
}


void rgk(int r, long double x)
{
    long double fk[5][3], y1[3];
    init(r - 1, x - 0.1);
    fk[1][1] = h * f1;
    y1[1] = y[r - 1] + 0.5 * fk[1][1];
    fk[1][2] = h * f2;
    y1[2] = y2[r - 1] + 0.5 * fk[1][2];

    x = x + 0.5 * h;
    f1 = y1[1] * y1[1] +  y1[2] * y1[2];
    f2 = (y1[1] * y1[2]);
    fk[2][1] = h * f1;
    y1[1] = y[r - 1] + 0.5 * fk[2][1];
    fk[2][2] = h * f2;
    y1[2] = y2[r - 1] + 0.5 * fk[2][2];

    f1 = y1[1] * y1[1] +  y1[2] * y1[2];
    f2 = (y1[1] * y1[2]);
    fk[3][1] = h * f1;
    y1[1] = y[r - 1] + fk[3][1];
    fk[3][2] = h * f2;
    y1[2] = y2[r - 1] + fk[3][2];

    x = x + 0.5 * h;
    f1 = y1[1] * y1[1] +  y1[2] * y1[2];
    f2 = (y1[1] * y1[2]);
    fk[4][1] = h * f1;
    y[r] = y[r - 1] + 0.1666667 * (fk[1][1] + 2.0 * fk[2][1] + 2.0 * fk[3][1] + fk[4][1]);
    fk[4][2] = h * f2;
    y2[r] = y2[r - 1] + 0.1666667 * (fk[1][2] + 2.0 * fk[2][2] + 2.0 * fk[3][2] + fk[4][2]);
}


int main()
{
    ofstream out ("eyler.out");
    long double x = 2;
    //double x = -1;
    //double x = 0;
    int r = 0;
    y[0] = -0.6;
    y2[0] = 2;
    //y[0] = 0;
    //y2[0] = 1;
    //y[0] = 0;
    //y2[0] = 0;
    r++;
    while (x < 5.0)
    {
        //y[r] = y[r - 1] + h * (x + y[r - 1] * y[r - 1]);
        //y2[r] = y2[r - 1] + h * ((y[r - 1] - y2[r - 1]) * (y[r - 1] - y2[r - 1]));
        y[r] = y[r - 1] + h *(x * cos(y[r - 1] + y2[r - 1]));
        y2[r] = y2[r - 1] + h * sin(y[r - 1] - y2[r - 1]);
        //y[r] = y[r - 1] + h * y2[r - 1];
        //y2[r] = y2[r - 1] + h * exp(-x * y[r - 1]);
        out << "x = " << x << " " << "y(1) = " << y[r - 1] << " " << "y(2) = " << y2[r - 1] << endl;
        //out << y2[r -1] << endl; //<< " " << y[r - 1] << " " << y2[r - 1] << endl;
        x += h;
        r++;
    }
    ofstream out1 ("rgk.out");
    for (int i = 0; i <= 40; i++)
    {
        y[i] = 0;
        y2[i] = 0;
    }
    y[0] = -1;
    y2[0] = 1;
    x = 0.1;
    r = 1;
    while (x <= 4.1)
    {
        rgk(r, x);
        //out1 << "x = " << x << " " << "y(1) = " << y[r] << " " << "y(2) = " << y2[r] << endl;
        out1 << y2[r] << endl;// << "," << y[r] << ";";
        r++;
        x += h;
    }
    return 0;
}