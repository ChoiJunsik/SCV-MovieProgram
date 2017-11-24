#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct singleData {
	char* name;
	struct singleData* next;
	struct Movie* linkAnotherM;
	struct Director* linkAnotherD;
	struct Actor* linkAnotherA;
} singleData;
typedef struct Director {
	int serialNumber;
	singleData* director;
	char sex;
	singleData* birth;
	singleData* title, *titleTail, *titleNew, *titleCur;
	struct Director* next;
} Director;
typedef struct Actor {
	int serialNumber;
	singleData* actor;
	char sex;
	singleData* birth;
	singleData* title, *titleTail, *titleNew, *titleCur;
	struct Actor* next;
} Actor;
typedef struct Movie {
	int serialNumber, year, runTime;
	singleData* title;
	singleData* genre;
	singleData* director;
	singleData* actor, *actorTail, *actorNew, *actorCur;
	struct Movie* next;
} Movie;

Movie *movie, *movieTail, *movieCur, *movieNew;
Director *director, *directorTail, *directorCur, *directorNew;
Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

FILE *mp, *dp, *ap;

int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;

void add(char*);
void loadMovielogs(void);
void loadDirectorlogs(void);
void loadActorlogs(void);
Movie* addSameMovie(void);
Director* addSameDirector(void);
Actor* addSameActor(void);
char* changeColon(char*);
char* changeLogColon(char*);
void linkAnotherMovie(void);
void linkAnotherDirector(void);
void linkAnotherActor(void);

int main(void)
{
	movie = movieTail = movieCur = movieNew = NULL;
	director = directorTail = directorCur = directorNew = NULL;
	char* commands, *mda, *option, *num;
	char* input;

	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	loadMovielogs();
	loadDirectorlogs();
	loadActorlogs();
	linkAnotherMovie();
	linkAnotherDirector();
	linkAnotherActor();
	printf("You can use add, update, delete, search, sort, save , end commands.\n");
	while (1) {
		mp = fopen("movie_log", "at");
		dp = fopen("director_log", "at");
		ap = fopen("actor_log", "at");
		input = (char*)malloc(30);
		printf("(movie) ");
		gets(input);
		commands = strtok(input, " ");
		mda = strtok(NULL, " ");
		if (mda == 0) {
			printf("@@ Please input the option!\n\n");
			free(input);
			continue;
		}
		if (strcmp(commands, "add") == 0) {
			add(mda);

		}
		free(input);
	}

	return 0;
}

