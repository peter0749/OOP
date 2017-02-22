all: java cpp
java:
	javac Main.java
cpp:
	g++ hw1.cpp -o MainCPP.bin
clean:
	rm -f MainCPP.bin Main.class
run.java: java
	java Main
run.cpp: cpp
	./MainCPP.bin
