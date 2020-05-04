.default: all

all: azul

clean:
	rm -rf azul *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Mosaic.o Factories.o driver.o Player.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^