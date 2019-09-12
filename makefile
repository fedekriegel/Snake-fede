
OBJ_C = snake.cc main.cc grafic.cc
OBJ_O = snake.o main.o graphic.o

all: snake

player:=1
getname:=0

snake:snake_g
	./snake_g $(player) $(getname)


$(objects): %.o : %.cc
	g++ -std=c++17 -O2 -c -o $@ $< -lncurses -lmysqlcppconn


snake_g: $(OBJ_O)
	g++ -std=c++17 -g -O2 -o snake_g $(OBJ_O)  -lncurses -lmysqlcppconn

rm:
	rm $(OBJ_O) snake_g


