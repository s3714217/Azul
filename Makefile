.default: all

all: azul

clean:
	rm -rf azul

azul:  
	g++ -Wall -Werror -std=c++14 -O -o azul *.cpp

run:	
	./azul 1