void add(char* mda) {
	char* actorCheck, *actorArray, *titleArray, *titleCheck;
	char* YorN;
	Movie* ifSameM;
	Director* ifSameD;
	Actor* ifSameA;
	if (strcmp(mda, "m") == 0) {
		++MovieSerialNumber;
		movieNew = (Movie*)malloc(sizeof(Movie));
		movieNew->actor = movieNew->actorNew = movieNew->actorTail = movieNew->actorCur = NULL;
		actorArray = (char*)malloc(255);
		movieNew->serialNumber = MovieSerialNumber;
		printf("title > ");
		movieNew->title = (singleData*)malloc(sizeof(singleData));
		movieNew->title->name = (char *)malloc(30);
		gets(movieNew->title->name);
		printf("genre > ");
		movieNew->genre = (singleData*)malloc(sizeof(singleData));
		movieNew->genre->name = (char *)malloc(30);
		gets(movieNew->genre->name);
		printf("director > ");
		movieNew->director = (singleData*)malloc(sizeof(singleData));
		movieNew->director->name = (char *)malloc(30);
		gets(movieNew->director->name);
		printf("year > ");
		scanf("%d", &(movieNew->year));
		while (getchar() != '\n');
		printf("run time > ");
		scanf("%d", &(movieNew->runTime));
		while (getchar() != '\n');
		printf("actors > ");
		gets(actorArray);

		movieNew->next = NULL;

		movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
		movieNew->actorNew->name = (char *)malloc(30);
		strcpy(movieNew->actorNew->name, strtok(actorArray, ","));

		movieNew->actorNew->next = NULL;

		movieNew->actor = movieNew->actorNew;
		movieNew->actorTail = movieNew->actorNew;

		while (1) {

			actorCheck = strtok(NULL, ",");

			if (actorCheck == 0) { break; }
			else if (*actorCheck == ' ') { ++actorCheck; }

			movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
			movieNew->actorNew->name = (char *)malloc(30);
			strcpy(movieNew->actorNew->name, actorCheck);
			movieNew->actorNew->next = NULL;

			movieNew->actorTail->next = movieNew->actorNew;
			movieNew->actorTail = movieNew->actorNew;
		}


		ifSameM = (Movie*)addSameMovie();
		if (ifSameM != NULL) {
			printf("@@ You have the same record in movie list.\n");
			printf("%d:%s:%s:%s:%d:%d:", ifSameM->serialNumber, ifSameM->title->name, ifSameM->genre->name, ifSameM->director->name, ifSameM->year, ifSameM->runTime);

			ifSameM->actorCur = ifSameM->actor;

			printf("%s", ifSameM->actorCur->name);

			while (ifSameM->actorCur->next != NULL)
			{
				ifSameM->actorCur = ifSameM->actorCur->next;
				printf(", %s", ifSameM->actorCur->name);
			}

			printf("\n");
			printf("@@ Do you want to add any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				printf("\n");
				free(actorArray);
				free(YorN);
				--MovieSerialNumber;
				return;
			}
			else {

				if (movie == NULL)
					movie = movieNew;
				else
					movieTail->next = movieNew;

				movieTail = movieNew;

				fprintf(mp, "add:%d:%s:%s:%s:%d:%d:", movieNew->serialNumber, changeColon(movieNew->title->name), changeColon(movieNew->genre->name), changeColon(movieNew->director->name), movieNew->year, movieNew->runTime);

				movieNew->actorCur = movieNew->actor;

				fprintf(mp, "%s", changeColon(movieNew->actorCur->name));

				while (movieNew->actorCur->next != NULL)
				{
					movieNew->actorCur = movieNew->actorCur->next;
					fprintf(mp, ", %s", changeColon(movieNew->actorCur->name));
				}

				fprintf(mp, "\n");
				linkAnotherMovie();
				linkAnotherDirector();
				linkAnotherActor();
				puts("@@ Done");
				free(actorArray);
				free(YorN);
			}
		}
		else {

			if (movie == NULL)
				movie = movieNew;
			else
				movieTail->next = movieNew;

			movieTail = movieNew;

			fprintf(mp, "add:%d:%s:%s:%s:%d:%d:", movieNew->serialNumber, changeColon(movieNew->title->name), changeColon(movieNew->genre->name), changeColon(movieNew->director->name), movieNew->year, movieNew->runTime);

			movieNew->actorCur = movieNew->actor;

			fprintf(mp, "%s", changeColon(movieNew->actorCur->name));

			while (movieNew->actorCur->next != NULL)
			{
				movieNew->actorCur = movieNew->actorCur->next;
				fprintf(mp, ", %s", changeColon(movieNew->actorCur->name));
			}

			fprintf(mp, "\n");
			linkAnotherMovie();
			linkAnotherDirector();
			linkAnotherActor();
			puts("@@ Done");
			free(actorArray);
		}
		fclose(mp);
	}
	if (strcmp(mda, "d") == 0) {
		++DirectorSerialNumber;
		directorNew = (Director*)malloc(sizeof(Director));
		directorNew->title = directorNew->titleNew = directorNew->titleTail = directorNew->titleCur = NULL;
		titleArray = (char*)malloc(255);
		directorNew->serialNumber = DirectorSerialNumber;
		printf("director > ");
		directorNew->director = (singleData*)malloc(sizeof(singleData));
		directorNew->director->name = (char *)malloc(30);
		gets(directorNew->director->name);
		printf("sex > ");
		scanf("%c", &(directorNew->sex));
		while (getchar() != '\n');
		printf("birth > ");
		directorNew->birth = (singleData*)malloc(sizeof(singleData));
		directorNew->birth->name = (char *)malloc(30);
		gets(directorNew->birth->name);
		printf("titles > ");
		gets(titleArray);

		directorNew->next = NULL;

		directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
		directorNew->titleNew->name = (char *)malloc(30);
		strcpy(directorNew->titleNew->name, strtok(titleArray, ","));

		directorNew->titleNew->next = NULL;

		directorNew->title = directorNew->titleNew;
		directorNew->titleTail = directorNew->titleNew;

		while (1) {

			titleCheck = strtok(NULL, ",");

			if (titleCheck == 0) { break; }
			else if (*titleCheck == ' ') { ++titleCheck; }

			directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
			directorNew->titleNew->name = (char *)malloc(30);
			strcpy(directorNew->titleNew->name, titleCheck);
			directorNew->titleNew->next = NULL;

			directorNew->titleTail->next = directorNew->titleNew;
			directorNew->titleTail = directorNew->titleNew;
		}


		ifSameD = (Director*)addSameDirector();
		if (ifSameD != NULL) {
			printf("@@ You have the same record in director list.\n");
			printf("%d:%s:%c:%s:", ifSameD->serialNumber, ifSameD->director->name, ifSameD->sex, ifSameD->birth->name);

			ifSameD->titleCur = ifSameD->title;

			printf("%s", ifSameD->titleCur->name);

			while (ifSameD->titleCur->next != NULL)
			{
				ifSameD->titleCur = ifSameD->titleCur->next;
				printf(", %s", ifSameD->titleCur->name);
			}

			printf("\n");
			printf("@@ Do you want to add any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				printf("\n");
				free(titleArray);
				free(YorN);
				--DirectorSerialNumber;
				return;
			}
			else {

				if (director == NULL)
					director = directorNew;
				else
					directorTail->next = directorNew;

				directorTail = directorNew;

				fprintf(dp, "add:%d:%s:%c:%s:", directorNew->serialNumber, changeColon(directorNew->director->name), directorNew->sex, changeColon(directorNew->birth->name));

				directorNew->titleCur = directorNew->title;

				fprintf(dp, "%s", changeColon(directorNew->titleCur->name));

				while (directorNew->titleCur->next != NULL)
				{
					directorNew->titleCur = directorNew->titleCur->next;
					fprintf(dp, ", %s", changeColon(directorNew->titleCur->name));
				}

				fprintf(dp, "\n");
				linkAnotherMovie();
				linkAnotherDirector();
				linkAnotherActor();
				puts("@@ Done");
				free(titleArray);
				free(YorN);
			}
		}
		else {

			if (director == NULL)
				director = directorNew;
			else
				directorTail->next = directorNew;

			directorTail = directorNew;

			fprintf(dp, "add:%d:%s:%c:%s:", directorNew->serialNumber, changeColon(directorNew->director->name), directorNew->sex, changeColon(directorNew->birth->name));

			directorNew->titleCur = directorNew->title;

			fprintf(dp, "%s", changeColon(directorNew->titleCur->name));

			while (directorNew->titleCur->next != NULL)
			{
				directorNew->titleCur = directorNew->titleCur->next;
				fprintf(dp, ", %s", changeColon(directorNew->titleCur->name));
			}

			fprintf(dp, "\n");
			linkAnotherMovie();
			linkAnotherDirector();
			linkAnotherActor();
			puts("@@ Done");
			free(titleArray);
		}
		fclose(dp);
	}
	if (strcmp(mda, "a") == 0) {
		++ActorSerialNumber;
		actorNew = (Actor*)malloc(sizeof(Actor));
		actorNew->title = actorNew->titleNew = actorNew->titleTail = actorNew->titleCur = NULL;
		titleArray = (char*)malloc(255);
		actorNew->serialNumber = ActorSerialNumber;
		printf("actor > ");
		actorNew->actor = (singleData*)malloc(sizeof(singleData));
		actorNew->actor->name = (char *)malloc(30);
		gets(actorNew->actor->name);
		printf("sex > ");
		scanf("%c", &(actorNew->sex));
		while (getchar() != '\n');
		printf("birth > ");
		actorNew->birth = (singleData*)malloc(sizeof(singleData));
		actorNew->birth->name = (char *)malloc(30);
		gets(actorNew->birth->name);
		printf("titles > ");
		gets(titleArray);

		actorNew->next = NULL;

		actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
		actorNew->titleNew->name = (char *)malloc(30);
		strcpy(actorNew->titleNew->name, strtok(titleArray, ","));

		actorNew->titleNew->next = NULL;

		actorNew->title = actorNew->titleNew;
		actorNew->titleTail = actorNew->titleNew;

		while (1) {

			titleCheck = strtok(NULL, ",");

			if (titleCheck == 0) { break; }
			else if (*titleCheck == ' ') { ++titleCheck; }

			actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
			actorNew->titleNew->name = (char *)malloc(30);
			strcpy(actorNew->titleNew->name, titleCheck);
			actorNew->titleNew->next = NULL;

			actorNew->titleTail->next = actorNew->titleNew;
			actorNew->titleTail = actorNew->titleNew;
		}


		ifSameA = (Actor*)addSameActor();
		if (ifSameA != NULL) {
			printf("@@ You have the same record in actor list.\n");
			printf("%d:%s:%c:%s:", ifSameA->serialNumber, ifSameA->actor->name, ifSameA->sex, ifSameA->birth->name);

			ifSameA->titleCur = ifSameA->title;

			printf("%s", ifSameA->titleCur->name);

			while (ifSameA->titleCur->next != NULL)
			{
				ifSameA->titleCur = ifSameA->titleCur->next;
				printf(", %s", ifSameA->titleCur->name);
			}

			printf("\n");
			printf("@@ Do you want to add any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				printf("\n");
				free(titleArray);
				free(YorN);
				--ActorSerialNumber;
				return;
			}
			else {

				if (actor == NULL)
					actor = actorNew;
				else
					actorTail->next = actorNew;

				actorTail = actorNew;

				fprintf(ap, "add:%d:%s:%c:%s:", actorNew->serialNumber, changeColon(actorNew->actor->name), actorNew->sex, changeColon(actorNew->birth->name));

				actorNew->titleCur = actorNew->title;

				fprintf(ap, "%s", changeColon(actorNew->titleCur->name));

				while (actorNew->titleCur->next != NULL)
				{
					actorNew->titleCur = actorNew->titleCur->next;
					fprintf(ap, ", %s", changeColon(actorNew->titleCur->name));
				}

				fprintf(ap, "\n");
				linkAnotherMovie();
				linkAnotherDirector();
				linkAnotherActor();
				puts("@@ Done");
				free(titleArray);
				free(YorN);
			}
		}
		else {

			if (actor == NULL)
				actor = actorNew;
			else
				actorTail->next = actorNew;

			actorTail = actorNew;

			fprintf(ap, "add:%d:%s:%c:%s:", actorNew->serialNumber, changeColon(actorNew->actor->name), actorNew->sex, changeColon(actorNew->birth->name));

			actorNew->titleCur = actorNew->title;

			fprintf(ap, "%s", changeColon(actorNew->titleCur->name));

			while (actorNew->titleCur->next != NULL)
			{
				actorNew->titleCur = actorNew->titleCur->next;
				fprintf(ap, ", %s", changeColon(actorNew->titleCur->name));
			}

			fprintf(ap, "\n");
			puts("@@ Done");
			free(titleArray);
		}
		fclose(ap);
	}


}

