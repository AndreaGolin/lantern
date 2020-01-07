# binname := lantern
# maincname := lantern.c

binname := test
maincname := test.c

.PHONY: run
run:build
	./$(binname)

.PHONY: build
build:
	gcc `pkg-config gtk+-3.0 --cflags` $(maincname) -o $(binname) `pkg-config gtk+-3.0 --libs`
