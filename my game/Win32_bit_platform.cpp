#include <windows.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <chrono>
#include "BMP.h"
#include <thread>
#include <conio.h>

using namespace std;

int ischanged[200];
int ispressed[200];

float speedduh = 0.1;
float speedduh1 = 0.05;
float speedpekmen = 0.1;

BMP pekmen1d("PacmanKM1d.bmp");
BMP pekmen2d("PacmanKM2d.bmp");
BMP pekmen3d("PacmanKM3d.bmp");
BMP pekmen4d("PacmanKM4d.bmp");
BMP pekmen5d("PacmanKM5d.bmp");
BMP pekmen6("PacmanKM6.bmp");

BMP pekmen1s("PacmanKM1s.bmp");
BMP pekmen2s("PacmanKM2s.bmp");
BMP pekmen3s("PacmanKM3s.bmp");
BMP pekmen4s("PacmanKM4s.bmp");
BMP pekmen5s("PacmanKM5s.bmp");

BMP pekmen1a("PacmanKM1a.bmp");
BMP pekmen2a("PacmanKM2a.bmp");
BMP pekmen3a("PacmanKM3a.bmp");
BMP pekmen4a("PacmanKM4a.bmp");
BMP pekmen5a("PacmanKM5a.bmp");

BMP pekmen1w("PacmanKM1w.bmp");
BMP pekmen2w("PacmanKM2w.bmp");
BMP pekmen3w("PacmanKM3w.bmp");
BMP pekmen4w("PacmanKM4w.bmp");
BMP pekmen5w("PacmanKM5w.bmp");

BMP board1("horizontala.bmp");
BMP board2("vertikala.bmp");
BMP board3("DD.bmp");
BMP board4("DL.bmp");
BMP board5("GD.bmp");
BMP board6("GL.bmp");
BMP board7("prazno.bmp");

BMP food("food.bmp");
BMP food1("food1.bmp");

BMP dduh10("duh10.bmp");
BMP dduh12("duh12.bmp");
BMP dduh14("duh14.bmp");
BMP dduh16("duh16.bmp");

BMP dduh20("duh20.bmp");
BMP dduh22("duh22.bmp");
BMP dduh24("duh24.bmp");
BMP dduh26("duh26.bmp");

BMP dduh30("duh30.bmp");
BMP dduh32("duh32.bmp");
BMP dduh34("duh34.bmp");
BMP dduh36("duh36.bmp");

BMP dduh40("duh40.bmp");
BMP dduh42("duh42.bmp");
BMP dduh44("duh44.bmp");
BMP dduh46("duh46.bmp");

BMP dduh50("duh50.bmp");
BMP dduh52("duh52.bmp");
BMP dduh54("duh54.bmp");
BMP dduh56("duh56.bmp");

int timer = 0;

bool running = true;
void* buffer_memory;
int buffer_width;
int buffer_heigth;
BITMAPINFO buffer_bitmap_info;

//int windowheigth = height * 20;
//int windowwidth = 20 * width;

//int windowwidth = 800;
//int windowheigth = 800;

int f(int x, int y, BMP* a, int color)
{
    int c = 0;
    if (x >= 1600 || y >= 900)
        c++;

    return a->data[3 * (y * a->bmp_info_header.width + x) + color];
}

#define width 28
#define height 31
#define grid '*'
#define pekmen 1
#define spacee ' '
#define ghost 'G'

int windowheigth = height * 20;
int windowwidth = 20 * width;

char matrica[height][width];

string table[31] = {
"****************************",
"*000000000000**000000000000*",
"*0****0*****0**0*****0****0*",
"*F****0*****0**0*****0****F*",
"*0****0*****0**0*****0****0*",
"*00000000000000000000000000*",
"*0****0**0********0**0****0*",
"*0****0**0********0**0****0*",
"*000000**0000**0000**000000*",
"******0*****0**0*****0******",
"******0*****0**0*****0******",
"******0**0000000000**0******",
"******0**0********0**0******",
"******0**0********0**0******",
"0000000000********0000000000",
"******0**0********0**0******",
"******0**0********0**0******",
"******0**0000000000**0******",
"******0**0********0**0******",
"******0**0********0**0******",
"*000000000000**000000000000*",
"*0****0*****0**0*****0****0*",
"*0****0*****0**0*****0****0*",
"*F00**0000000000000000**00F*",
"***0**0**0********0**0**0***",
"***0**0**0********0**0**0***",
"*000000**0000**0000**000000*",
"*0**********0**0**********0*",
"*0**********0**0**********0*",
"*00000000000000000000000000*",
"****************************"
};

/*string table[31] = {
"****************************",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"*00000000000000000000000000*",
"****************************"
};*/

pair <float, float> igrac = make_pair(14, 1);
pair <float, float> duh1 = make_pair(12, 12);
pair <float, float> duh2 = make_pair(12, 13);
pair <float, float> duh3 = make_pair(12, 14);
pair <float, float> duh4 = make_pair(12, 15);
pair <int, int> ciljduh2;

int randx = duh4.first, randy = duh4.second;

char ci='s';
char konteiner;
char cd1;
char cd2;
char cd3;
char cd4;

int scared = 0;
int scared1 = 0;
int scared2 = 0;
int scared3 = 0;
int scared4 = 0;

int tajmer1 = 0;
int tajmer2 = 0;
int tajmer3 = 0;
int tajmer4 = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float abss(float x) {
    if (x < 0) x *= -1;
    return x;
}

float distanca(float x2, float y2, float x1, float y1) {
    
    if (x2 >= height) x2 -= height;
    if (y2 >= width) y2 -= width;
    if (x2 < 0) x2 += height;
    if (y2 < 0) y2 += width;

    return sqrt((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2));
}

vector < pair <int, int> > bfs(int x1, int y1, int x2, int y2) {

    vector < vector < pair <int, int> > > putevi;

    bool used[height][width] = { 0 };

    vector <pair <int, int> > put1;
    put1.push_back(make_pair(x1, y1));
    if (x1 == x2 && y1 == y2) return put1;
    putevi.push_back(put1);
    used[x1][y1] = 1;

    while (1) {
        int k = putevi.size();
        for (int i = 0; i < k; i++) {

            int a, b;
            a = (putevi[i][putevi[i].size() - 1]).first;
            b = (putevi[i][putevi[i].size() - 1]).second;
            bool flag1 = 0;

            for (int hhh = 0; hhh < 4; hhh++) {

                int ggg1 = hhh < 2, ggg2 = hhh >= 2;

                if (hhh % 2 && ggg1) ggg1 = -1;
                if (hhh % 2 && ggg2) ggg2 = -1;
                int a1, b1;
                b1 = (width + b + ggg1) % width;
                a1 = (height + a + ggg2) % height;
                if (used[a1][b1] == 0 && matrica[a1][b1]) {
                    used[a1][b1] = 1;
                    if (flag1 == 0) {
                        putevi[i].push_back(make_pair(a1, b1));
                    }
                    else {
                        vector <pair <int, int> > vek;
                        for (int j = 0; j < putevi[i].size() - 1; j++) {
                            vek.push_back(putevi[i][j]);
                        }
                        vek.push_back(make_pair(a1, b1));
                        putevi.push_back(vek);

                    }
                    flag1 = 1;
                }
            }
        }
        for (int asd = 0; asd < putevi.size(); asd++) {

            /*
            for(int asd1=0;asd1<putevi[asd].size();asd1++){
                cout << putevi[asd][asd1].first << putevi[asd][asd1].second << ", ";
            }
            cout << '\n';
            */

            if (putevi[asd][putevi[asd].size() - 1].first == x2 && putevi[asd][putevi[asd].size() - 1].second == y2)
                return putevi[asd];
        }
    }
}

