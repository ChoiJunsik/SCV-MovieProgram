#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct singleData {
	char* name;
	struct singleData* next;
} singleData;
typedef struct Director {
	int serialNumber;
	singleData* director;
	char sex;
	singleData* birth;
	singleData* title;
	struct Director* next;
} Director;
typedef struct Actor {
	int serialNumber;
	singleData* actor;
	char sex;
	singleData* birth;
	singleData* title;
	struct Actor* next;
} Actor;
typedef struct Movie {
	int serialNumber;
	singleData* title;
	singleData* genre;
	singleData* director;
	singleData* actor;
	struct Movie* next;
} Movie;

Movie* movie = NULL;
Director* director = NULL;
Actor* actor = NULL;
FILE *mp, *dp, *ap;

int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
void add(char*);

int main(void)
{

	char* commands, *mda, *option, *num;
	char* input = (char *)malloc(50);

	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	mp = fopen("movie_log", "wt");
	dp = fopen("director_log", "wt");
	ap = fopen("actor_log", "wt");
	if (mp == NULL || dp == NULL || ap == NULL) {
		printf("File Loading Faile!!\n");
		return -1;
	}
	else
		printf("You can use add, update, delete, search, sort, save , end commands.\n");

	printf("(movie) ");
  gets(input);
	commands = strtok(input, " ");
	mda = strtok(NULL, " ");
  if (strcmp(commands, "add") == 0)
		                      add(mda);
	return 0;
}

void add(char* mda) {
	printf("check");
	int year, runTime;
	++MovieSerialNumber;
	if (strcmp(mda, "m") == 0) {
    char* actorArray = (char*)malloc(100);
		movie = (Movie *)malloc(sizeof(Movie));
		movie->serialNumber = MovieSerialNumber;
		printf("title > ");
		movie->title = (singleData*)malloc(sizeof(singleData));
    movie->title->name = (char *)malloc(sizeof(30));
		gets(movie->title->name);
		printf("genre > ");
		movie->genre = (singleData*)malloc(sizeof(singleData));
    movie->genre->name = (char *)malloc(sizeof(20));
		gets(movie->genre->name);
		printf("director > ");
		movie->director = (singleData*)malloc(sizeof(singleData));
    movie->director->name = (char *)malloc(sizeof(30));
    printf("year > ");
    scanf("%d",&year);
    printf("run time > ");
    scanf("%d",&runTime);
		gets(movie->director->name);
		printf("actors > ");
		movie->actor = (singleData*)malloc(sizeof(singleData));
		gets(actorArray);
    fprintf(mp, "add:%d:%s:%s:%s:%d:%d:%s", movie->serialNumber, movie->title->name, movie->genre->name, movie->director->name, year, runTime, actorArray);
    return;
	}

}
