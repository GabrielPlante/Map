JAVA_HOME = ../Dependencies/include
CC = g++
CPPFLAGS = -I. -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/win32 -lm -m64
LDFLAGS = -Wl,--add-stdcall-alias -m64
LIB = ../x64/Debug/pns-innov.dll
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
GCH = $(wildcard *.h.gch)

clean:
	rm -f GeneticBotJNI.Class $(LIB) $(OBJ) $(GCH)

re: clean $(LIB)

%.o: %.cpp %.h
	$(CC) $(CPPFLAGS) -c $<

all: $(LIB)

$(LIB): $(OBJ)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

run: GeneticBotJNI.class
	java -cp . -Djava.library.path=../x64/Debug/ GeneticBotJNI
#run: TowerManagerJNI.class
#	java -cp . -Djava.library.path=../x64/Debug/ TowerManagerJNI

%.class: %.java
	javac $<

%.h: %.class
	javah -cp . $(<:.class=)


#g++ -c -I 
#-IC:/Program\ Files/Java/jdk1.8.0_181/include/win32 GeneticBotJNI.cpp -o GeneticBotJNI.o

#g++ -shared -o ../x64/Debug/pns-innov.dll GeneticBotJNI.o -Wl,--add-stdcall-alias