void figrac() {

    if (!(abss(igrac.first - (int)(igrac.first + 0.5)) < 0.0001 && abss(igrac.second - (int)(igrac.second + 0.5)) < 0.0001)) {
        if (ci == 'w') igrac.first -= speedpekmen;
        if (ci == 's') igrac.first += speedpekmen;
        if (ci == 'd') igrac.second += speedpekmen;
        if (ci == 'a') igrac.second -= speedpekmen;

        if (igrac.first < 0) igrac.first += height;
        if (igrac.first >= height) igrac.first -= height;
        if (igrac.second < 0) igrac.second += width;
        if (igrac.second >= width) igrac.second -= width;
        return;
    }

    igrac.first = (int)(igrac.first + 0.001);
    igrac.second = (int)(igrac.second + 0.001);

    matrica[(int)igrac.first][(int)igrac.second] = 1;
    int cnt = 0;

    if (ispressed['S']) konteiner = 's';
    if (ispressed['A']) konteiner = 'a';
    if (ispressed['D']) konteiner = 'd';
    if (ispressed['W']) konteiner = 'w';

    if (konteiner == 's' && matrica[((int)igrac.first + 1) % height][(int)igrac.second]) ci = konteiner;
    if (konteiner == 'w' && matrica[((int)igrac.first - 1 + height) % height][(int)igrac.second]) ci = konteiner;
    if (konteiner == 'a' && matrica[(int)igrac.first][((int)igrac.second - 1 + width) % width]) ci = konteiner;
    if (konteiner == 'd' && matrica[(int)igrac.first][((int)igrac.second + 1) % width]) ci = konteiner;

    if (ci == 's' && matrica[((int)igrac.first + 1) % height][(int)igrac.second] == 6) { scared = 1; timer = 0; }
    if (ci == 'w' && matrica[((int)igrac.first - 1 + height) % height][(int)igrac.second]==6) { scared = 1; timer = 0; }
    if (ci == 'a' && matrica[(int)igrac.first][((int)igrac.second - 1 + width) % width]==6) { scared = 1; timer = 0; }
    if (ci == 'd' && matrica[(int)igrac.first][((int)igrac.second + 1) % width]==6) { scared = 1; timer = 0; }

    if (ci == 's' && matrica[((int)igrac.first + 1) % height][(int)igrac.second]) igrac.first = (igrac.first + speedpekmen);
    if (ci == 'w' && matrica[((int)igrac.first - 1 + height) % height][(int)igrac.second]) igrac.first = (igrac.first - speedpekmen);
    if (ci == 'a' && matrica[(int)igrac.first][((int)igrac.second - 1 + width) % width]) igrac.second = (igrac.second - speedpekmen);
    if (ci == 'd' && matrica[(int)igrac.first][((int)igrac.second + 1) % width]) igrac.second = (igrac.second + speedpekmen);

    if (igrac.first >= height) igrac.first -= height;
    if (igrac.second >= width) igrac.second -= width;
    if (igrac.first < 0) igrac.first += height;
    if (igrac.second < 0) igrac.second += width;

    //matrica[(int)igrac.first][(int)igrac.second] = 2;
}

void fduh1() {

    if (!(abss(duh1.first - (int)(duh1.first + 0.5)) < 0.0001 && abss(duh1.second - (int)(duh1.second + 0.5)) < 0.0001)) {
        if (scared1 == 1) {
            if (cd1 == 'w') duh1.first -= speedduh1;
            if (cd1 == 's') duh1.first += speedduh1;
            if (cd1 == 'd') duh1.second += speedduh1;
            if (cd1 == 'a') duh1.second -= speedduh1;
        }
        else {
            if (cd1 == 'w') duh1.first -= speedduh;
            if (cd1 == 's') duh1.first += speedduh;
            if (cd1 == 'd') duh1.second += speedduh;
            if (cd1 == 'a') duh1.second -= speedduh;
        }

        if (duh1.first < 0) duh1.first += height;
        if (duh1.first >= height) duh1.first -= height;
        if (duh1.second < 0) duh1.second += width;
        if (duh1.second >= width) duh1.second -= width;
        return;
    }

    duh1.first = (int)(duh1.first + 0.001);
    duh1.second = (int)(duh1.second + 0.001);

    char cd11 = cd1;

    float distmax = 100000000;

    if (scared1 == 1) {
        int hhh=0;
        string sss = "wasd";
        int flagg = 0;
        do {
            hhh = rand() % 4;
            flagg = 0;
            if (sss[hhh] == 's')
                if (matrica[((int)duh1.first + 1) % height][(int)duh1.second] == 0) flagg = 1;
            if (sss[hhh] == 'w')
                if (matrica[((int)duh1.first - 1 + height) % height][(int)duh1.second] == 0) flagg = 1;
            if (sss[hhh] == 'd')
                if (matrica[((int)duh1.first)][((int)duh1.second + 1) % width] == 0) flagg = 1;
            if (sss[hhh] == 'a')
                if (matrica[((int)duh1.first)][((int)duh1.second - 1 + width) % width] == 0) flagg = 1;
        } while (sss[(hhh + 2) % 4] == cd11 || flagg==1);

        cd1 = sss[hhh];

        if (cd1 == 'w') duh1.first -= speedduh1;
        if (cd1 == 's') duh1.first += speedduh1;
        if (cd1 == 'd') duh1.second += speedduh1;
        if (cd1 == 'a') duh1.second -= speedduh1;

        if (duh1.first >= height) duh1.first -= height;
        if (duh1.first < 0) duh1.first += height;
        if (duh1.second >= width) duh1.second -= width;
        if (duh1.second < 0) duh1.second += width;
        return;
    }

    pair <float, float> ciljduh1 = igrac;

    if (matrica[((int)duh1.first + 1) % height][(int)duh1.second] && cd11 != 'w')
        if (distanca(duh1.first + 1, duh1.second, ciljduh1.first, ciljduh1.second) < distmax) {
            distmax = distanca(duh1.first + 1, duh1.second, ciljduh1.first, ciljduh1.second);
            cd1 = 's';
        }

    if (matrica[((int)duh1.first - 1 + height) % height][(int)duh1.second] && cd11 != 's')
        if (distanca(duh1.first - 1, duh1.second, ciljduh1.first, ciljduh1.second) < distmax) {
            distmax = distanca(duh1.first - 1, duh1.second, ciljduh1.first, ciljduh1.second);
            cd1 = 'w';
        }

    if (matrica[(int)duh1.first][((int)duh1.second + 1) % width] && cd11 != 'a')
        if (distanca(duh1.first, duh1.second + 1, ciljduh1.first, ciljduh1.second) < distmax) {
            distmax = distanca(duh1.first, duh1.second + 1, ciljduh1.first, ciljduh1.second);
            cd1 = 'd';
        }

    if (matrica[(int)duh1.first][((int)duh1.second - 1 + width) % width] && cd11 != 'd')
        if (distanca(duh1.first, duh1.second - 1, ciljduh1.first, ciljduh1.second) < distmax) {
            distmax = distanca(duh1.first, duh1.second - 1, ciljduh1.first, ciljduh1.second);
            cd1 = 'a';
        }

    if (cd1 == 'w') duh1.first -= speedduh;
    if (cd1 == 's') duh1.first += speedduh;
    if (cd1 == 'd') duh1.second += speedduh;
    if (cd1 == 'a') duh1.second -= speedduh;

    if (duh1.first >= height) duh1.first -= height;
    if (duh1.first < 0) duh1.first += height;
    if (duh1.second >= width) duh1.second -= width;
    if (duh1.second < 0) duh1.second += width;
}