void loadMovielogs(void) {
	int fileSize;
	mp = fopen("movie_log", "rt");
	if (mp == NULL)
		return;
	fseek(mp, 0L, SEEK_END);
	fileSize = ftell(mp);
	if (fileSize == 0) { return; }
	rewind(mp);
	char* keyword;
	char *check, *actorCheck;
	while (1) {
		if (ftell(mp) == fileSize) { break; }
		keyword = (char*)malloc(255);
		fgets(keyword, 255, mp);
		strtok(keyword, "\n");
		check = strtok(keyword, ":");
		if (strcmp(check, "add") == 0) {
			movieNew = (Movie*)malloc(sizeof(Movie));
			movieNew->actor = movieNew->actorNew = movieNew->actorTail = movieNew->actorCur = NULL;
			check = strtok(NULL, ":");
			movieNew->serialNumber = (int)atoi(check);
			MovieSerialNumber = (movieNew->serialNumber);

			movieNew->title = (singleData*)malloc(sizeof(singleData));
			movieNew->title->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(movieNew->title->name, check);
			strcpy(movieNew->title->name, changeLogColon(movieNew->title->name));

			movieNew->genre = (singleData*)malloc(sizeof(singleData));
			movieNew->genre->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(movieNew->genre->name, check);
			strcpy(movieNew->genre->name, changeLogColon(movieNew->genre->name));

			movieNew->director = (singleData*)malloc(sizeof(singleData));
			movieNew->director->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(movieNew->director->name, check);
			strcpy(movieNew->director->name, changeLogColon(movieNew->director->name));

			check = strtok(NULL, ":");
			movieNew->year = (int)atoi(check);
			check = strtok(NULL, ":");
			movieNew->runTime = (int)atoi(check);

			movieNew->next = NULL;

			movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
			movieNew->actorNew->name = (char *)malloc(30);
			strcpy(movieNew->actorNew->name, strtok(NULL, ","));
			strcpy(movieNew->actorNew->name, changeLogColon(movieNew->actorNew->name));

			movieNew->actor = movieNew->actorNew;
			movieNew->actorTail = movieNew->actorNew;

			while (1)
			{
				actorCheck = strtok(NULL, ",");

				if (actorCheck == 0) { break; }
				else if (*actorCheck == ' ') { ++actorCheck; }

				movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
				movieNew->actorNew->name = (char *)malloc(30);
				strcpy(movieNew->actorNew->name, actorCheck);
				strcpy(movieNew->actorNew->name, changeLogColon(movieNew->actorNew->name));


				movieNew->actorNew->next = NULL;

				movieNew->actorTail->next = movieNew->actorNew;
				movieNew->actorTail = movieNew->actorNew;
			}

			if (movie == NULL)
				movie = movieNew;
			else
				movieTail->next = movieNew;

			movieTail = movieNew;
		}
		free(keyword);
	}
	fclose(mp);
}

