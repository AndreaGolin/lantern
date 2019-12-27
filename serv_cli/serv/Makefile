# binname := lantern
# maincname := lantern.c

binname := serv
maincname := serv.c

.PHONY: run
run:build
	./$(binname)

.PHONY: build
build:
	gcc $(maincname) -o $(binname)
