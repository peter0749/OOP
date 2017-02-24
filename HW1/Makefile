CFLAG= -w
JFLAG= 
all: SubFactorialJAVA.jar SubFactorialCPP.bin
SubFactorial.class: SubFactorial.java
	javac ${JFLAG} ${JEXFLAG} SubFactorial.java
SubFactorialJAVA.jar: SubFactorial.class main.mf
	jar cvfm SubFactorialJAVA.jar main.mf SubFactorial.class
SubFactorialCPP.bin: SubFactorial.cpp
	g++ ${CFLAG} ${CEXFLAG} ${CDEFINE} SubFactorial.cpp -o SubFactorialCPP.bin
clean:
	rm -f SubFactorialCPP.bin SubFactorial.class SubFactorialJAVA.jar
run.java: SubFactorialJAVA.jar
	java -jar SubFactorialJAVA.jar
run.cpp: SubFactorialCPP.bin
	./SubFactorialCPP.bin
