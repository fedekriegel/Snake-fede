#ifndef GRAFIC_H
#define GRAFIC_H 448

#include <bits/stdc++.h>
#include <ncurses.h>

using namespace std;

#define BLACK 255
#define BLUE 1
#define GREEN 2
#define RED 4


void sqr(pair<int,int> pos,int n);

void clean(WINDOW * st, int h,int w);

pair<int,int> init();

void end();

#endif