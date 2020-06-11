TEST_FILES = $(wildcard *.java)
EXE = $(basename $(TEST_FILES))

test: build_lib build_test
	java -cp "../pns-innov;junit-4.13.jar;hamcrest-core-1.3.jar;." \
		org.junit.runner.JUnitCore $(EXE)

build_lib:
	cd ../pns-innov && mingw32-make.exe all
	cd ../pns-innov && mingw32-make.exe run

build_test: junit-4.13.jar $(TEST_FILES)
	javac -cp $^

clean:
	cd ../pns-innov && mingw32-make.exe clean
	rm -rf *.class