void fduh2() {

    if (!(abss(duh2.first - (int)(duh2.first + 0.5)) < 0.0001 && abss(duh2.second - (int)(duh2.second + 0.5)) < 0.0001)) {
        if (scared2 == 1) {
            if (cd2 == 'w') duh2.first -= speedduh1;
            if (cd2 == 's') duh2.first += speedduh1;
            if (cd2 == 'd') duh2.second += speedduh1;
            if (cd2 == 'a') duh2.second -= speedduh1;
        }
        else {
            if (cd2 == 'w') duh2.first -= speedduh;
            if (cd2 == 's') duh2.first += speedduh;
            if (cd2 == 'd') duh2.second += speedduh;
            if (cd2 == 'a') duh2.second -= speedduh;
        }
        if (duh2.first < 0) duh2.first += height;
        if (duh2.first >= height) duh2.first -= height;
        if (duh2.second < 0) duh2.second += width;
        if (duh2.second >= width) duh2.second -= width;
        return;
    }

    duh2.first = (int)(duh2.first + 0.001);
    duh2.second = (int)(duh2.second + 0.001);

    char cd21 = cd2;

    if (scared2 == 1) {
        int hhh = 0;
        string sss = "wasd";
        int flagg = 0;
        do {
            hhh = rand() % 4;
            flagg = 0;
            if (sss[hhh] == 's')
                if (matrica[((int)duh2.first + 1) % height][(int)duh2.second] == 0) flagg = 1;
            if (sss[hhh] == 'w')
                if (matrica[((int)duh2.first - 1 + height) % height][(int)duh2.second] == 0) flagg = 1;
            if (sss[hhh] == 'd')
                if (matrica[((int)duh2.first)][((int)duh2.second + 1) % width] == 0) flagg = 1;
            if (sss[hhh] == 'a')
                if (matrica[((int)duh2.first)][((int)duh2.second - 1 + width) % width] == 0) flagg = 1;
        } while (sss[(hhh + 2) % 4] == cd21 || flagg == 1);

        cd2 = sss[hhh];

        if (cd2 == 'w') duh2.first -= speedduh1;
        if (cd2 == 's') duh2.first += speedduh1;
        if (cd2 == 'd') duh2.second += speedduh1;
        if (cd2 == 'a') duh2.second -= speedduh1;

        if (duh2.first >= height) duh2.first -= height;
        if (duh2.first < 0) duh2.first += height;
        if (duh2.second >= width) duh2.second -= width;
        if (duh2.second < 0) duh2.second += width;
        return;

    }

    ciljduh2 = igrac;

    for (int i = 0; i < 4; i++) {
        if (ci == 's') ciljduh2.first = (ciljduh2.first + 1) % height;
        if (ci == 'w') ciljduh2.first = (height + ciljduh2.first - 1) % height;
        if (ci == 'a') ciljduh2.second = (width + ciljduh2.second - 1) % width;
        if (ci == 'd') ciljduh2.second = (ciljduh2.second + 1) % width;
    }

    while (matrica[ciljduh2.first][ciljduh2.second] == 0 || matrica[ciljduh2.first][ciljduh2.second] == 3) {
        if (ci == 's') ciljduh2.first = (height + ciljduh2.first - 1) % height;
        if (ci == 'w') ciljduh2.first = (ciljduh2.first + 1) % height;
        if (ci == 'a') ciljduh2.second = (ciljduh2.second + 1) % width;
        if (ci == 'd') ciljduh2.second = (width + ciljduh2.second - 1) % width;
    }
    
    float distmax = 100000000;

    if (matrica[((int)duh2.first + 1) % height][(int)duh2.second] && cd21 != 'w')
        if (distanca(duh2.first + 1, duh2.second, ciljduh2.first, ciljduh2.second) < distmax) {
            distmax = distanca(duh2.first + 1, duh2.second, ciljduh2.first, ciljduh2.second);
            cd2 = 's';
        }

    if (matrica[((int)duh2.first - 1 + height) % height][(int)duh2.second] && cd21 != 's')
        if (distanca(duh2.first - 1, duh2.second, ciljduh2.first, ciljduh2.second) < distmax) {
            distmax = distanca(duh2.first - 1, duh2.second, ciljduh2.first, ciljduh2.second);
            cd2 = 'w';
        }

    if (matrica[(int)duh2.first][((int)duh2.second + 1) % width] && cd21 != 'a')
        if (distanca(duh2.first, duh2.second + 1, ciljduh2.first, ciljduh2.second) < distmax) {
            distmax = distanca(duh2.first, duh2.second + 1, ciljduh2.first, ciljduh2.second);
            cd2 = 'd';
        }

    if (matrica[(int)duh2.first][((int)duh2.second - 1 + width) % width] && cd21 != 'd')
        if (distanca(duh2.first, duh2.second - 1, ciljduh2.first, ciljduh2.second) < distmax) {
            distmax = distanca(duh2.first, duh2.second - 1, ciljduh2.first, ciljduh2.second);
            cd2 = 'a';
        }

    if (cd2 == 'w') duh2.first -= speedduh;
    if (cd2 == 's') duh2.first += speedduh;
    if (cd2 == 'd') duh2.second += speedduh;
    if (cd2 == 'a') duh2.second -= speedduh;

    if (duh2.first >= height) duh2.first -= height;
    if (duh2.first < 0) duh2.first += height;
    if (duh2.second >= width) duh2.second -= width;
    if (duh2.second < 0) duh2.second += width;

}

