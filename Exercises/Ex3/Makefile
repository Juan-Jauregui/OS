all: increment consecutive spawn

clean:
	rm bin/*

increment: src/increment.c
	mkdir -p bin
	cc -o bin/increment src/increment.c

consecutive: src/consecutive.c
	mkdir -p bin
	cc -o bin/consecutive src/consecutive.c

spawn: src/spawn.c
	mkdir -p bin
	cc -o bin/spawn src/spawn.c
