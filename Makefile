CPPFLAGS = $(-Wall -Werror -pedantic -Wconversion -W-sign-conversion -std=c++23)

main:main.o calculator.o
	g++ $(CPPFLAGS) -o main main.o calculator.o

main.o:calculator.h
	g++ $(CPPFLAGS) -c calculator.h

calculator.o:calculator.h
	g++ $(CPPFLAGS) -c calculator.h

.PHONY:clean
clean:
	rm -rf *~ *.o

