all: hw2.bin
hw2.bin: hw2.cpp
	g++ hw2.cpp -std=c++11 -o hw2.bin
run: hw2.bin
	./hw2.bin
judge:
	./judge.sh
clean:
	rm -f hw2.bin
	rm -f gen
	rm -f testfile.txt
