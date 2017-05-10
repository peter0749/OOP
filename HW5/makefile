all: main
main: Node.o CircularList.o Polynomial.o main.cpp
	g++ main.cpp Node.o CircularList.o Polynomial.o -o main
Node.o:
	g++ -c src/Node.cpp -o Node.o
CircularList.o:
	g++ -c src/CircularList.cpp -o CircularList.o
Polynomial.o:
	g++ -c src/Polynomial.cpp -o Polynomial.o
clean:
	rm -f *.o main

