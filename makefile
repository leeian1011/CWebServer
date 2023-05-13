src/all: src/server

src/server: src/server.c
	clang -c src/httprequestfunctions.c
	clang -c src/serverfunctions.c
	clang -o server httprequestfunctions.o serverfunctions.o src/server.c

clean:
	rm server

