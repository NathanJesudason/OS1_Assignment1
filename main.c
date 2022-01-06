
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct movie {
	char *title;
	int year;
	char *languages;
	double rating_value;
	struct movie *next;
};

struct movie *createMovie(char *line){
	struct movie *currMovie = malloc(sizeof(struct movie));
	char *saveptr;
	char *token = strtok_r(line, ",", &saveptr);
	currMovie->title = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->title, token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->year = atoi(token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
	strcpy(currMovie->languages, token);

	token = strtok_r(NULL, ",", &saveptr);
	currMovie->rating_value = strtod(token, NULL);

	currMovie->next= NULL;

	return currMovie;
}

struct movie *readFile(char *filePath){
	FILE *movieFile = fopen(filePath, "r");

	char *Line = NULL;
	size_t len = 0;
	ssize_t nread;

	struct movie *head = NULL;
	struct movie *tail = NULL;

	while ((nread = getline(&Line, &len, movieFile)) != -1){
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

void input_loop(){
	bool continue_flag = true;
	while(continue_flag){
		//print statements
		//get input
		char inputbuffer[50];
		int input = -1;
		fgets(inputbuffer,50,stdin);
		input = atoi(inputbuffer);
		switch(input){
			case 1:
				//specify year
				break;
			case 2:
				//highest rated each year
				break;
			case 3:
				//specify language
				break;
			case 4:
				continue_flag = false;
				break;
			default:
				printf("input fail \n");
		}
	}
}

int main(int argc, char * argv[]){

	if(argc < 2){
		printf("Provide name of file \n");
		printf("Example: ./movies movie.csv \n");
		return EXIT_FAILURE;
	}
	struct movie *list = readFile(argv[1]);
	//Processed file [filename] and parsed data for [n] movies
	input_loop();
	return EXIT_SUCCESS;
}


