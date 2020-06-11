#Installation Instructions to run JNI Tests

The Makefile was written to work ONLY on MS Windows, with Mingw32/TDM-G++

1. add the path containing javac and java programs in you system environment variables: on Windows, it looks like:
```C:\Program Files\Java\jdk1.8.0_181\bin```

2. Install compilation tools:
    - Install TDM-G++ available at: https://jmeubank.github.io/tdm-gcc/
    - on windows, add ```C:\TDM-GCC-64\bin``` to the Windows Path: you will be able to use mingw32-make.exe
      on git bash or cmd (like make program on Linux)
    - to launch JNI Tests open git bash and go to Test directory/project and then: 
      mingw32-make.exe test
      This will: build pns-innov.dll in the pns-innov project and build all *.class files in pns-innov
      and Test projects, then it launches the junit tests.
