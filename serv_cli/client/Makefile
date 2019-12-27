# binname := lantern
# maincname := lantern.c

binname := client
maincname := client.c

.PHONY: run
run:build
	./$(binname)

.PHONY: build
build:
	gcc $(maincname) -o $(binname)