void loadDirectorlogs(void) {
	int fileSize;
	dp = fopen("director_log", "rt");
	if (dp == NULL)
		return;
	fseek(dp, 0L, SEEK_END);
	fileSize = ftell(dp);
	if (fileSize == 0) { return; }
	rewind(dp);
	char* keyword;
	char *check, *titleCheck;
	while (1) {
		if (ftell(dp) == fileSize) { break; }
		keyword = (char*)malloc(255);
		fgets(keyword, 255, dp);
		strtok(keyword, "\n");
		check = strtok(keyword, ":");

		if (strcmp(check, "add") == 0) {

			directorNew = (Director*)malloc(sizeof(Director));
			directorNew->title = directorNew->titleNew = directorNew->titleTail = directorNew->titleCur = NULL;
			check = strtok(NULL, ":");
			directorNew->serialNumber = (int)atoi(check);
			DirectorSerialNumber = (directorNew->serialNumber);

			directorNew->director = (singleData*)malloc(sizeof(singleData));
			directorNew->director->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(directorNew->director->name, check);
			strcpy(directorNew->director->name, changeLogColon(directorNew->director->name));

			check = strtok(NULL, ":");
			directorNew->sex = *check;

			directorNew->birth = (singleData*)malloc(sizeof(singleData));
			directorNew->birth->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(directorNew->birth->name, check);
			strcpy(directorNew->birth->name, changeLogColon(directorNew->birth->name));

			directorNew->next = NULL;

			directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
			directorNew->titleNew->name = (char *)malloc(30);
			strcpy(directorNew->titleNew->name, strtok(NULL, ","));
			strcpy(directorNew->titleNew->name, changeLogColon(directorNew->titleNew->name));

			directorNew->title = directorNew->titleNew;
			directorNew->titleTail = directorNew->titleNew;

			while (1)
			{
				titleCheck = strtok(NULL, ",");

				if (titleCheck == 0) { break; }
				else if (*titleCheck == ' ') { ++titleCheck; }

				directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				directorNew->titleNew->name = (char *)malloc(30);
				strcpy(directorNew->titleNew->name, titleCheck);
				strcpy(directorNew->titleNew->name, changeLogColon(directorNew->titleNew->name));


				directorNew->titleNew->next = NULL;

				directorNew->titleTail->next = directorNew->titleNew;
				directorNew->titleTail = directorNew->titleNew;
			}

			if (director == NULL)
				director = directorNew;
			else
				directorTail->next = directorNew;

			directorTail = directorNew;
		}
		free(keyword);
	}
	fclose(dp);
}
void loadActorlogs(void) {
	int fileSize;
	ap = fopen("actor_log", "rt");
	if (ap == NULL)
		return;
	fseek(ap, 0L, SEEK_END);
	fileSize = ftell(ap);
	if (fileSize == 0) { return; }
	rewind(ap);
	char* keyword;
	char *check, *titleCheck;
	while (1) {
		if (ftell(ap) == fileSize) { break; }
		keyword = (char*)malloc(255);
		fgets(keyword, 255, ap);
		strtok(keyword, "\n");
		check = strtok(keyword, ":");

		if (strcmp(check, "add") == 0) {

			actorNew = (Actor*)malloc(sizeof(Actor));
			actorNew->title = actorNew->titleNew = actorNew->titleTail = actorNew->titleCur = NULL;
			check = strtok(NULL, ":");
			actorNew->serialNumber = (int)atoi(check);
			ActorSerialNumber = (actorNew->serialNumber);

			actorNew->actor = (singleData*)malloc(sizeof(singleData));
			actorNew->actor->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(actorNew->actor->name, check);
			strcpy(actorNew->actor->name, changeLogColon(actorNew->actor->name));

			check = strtok(NULL, ":");
			actorNew->sex = *check;

			actorNew->birth = (singleData*)malloc(sizeof(singleData));
			actorNew->birth->name = (char *)malloc(30);
			check = strtok(NULL, ":");
			strcpy(actorNew->birth->name, check);
			strcpy(actorNew->birth->name, changeLogColon(actorNew->birth->name));

			actorNew->next = NULL;

			actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
			actorNew->titleNew->name = (char *)malloc(30);
			strcpy(actorNew->titleNew->name, strtok(NULL, ","));
			strcpy(actorNew->titleNew->name, changeLogColon(actorNew->titleNew->name));

			actorNew->title = actorNew->titleNew;
			actorNew->titleTail = actorNew->titleNew;

			while (1)
			{
				titleCheck = strtok(NULL, ",");

				if (titleCheck == 0) { break; }
				else if (*titleCheck == ' ') { ++titleCheck; }

				actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				actorNew->titleNew->name = (char *)malloc(30);
				strcpy(actorNew->titleNew->name, titleCheck);
				strcpy(actorNew->titleNew->name, changeLogColon(actorNew->titleNew->name));


				actorNew->titleNew->next = NULL;

				actorNew->titleTail->next = actorNew->titleNew;
				actorNew->titleTail = actorNew->titleNew;
			}

			if (actor == NULL)
				actor = actorNew;
			else
				actorTail->next = actorNew;

			actorTail = actorNew;
		}
		free(keyword);
	}
	fclose(ap);
}


