all: java cpp
java:
	javac SubFactorial.java
	jar cvfm SubFactorialJAVA.jar main.mf SubFactorial.class
cpp:
	g++ SubFactorial.cpp -o SubFactorialCPP.bin
clean:
	rm -f SubFactorialCPP.bin SubFactorial.class SubFactorialJAVA.jar
run.java: java
	java -jar SubFactorialJAVA.jar
run.cpp: cpp
	./SubFactorialCPP.bin
