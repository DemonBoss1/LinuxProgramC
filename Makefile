#
# This is my first Makefile
#

main: main.o func1.o func2.o lab3.o lab4.o lab5.o ArgPrint
	gcc -pthread -o  main main.o func1.o func2.o lab3.o lab4.o lab5.o

main.o: main.c main_header.h func1.h func2.h
	gcc -O0 -g3 -Wall -c -pthread main.c

func1.o: func1.c func1.h
	gcc -O0 -g3 -Wall -c func1.c

func2.o: func2.c func2.h
	gcc -O0 -g3 -Wall -c func2.c

lab3.o: lab3.c labs.h
	gcc -O0 -g3 -Wall -c lab3.c

lab4.o: lab4.c labs.h
	gcc -O0 -g3 -Wall -c lab4.c

lab5.o: lab5.c labs.h
	gcc -O0 -g3 -Wall -c lab5.c

some_app: some_app.o
	gcc -o some_app some_app.o

some_app.o: some_app.c
	gcc -O0 -g3 -Wall -c some_app.c

ArgPrint: ArgPrint.o
	gcc -o ArgPrint ArgPrint.o

ArgPrint.o:ArgPrint.c	
	gcc -O0 -g3 -Wall -c ArgPrint.c

clean:
	@echo "This is clean action"
	rm -rf main some_app *.o

all: some_app main