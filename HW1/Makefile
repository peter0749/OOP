all: java cpp
java:
	javac Main.java
	jar cvfm MainJava.jar main.mf Main.class
cpp:
	g++ hw1.cpp -o MainCPP.bin
clean:
	rm -f MainCPP.bin Main.class MainJava.jar
run.java: java
	java -jar MainJava.jar
run.cpp: cpp
	./MainCPP.bin
