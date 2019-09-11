#ifndef SNAKE_H
#define SNAKE_H 447
#endif


#include <bits/stdc++.h>
#include <ncurses.h>
#include "grafic.h"
using namespace std;

class Snake{
private:
    string name;                    // nombre del jugador
    int score;                      // puntaje actual
    int col;                         // color de la serpiente
    pair<int,int> pos;              // pocision actual de la cavea
    pair<int,int> dir;              // direccion a laque se mueve 
  
    queue<pair< int,int> > order;   // orden en el que se eliminan las piesas;
    set< pair<int,int> > cels;      // pocisiones donde hay una celda
    vector<int> mov;                // movimientos U,D,L,R 

public:
    Snake(string name = "Lucario",
        int col = BLUE,
        vector<int> mov = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT},
        pair<int,int> pos = {-1,-1}
        ) 
        : name(name), mov(mov), pos(pos), dir({0,2}), score(0), col(col) 
    {
        if(this->pos == (pair<int,int>){-1,-1}){
            int h,w;
            getmaxyx(stdscr, h, w);
            this->pos = {h/2,w/2};
            this->pos.second -= (this->pos.second & 1);         
            order.push(this->pos);
            cels.insert(this->pos);
        }else{
            this->pos.second -= (this->pos.second & 1);         
            order.push(this->pos);
            cels.insert(this->pos);            
        }
    }
    void dump();
    void parceMov(int ch);
    int actPos(pair<int,int> a);
    bool hit(Snake *s);
    pair<int,int> getPos();
    bool isValid(int h, int w);
    bool hit(pair<int,int> p);
    int getScore(){
        return score;
    }    
    string getName(){
        return name;
    }
    

};
