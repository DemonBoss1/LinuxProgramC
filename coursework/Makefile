main: main.o TestCode
	gcc -o main main.o 

main.o: main.c main.h
	gcc -O0 -g3 -Wall -c main.c

TestCode: TestCode.o
	gcc -o TestCode TestCode.o

TestCode.o: TestCode.c 
	gcc -O0 -g3 -Wall -c TestCode.c

clean:
	@echo "This is clean action"
	rm -rf main TestCode *.o

all: TestCode main