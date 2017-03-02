1.  Create \*.java file
2.  Compile \*.java file using javac

    ```
    javac Hello.java
    ```

3.  Create jni.h header file.

    ```
    javah -jni Hello
    ```

    Will create `Hello.h`.
4.  Create C source code
5.  Compile by

    ```
    gcc -I"/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers" -I"/System/Library/Frameworks/JavaVM.framework/Versions/A/Headers" -c Hello.c
    gcc -dynamiclib -o libhello.jnilib Hello.o
    
    ```
6.  Try `java Hello`
7.  Done!
