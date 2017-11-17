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
	singleData* actor,*actorTail,*actorNew,*actorCur;
	struct Movie* next;
} Movie;

Movie *movie,*movieTail,*movieCur,*movieNew;
Director *director,*directorTail;
Actor *actorIndex,*actor;

FILE *mp, *dp, *ap;

int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber, MovieCnt, ActorCnt, DirectorCnt;

void add(char*);

int main(void)
{
	movie=movieTail=movieCur=movieNew=NULL;
	char* commands, *mda, *option, *num;
	char* input = (char*)malloc(30);

	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	mp = fopen("movie_log", "wt");
	dp = fopen("director_log", "wt");
	ap = fopen("actor_log", "wt");
	if (mp == NULL || dp == NULL || ap == NULL) {
		printf("File Loading Fail!!\n");
		return -1;
	}
	else
		printf("You can use add, update, delete, search, sort, save , end commands.\n");
	while(1){
	printf("(movie) ");
  gets(input);
	commands = strtok(input, " ");
	mda = strtok(NULL, " ");
  if (strcmp(commands, "add") == 0){
		                      add(mda);
													fclose(mp);
			}
	}
	return 0;
}

void add(char* mda) {
	int year, runTime;
	char* actorCheck;
	if (strcmp(mda, "m") == 0) {
		movieNew = (Movie*)malloc(sizeof(Movie));
		movieNew->actor=movieNew->actorNew=movieNew->actorTail=movieNew->actorCur=NULL;
    char* actorArray = (char*)malloc(100);
		movieNew->serialNumber = MovieSerialNumber;
		printf("title > ");
		movieNew->title = (singleData*)malloc(sizeof(singleData));
    movieNew->title->name = (char *)malloc(sizeof(30));
		gets(movieNew->title->name);
		printf("genre > ");
		movieNew->genre = (singleData*)malloc(sizeof(singleData));
    movieNew->genre->name = (char *)malloc(sizeof(30));
		gets(movieNew->genre->name);
		printf("director > ");
		movieNew->director = (singleData*)malloc(sizeof(singleData));
    movieNew->director->name = (char *)malloc(sizeof(30));
		gets(movieNew->director->name);
    printf("year > ");
    scanf("%d",&year);
    printf("run time > ");
    scanf("%d",&runTime);
		getchar();
		printf("actors > ");
		gets(actorArray);
		movieNew->next = NULL;

		fprintf(mp, "add:%d:%s:%s:%s:%d:%d:%s", movieNew->serialNumber, movieNew->title->name, movieNew->genre->name, movieNew->director->name, year, runTime, actorArray);

		movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
		movieNew->actorNew->name = strtok(actorArray, ",");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
		//정리
			movieNew->actor = movieNew->actorNew;
			movieNew->actorTail = movieNew->actorNew;
		//

		while (1) // actor 연결리스트에 넣는 과정
		{
		actorCheck=strtok(NULL,",");
		if(actorCheck == 0) {break;}
		else if(*actorCheck == ' '){continue;}
		movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
    movieNew->actorNew->name = actorCheck;

		movieNew->actorTail->next = movieNew->actorNew;
		movieNew->actorTail = movieNew->actorNew;
	}

		if(movie==NULL)
			movie = movieNew;
		else
			movieTail->next = movieNew;

			movieTail = movieNew;
		puts("@@ Done");
		} // add 함수의 끝
	return ;
	}
