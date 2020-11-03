# db:db.c
# 	gcc db.c -o db -g
main:main.o db.o
	gcc main.o db.o -o main
main.o:main.c db.h
	gcc -c main.c -o main.o
db.o:db.c db.h
	gcc -c db.c -o db.o		
.PHONY:clean run
clean:
	rm -rf db.o main.o main
run:
	./main