Movie* addSameMovie(void) {
	int cnt = 0, actorCurCnt = 0, actorNewCnt = 0;
	if (movie == NULL)
	{
		return NULL;
	}

	movieCur = movie;

	if (movieCur->year != movieNew->year)
		++cnt;
	else if (movieCur->runTime != movieNew->runTime)
		++cnt;
	else if (strcmp(movieCur->title->name, movieNew->title->name) != 0)
		++cnt;
	else if (strcmp(movieCur->genre->name, movieNew->genre->name) != 0)
		++cnt;
	else if (strcmp(movieCur->director->name, movieNew->director->name) != 0)
		++cnt;

	movieCur->actorCur = movieCur->actor;
	movieNew->actorCur = movieNew->actor;

	if (movieCur->actorCur->next != NULL)
		++actorCurCnt;
	movieCur->actorCur = movieCur->actorCur->next;
	if (actorCurCnt > 0) {
		while (movieCur->actorCur->next != NULL) {
			movieCur->actorCur = movieCur->actorCur->next;
			++actorCurCnt;
		}
	}
	if (movieNew->actorCur->next != NULL)
		++actorNewCnt;
	movieNew->actorCur = movieNew->actorCur->next;
	if (actorNewCnt > 0) {
		while (movieNew->actorCur->next != NULL) {
			movieNew->actorCur = movieNew->actorCur->next;
			++actorNewCnt;
		}
	}


	if (actorCurCnt == actorNewCnt) {

		movieCur->actorCur = movieCur->actor;
		movieNew->actorCur = movieNew->actor;

		if (strcmp(movieCur->actorCur->name, movieNew->actorCur->name) != 0)
			++cnt;

		while (movieCur->actorCur->next != NULL) {
			movieCur->actorCur = movieCur->actorCur->next;
			movieNew->actorCur = movieNew->actorCur->next;
			if (strcmp(movieCur->actorCur->name, movieNew->actorCur->name) != 0)
				++cnt;
		}
		if (cnt == 0)
			return movieCur;
	}
	else {

		actorCurCnt = actorNewCnt = 0;
		cnt = 0;
		while (movieCur->next != NULL)
		{
			movieCur = movieCur->next;

			if (movieCur->year != movieNew->year)
				++cnt;
			else if (movieCur->runTime != movieNew->runTime)
				++cnt;
			else if (strcmp(movieCur->title->name, movieNew->title->name) != 0)
				++cnt;
			else if (strcmp(movieCur->genre->name, movieNew->genre->name) != 0)
				++cnt;
			else if (strcmp(movieCur->director->name, movieNew->director->name) != 0)
				++cnt;

			movieCur->actorCur = movieCur->actor;
			movieNew->actorCur = movieNew->actor;

			if (movieCur->actorCur->next != NULL)
				++actorCurCnt;
			movieCur->actorCur = movieCur->actorCur->next;
			if (actorCurCnt > 0) {
				while (movieCur->actorCur->next != NULL) {
					movieCur->actorCur = movieCur->actorCur->next;
					++actorCurCnt;
				}
			}
			if (movieNew->actorCur->next != NULL)
				++actorNewCnt;
			movieNew->actorCur = movieNew->actorCur->next;
			if (actorNewCnt > 0) {
				while (movieNew->actorCur->next != NULL) {
					movieNew->actorCur = movieNew->actorCur->next;
					++actorNewCnt;
				}
			}

			if (actorCurCnt == actorNewCnt) {
				movieCur->actorCur = movieCur->actor;
				movieNew->actorCur = movieNew->actor;

				if (strcmp(movieCur->actorCur->name, movieNew->actorCur->name) != 0)
					++cnt;

				while (movieCur->actorCur->next != NULL) {
					movieCur->actorCur = movieCur->actorCur->next;
					movieNew->actorCur = movieNew->actorCur->next;
					if (strcmp(movieCur->actorCur->name, movieNew->actorCur->name) != 0)
						++cnt;
				}
				if (cnt == 0)
					return movieCur;
				else {
					actorCurCnt = actorNewCnt = 0;
					cnt = 0;
				}
			}

		}
		return NULL;
	}
}

