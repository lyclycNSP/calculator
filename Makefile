CPPFLAGS = -Wall -Werror -pedantic -Wconversion -Wsign-conversion -std=c++23

main:main.o calculator.o
	g++ $(CPPFLAGS) -o main main.o calculator.o

calculator.o:calculator.cpp calculator.h
	g++ $(CPPFLAGS) -c calculator.cpp

main.o:main.cpp calculator.h
	g++ $(CPPFLAGS) -c main.cpp

.PHONY:clean
clean:
	rm -rf *~ *.o main

