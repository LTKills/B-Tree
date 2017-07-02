#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>


bool is_EOF(FILE *stream) {
    //verifica se é o final do arquivo de um stream.
    char letra;
    letra = fgetc(stream);
    if(letra == EOF) {
        ungetc(letra, stream);
        return true;
    }
    ungetc(letra, stream);
    return false;
}


int main (int argc, char *argv[]) {
	FILE *fp;
	fp = fopen("worst.idx", "rb");
	int ticket, count = 0;

	while (!feof(fp)) {
		fread(&ticket, sizeof(int), 1, fp);
        if(feof(fp)) break;
		printf("%d: %d \n", count, ticket);
		count++;
	}

	return 0;
}
