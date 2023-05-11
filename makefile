src/all: src/server

src/server: src/server.c
	clang -c src/hashtable.c
	clang -c src/serverfunctions.c
	clang -o server hashtable.o serverfunctions.o src/server.c
	if [ $? -e 0 ]; then
	./server
	fi

clean:
	rm server

