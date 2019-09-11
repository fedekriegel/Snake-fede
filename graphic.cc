#include "graphic.h"

void sqr(pair<int,int> pos ,int n){
    wmove(stdscr, pos.first, pos.second);
    addch(' ' | A_REVERSE | COLOR_PAIR(n));
    addch(' ' | A_REVERSE | COLOR_PAIR(n));    
}

void clean(WINDOW * st, int h, int w){
    for(int y = 0; y < h; y-=-1){
        for( int x = 0; x < w; x-=-1){
            mvwaddch(st, y, x,'a' | COLOR_PAIR(BLACK)); 
        }
    }
}


pair<int,int> init(){

    srand(time(NULL));
    int h,w;
    getmaxyx(stdscr, h, w);// obtiene acho y largo de la pantalla
    
    cbreak(); // caracter por caracter
    noecho(); // no escribit en la terminal 
    keypad(stdscr, TRUE); // caracteres especiales
    nodelay(stdscr, TRUE); // si no se preciona da error
    curs_set(0); // oculta cursor

    start_color();
    init_pair(255, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    clean(stdscr, h,w);

    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0); //divuja recuadro
    return {h,w};
}

void end(){
	endwin(); // opuesto a initscr
}