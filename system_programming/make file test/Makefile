

main.out: main.o b.o a.o
	gcc -o main.out main.o b.o a.o

main.o: main.c b.h
	gcc -c main.c

b.o: b.c b.h a.h
	gcc -c b.c

a.o: a.c a.h
	gcc -c a.c

.PHONY: clean
clean:
	-rm -f main.out main.o b.o a.o