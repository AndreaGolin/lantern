# binname := lantern
# maincname := lantern.c

binname := sock
maincname := sock.c

.PHONY: run
run:build
	./$(binname)

.PHONY: build
build:
	gcc $(maincname) -o $(binname)
