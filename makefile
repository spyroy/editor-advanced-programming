CC = g++
CXXFLAGS=-std=c++0x

all: main.o Editor.o Document.o
	$(CC) main.o Editor.o Document.o -o ed

Editor.o: Editor.cpp Editor.h
	$(CC) $(CXXFLAGS) --compile Editor.cpp -o Editor.o

Document.o: Document.cpp Document.h
	$(CC) $(CXXFLAGS) --compile Document.cpp -o Document.o

main.o: main.cpp 
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

.phony: claen all

clean:
	rm -f *.o ed 