Director* addSameDirector(void) {
	int cnt = 0, titleCurCnt = 0, titleNewCnt = 0;
	if (director == NULL)
	{
		return NULL;
	}

	directorCur = director;

	if (directorCur->sex != directorNew->sex)
		++cnt;
	else if (strcmp(directorCur->director->name, directorNew->director->name) != 0)
		++cnt;
	else if (strcmp(directorCur->birth->name, directorNew->birth->name) != 0)
		++cnt;

	directorCur->titleCur = directorCur->title;
	directorNew->titleCur = directorNew->title;

	if (directorCur->titleCur->next != NULL)
		++titleCurCnt;
	directorCur->titleCur = directorCur->titleCur->next;
	if (titleCurCnt > 0) {
		while (directorCur->titleCur->next != NULL) {
			directorCur->titleCur = directorCur->titleCur->next;
			++titleCurCnt;
		}
	}
	if (directorNew->titleCur->next != NULL)
		++titleNewCnt;
	directorNew->titleCur = directorNew->titleCur->next;
	if (titleNewCnt > 0) {
		while (directorNew->titleCur->next != NULL) {
			directorNew->titleCur = directorNew->titleCur->next;
			++titleNewCnt;
		}
	}

	if (titleCurCnt == titleNewCnt) {

		directorCur->titleCur = directorCur->title;
		directorNew->titleCur = directorNew->title;

		if (strcmp(directorCur->titleCur->name, directorNew->titleCur->name) != 0)
			++cnt;

		while (directorCur->titleCur->next != NULL) {
			directorCur->titleCur = directorCur->titleCur->next;
			directorNew->titleCur = directorNew->titleCur->next;
			if (strcmp(directorCur->titleCur->name, directorNew->titleCur->name) != 0)
				++cnt;
		}

		if (cnt == 0)
			return directorCur;
	}
	else {

		titleCurCnt = titleNewCnt = 0;
		cnt = 0;
		while (directorCur->next != NULL)
		{
			directorCur = directorCur->next;

			if (directorCur->sex != directorNew->sex)
				++cnt;
			else if (strcmp(directorCur->director->name, directorNew->director->name) != 0)
				++cnt;
			else if (strcmp(directorCur->birth->name, directorNew->birth->name) != 0)
				++cnt;

			directorCur->titleCur = directorCur->title;
			directorNew->titleCur = directorNew->title;

			if (directorCur->titleCur->next != NULL)
				++titleCurCnt;
			directorCur->titleCur = directorCur->titleCur->next;
			if (titleCurCnt > 0) {
				while (directorCur->titleCur->next != NULL) {
					directorCur->titleCur = directorCur->titleCur->next;
					++titleCurCnt;
				}
			}
			if (directorNew->titleCur->next != NULL)
				++titleNewCnt;
			directorNew->titleCur = directorNew->titleCur->next;
			if (titleNewCnt > 0) {
				while (directorNew->titleCur->next != NULL) {
					directorNew->titleCur = directorNew->titleCur->next;
					++titleNewCnt;
				}
			}

			if (titleCurCnt == titleNewCnt) {
				directorCur->titleCur = directorCur->title;
				directorNew->titleCur = directorNew->title;

				if (strcmp(directorCur->titleCur->name, directorNew->titleCur->name) != 0)
					++cnt;
				while (directorCur->titleCur->next != NULL) {
					directorCur->titleCur = directorCur->titleCur->next;
					directorNew->titleCur = directorNew->titleCur->next;
					if (strcmp(directorCur->titleCur->name, directorNew->titleCur->name) != 0)
						++cnt;
				}

				if (cnt == 0)
					return directorCur;
				else {
					titleCurCnt = titleNewCnt = 0;
					cnt = 0;
				}
			}

		}
		return NULL;
	}
}
Actor* addSameActor(void) {
	int cnt = 0, titleCurCnt = 0, titleNewCnt = 0;
	if (actor == NULL)
	{
		return NULL;
	}

	actorCur = actor;

	if (actorCur->sex != actorNew->sex)
		++cnt;
	else if (strcmp(actorCur->actor->name, actorNew->actor->name) != 0)
		++cnt;
	else if (strcmp(actorCur->birth->name, actorNew->birth->name) != 0)
		++cnt;

	actorCur->titleCur = actorCur->title;
	actorNew->titleCur = actorNew->title;

	if (actorCur->titleCur->next != NULL)
		++titleCurCnt;
	actorCur->titleCur = actorCur->titleCur->next;
	if (titleCurCnt > 0) {
		while (actorCur->titleCur->next != NULL) {
			actorCur->titleCur = actorCur->titleCur->next;
			++titleCurCnt;
		}
	}
	if (actorNew->titleCur->next != NULL)
		++titleNewCnt;
	actorNew->titleCur = actorNew->titleCur->next;
	if (titleNewCnt > 0) {
		while (actorNew->titleCur->next != NULL) {
			actorNew->titleCur = actorNew->titleCur->next;
			++titleNewCnt;
		}
	}

	if (titleCurCnt == titleNewCnt) {

		actorCur->titleCur = actorCur->title;
		actorNew->titleCur = actorNew->title;

		if (strcmp(actorCur->titleCur->name, actorNew->titleCur->name) != 0)
			++cnt;

		while (actorCur->titleCur->next != NULL) {
			actorCur->titleCur = actorCur->titleCur->next;
			actorNew->titleCur = actorNew->titleCur->next;
			if (strcmp(actorCur->titleCur->name, actorNew->titleCur->name) != 0)
				++cnt;
		}

		if (cnt == 0)
			return actorCur;
	}
	else {

		titleCurCnt = titleNewCnt = 0;
		cnt = 0;
		while (actorCur->next != NULL)
		{
			actorCur = actorCur->next;

			if (actorCur->sex != actorNew->sex)
				++cnt;
			else if (strcmp(actorCur->actor->name, actorNew->actor->name) != 0)
				++cnt;
			else if (strcmp(actorCur->birth->name, actorNew->birth->name) != 0)
				++cnt;

			actorCur->titleCur = actorCur->title;
			actorNew->titleCur = actorNew->title;

			if (actorCur->titleCur->next != NULL)
				++titleCurCnt;
			actorCur->titleCur = actorCur->titleCur->next;
			if (titleCurCnt > 0) {
				while (actorCur->titleCur->next != NULL) {
					actorCur->titleCur = actorCur->titleCur->next;
					++titleCurCnt;
				}
			}
			if (actorNew->titleCur->next != NULL)
				++titleNewCnt;
			actorNew->titleCur = actorNew->titleCur->next;
			if (titleNewCnt > 0) {
				while (actorNew->titleCur->next != NULL) {
					actorNew->titleCur = actorNew->titleCur->next;
					++titleNewCnt;
				}
			}

			if (titleCurCnt == titleNewCnt) {
				actorCur->titleCur = actorCur->title;
				actorNew->titleCur = actorNew->title;

				if (strcmp(actorCur->titleCur->name, actorNew->titleCur->name) != 0)
					++cnt;
				while (actorCur->titleCur->next != NULL) {
					actorCur->titleCur = actorCur->titleCur->next;
					actorNew->titleCur = actorNew->titleCur->next;
					if (strcmp(actorCur->titleCur->name, actorNew->titleCur->name) != 0)
						++cnt;
				}

				if (cnt == 0)
					return actorCur;
				else {
					titleCurCnt = titleNewCnt = 0;
					cnt = 0;
				}
			}

		}
		return NULL;
	}
}



