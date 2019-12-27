#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	const int SIZE = 20;

	char *store = malloc(SIZE * sizeof(char));
	char *t = store;
	memset(store, 0, SIZE);

	strcpy(store, "Hi there!");
	puts(store);

	for(int j = 0; j < SIZE; j++){
		printf("%s: %x\n", "Address of store pointer", store);
		printf("%s: %c\n", "Val of dereferenced pointer", *store);
		store++;
	}

	free(t);
	return 0;

}