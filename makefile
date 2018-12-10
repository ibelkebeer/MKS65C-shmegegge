all: shm.c
	gcc shm.c

run: a.out
	./a.out
