all: SubFactorialJAVA.jar SubFactorialCPP.bin
SubFactorialJAVA.jar: SubFactorial.java main.mf
	javac SubFactorial.java
	jar cvfm SubFactorialJAVA.jar main.mf SubFactorial.class
SubFactorialCPP.bin: SubFactorial.cpp
	g++ SubFactorial.cpp -o SubFactorialCPP.bin
clean:
	rm -f SubFactorialCPP.bin SubFactorial.class SubFactorialJAVA.jar
run.java:
	java -jar SubFactorialJAVA.jar
run.cpp:
	./SubFactorialCPP.bin