void fduh3() {

    if (!(abss(duh3.first - (int)(duh3.first+0.5)) <0.0001 && abss(duh3.second - (int)(duh3.second+0.5)) < 0.0001)) {
        if (scared3 == 1) {
            if (cd3 == 'w') duh3.first -= speedduh1;
            if (cd3 == 's') duh3.first += speedduh1;
            if (cd3 == 'd') duh3.second += speedduh1;
            if (cd3 == 'a') duh3.second -= speedduh1;
        }
        else {
            if (cd3 == 'w') duh3.first -= speedduh;
            if (cd3 == 's') duh3.first += speedduh;
            if (cd3 == 'd') duh3.second += speedduh;
            if (cd3 == 'a') duh3.second -= speedduh;
        }
        if (duh3.first < 0) duh3.first += height;
        if (duh3.first >= height) duh3.first -= height;
        if (duh3.second < 0) duh3.second += width;
        if (duh3.second >= width) duh3.second -= width;
        return;
    }

    duh3.first = (int)(duh3.first + 0.001);
    duh3.second = (int)(duh3.second + 0.001);

    char cd31 = cd3;

    if (scared3 == 1) {
        int hhh = 0;
        string sss = "wasd";
        int flagg = 0;
        do {
            hhh = rand() % 4;
            flagg = 0;
            if (sss[hhh] == 's')
                if (matrica[((int)duh3.first + 1) % height][(int)duh3.second] == 0) flagg = 1;
            if (sss[hhh] == 'w')
                if (matrica[((int)duh3.first - 1 + height) % height][(int)duh3.second] == 0) flagg = 1;
            if (sss[hhh] == 'd')
                if (matrica[((int)duh3.first)][((int)duh3.second + 1) % width] == 0) flagg = 1;
            if (sss[hhh] == 'a')
                if (matrica[((int)duh3.first)][((int)duh3.second - 1 + width) % width] == 0) flagg = 1;
        } while (sss[(hhh + 2) % 4] == cd31 || flagg == 1);

        cd3 = sss[hhh];

        if (cd3 == 'w') duh3.first -= speedduh1;
        if (cd3 == 's') duh3.first += speedduh1;
        if (cd3 == 'd') duh3.second += speedduh1;
        if (cd3 == 'a') duh3.second -= speedduh1;

        if (duh3.first >= height) duh3.first -= height;
        if (duh3.first < 0) duh3.first += height;
        if (duh3.second >= width) duh3.second -= width;
        if (duh3.second < 0) duh3.second += width;
        return;

    }

    pair <float, float> ciljduh3;
    ciljduh3.first = -1 * (duh1.first - 2*ciljduh2.first);
    ciljduh3.second = -1 * (duh1.second - 2*ciljduh2.second);
    float distmax = 1000000000;
    
    if (matrica[((int)duh3.first + 1) % height][(int)duh3.second] && cd31!='w')
        if (distanca(duh3.first + 1, duh3.second, ciljduh3.first, ciljduh3.second) < distmax) {
            distmax = distanca(duh3.first + 1, duh3.second, ciljduh3.first, ciljduh3.second);
            cd3 = 's';
        }
    
    if (matrica[((int)duh3.first - 1 + height) % height][(int)duh3.second] && cd31 != 's')
        if (distanca(duh3.first - 1, duh3.second, ciljduh3.first, ciljduh3.second) < distmax) {
            distmax = distanca(duh3.first - 1, duh3.second, ciljduh3.first, ciljduh3.second);
            cd3 = 'w';
        }
    
    if (matrica[(int)duh3.first][((int)duh3.second+1) % width] && cd31 != 'a')
        if (distanca(duh3.first, duh3.second + 1, ciljduh3.first, ciljduh3.second) < distmax) {
            distmax = distanca(duh3.first, duh3.second + 1, ciljduh3.first, ciljduh3.second);
            cd3 = 'd';
        }
    
    if (matrica[(int)duh3.first][((int)duh3.second - 1 + width) % width] && cd31 != 'd')
        if (distanca(duh3.first, duh3.second - 1, ciljduh3.first, ciljduh3.second) < distmax) {
            distmax = distanca(duh3.first, duh3.second - 1, ciljduh3.first, ciljduh3.second);
            cd3 = 'a';
        }
    
    if (cd3 == 'w') duh3.first -= speedduh;
    if (cd3 == 's') duh3.first += speedduh;
    if (cd3 == 'd') duh3.second += speedduh;
    if (cd3 == 'a') duh3.second -= speedduh;

    if (duh3.first < 0) duh3.first += height;
    if (duh3.first >= height) duh3.first -= height;
    if (duh3.second < 0) duh3.second += width;
    if (duh3.second >= width) duh3.second -= width;
}

void fduh4() {
    
    if (!(abss(duh4.first - (int)(duh4.first + 0.5)) < 0.0001 && abss(duh4.second - (int)(duh4.second + 0.5)) < 0.0001)) {
        if (scared4 == 1) {
            if (cd4 == 'w') duh4.first -= speedduh1;
            if (cd4 == 's') duh4.first += speedduh1;
            if (cd4 == 'd') duh4.second += speedduh1;
            if (cd4 == 'a') duh4.second -= speedduh1;
        }
        else {
            if (cd4 == 'w') duh4.first -= speedduh;
            if (cd4 == 's') duh4.first += speedduh;
            if (cd4 == 'd') duh4.second += speedduh;
            if (cd4 == 'a') duh4.second -= speedduh;
        }
        if (duh4.first < 0) duh4.first += height;
        if (duh4.first >= height) duh4.first -= height;
        if (duh4.second < 0) duh4.second += width;
        if (duh4.second >= width) duh4.second -= width;
        return;
    }

    duh4.first = (int)(duh4.first + 0.001);
    duh4.second = (int)(duh4.second + 0.001);
    
    char cd41 = cd4;

    if (scared4 == 1) {
        int hhh = 0;
        string sss = "wasd";
        int flagg = 0;
        do {
            hhh = rand() % 4;
            flagg = 0;
            if (sss[hhh] == 's')
                if (matrica[((int)duh4.first + 1) % height][(int)duh4.second] == 0) flagg = 1;
            if (sss[hhh] == 'w')
                if (matrica[((int)duh4.first - 1 + height) % height][(int)duh4.second] == 0) flagg = 1;
            if (sss[hhh] == 'd')
                if (matrica[((int)duh4.first)][((int)duh4.second + 1) % width] == 0) flagg = 1;
            if (sss[hhh] == 'a')
                if (matrica[((int)duh4.first)][((int)duh4.second - 1 + width) % width] == 0) flagg = 1;
        } while (sss[(hhh + 2) % 4] == cd41 || flagg == 1);

        cd4 = sss[hhh];

        if (cd4 == 'w') duh4.first -= speedduh1;
        if (cd4 == 's') duh4.first += speedduh1;
        if (cd4 == 'd') duh4.second += speedduh1;
        if (cd4 == 'a') duh4.second -= speedduh1;

        if (duh4.first >= height) duh4.first -= height;
        if (duh4.first < 0) duh4.first += height;
        if (duh4.second >= width) duh4.second -= width;
        if (duh4.second < 0) duh4.second += width;
        return;

    }

    do {
        randy = rand() % width;
        randx = rand() % height;
    } while (matrica[randx][randy] == 0);

    float distmax = 1000000000;
    
    pair <float, float> ciljduh4 = make_pair((float)randx, (float)randy);

    if (matrica[((int)duh4.first + 1) % height][(int)duh4.second] && cd41 != 'w')
        if (distanca(duh4.first + 1, duh4.second, ciljduh4.first, ciljduh4.second) < distmax) {
            distmax = distanca(duh4.first + 1, duh4.second, ciljduh4.first, ciljduh4.second);
            cd4 = 's';
        }

    if (matrica[((int)duh4.first - 1 + height) % height][(int)duh4.second] && cd41 != 's')
        if (distanca(duh4.first - 1, duh4.second, ciljduh4.first, ciljduh4.second) < distmax) {
            distmax = distanca(duh4.first - 1, duh4.second, ciljduh4.first, ciljduh4.second);
            cd4 = 'w';
        }

    if (matrica[(int)duh4.first][((int)duh4.second + 1) % width] && cd41 != 'a')
        if (distanca(duh4.first, duh4.second + 1, ciljduh4.first, ciljduh4.second) < distmax) {
            distmax = distanca(duh4.first, duh4.second + 1, ciljduh4.first, ciljduh4.second);
            cd4 = 'd';
        }

    if (matrica[(int)duh4.first][((int)duh4.second - 1 + width) % width] && cd41 != 'd')
        if (distanca(duh4.first, duh4.second - 1, ciljduh4.first, ciljduh4.second) < distmax) {
            distmax = distanca(duh4.first, duh4.second - 1, ciljduh4.first, ciljduh4.second);
            cd4 = 'a';
        }

    if (cd4 == 'w') duh4.first -= speedduh;
    if (cd4 == 's') duh4.first += speedduh;
    if (cd4 == 'd') duh4.second += speedduh;
    if (cd4 == 'a') duh4.second -= speedduh;

    if (duh4.first < 0) duh4.first += height;
    if (duh4.first >= height) duh4.first -= height;
    if (duh4.second < 0) duh4.second += width;
    if (duh4.second >= width) duh4.second -= width;

}

