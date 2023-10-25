#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	int begin = 1;
	int number = 1;

	while (1){
		begin = begin * number;
	}

	printf("%s%d", "Wynik: ", begin);
	return 0;
}
