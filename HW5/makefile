all: main
main: Polynomial.o main.cpp
	g++ main.cpp Polynomial.o -o main
Polynomial.o:
	g++ -c src/Polynomial.cpp -o Polynomial.o
clean:
	rm -f *.o main