int drawgrid(int x, int y) {
    
    //if (y - 1 < 0 || y + 1 >= height || x - 1 < 0 || x + 1 >= width) return 7;
    
    int U, D, L, R, UL, UR, DL, DR;
    U = (y-1<0 || matrica[y - 1][x] == 0);
    UL = (y-1<0 || x - 1 < 0 || matrica[y - 1][x-1] == 0);
    UR = (y-1<0 || x+1>=width || matrica[y - 1][x+1] == 0);
    L = (x - 1 < 0 || matrica[y][x-1] == 0);
    R = (x + 1 >= width || matrica[y][x+1] == 0);
    D = (y+1 >= height || matrica[y + 1][x] == 0);
    DL = (y + 1 >= height || x - 1 < 0 || matrica[y + 1][x-1] == 0);
    DR = (y + 1 >= height || x + 1 >= width || matrica[y + 1][x+1] == 0);

    if (U+UL+UR+L+R+D+DL+DR==8) {
        return 7;
    }
    if ((L+R==2) && !(U+D==2)) {
        return 1;
    }
    if ((U+D==2) && !(L+R==2)) {
        return 2;
    }
    if ((U + DL + UR + L + R + D + DR == 7) ) {
        return 3;
    }
    if ((U + UL + DL + L + R + D + DR == 7) ) {
        return 4;
    }
    if ((U + UL + UR + L + R + D + DR == 7) ) {
        return 5;
    }
    if ((U + UL + UR + L + R + D + DL == 7)) {
        return 6;
    }

    if (U + L==2) {
        return 3;
    }
    if (D + L==2) {
        return 5;
    }
    if (U + R==2) {
        return 4;
    }
    if (D + R==2) {
        return 6;
    }

    return 7;
}

void putpixel(unsigned int* pixel, int x, int y, int red, int green, int blue)
{
	unsigned int* target = pixel + x + y * buffer_width;
	if (x >= 0 && x < windowwidth && y >= 0 && y < windowheigth)
		*target = (red << 16) + (green << 8) + (blue);
}

void drawcircle(unsigned int* pixel, int x, int y, int r, int red, int green, int blue)
{
	int j = r;
	for (int i = 0; i < r;)
	{
		if ((i + 1) * (i + 1) + j * j <= r * r)
			i++;
		else
			j--;


		if (1)
			putpixel(pixel, x + i, y + j, red, green, blue);
		if (1)
			putpixel(pixel, x + i, y - j, red, green, blue);
		if (1)
			putpixel(pixel, x - i, y + j, red, green, blue);
		if (1)
			putpixel(pixel, x - i, y - j, red, green, blue);
	}
	putpixel(pixel, x, y + r, red, green, blue);
	putpixel(pixel, x, y - r, red, green, blue);
}

