#include "snake.h"

pair<int,int> operator+(pair<int,int> a, pair<int,int> b){
    return {a.first+b.first,a.second+b.second};
}
void Snake::dump(){
    cout<<"Nmombre del jugador = "<< name<<endl;
    cout<<"Score del jugador = "<< score<<endl;
    cout<<"Pocicion actual (y,x) del jugador = "<< pos.first <<" "<<pos.second <<endl;
    cout<<"Direccion actual (y,x) del jugador = "<< dir.first <<" "<<dir.second <<endl; 
    cout<<"Los movimientos establecidos son = "<<endl<<"\t";
    for(auto x : mov){
        cout<<x<<" ";
    }
    cout<<endl;
}

void Snake::parceMov(int ch){
    if(ch == mov[0]){
        if(dir.first != 1)
            dir.first=-1,
            dir.second=0;

    }else if(ch == mov[1]){
        if(dir.first != -1)
            dir.first=1,
            dir.second=0;
    }else if(ch == mov[2]){
        if(dir.second != 2)
            dir.second=-2,
            dir.first=0;
    }else if(ch == mov[3]){
        if(dir.second != -2)
            dir.second=2,
            dir.first=-0;
    }
}

int Snake::actPos(pair<int,int> a){
    pos = pos+dir;
    if(cels.find(pos) != cels.end()){ // si me choco con migomismo err 
        return 0;
    }
    sqr(pos,col);
    order.push(pos);
    cels.insert(pos);
    if(pos != a){  // si la siguiente pocicion no es una manzana
        sqr(order.front(),BLACK);
        cels.erase(order.front());
        order.pop();
        return 2;
    }
    // caso contrario me comi una mansana   
    score++;
    return 1;
}

pair<int,int> Snake::getPos(){
    return pos;
}

bool Snake::hit(Snake *s){
    return (cels.find(s->getPos()) == cels.end());
}


bool Snake::isValid(int h, int w){
    pair<int,int> pos2 = pos+dir;
    return (pos2.first > 0 && pos2.second > 0 && pos2.first < h-1 && pos2.second < w-2);
}


bool Snake::hit(pair<int,int> p){
    return (cels.find(p) != cels.end());
}

