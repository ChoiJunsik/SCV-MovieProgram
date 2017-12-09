#include "movieProject.h"


	extern Movie *movie, *movieTail, *movieCur, *movieNew;
	extern Director *director, *directorTail, *directorCur, *directorNew;
	extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

	extern FILE *mp, *dp, *ap;

	extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
int main(void)
{
	signal(2,interrupt);
	movie = movieTail = movieCur = movieNew = NULL;
	director = directorTail = directorCur = directorNew = NULL;
	char* commands, *mda, *option, *num, *fileName,*searchInput,*searchMda, *string;
	char* input;
	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	loadMovielogs();
	loadDirectorlogs();
	loadActorlogs();
	makeMovieList();
	makeDirectorList();
	makeActorList();
	linkAnotherMovie();
	linkAnotherDirector();
	linkAnotherActor();
	printf("You can use add, update, delete, search, print, sort, save , end commands.\n");
	while (1) {
		mp = fopen("movie_log", "at");
		dp = fopen("director_log", "at");
		ap = fopen("actor_log", "at");
		input = (char*)malloc(30);
		searchInput = (char*)malloc(30);
		printf("(movie) ");
		gets(input);
		strcpy(searchInput,input);
		commands = strtok(input, " ");
		if(commands == 0){
		printf("@@ Please input the correct commands!\n\n");
		free(input);
		continue;
		}
		else if(strcmp(commands,"add")!=0 && strcmp(commands,"update")!=0 && strcmp(commands,"delete")!=0 && strcmp(commands,"search")!=0 && strcmp(commands,"print")!=0 && strcmp(commands,"sort")!=0 && strcmp(commands,"save")!=0 && strcmp(commands,"end")!=0){
			printf("@@ Please input the correct commands!\n\n");
			free(input);
			continue;
			}
		if (strcmp(commands, "end") == 0) {
			end();
		}
		else if (strcmp(commands, "search") == 0) {
			strtok(searchInput," ");
			searchMda = strtok(NULL,"");
			if(searchMda == 0){
					printf("@@ Please input the string!\n\n");
					free(input);
					free(searchInput);
					continue;
			}
			if (searchMda != 0 && *searchMda == '-') {
				if((strlen(searchMda)==2 && *(searchMda+2)=='\0')||(strlen(searchMda)==3 &&*(searchMda+3)=='\0')||(strlen(searchMda)==3 && *(searchMda+4)=='\0')){
					  printf("@@ Please input the string!\n\n");
						free(input);
						free(searchInput);
						continue;
				}
				searchMda = strtok(searchMda," ");
 				string = searchMda+strlen(searchMda)+1;
				search(searchMda+1, string);
			}
			else if (searchMda != 0 && *searchMda != '-') {
				string = searchMda;
				searchMda = "mda";
				search(searchMda, string);
			}
			printf("\n");
		}
		else if (strcmp(commands, "add") == 0) {
			mda = strtok(NULL, " ");
			if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
				printf("@@ Please input the m|d|a option!\n\n");
				free(input);
				continue;
			}
			add(mda);

			makeMovieList();
			makeDirectorList();
			makeActorList();
		}
		else if (strcmp(commands, "update") == 0) {
		mda = strtok(NULL, " ");
		if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
			printf("@@ Please input the m|d|a option!\n\n");
			free(input);
			continue;
		}
			option = strtok(NULL, " ");
			num = strtok(NULL, " ");
			if (option == 0 || num == 0) {
				printf("@@ Please input the option!\n\n");
				free(input);
				continue;
			}
			update(mda, option, num);

			makeMovieList();
			makeDirectorList();
			makeActorList();
		}
		else if (strcmp(commands, "delete") == 0) {
			mda = strtok(NULL, " ");
			if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
				printf("@@ Please input the m|d|a option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			num = strtok(NULL, " ");
			if (num == 0) {
				printf("@@ Please input the option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			delete(mda, num);

			makeMovieList();
			makeDirectorList();
			makeActorList();
		}
		else if (strcmp(commands, "print") == 0) {
			mda = strtok(NULL, " ");
			if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
				printf("@@ Please input the m|d|a option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			num = strtok(NULL, " ");
			if (num == 0) {
				printf("@@ Please input the option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			print(mda, num);
		}
		else if (strcmp(commands, "sort") == 0) {
			mda = strtok(NULL, " ");
			if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
				printf("@@ Please input the m|d|a option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			option = strtok(NULL, " ");
			if (option == 0)
				sort(mda, NULL, NULL);
			else if (*option == '-') {
				*(option + 2) = ' ';
				fileName = option + 3;
				sort(mda, NULL, fileName);
			}
			else {
				fileName = strtok(NULL, " ");
				if (fileName == 0 && *option != '-')
					sort(mda, option, NULL);
				else if (fileName != 0) {
					if (*fileName != '-') {
						printf("@@ Please input the correct file option!\n\n");
						free(input);
						free(searchInput);
						continue;
					}
					fileName += 3;
					sort(mda, option, fileName);
				}
			}
		}
		else if (strcmp(commands, "save") == 0) {
			mda = strtok(NULL, " ");
			if (mda == 0 || ((*mda != 'm') && (*mda != 'd') && (*mda != 'a'))) {
				printf("@@ Please input the m|d|a option!\n\n");
				free(input);
				free(searchInput);
				continue;
			}
			option = strtok(NULL, " ");
			if (option == 0)
				save(mda, NULL, NULL);
			else if (*(option + 1) == 'f') {
				*(option + 2) = ' ';
				fileName = option + 3;
				save(mda, NULL, fileName);
			}
			else {
				fileName = strtok(NULL, " ");
				if (fileName == 0 && *(option + 1) != 'f'){
					if(*option != '-'){
						printf("@@ Please input the correct option!\n\n");
						free(input);
						free(searchInput);
						continue;
					}
					save(mda, option, NULL);}
				else if (fileName != 0) {
					if (*fileName != '-') {
						printf("@@ Please input the correct file option!\n\n");
						free(input);
						free(searchInput);
						continue;
					}
					fileName += 3;
					if(*option != '-'){
						printf("@@ Please input the correct option!\n\n");
						free(input);
						free(searchInput);
						continue;
					}
					save(mda, option, fileName);
				}
			}
			printf("@@ Done\n");
		}
		free(input);
		free(searchInput);
		linkAnotherMovie();
		linkAnotherDirector();
		linkAnotherActor();
	}

	return 0;
}
