
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

//returns list or NULL if fopen fail
struct movie *readFile(char *filePath){
	FILE *movieFile = fopen(filePath, "r");
	//test to ensure filePath is valid
	if(movieFile == NULL)
		return NULL;

	char *Line = NULL;
	size_t len = 0;
	ssize_t nread;

	struct movie *head = NULL;
	struct movie *tail = NULL;
	//Ignore first line because that is just headers
	nread = getline(&Line, &len, movieFile);
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

void year_list(struct movie *list){
	printf("Enter the year for which you want to see movies: ");
	int year_input;
	scanf("%4d", &year_input);
	bool noMovies = true;
	while(list != NULL){
		if(list->year == year_input){
			printf("%s", list->title);
			noMovies = false;
		}
		list = list->next;
	}
	if(noMovies){
		printf("No data about movies released in the year %d \n", year_input);
	}
}

void ratings_list(struct movie *list){
	//indexed as year - 1900 (min year)
	//because max year is 2021, the max index is 121
	struct movie* greatest[122] = {NULL, };
	int index;
	while(list != NULL){
		index = list->year - 1900;
		if(greatest[index] == NULL || greatest[index]->rating_value < list->rating_value){
			greatest[index] = list;
		}
		list = list->next;
	}
	for(int i = 0; i < 122; i++){
		if(greatest[i] == NULL)
			continue;
		printf("%d %.1f %s \n", greatest[i]->year, greatest[i]->rating_value, greatest[i]->title);
	}
}

void language_list(struct movie *list){
	printf("Enter the language for which you want to see movies: ");
	char inputbuffer[22];
	//Used to avoid finding substring that is part of a language (ex 'Eng')
	//Language is stored [English;French...German], so concat ';' and ']'
	//ensures strstr doesn't find a substring that isn't the full language name
	char *language_input_semi = NULL;
	char *language_input_brac = NULL;
	char *result;
	char *result2;
	scanf("%20s", inputbuffer);
	language_input_semi = calloc(strlen(inputbuffer) + 2, sizeof(char)); 
	language_input_brac = calloc(strlen(inputbuffer) + 2, sizeof(char));
	strcpy(language_input_semi, inputbuffer);
	strcpy(language_input_brac, inputbuffer);
	strcat(language_input_semi, ";");
	strcat(language_input_brac, "]");
	bool noMovies = true;
	while(list != NULL){
		//if input is in languages string
		result = strstr(list->languages, language_input_semi);
		result2 = strstr(list->languages, language_input_brac);
		if(result != NULL || result2 != NULL){
			noMovies = false;
			printf("%s \n", list->title);
		}
		list = list->next;
	}
	if(noMovies)
		printf("No data about movies released in %s \n", inputbuffer);
	free(language_input_semi);
	free(language_input_brac);
}

void input_loop(struct movie *list){
	bool continue_flag = true;
	char inputbuffer[4];
	int input = -1;
	while(continue_flag){
		//print statements
		printf("1. Show movies released in the specified year \n");
		printf("2. Show highest rated movie for each year \n");
		printf("3. Show the title and year of release of all movies in a specified language \n");
		printf("4. Exit from the program \n");
		printf("\n");
		printf("Enter a choice from 1 to 4: ");
		scanf("%1d", &input);
		//choose action based on input
		switch(input){
			case 1:
				//specify year
				year_list(list);
				break;
			case 2:
				//highest rated each year
				ratings_list(list);
				break;
			case 3:
				//specify language
				language_list(list);
				break;
			case 4:
				//set flag false to end while loop
				continue_flag = false;
				break;
			default:
				printf("You entered an incorrect choice. Try again.\n");
		}
	}
}

//test function to ensure movie list is parsed correctly
void print_movie_list(struct movie *list){
	while(list != NULL){
		printf("%s %d %s %.1f \n", list->title, list->year, list->languages, list->rating_value);
		list = list->next;
	}
}

int main(int argc, char * argv[]){
	//check for file argument
	if(argc < 2){
		printf("Provide name of file \n");
		printf("Example: ./movies movie.csv \n");
		return EXIT_FAILURE;
	}
	struct movie *list = readFile(argv[1]);
	if(list == NULL){
		printf("File read fail \n");
		return EXIT_FAILURE;
	}
	int numMovies = 0;
	struct movie *movieptr = list;
	while(movieptr != NULL){
		numMovies = numMovies + 1;
		movieptr = movieptr->next;
	}
   printf("Processed file %s and parsed data for %d movies \n", argv[1], numMovies);
	input_loop(list);
	//clean up linked list
	struct movie *last;
	while(list != NULL){
		last = list;
		list = list->next;
		free(last->languages);
		free(last->title);
		free(last);
	}
	return EXIT_SUCCESS;
}


