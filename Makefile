build:
	gcc -g -c -o main.o main.c 
	gcc -g -c -o e1.o e1.c
	gcc -g -c -o e2.o e2.c 
	gcc -g -c -o e3.o e3.c 
	gcc -g -o tema3 main.o e1.o e2.o e3.o

clean:
	rm -f *.o tema3
