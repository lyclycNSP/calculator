CPPFLAGS = -Wall -Werror -pedantic -Wconversion -Wsign-conversion -std=c++23

main:main.o calculator.o
	g++ $(CPPFLAGS) -o main main.o calculator.o
calculator.o: calculator.h
main.o: calculator.h

.PHONY:clean
clean:
	rm -rf *~ *.o main

