
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

struct movie *createMovie(char *line){

}

struct movie *readFile(char *filePath){
	FILE *movieFile = fopen(filePath, "r");

	char *Line = NULL;
	size_t len = 0;

	struct movie *head = NULL;
	struct movei *tail = NULL;

	while ((nread = getLine(&Line, &len, movieFile)) != -1){
		struct movie *newNode = createMovie(Line);
		if (head == NULL){
			head = newNode;
			tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	}
	free(Line);
	fclose(movieFile);
	return head;
}


int main(int argc, char * argv[]){

	if(argc < 2){
		printf("Provide name of file \n");
		printf("Example: ./movies movie.csv \n");
	}
}
