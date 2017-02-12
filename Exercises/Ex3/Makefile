all: consecutive spawn

clean:
	rm bin/*

consecutive: src/consecutive.c
	mkdir -p bin
	cc -o bin/consecutive src/consecutive.c

spawn: src/spawn.c
	mkdir -p bin
	cc -o bin/spawn src/spawn.c

# Though not required for the assignment, also building the provided increment.c
increment: src/increment.c
	mkdir -p bin
	cc -o bin/increment src/increment.c
