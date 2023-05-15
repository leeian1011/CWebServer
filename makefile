src/all: src/server

src/server: src/server.c
	clang -c src/httpfunctions.c
	clang -c src/serverfunctions.c
	clang -o server httpfunctions.o serverfunctions.o src/server.c

clean:
	rm server