char* changeColon(char* ifColon) {
	char* tmp = (char*)malloc(30);
	int len = strlen(ifColon), check = 0, arrTmp;
	strcpy(tmp, ifColon);
	for (int i = 0; i < len; ++i) {
		if (*(tmp + i) == ':') {
			check = i;
		}
	}
	if (check != 0) {
		for (int i = len + 1; i > check; --i) {
			*(tmp + i + 2) = *(tmp + i);
		}
		*(tmp + check) = '?';
		*(tmp + check + 1) = '?';
		*(tmp + check + 2) = ';';
		return tmp;
	}
	else {
		free(tmp);
		return ifColon;
	}
}

char* changeLogColon(char* ifColon) {
	char* tmp = (char*)malloc(30);
	int len = strlen(ifColon), check = 0;
	strcpy(tmp, ifColon);
	for (int i = 0; i < len; ++i)
		if ((*(tmp + i) == ';') && (*(tmp + i - 1) == '?') && (*(tmp + i - 2) == '?'))
			check = i;
	if (check != 0) {

		for (int i = check + 1; i <= len + 1; ++i) {
			*(tmp + i - 2) = *(tmp + i);
		}
		*(tmp + check - 2) = ':';
		return tmp;
	}
	else {
		free(tmp);
		return ifColon;
	}
}
void linkAnotherMovie(void) {
	int actorCurCnt = 0;
	if (movie == NULL)
	{
		return;
	}

	movieCur = movie;
	directorCur = director;
	actorCur = actor;

	if (strcmp(movieCur->director->name, directorCur->director->name) == 0)
		movieCur->director->linkAnotherD = directorCur;
	else {
		while (directorCur->next != NULL) {
			directorCur = directorCur->next;
			if (strcmp(movieCur->director->name, directorCur->director->name) == 0)
				movieCur->director->linkAnotherD = directorCur;
		}
	}
	directorCur = director;

	movieCur->actorCur = movieCur->actor;

	if (movieCur->actorCur->next != NULL)
		++actorCurCnt;
	movieCur->actorCur = movieCur->actorCur->next;
	if (actorCurCnt > 0) {
		while (movieCur->actorCur->next != NULL) {
			movieCur->actorCur = movieCur->actorCur->next;
			++actorCurCnt;
		}
	}

	movieCur->actorCur = movieCur->actor;


	for (int i = 0; i <= actorCurCnt; ++i) {
		if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0)
			movieCur->actorCur->linkAnotherA = actorCur;
		else {
			while (actorCur->next != NULL) {
				actorCur = actorCur->next;
				if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0)
					movieCur->actorCur->linkAnotherA = actorCur;
			}
		}
		movieCur->actorCur = movieCur->actorCur->next;
		actorCur = actor;
	}


	movieCur = movie;
	directorCur = director;
	actorCur = actor;
	actorCurCnt = 0;

	while (movieCur->next != NULL)
	{
		movieCur = movieCur->next;

		if (strcmp(movieCur->director->name, directorCur->director->name) == 0)
			movieCur->director->linkAnotherD = directorCur;
		else {
			while (directorCur->next != NULL) {
				directorCur = directorCur->next;
				if (strcmp(movieCur->director->name, directorCur->director->name) == 0)
					movieCur->director->linkAnotherD = directorCur;
			}
		}
		directorCur = director;



		movieCur->actorCur = movieCur->actor;

		if (movieCur->actorCur->next != NULL)
			++actorCurCnt;
		movieCur->actorCur = movieCur->actorCur->next;
		if (actorCurCnt > 0) {
			while (movieCur->actorCur->next != NULL) {
				movieCur->actorCur = movieCur->actorCur->next;
				++actorCurCnt;
			}
		}
		movieCur->actorCur = movieCur->actor;


		for (int i = 0; i <= actorCurCnt; ++i) {
			if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0)
				movieCur->actorCur->linkAnotherA = actorCur;
			else {
				while (actorCur->next != NULL) {
					actorCur = actorCur->next;
					if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0)
						movieCur->actorCur->linkAnotherA = actorCur;
				}
			}
			movieCur->actorCur = movieCur->actorCur->next;
			actorCur = actor;
		}

		actorCurCnt = 0;

	}

}
void linkAnotherDirector(void) {
	int titleCurCnt = 0;
	if (director == NULL)
	{
		return;
	}

	movieCur = movie;
	directorCur = director;

	directorCur->titleCur = directorCur->title;

	if (directorCur->titleCur->next != NULL)
		++titleCurCnt;
	directorCur->titleCur = directorCur->titleCur->next;
	if (titleCurCnt > 0) {
		while (directorCur->titleCur->next != NULL) {
			directorCur->titleCur = directorCur->titleCur->next;
			++titleCurCnt;
		}
	}

	directorCur->titleCur = directorCur->title;


	for (int i = 0; i <= titleCurCnt; ++i) {
		if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0)
			directorCur->titleCur->linkAnotherM = movieCur;
		else {
			while (movieCur->next != NULL) {
				movieCur = movieCur->next;
				if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0)
					directorCur->titleCur->linkAnotherM = movieCur;
			}
		}
		directorCur->titleCur = directorCur->titleCur->next;
		movieCur = movie;
	}

	movieCur = movie;
	directorCur = director;

	titleCurCnt = 0;

	while (directorCur->next != NULL)
	{
		directorCur = directorCur->next;

		directorCur->titleCur = directorCur->title;

		if (directorCur->titleCur->next != NULL)
			++titleCurCnt;
		directorCur->titleCur = directorCur->titleCur->next;
		if (titleCurCnt > 0) {
			while (directorCur->titleCur->next != NULL) {
				directorCur->titleCur = directorCur->titleCur->next;
				++titleCurCnt;
			}
		}

		directorCur->titleCur = directorCur->title;


		for (int i = 0; i <= titleCurCnt; ++i) {
			if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0)
				directorCur->titleCur->linkAnotherM = movieCur;
			else {
				while (movieCur->next != NULL) {
					movieCur = movieCur->next;
					if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0)
						directorCur->titleCur->linkAnotherM = movieCur;
				}
			}
			directorCur->titleCur = directorCur->titleCur->next;
			movieCur = movie;
		}
		titleCurCnt = 0;
	}
}
void linkAnotherActor(void) {
	int titleCurCnt = 0;
	if (actor == NULL)
	{
		return;
	}

	movieCur = movie;
	actorCur = actor;

	actorCur->titleCur = actorCur->title;

	if (actorCur->titleCur->next != NULL)
		++titleCurCnt;
	actorCur->titleCur = actorCur->titleCur->next;
	if (titleCurCnt > 0) {
		while (actorCur->titleCur->next != NULL) {
			actorCur->titleCur = actorCur->titleCur->next;
			++titleCurCnt;
		}
	}

	actorCur->titleCur = actorCur->title;


	for (int i = 0; i <= titleCurCnt; ++i) {
		if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0)
			actorCur->titleCur->linkAnotherM = movieCur;
		else {
			while (movieCur->next != NULL) {
				movieCur = movieCur->next;
				if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0)
					actorCur->titleCur->linkAnotherM = movieCur;
			}
		}
		actorCur->titleCur = actorCur->titleCur->next;
		movieCur = movie;
	}

	movieCur = movie;
	actorCur = actor;

	titleCurCnt = 0;

	while (actorCur->next != NULL)
	{
		actorCur = actorCur->next;

		actorCur->titleCur = actorCur->title;

		if (actorCur->titleCur->next != NULL)
			++titleCurCnt;
		actorCur->titleCur = actorCur->titleCur->next;
		if (titleCurCnt > 0) {
			while (actorCur->titleCur->next != NULL) {
				actorCur->titleCur = actorCur->titleCur->next;
				++titleCurCnt;
			}
		}

		actorCur->titleCur = actorCur->title;


		for (int i = 0; i <= titleCurCnt; ++i) {
			if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0)
				actorCur->titleCur->linkAnotherM = movieCur;
			else {
				while (movieCur->next != NULL) {
					movieCur = movieCur->next;
					if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0)
						actorCur->titleCur->linkAnotherM = movieCur;
				}
			}
			actorCur->titleCur = actorCur->titleCur->next;
			movieCur = movie;
		}
		titleCurCnt = 0;

	}
}
