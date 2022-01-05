
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie {
	char *title;
	int year;
	char *languages;
	double rating_value;
	struct movie *next;

};



int main(int argc, char * argv[]){

	if(argc < 2){
		printf("Provide name of file \n");
		printf("Example: ./movies movie.csv \n");
	}
}