LRESULT CALLBACK window_callback(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		running = false;
	} break;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		buffer_width = rect.right - rect.left;
		buffer_heigth = rect.bottom - rect.top;

        //buffer_heigth = height * 20;
        //buffer_width = 20 * width;

		int buffer_size = buffer_width * buffer_heigth * sizeof(unsigned int);

		if (buffer_memory)VirtualFree(buffer_memory, 0, MEM_RELEASE);
		buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
		buffer_bitmap_info.bmiHeader.biWidth = buffer_width;
		buffer_bitmap_info.bmiHeader.biHeight = buffer_heigth;
		buffer_bitmap_info.bmiHeader.biPlanes = 1;
		buffer_bitmap_info.bmiHeader.biBitCount = 32;
		buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

	} break;
	default:
	{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

    igrac = make_pair(17, 14);
    duh1 = make_pair(14, 12);
    duh2 = make_pair(14, 13);
    duh3 = make_pair(14, 14);
    duh4 = make_pair(14, 15);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            if (table[j][i] == '*') matrica[j][i] = 0;
            else matrica[j][i] = 1;
            if (((j < 10 || j>22) || (i < 7 || i>20)) && matrica[j][i] == 1) matrica[j][i] = 4;
            if (table[j][i] == 'F') matrica[j][i] = 6;
        }

    srand(time(0));

    int tajmerigre = 0;

	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	RegisterClass(&window_class);

	HWND window = CreateWindow(window_class.lpszClassName, "THE GAME", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, windowwidth+17 ,  windowheigth+50, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

    int animacijapekmen = 0;
    int animacijaduh = 0;

    int proba=0;
    int kreni = 0;
    while (running)
    {
        auto start = std::chrono::high_resolution_clock::now();

        unsigned int* pixel = (unsigned int*)buffer_memory;
        unsigned int* pixel1;
        pixel1 = pixel;

        MSG message;
        for (int i = 0; i < 200; i++)
        {
            ischanged[i] = 0;
        }
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {

            switch (message.message)
            {
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                int key = message.wParam;
                bool is_down = ((message.lParam & (1 << 31)) == 0);
                ispressed[key] = is_down;
                ischanged[key] = true;
            } break;
            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            }
        };
        if (ischanged[VK_TAB] && ispressed[VK_TAB]) { 
            kreni = 1;
            scared = 0;
            scared1 = 0;
            scared2 = 0;
            scared3 = 0;
            scared4 = 0;

            tajmer1 = 0;
            tajmer2 = 0;
            tajmer3 = 0;
            tajmer4 = 0;
            igrac = make_pair(17, 14);
            duh1 = make_pair(14, 12);
            duh2 = make_pair(14, 13);
            duh3 = make_pair(14, 14);
            duh4 = make_pair(14, 15);
            for (int i = 0; i < width; i++)
                for (int j = 0; j < height; j++) {
                    if (table[j][i] == '*') matrica[j][i] = 0;
                    else matrica[j][i] = 1;
                    if (((j < 10 || j>22) || (i < 7 || i>20)) && matrica[j][i] == 1) matrica[j][i] = 4;
                    if (table[j][i] == 'F') matrica[j][i] = 6;
                }
            tajmerigre = 0;
        }

        StretchDIBits(hdc, 0, 0, buffer_width, buffer_heigth, 0, 0, buffer_width, buffer_heigth, buffer_memory,
            &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);

        if (kreni == 0) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    for (int y = 0; y < 20; y++)
                        for (int x = 0; x < 20; x++)
                        {
                            if (matrica[j][i] == 0) //grid
                            {
                                int hj = drawgrid(i, j);
                                if (hj == 1) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board1, 0) + (f(x, y, &board1, 1) << 8) + (f(x, y, &board1, 2) << 16);
                                if (hj == 2) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board2, 0) + (f(x, y, &board2, 1) << 8) + (f(x, y, &board2, 2) << 16);
                                if (hj == 3) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board3, 0) + (f(x, y, &board3, 1) << 8) + (f(x, y, &board3, 2) << 16);
                                if (hj == 4) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board4, 0) + (f(x, y, &board4, 1) << 8) + (f(x, y, &board4, 2) << 16);
                                if (hj == 5) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board5, 0) + (f(x, y, &board5, 1) << 8) + (f(x, y, &board5, 2) << 16);
                                if (hj == 6) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board6, 0) + (f(x, y, &board6, 1) << 8) + (f(x, y, &board6, 2) << 16);
                                if (hj == 7) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board7, 0) + (f(x, y, &board7, 1) << 8) + (f(x, y, &board7, 2) << 16);
                            }

                            if (matrica[j][i] == 1) //space
                            {
                                *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board7, 0) + (f(x, y, &board7, 1) << 8) + (f(x, y, &board7, 2) << 16);
                            }
                            if (matrica[j][i] == 4) //food
                            {
                                *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &food, 0) + (f(x, y, &food, 1) << 8) + (f(x, y, &food, 2) << 16);
                            }
                            if (matrica[j][i] == 6) //food1
                            {
                                *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &food1, 0) + (f(x, y, &food1, 1) << 8) + (f(x, y, &food1, 2) << 16);
                            }

                        }
                }
            }
            continue;
        }

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int y = 0; y < 20; y++)
                    for (int x = 0; x < 20; x++)
                    {
                        if (matrica[j][i] == 0) //grid
                        {
                            int hj = drawgrid(i, j);
                            if (hj == 1) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board1, 0) + (f(x, y, &board1, 1) << 8) + (f(x, y, &board1, 2) << 16);
                            if (hj == 2) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board2, 0) + (f(x, y, &board2, 1) << 8) + (f(x, y, &board2, 2) << 16);
                            if (hj == 3) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board3, 0) + (f(x, y, &board3, 1) << 8) + (f(x, y, &board3, 2) << 16);
                            if (hj == 4) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board4, 0) + (f(x, y, &board4, 1) << 8) + (f(x, y, &board4, 2) << 16);
                            if (hj == 5) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board5, 0) + (f(x, y, &board5, 1) << 8) + (f(x, y, &board5, 2) << 16);
                            if (hj == 6) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board6, 0) + (f(x, y, &board6, 1) << 8) + (f(x, y, &board6, 2) << 16);
                            if (hj == 7) *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board7, 0) + (f(x, y, &board7, 1) << 8) + (f(x, y, &board7, 2) << 16);
                        }

                        if (matrica[j][i] == 1) //space
                        {
                            *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &board7, 0) + (f(x, y, &board7, 1) << 8) + (f(x, y, &board7, 2) << 16);
                        }
                        if (matrica[j][i] == 4) //food
                        {
                            *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &food, 0) + (f(x, y, &food, 1) << 8) + (f(x, y, &food, 2) << 16);
                        }
                        if (matrica[j][i] == 6) //food1
                        {
                            *(pixel + x + i * 20 + (y + buffer_heigth - 20 - j * 20) * buffer_width) = f(x, y, &food1, 0) + (f(x, y, &food1, 1) << 8) + (f(x, y, &food1, 2) << 16);
                        }

                    }
            }
        }

        for (int y = 0; y < 20; y++)
            for (int x = 0; x < 20; x++)
            {
                if (scared1 == 0) {
                    if (animacijaduh == 0 && f(x, y, &dduh10, 0) + (f(x, y, &dduh10, 1) << 8) + (f(x, y, &dduh10, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh10, 0) + (f(x, y, &dduh10, 1) << 8) + (f(x, y, &dduh10, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh12, 0) + (f(x, y, &dduh12, 1) << 8) + (f(x, y, &dduh12, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh12, 0) + (f(x, y, &dduh12, 1) << 8) + (f(x, y, &dduh12, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh14, 0) + (f(x, y, &dduh14, 1) << 8) + (f(x, y, &dduh14, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh14, 0) + (f(x, y, &dduh14, 1) << 8) + (f(x, y, &dduh14, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh16, 0) + (f(x, y, &dduh16, 1) << 8) + (f(x, y, &dduh16, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh16, 0) + (f(x, y, &dduh16, 1) << 8) + (f(x, y, &dduh16, 2) << 16);
                }
                if (scared2 == 0) {
                    if (animacijaduh == 1 && f(x, y, &dduh20, 0) + (f(x, y, &dduh20, 1) << 8) + (f(x, y, &dduh20, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh20, 0) + (f(x, y, &dduh20, 1) << 8) + (f(x, y, &dduh20, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh22, 0) + (f(x, y, &dduh22, 1) << 8) + (f(x, y, &dduh22, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh22, 0) + (f(x, y, &dduh22, 1) << 8) + (f(x, y, &dduh22, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh24, 0) + (f(x, y, &dduh24, 1) << 8) + (f(x, y, &dduh24, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh24, 0) + (f(x, y, &dduh24, 1) << 8) + (f(x, y, &dduh24, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh26, 0) + (f(x, y, &dduh26, 1) << 8) + (f(x, y, &dduh26, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh26, 0) + (f(x, y, &dduh26, 1) << 8) + (f(x, y, &dduh26, 2) << 16);
                }
                if (scared3 == 0) {
                    if (animacijaduh == 2 && f(x, y, &dduh30, 0) + (f(x, y, &dduh30, 1) << 8) + (f(x, y, &dduh30, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh30, 0) + (f(x, y, &dduh30, 1) << 8) + (f(x, y, &dduh30, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh32, 0) + (f(x, y, &dduh32, 1) << 8) + (f(x, y, &dduh32, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh32, 0) + (f(x, y, &dduh32, 1) << 8) + (f(x, y, &dduh32, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh34, 0) + (f(x, y, &dduh34, 1) << 8) + (f(x, y, &dduh34, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh34, 0) + (f(x, y, &dduh34, 1) << 8) + (f(x, y, &dduh34, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh36, 0) + (f(x, y, &dduh36, 1) << 8) + (f(x, y, &dduh36, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh36, 0) + (f(x, y, &dduh36, 1) << 8) + (f(x, y, &dduh36, 2) << 16);
                }
                if (scared4 == 0) {
                    if (animacijaduh == 3 && f(x, y, &dduh40, 0) + (f(x, y, &dduh40, 1) << 8) + (f(x, y, &dduh40, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh40, 0) + (f(x, y, &dduh40, 1) << 8) + (f(x, y, &dduh40, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh42, 0) + (f(x, y, &dduh42, 1) << 8) + (f(x, y, &dduh42, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh42, 0) + (f(x, y, &dduh42, 1) << 8) + (f(x, y, &dduh42, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh44, 0) + (f(x, y, &dduh44, 1) << 8) + (f(x, y, &dduh44, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh44, 0) + (f(x, y, &dduh44, 1) << 8) + (f(x, y, &dduh44, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh46, 0) + (f(x, y, &dduh46, 1) << 8) + (f(x, y, &dduh46, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh46, 0) + (f(x, y, &dduh46, 1) << 8) + (f(x, y, &dduh46, 2) << 16);
                }
                if (scared1 == 1) {
                    if (animacijaduh == 0 && f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16)) *(pixel + x + (int)(duh1.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh1.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16);
                }
                if (scared2 == 1) {
                    if (animacijaduh == 1 && f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16)) *(pixel + x + (int)(duh2.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh2.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16);
                }
                if (scared3 == 1) {
                    if (animacijaduh == 2 && f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16);
                    if (animacijaduh == 3 && f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16)) *(pixel + x + (int)(duh3.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh3.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16);
                }
                if (scared4 == 1) {
                    if (animacijaduh == 3 && f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh50, 0) + (f(x, y, &dduh50, 1) << 8) + (f(x, y, &dduh50, 2) << 16);
                    if (animacijaduh == 0 && f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh52, 0) + (f(x, y, &dduh52, 1) << 8) + (f(x, y, &dduh52, 2) << 16);
                    if (animacijaduh == 1 && f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh54, 0) + (f(x, y, &dduh54, 1) << 8) + (f(x, y, &dduh54, 2) << 16);
                    if (animacijaduh == 2 && f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16)) *(pixel + x + (int)(duh4.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(duh4.first * 20 + 0.5)) * buffer_width) = f(x, y, &dduh56, 0) + (f(x, y, &dduh56, 1) << 8) + (f(x, y, &dduh56, 2) << 16);
                }
                if (ci == 'd') {
                    if (f(x, y, &pekmen1d, 0) + (f(x, y, &pekmen1d, 1) << 8) + (f(x, y, &pekmen1d, 2) << 16) && animacijapekmen == 0) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen1d, 0) + (f(x, y, &pekmen1d, 1) << 8) + (f(x, y, &pekmen1d, 2) << 16);
                    if (f(x, y, &pekmen2d, 0) + (f(x, y, &pekmen2d, 1) << 8) + (f(x, y, &pekmen2d, 2) << 16) && (animacijapekmen == 1 || animacijapekmen == 9)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen2d, 0) + (f(x, y, &pekmen2d, 1) << 8) + (f(x, y, &pekmen2d, 2) << 16);
                    if (f(x, y, &pekmen3d, 0) + (f(x, y, &pekmen3d, 1) << 8) + (f(x, y, &pekmen3d, 2) << 16) && (animacijapekmen == 2 || animacijapekmen == 8)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen3d, 0) + (f(x, y, &pekmen3d, 1) << 8) + (f(x, y, &pekmen3d, 2) << 16);
                    if (f(x, y, &pekmen4d, 0) + (f(x, y, &pekmen4d, 1) << 8) + (f(x, y, &pekmen4d, 2) << 16) && (animacijapekmen == 3 || animacijapekmen == 7)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen4d, 0) + (f(x, y, &pekmen4d, 1) << 8) + (f(x, y, &pekmen4d, 2) << 16);
                    if (f(x, y, &pekmen5d, 0) + (f(x, y, &pekmen5d, 1) << 8) + (f(x, y, &pekmen5d, 2) << 16) && (animacijapekmen == 4 || animacijapekmen == 6)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen5d, 0) + (f(x, y, &pekmen5d, 1) << 8) + (f(x, y, &pekmen5d, 2) << 16);
                    if (f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16) && animacijapekmen == 5) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16);
                }
                if (ci == 'a') {
                    if (f(x, y, &pekmen1a, 0) + (f(x, y, &pekmen1a, 1) << 8) + (f(x, y, &pekmen1a, 2) << 16) && animacijapekmen == 0) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen1a, 0) + (f(x, y, &pekmen1a, 1) << 8) + (f(x, y, &pekmen1a, 2) << 16);
                    if (f(x, y, &pekmen2a, 0) + (f(x, y, &pekmen2a, 1) << 8) + (f(x, y, &pekmen2a, 2) << 16) && (animacijapekmen == 1 || animacijapekmen == 9)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen2a, 0) + (f(x, y, &pekmen2a, 1) << 8) + (f(x, y, &pekmen2a, 2) << 16);
                    if (f(x, y, &pekmen3a, 0) + (f(x, y, &pekmen3a, 1) << 8) + (f(x, y, &pekmen3a, 2) << 16) && (animacijapekmen == 2 || animacijapekmen == 8)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen3a, 0) + (f(x, y, &pekmen3a, 1) << 8) + (f(x, y, &pekmen3a, 2) << 16);
                    if (f(x, y, &pekmen4a, 0) + (f(x, y, &pekmen4a, 1) << 8) + (f(x, y, &pekmen4a, 2) << 16) && (animacijapekmen == 3 || animacijapekmen == 7)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen4a, 0) + (f(x, y, &pekmen4a, 1) << 8) + (f(x, y, &pekmen4a, 2) << 16);
                    if (f(x, y, &pekmen5a, 0) + (f(x, y, &pekmen5a, 1) << 8) + (f(x, y, &pekmen5a, 2) << 16) && (animacijapekmen == 4 || animacijapekmen == 6)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen5a, 0) + (f(x, y, &pekmen5a, 1) << 8) + (f(x, y, &pekmen5a, 2) << 16);
                    if (f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16) && animacijapekmen == 5) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16);
                }
                if (ci == 'w') {
                    if (f(x, y, &pekmen1w, 0) + (f(x, y, &pekmen1w, 1) << 8) + (f(x, y, &pekmen1w, 2) << 16) && animacijapekmen == 0) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen1w, 0) + (f(x, y, &pekmen1w, 1) << 8) + (f(x, y, &pekmen1w, 2) << 16);
                    if (f(x, y, &pekmen2w, 0) + (f(x, y, &pekmen2w, 1) << 8) + (f(x, y, &pekmen2w, 2) << 16) && (animacijapekmen == 1 || animacijapekmen == 9)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen2w, 0) + (f(x, y, &pekmen2w, 1) << 8) + (f(x, y, &pekmen2w, 2) << 16);
                    if (f(x, y, &pekmen3w, 0) + (f(x, y, &pekmen3w, 1) << 8) + (f(x, y, &pekmen3w, 2) << 16) && (animacijapekmen == 2 || animacijapekmen == 8)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen3w, 0) + (f(x, y, &pekmen3w, 1) << 8) + (f(x, y, &pekmen3w, 2) << 16);
                    if (f(x, y, &pekmen4w, 0) + (f(x, y, &pekmen4w, 1) << 8) + (f(x, y, &pekmen4w, 2) << 16) && (animacijapekmen == 3 || animacijapekmen == 7)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen4w, 0) + (f(x, y, &pekmen4w, 1) << 8) + (f(x, y, &pekmen4w, 2) << 16);
                    if (f(x, y, &pekmen5w, 0) + (f(x, y, &pekmen5w, 1) << 8) + (f(x, y, &pekmen5w, 2) << 16) && (animacijapekmen == 4 || animacijapekmen == 6)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen5w, 0) + (f(x, y, &pekmen5w, 1) << 8) + (f(x, y, &pekmen5w, 2) << 16);
                    if (f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16) && animacijapekmen == 5) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16);
                }
                if (ci == 's') {
                    if (f(x, y, &pekmen1s, 0) + (f(x, y, &pekmen1s, 1) << 8) + (f(x, y, &pekmen1s, 2) << 16) && animacijapekmen == 0) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen1s, 0) + (f(x, y, &pekmen1s, 1) << 8) + (f(x, y, &pekmen1s, 2) << 16);
                    if (f(x, y, &pekmen2s, 0) + (f(x, y, &pekmen2s, 1) << 8) + (f(x, y, &pekmen2s, 2) << 16) && (animacijapekmen == 1 || animacijapekmen == 9)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen2s, 0) + (f(x, y, &pekmen2s, 1) << 8) + (f(x, y, &pekmen2s, 2) << 16);
                    if (f(x, y, &pekmen3s, 0) + (f(x, y, &pekmen3s, 1) << 8) + (f(x, y, &pekmen3s, 2) << 16) && (animacijapekmen == 2 || animacijapekmen == 8)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen3s, 0) + (f(x, y, &pekmen3s, 1) << 8) + (f(x, y, &pekmen3s, 2) << 16);
                    if (f(x, y, &pekmen4s, 0) + (f(x, y, &pekmen4s, 1) << 8) + (f(x, y, &pekmen4s, 2) << 16) && (animacijapekmen == 3 || animacijapekmen == 7)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen4s, 0) + (f(x, y, &pekmen4s, 1) << 8) + (f(x, y, &pekmen4s, 2) << 16);
                    if (f(x, y, &pekmen5s, 0) + (f(x, y, &pekmen5s, 1) << 8) + (f(x, y, &pekmen5s, 2) << 16) && (animacijapekmen == 4 || animacijapekmen == 6)) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen5s, 0) + (f(x, y, &pekmen5s, 1) << 8) + (f(x, y, &pekmen5s, 2) << 16);
                    if (f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16) && animacijapekmen == 5) *(pixel + x + (int)(igrac.second * 20 + 0.5) + (y + buffer_heigth - 20 - (int)(igrac.first * 20 + 0.5)) * buffer_width) = f(x, y, &pekmen6, 0) + (f(x, y, &pekmen6, 1) << 8) + (f(x, y, &pekmen6, 2) << 16);
                }
            }


        figrac();
        if(((int)(igrac.first + 0.5) == (int)(duh1.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh1.second + 0.5) && scared1 == 0) || ((int)(igrac.first + 0.5) == (int)(duh2.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh2.second + 0.5) && scared2 == 0) || ((int)(igrac.first + 0.5) == (int)(duh3.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh3.second + 0.5) && scared3 == 0) || ((int)(igrac.first + 0.5) == (int)(duh4.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh4.second + 0.5) && scared4 == 0)) kreni = 0;
        if ((int)(igrac.first + 0.5) == (int)(duh1.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh1.second + 0.5) && scared1 == 1) { duh1 = make_pair(14, 12); scared1 = 0; tajmer1 = 400; }
        if ((int)(igrac.first + 0.5) == (int)(duh2.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh2.second + 0.5) && scared2 == 1) { duh2 = make_pair(14, 13); scared2 = 0; tajmer2 = 400; }
        if ((int)(igrac.first + 0.5) == (int)(duh3.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh3.second + 0.5) && scared3 == 1) { duh3 = make_pair(14, 14); scared3 = 0; tajmer3 = 400; }
        if ((int)(igrac.first + 0.5) == (int)(duh4.first + 0.5) && (int)(igrac.second + 0.5) == (int)(duh4.second + 0.5) && scared4 == 1) { duh4 = make_pair(14, 15); scared4 = 0; tajmer4 = 400; }

        if (tajmerigre == 10 || tajmer1 == 1) duh1 = make_pair(11, 14);
        if(tajmerigre>10 && tajmer1==0)fduh1();

        if (tajmerigre == 200 || tajmer2 == 1) duh2 = make_pair(11, 14);
        if(tajmerigre>200 && tajmer2==0)fduh2();

        if (tajmerigre == 500 || tajmer3 == 1) duh3 = make_pair(11, 14);
        if(tajmerigre>500 && tajmer3==0)fduh3();

        if (tajmerigre == 1000 || tajmer4 == 1) duh4 = make_pair(11, 14);
        if(tajmerigre>1000 && tajmer4==0)fduh4();
        
        
        if (tajmer1 > 0)tajmer1--;
        if (tajmer2 > 0)tajmer2--;
        if (tajmer3 > 0)tajmer3--;
        if (tajmer4 > 0)tajmer4--;
        
        if (((int)(igrac.first+0.5) == (int)(duh1.first+0.5) && (int)(igrac.second+0.5) == (int)(duh1.second+0.5) && scared1==0) || ((int)(igrac.first+0.5) == (int)(duh2.first+0.5) && (int)(igrac.second+0.5) == (int)(duh2.second+0.5) && scared2 == 0) || ((int)(igrac.first+0.5) == (int)(duh3.first+0.5) && (int)(igrac.second+0.5) == (int)(duh3.second+0.5) && scared3 == 0) || ((int)(igrac.first+0.5) == (int)(duh4.first+0.5) && (int)(igrac.second+0.5) == (int)(duh4.second+0.5) && scared4 == 0)) kreni=0;
        //if (((int)igrac.first == (int)duh1.first && (int)igrac.second == (int)duh1.second && scared1==0) || ((int)igrac.first == (int)duh2.first && (int)igrac.second == (int)duh2.second && scared2 == 0) || ((int)igrac.first == (int)duh3.first && (int)igrac.second == (int)duh3.second && scared3 == 0) || ((int)igrac.first == (int)duh4.first && (int)igrac.second == (int)duh4.second && scared4 == 0)) kreni=0;
        
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        if (microseconds < 10000)
            std::this_thread::sleep_for(std::chrono::milliseconds(10 - microseconds / 1000));

        proba = (proba + 1) % 2;
        if (proba == 0) {
            
            animacijapekmen = (animacijapekmen + 1) % 10;
            animacijaduh = (animacijaduh + 1) % 4;
        }

        if (scared == 1) {
            if (timer == 0) {
                if(tajmerigre>=10 && tajmer1==0) scared1 = 1;
                if(tajmerigre>=200 && tajmer2==0)scared2 = 1;
                if(tajmerigre>=500 && tajmer3==0)scared3 = 1;
                if(tajmerigre>=1000 && tajmer4==0)scared4 = 1;
            }
            timer++;
            if (timer == 500) {
                scared = 0;
                if (scared1 == 1) { duh1.first = (int)duh1.first; duh1.second = (int)duh1.second; }
                scared1 = 0;
                if (scared2 == 1) { duh2.first = (int)duh2.first; duh2.second = (int)duh2.second; }
                scared2 = 0;
                if (scared3 == 1) { duh3.first = (int)duh3.first; duh3.second = (int)duh3.second; }
                scared3 = 0;
                if (scared4 == 1) { duh4.first = (int)duh4.first; duh4.second = (int)duh4.second; }
                scared4 = 0;
                timer = 0;
            }
        }
        tajmerigre++;
        int kkkk = 0;
        for (int i = 0; i < width && kkkk==0; i++) {
            for (int j = 0; j < height; j++) {
                if (matrica[j][i] == 4) kkkk = 1;
            }
        }
        if (kkkk == 0) kreni = 0;

	};
};