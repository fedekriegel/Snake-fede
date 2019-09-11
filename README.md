# Snake-fede

## Requerimientos:
Se necesita tener instalasdas las siguientes librerias

* ncurses
  > $ sudo apt-get install libncurses-dev
* MySQL connector para c++
  > $ sudo apt-get install libmysqlcppconn-dev

## Uso:
 * make snake : se inica el juego para 1 jugador sin la posibilidad de elejir nombre;
 
 ### opciones
 * player: cantidad de jugadores (1 o 2) (ej make snake player=2)
 * getname: abilita el elegir el nombre de los jugadores 
    > al finalizar la partida se guarda el resultado del jugador que gane
    
