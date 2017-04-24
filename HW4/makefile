all: main.bin
main.bin: src/main.cpp src/car.o
	g++ src/main.cpp src/car.o -o main.bin -Wall
src/car.o:
	g++ -c -o src/car.o src/car.cpp -Wall
clean:
	rm -f main.bin src/*.o
