all: main
main: main.cpp Number.o TestNumbers.o
	g++ main.cpp Number.o TestNumbers.o -o main
Number.o:
	g++ -c Number.cpp -o Number.o
TestNumbers.o:
	g++ -c TestNumbers.cpp -o TestNumbers.o
clean:
	rm -f main *.o
