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
char* changeColon(char*);
char* changeLogColon(char*);
void linkAnotherMovie(void);
void linkAnotherDirector(void);
void linkAnotherActor(void);
void update(char* mda, char* option, char* num);
void delete(char* mda, char* num);
Movie* addSameMovie(void);
Director* addSameDirector(void);
Actor* addSameActor(void);
Movie* updateSameMovie(void);
Director* updateSameDirector(void);
Actor* updateSameActor(void);
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
	//printf("%s %s %s %s\n",movie->next->title->name,movie->next->genre->name,movie->next->director->name,movie->next->actor->next->name);
	//printf("%s %c %s %d\n", actor->next->actor->name, actor->next->sex, actor->next->birth->name, actor->next->title->next);
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
		else if (strcmp(commands, "update") == 0) {
			option = strtok(NULL, " ");
			num = strtok(NULL, " ");
      if (option == 0 || num == 0) {
        printf("@@ Please input the option!\n\n");
        free(input);
        continue;
      }
			update(mda, option, num);
		}
		else if (strcmp(commands, "delete") == 0) {
			num = strtok(NULL, " ");
      if (num == 0) {
        printf("@@ Please input the option!\n\n");
        free(input);
        continue;
      }
			delete(mda, num);
		}
		free(input);
		linkAnotherMovie();
		linkAnotherDirector();
		linkAnotherActor();

	}

	return 0;
}

void add(char* mda) {
	char* actorCheck, *actorArray, *titleArray, *titleCheck;
	char* YorN;
	Movie* ifSameM = NULL;
	Director* ifSameD = NULL;
	Actor* ifSameA = NULL;
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
	int fileSize, updateNum, deleteNum;
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

			movieNew->actorNew->next = NULL;

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
		else if (strcmp(check, "update") == 0) {
			check = strtok(NULL, ":");//숫자
			updateNum = (int)atoi(check);

			movieCur = movie;
			if (movieCur->serialNumber == updateNum);
			else {
				while (movieCur->next != NULL) {

					movieCur = movieCur->next;
					if (movieCur->serialNumber == updateNum)
						break;
				}
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(movieCur->title->name, check);
				strcpy(movieCur->title->name, changeLogColon(movieCur->title->name));
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(movieCur->genre->name, check);
				strcpy(movieCur->genre->name, changeLogColon(movieCur->genre->name));
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(movieCur->director->name, check);
				strcpy(movieCur->director->name, changeLogColon(movieCur->director->name));
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else
				movieCur->year = (int)atoi(check);
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else
				movieCur->runTime = (int)atoi(check);

			if (strcmp(check + 2, "=") == 0);
			else {
				singleData * delActor = movieCur->actor;
				singleData * delNextActor = movieCur->actor->next;
				free(delActor);
				while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delActor = delNextActor;
					delNextActor = delNextActor->next;
					free(delActor);    // 두 번째 이후의 노드 삭제
				}
				movieCur->actorNew = (singleData*)malloc(sizeof(singleData));
				movieCur->actorNew->name = (char *)malloc(30);
				strcpy(movieCur->actorNew->name, strtok(NULL, ","));
				strcpy(movieCur->actorNew->name, changeLogColon(movieCur->actorNew->name));
				movieCur->actorNew->next = NULL;

				movieCur->actor = movieCur->actorNew;
				movieCur->actorTail = movieCur->actorNew;
				while (1)
				{
					actorCheck = strtok(NULL, ",");

					if (actorCheck == 0) { break; }
					else if (*actorCheck == ' ') { ++actorCheck; }

					movieCur->actorNew = (singleData*)malloc(sizeof(singleData));
					movieCur->actorNew->name = (char *)malloc(30);
					strcpy(movieCur->actorNew->name, actorCheck);
					strcpy(movieCur->actorNew->name, changeLogColon(movieCur->actorNew->name));


					movieCur->actorNew->next = NULL;

					movieCur->actorTail->next = movieCur->actorNew;
					movieCur->actorTail = movieCur->actorNew;
				}
			}
		}
		else if (strcmp(check, "delete") == 0) {
			check = strtok(NULL, ":");//숫자
			deleteNum = (int)atoi(check);
			Movie* movieBefore = NULL;
			movieCur = movie;
			if (movieCur->serialNumber == deleteNum);
			else {
				while (movieCur->next != NULL) {

					movieCur = movieCur->next;
					if (movieCur->serialNumber == deleteNum)
						break;
				}
			}//
			if (movieCur == movieTail && movieCur == movie)
				movieTail = movie = NULL;
			else if (movieCur != movieTail && movieCur == movie)
				movie = movieCur->next;
			else {
				movieBefore = movie;
				if (movieBefore->next->serialNumber == deleteNum);
				else {
					while (movieBefore->next != NULL) {

						movieBefore = movieBefore->next;
						if (movieBefore->next->serialNumber == deleteNum)
							break;
					}
				}//
				movieBefore->next = movieCur->next;
			}
			//
			singleData * delActor = movieCur->actor;
			singleData * delNextActor = movieCur->actor->next;
			free(delActor);
			while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				delActor = delNextActor;
				delNextActor = delNextActor->next;
				free(delActor);    // 두 번째 이후의 노드 삭제
			}
			free(movieCur->title);
			free(movieCur->genre);
			free(movieCur->director);
			free(movieCur);

		}
		free(keyword);
	}
	fclose(mp);
}

void loadDirectorlogs(void) {

	int fileSize, updateNum, deleteNum;
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
			directorNew->titleNew->next = NULL;
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
		else if (strcmp(check, "update") == 0) {

			check = strtok(NULL, ":");//숫자

			updateNum = (int)atoi(check);

			directorCur = director;
			if (directorCur->serialNumber == updateNum);
			else {
				while (directorCur->next != NULL) {

					directorCur = directorCur->next;
					if (directorCur->serialNumber == updateNum)
						break;
				}
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(directorCur->director->name, check);
				strcpy(directorCur->director->name, changeLogColon(directorCur->director->name));
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				directorCur->sex = *check;
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(directorCur->birth->name, check);
				strcpy(directorCur->birth->name, changeLogColon(directorCur->birth->name));
			}

			if (strcmp(check + 2, "=") == 0);
			else {
				singleData * delTitle = directorCur->title;
				singleData * delNextTitle = directorCur->title->next;
				free(delTitle);

				while (delNextTitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delTitle = delNextTitle;
					delNextTitle = delNextTitle->next;
					free(delTitle);    // 두 번째 이후의 노드 삭제
				}
				directorCur->titleNew = (singleData*)malloc(sizeof(singleData));
				directorCur->titleNew->name = (char *)malloc(30);
				strcpy(directorCur->titleNew->name, strtok(NULL, ","));
				strcpy(directorCur->titleNew->name, changeLogColon(directorCur->titleNew->name));
				directorCur->titleNew->next = NULL;


				directorCur->title = directorCur->titleNew;
				directorCur->titleTail = directorCur->titleNew;

				while (1)
				{
					titleCheck = strtok(NULL, ",");

					if (titleCheck == 0) { break; }
					else if (*titleCheck == ' ') { ++titleCheck; }

					directorCur->titleNew = (singleData*)malloc(sizeof(singleData));
					directorCur->titleNew->name = (char *)malloc(30);

					strcpy(directorCur->titleNew->name, titleCheck);
					strcpy(directorCur->titleNew->name, changeLogColon(directorCur->titleNew->name));


					directorCur->titleNew->next = NULL;

					directorCur->titleTail->next = directorCur->titleNew;
					directorCur->titleTail = directorCur->titleNew;
				}
			}
		}
		else if (strcmp(check, "delete") == 0) {
			check = strtok(NULL, ":");//숫자
			deleteNum = (int)atoi(check);
			Director* directorBefore = NULL;
			directorCur = director;
			if (directorCur->serialNumber == deleteNum);
			else {
				while (directorCur->next != NULL) {

					directorCur = directorCur->next;
					if (directorCur->serialNumber == deleteNum)
						break;
				}
			}//
			if (directorCur == directorTail && directorCur == director)
				directorTail = director = NULL;
			else if (directorCur != directorTail && directorCur == director)
				director = directorCur->next;
			else {
				directorBefore = director;
				if (directorBefore->next->serialNumber == deleteNum);
				else {
					while (directorBefore->next != NULL) {

						directorBefore = directorBefore->next;
						if (directorBefore->next->serialNumber == deleteNum)
							break;
					}
				}
				directorBefore->next = directorCur->next;
			}
			//
			singleData * deltitle = directorCur->title;
			singleData * delNexttitle = directorCur->title->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			free(directorCur->director);
			free(directorCur->birth);
			free(directorCur);

		}



		free(keyword);
	}

	fclose(dp);
}
void loadActorlogs(void) {
	int fileSize, updateNum, deleteNum;
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
			actorNew->titleNew->next = NULL;
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

		else if (strcmp(check, "update") == 0) {

			check = strtok(NULL, ":");//숫자

			updateNum = (int)atoi(check);

			actorCur = actor;
			if (actorCur->serialNumber == updateNum);
			else {
				while (actorCur->next != NULL) {

					actorCur = actorCur->next;
					if (actorCur->serialNumber == updateNum)
						break;
				}
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(actorCur->actor->name, check);
				strcpy(actorCur->actor->name, changeLogColon(actorCur->actor->name));
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				actorCur->sex = *check;
			}
			check = strtok(NULL, ":");
			if (strcmp(check, "=") == 0);
			else {
				strcpy(actorCur->birth->name, check);
				strcpy(actorCur->birth->name, changeLogColon(actorCur->birth->name));
			}

			if (strcmp(check + 2, "=") == 0);
			else {
				singleData * delTitle = actorCur->title;
				singleData * delNextTitle = actorCur->title->next;
				free(delTitle);

				while (delNextTitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delTitle = delNextTitle;
					delNextTitle = delNextTitle->next;
					free(delTitle);    // 두 번째 이후의 노드 삭제
				}
				actorCur->titleNew = (singleData*)malloc(sizeof(singleData));
				actorCur->titleNew->name = (char *)malloc(30);
				strcpy(actorCur->titleNew->name, strtok(NULL, ","));
				strcpy(actorCur->titleNew->name, changeLogColon(actorCur->titleNew->name));
				actorCur->titleNew->next = NULL;

				actorCur->title = actorCur->titleNew;
				actorCur->titleTail = actorCur->titleNew;

				while (1)
				{
					titleCheck = strtok(NULL, ",");

					if (titleCheck == 0) { break; }
					else if (*titleCheck == ' ') { ++titleCheck; }

					actorCur->titleNew = (singleData*)malloc(sizeof(singleData));
					actorCur->titleNew->name = (char *)malloc(30);

					strcpy(actorCur->titleNew->name, titleCheck);
					strcpy(actorCur->titleNew->name, changeLogColon(actorCur->titleNew->name));


					actorCur->titleNew->next = NULL;

					actorCur->titleTail->next = actorCur->titleNew;
					actorCur->titleTail = actorCur->titleNew;
				}
			}
		}
		else if (strcmp(check, "delete") == 0) {
			check = strtok(NULL, ":");//숫자
			deleteNum = (int)atoi(check);
			Actor* actorBefore = NULL;
			actorCur = actor;
			if (actorCur->serialNumber == deleteNum);
			else {
				while (actorCur->next != NULL) {

					actorCur = actorCur->next;
					if (actorCur->serialNumber == deleteNum)
						break;
				}
			}//
			if (actorCur == actorTail && actorCur == actor)
				actorTail = actor = NULL;
			else if (actorCur != actorTail && actorCur == actor)
				actor = actorCur->next;
			else {
				actorBefore = actor;
				if (actorBefore->next->serialNumber == deleteNum);
				else {
					while (actorBefore->next != NULL) {

						actorBefore = actorBefore->next;
						if (actorBefore->next->serialNumber == deleteNum)
							break;
					}
				}//
				actorBefore->next = actorCur->next;
			}
			//
			singleData * deltitle = actorCur->title;
			singleData * delNexttitle = actorCur->title->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			free(actorCur->actor);
			free(actorCur->birth);
			free(actorCur);

		}


		free(keyword);
	}
	fclose(mp);
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
void update(char* mda, char* option, char* num) {
	int optLen = strlen(option) + 1, actorCnt = 0, cnt = 0,check=0;
	char *input, *actorCheck, *titleCheck, *opt = (char*)malloc(optLen), *YorN;
	Movie* ifSameM = NULL;
	Director* ifSameD = NULL;
	Actor* ifSameA = NULL;
	int updateNum = (int)atoi(num);
	strcpy(opt, option);

	if (strcmp(mda, "m") == 0) {
		char *tmpTitle = (char*)malloc(30);
		char *tmpGenre = (char*)malloc(30);
		char *tmpDirector = (char*)malloc(30);
		singleData* tmpActorNew;
		singleData* tmpActorCur;
		singleData* tmpActorTail;
		singleData* tmpActor;
		int tmpYear, tmpRuntime;
		movieNew = movie;
		if (movieNew->serialNumber == updateNum) ++check;
		else {
			while (movieNew->next != NULL) {

				movieNew = movieNew->next;
				if (movieNew->serialNumber == updateNum)
					++check;
					break;
			}
		}
		if (check == 0) {
			printf("@@ No such record!!\n");
			return;
		}
		strcpy(tmpTitle, movieNew->title->name);
		strcpy(tmpGenre, movieNew->genre->name);
		strcpy(tmpDirector, movieNew->director->name);
		tmpYear = movieNew->year;
		tmpRuntime = movieNew->runTime;

		movieNew->actorCur = movieNew->actor;

		tmpActorNew = (singleData*)malloc(sizeof(singleData));
		tmpActorNew->name = (char *)malloc(30);
		strcpy(tmpActorNew->name, movieNew->actorCur->name);
		tmpActorNew->next = NULL;

		tmpActor = tmpActorNew;
		tmpActorTail = tmpActorNew;

		movieNew->actorCur = movieNew->actorCur->next;
		while (movieNew->actorCur != NULL) {

			tmpActorNew = (singleData*)malloc(sizeof(singleData));
			tmpActorNew->name = (char *)malloc(30);
			strcpy(tmpActorNew->name, movieNew->actorCur->name);
			tmpActorNew->next = NULL;
			tmpActorTail->next = tmpActorNew;
			tmpActorTail = tmpActorNew;
			movieNew->actorCur = movieNew->actorCur->next;
		}

		for (int i = 0; i < optLen - 1; ++i) {
			input = (char *)malloc(255);
			if (*(opt + i) == 't') {
				printf("title > ");
				gets(input);
				strcpy(movieNew->title->name, input);
				free(input);
			}
			else if (*(opt + i) == 'g') {
				printf("genre > ");
				gets(input);
				strcpy(movieNew->genre->name, input);
				free(input);
			}
			else if (*(opt + i) == 'd') {
				printf("director > ");
				gets(input);
				strcpy(movieNew->director->name, input);
				free(input);
			}
			else if (*(opt + i) == 'y') {
				printf("year > ");
				gets(input);
				movieNew->year = (int)atoi(input);
				free(input);
			}
			else if (*(opt + i) == 'r') {
				printf("runtime > ");
				gets(input);
				movieNew->runTime = (int)atoi(input);
				free(input);
			}
			else if (*(opt + i) == 'a') {
				printf("actors > ");
				singleData * delActor = movieNew->actor;
				singleData * delNextActor = movieNew->actor->next;
				free(delActor);
				while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delActor = delNextActor;
					delNextActor = delNextActor->next;
					free(delActor);    // 두 번째 이후의 노드 삭제
				}
				gets(input);
				movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
				movieNew->actorNew->name = (char *)malloc(30);
				strcpy(movieNew->actorNew->name, strtok(input, ","));
				movieNew->actorNew->next = NULL;
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
					movieNew->actorNew->next = NULL;

					movieNew->actorTail->next = movieNew->actorNew;
					movieNew->actorTail = movieNew->actorNew;
				}
				free(input);
			}
		}//for끝

		ifSameM = (Movie*)updateSameMovie();
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
			printf("@@ Do you want to update any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				strcpy(movieNew->title->name, tmpTitle);
				strcpy(movieNew->genre->name, tmpGenre);
				strcpy(movieNew->director->name, tmpDirector);
				movieNew->year = tmpYear;
				movieNew->runTime = tmpRuntime;
				singleData * delActor = movieNew->actor;
				singleData * delNextActor = movieNew->actor->next;
				free(delActor);
				while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delActor = delNextActor;
					delNextActor = delNextActor->next;
					free(delActor);    // 두 번째 이후의 노드 삭제
				}
				tmpActorCur = tmpActor;
				movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
				movieNew->actorNew->name = (char *)malloc(30);
				strcpy(movieNew->actorNew->name, tmpActorCur->name);
				movieNew->actorNew->next = NULL;

				movieNew->actor = movieNew->actorNew;
				movieNew->actorTail = movieNew->actorNew;

				tmpActorCur = tmpActorCur->next;
				while (tmpActorCur != NULL) {
					movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
					movieNew->actorNew->name = (char *)malloc(30);
					strcpy(movieNew->actorNew->name, tmpActorCur->name);
					movieNew->actorNew->next = NULL;
					movieNew->actorTail->next = movieNew->actorNew;
					movieNew->actorTail = movieNew->actorNew;
					tmpActorCur = tmpActorCur->next;
				}
				free(tmpTitle);
				free(tmpGenre);
				free(tmpDirector);
				delActor = tmpActor;
				delNextActor = tmpActor->next;
				free(delActor);
				while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delActor = delNextActor;
					delNextActor = delNextActor->next;
					free(delActor);    // 두 번째 이후의 노드 삭제
				}
				fclose(mp);
				return;
			}//No
			else {
				fprintf(mp, "update:%d", movieNew->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 't')
						fprintf(mp, ":%s", changeColon(movieNew->title->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'g')
						fprintf(mp, ":%s", changeColon(movieNew->genre->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'd')
						fprintf(mp, ":%s", changeColon(movieNew->director->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'y')
						fprintf(mp, ":%d", movieNew->year);
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'r')
						fprintf(mp, ":%d", movieNew->runTime);
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'a') {
						movieNew->actorCur = movieNew->actor;

						fprintf(mp, ":%s", changeColon(movieNew->actorCur->name));

						while (movieNew->actorCur->next != NULL)
						{
							movieNew->actorCur = movieNew->actorCur->next;
							fprintf(mp, ", %s", changeColon(movieNew->actorCur->name));
						}
						fprintf(mp, "\n");
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");

				puts("@@ Done");
				free(tmpTitle);
				free(tmpGenre);
				free(tmpDirector);
				singleData * delActor = tmpActor;
				singleData * delNextActor = tmpActor->next;
				free(delActor);
				while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					delActor = delNextActor;
					delNextActor = delNextActor->next;
					free(delActor);    // 두 번째 이후의 노드 삭제
				}
				free(YorN);
				fclose(mp);
				return;
			}//yes 분기문
		}
		else { //NULL일때
			fprintf(mp, "update:%d", movieNew->serialNumber);
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 't')
					fprintf(mp, ":%s", changeColon(movieNew->title->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'g')
					fprintf(mp, ":%s", changeColon(movieNew->genre->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'd')
					fprintf(mp, ":%s", changeColon(movieNew->director->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'y')
					fprintf(mp, ":%d", movieNew->year);
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'r')
					fprintf(mp, ":%d", movieNew->runTime);
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'a') {
					movieNew->actorCur = movieNew->actor;

					fprintf(mp, ":%s", changeColon(movieNew->actorCur->name));

					while (movieNew->actorCur->next != NULL)
					{
						movieNew->actorCur = movieNew->actorCur->next;
						fprintf(mp, ", %s", changeColon(movieNew->actorCur->name));
					}
					fprintf(mp, "\n");
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");

			puts("@@ Done");
			free(tmpTitle);
			free(tmpGenre);
			free(tmpDirector);
			singleData * delActor = tmpActor;
			singleData * delNextActor = tmpActor->next;
			free(delActor);
			while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				delActor = delNextActor;
				delNextActor = delNextActor->next;
				free(delActor);    // 두 번째 이후의 노드 삭제
			}
			fclose(mp);
			return;
		}

	}//movie일때
	else if (strcmp(mda, "d") == 0) {
		char *tmpBirth = (char*)malloc(30);
		char *tmpDirector = (char*)malloc(30);
		singleData* tmptitleNew;
		singleData* tmptitleCur;
		singleData* tmptitleTail;
		singleData* tmptitle;
		char tmpSex;
		directorNew = director;
		if (directorNew->serialNumber == updateNum) ++check;
		else {
			while (directorNew->next != NULL) {

				directorNew = directorNew->next;
				if (directorNew->serialNumber == updateNum){
					++check;
					break;}
			}
		}
		if (check == 0) {
			printf("@@ No such record!!\n");
			return;
		}
		strcpy(tmpBirth, directorNew->birth->name);
		strcpy(tmpDirector, directorNew->director->name);
		tmpSex = directorNew->sex;

		directorNew->titleCur = directorNew->title;

		tmptitleNew = (singleData*)malloc(sizeof(singleData));
		tmptitleNew->name = (char *)malloc(30);
		strcpy(tmptitleNew->name, directorNew->titleCur->name);
		tmptitleNew->next = NULL;

		tmptitle = tmptitleNew;
		tmptitleTail = tmptitleNew;

		directorNew->titleCur = directorNew->titleCur->next;
		while (directorNew->titleCur != NULL) {

			tmptitleNew = (singleData*)malloc(sizeof(singleData));
			tmptitleNew->name = (char *)malloc(30);
			strcpy(tmptitleNew->name, directorNew->titleCur->name);
			tmptitleNew->next = NULL;
			tmptitleTail->next = tmptitleNew;
			tmptitleTail = tmptitleNew;
			directorNew->titleCur = directorNew->titleCur->next;
		}

		for (int i = 0; i < optLen - 1; ++i) {
			input = (char *)malloc(255);
			if (*(opt + i) == 'n') {
				printf("director > ");
				gets(input);
				strcpy(directorNew->director->name, input);
				free(input);
			}
			else if (*(opt + i) == 's') {
				printf("sex > ");
				gets(input);
				directorNew->sex = *input;
				free(input);
			}
			else if (*(opt + i) == 'b') {
				printf("birth > ");
				gets(input);
				strcpy(directorNew->birth->name, input);
				free(input);
			}
			else if (*(opt + i) == 'm') {
				printf("titles > ");
				singleData * deltitle = directorNew->title;
				singleData * delNexttitle = directorNew->title->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				gets(input);
				directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				directorNew->titleNew->name = (char *)malloc(30);
				strcpy(directorNew->titleNew->name, strtok(input, ","));
				directorNew->titleNew->next = NULL;
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


					directorNew->titleNew->next = NULL;

					directorNew->titleTail->next = directorNew->titleNew;
					directorNew->titleTail = directorNew->titleNew;
				}
				free(input);
			}
		}//for끝

		ifSameD = (Director*)updateSameDirector();
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
			printf("@@ Do you want to update any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				strcpy(directorNew->birth->name, tmpBirth);
				strcpy(directorNew->director->name, tmpDirector);
				directorNew->sex = tmpSex;
				singleData * deltitle = directorNew->title;
				singleData * delNexttitle = directorNew->title->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				tmptitleCur = tmptitle;
				directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				directorNew->titleNew->name = (char *)malloc(30);
				strcpy(directorNew->titleNew->name, tmptitleCur->name);
				directorNew->titleNew->next = NULL;

				directorNew->title = directorNew->titleNew;
				directorNew->titleTail = directorNew->titleNew;

				tmptitleCur = tmptitleCur->next;
				while (tmptitleCur != NULL) {
					directorNew->titleNew = (singleData*)malloc(sizeof(singleData));
					directorNew->titleNew->name = (char *)malloc(30);
					strcpy(directorNew->titleNew->name, tmptitleCur->name);
					directorNew->titleNew->next = NULL;
					directorNew->titleTail->next = directorNew->titleNew;
					directorNew->titleTail = directorNew->titleNew;
					tmptitleCur = tmptitleCur->next;
				}
				free(tmpBirth);
				free(tmpDirector);
				deltitle = tmptitle;
				delNexttitle = tmptitle->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				fclose(dp);
				return;
			}//No
			else {
				fprintf(dp, "update:%d", directorNew->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'n')
						fprintf(dp, ":%s", changeColon(directorNew->director->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(dp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 's')
						fprintf(dp, ":%c", directorNew->sex);
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(dp, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'b')
						fprintf(dp, ":%s", changeColon(directorNew->birth->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(dp, ":=");
				cnt = 0;

				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'm') {
						directorNew->titleCur = directorNew->title;

						fprintf(dp, ":%s", changeColon(directorNew->titleCur->name));

						while (directorNew->titleCur->next != NULL)
						{
							directorNew->titleCur = directorNew->titleCur->next;
							fprintf(dp, ", %s", changeColon(directorNew->titleCur->name));
						}
						fprintf(dp, "\n");
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(dp, ":=");
				cnt = 0;

				puts("@@ Done");
				free(tmpBirth);
				free(tmpDirector);
				singleData * deltitle = tmptitle;
				singleData * delNexttitle = tmptitle->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				free(YorN);
				fclose(dp);
				return;
			}//yes 분기문
		}
		else {
			fprintf(dp, "update:%d", directorNew->serialNumber);
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'n')
					fprintf(dp, ":%s", changeColon(directorNew->director->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(dp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 's')
					fprintf(dp, ":%c", directorNew->sex);
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(dp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'b')
					fprintf(dp, ":%s", changeColon(directorNew->birth->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(dp, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'm') {
					directorNew->titleCur = directorNew->title;

					fprintf(dp, ":%s", changeColon(directorNew->titleCur->name));

					while (directorNew->titleCur->next != NULL)
					{
						directorNew->titleCur = directorNew->titleCur->next;
						fprintf(dp, ", %s", changeColon(directorNew->titleCur->name));
					}
					fprintf(dp, "\n");
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(dp, ":=");
			cnt = 0;
			puts("@@ Done");
			free(tmpBirth);
			free(tmpDirector);
			singleData * deltitle = tmptitle;
			singleData * delNexttitle = tmptitle->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			fclose(dp);
			return;
		}

	}//director일때
	else if (strcmp(mda, "a") == 0) {
		char *tmpBirth = (char*)malloc(30);
		char *tmpactor = (char*)malloc(30);
		singleData* tmptitleNew;
		singleData* tmptitleCur;
		singleData* tmptitleTail;
		singleData* tmptitle;
		char tmpSex;
		actorNew = actor;
		if (actorNew->serialNumber == updateNum) ++check;
		else {
		  while (actorNew->next != NULL) {

		    actorNew = actorNew->next;
		    if (actorNew->serialNumber == updateNum){
		      ++check;
		      break;}
		  }
		}
		if (check == 0) {
		  printf("@@ No such record!!\n");
		  return;
		}
		strcpy(tmpBirth, actorNew->birth->name);
		strcpy(tmpactor, actorNew->actor->name);
		tmpSex = actorNew->sex;

		actorNew->titleCur = actorNew->title;

		tmptitleNew = (singleData*)malloc(sizeof(singleData));
		tmptitleNew->name = (char *)malloc(30);
		strcpy(tmptitleNew->name, actorNew->titleCur->name);
		tmptitleNew->next = NULL;

		tmptitle = tmptitleNew;
		tmptitleTail = tmptitleNew;

		actorNew->titleCur = actorNew->titleCur->next;
		while (actorNew->titleCur != NULL) {

			tmptitleNew = (singleData*)malloc(sizeof(singleData));
			tmptitleNew->name = (char *)malloc(30);
			strcpy(tmptitleNew->name, actorNew->titleCur->name);
			tmptitleNew->next = NULL;
			tmptitleTail->next = tmptitleNew;
			tmptitleTail = tmptitleNew;
			actorNew->titleCur = actorNew->titleCur->next;
		}

		for (int i = 0; i < optLen - 1; ++i) {
			input = (char *)malloc(255);
			if (*(opt + i) == 'n') {
				printf("actor > ");
				gets(input);
				strcpy(actorNew->actor->name, input);
				free(input);
			}
			else if (*(opt + i) == 's') {
				printf("sex > ");
				gets(input);
				actorNew->sex = *input;
				free(input);
			}
			else if (*(opt + i) == 'b') {
				printf("birth > ");
				gets(input);
				strcpy(actorNew->birth->name, input);
				free(input);
			}
			else if (*(opt + i) == 'm') {
				printf("titles > ");
				singleData * deltitle = actorNew->title;
				singleData * delNexttitle = actorNew->title->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				gets(input);
				actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				actorNew->titleNew->name = (char *)malloc(30);
				strcpy(actorNew->titleNew->name, strtok(input, ","));
				actorNew->titleNew->next = NULL;
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


					actorNew->titleNew->next = NULL;

					actorNew->titleTail->next = actorNew->titleNew;
					actorNew->titleTail = actorNew->titleNew;
				}
				free(input);
			}
		}//for끝

		ifSameA = (Actor*)updateSameActor();
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
			printf("@@ Do you want to update any way? ");
			YorN = (char*)malloc(10);
			gets(YorN);
			if (strcmp(YorN, "No") == 0 || strcmp(YorN, "NO") == 0 || strcmp(YorN, "no") == 0 || strcmp(YorN, "nO") == 0) {
				strcpy(actorNew->birth->name, tmpBirth);
				strcpy(actorNew->actor->name, tmpactor);
				actorNew->sex = tmpSex;
				singleData * deltitle = actorNew->title;
				singleData * delNexttitle = actorNew->title->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				tmptitleCur = tmptitle;
				actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
				actorNew->titleNew->name = (char *)malloc(30);
				strcpy(actorNew->titleNew->name, tmptitleCur->name);
				actorNew->titleNew->next = NULL;

				actorNew->title = actorNew->titleNew;
				actorNew->titleTail = actorNew->titleNew;

				tmptitleCur = tmptitleCur->next;
				while (tmptitleCur != NULL) {
					actorNew->titleNew = (singleData*)malloc(sizeof(singleData));
					actorNew->titleNew->name = (char *)malloc(30);
					strcpy(actorNew->titleNew->name, tmptitleCur->name);
					actorNew->titleNew->next = NULL;
					actorNew->titleTail->next = actorNew->titleNew;
					actorNew->titleTail = actorNew->titleNew;
					tmptitleCur = tmptitleCur->next;
				}
				free(tmpBirth);
				free(tmpactor);
				deltitle = tmptitle;
				delNexttitle = tmptitle->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				fclose(ap);
				return;
			}//No
			else {
				fprintf(ap, "update:%d", actorNew->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'n')
						fprintf(ap, ":%s", changeColon(actorNew->actor->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(ap, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 's')
						fprintf(ap, ":%c", actorNew->sex);
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(ap, ":=");
				cnt = 0;
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'b')
						fprintf(ap, ":%s", changeColon(actorNew->birth->name));
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(ap, ":=");
				cnt = 0;

				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'm') {
						actorNew->titleCur = actorNew->title;

						fprintf(ap, ":%s", changeColon(actorNew->titleCur->name));

						while (actorNew->titleCur->next != NULL)
						{
							actorNew->titleCur = actorNew->titleCur->next;
							fprintf(ap, ", %s", changeColon(actorNew->titleCur->name));
						}
						fprintf(ap, "\n");
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(ap, ":=");
				cnt = 0;

				puts("@@ Done");
				free(tmpBirth);
				free(tmpactor);
				singleData * deltitle = tmptitle;
				singleData * delNexttitle = tmptitle->next;
				free(deltitle);
				while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
				{
					deltitle = delNexttitle;
					delNexttitle = delNexttitle->next;
					free(deltitle);    // 두 번째 이후의 노드 삭제
				}
				free(YorN);
				fclose(ap);
				return;
			}//yes 분기문
		}
		else {
			fprintf(ap, "update:%d", actorNew->serialNumber);
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'n')
					fprintf(ap, ":%s", changeColon(actorNew->actor->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(ap, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 's')
					fprintf(ap, ":%c", actorNew->sex);
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(ap, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'b')
					fprintf(ap, ":%s", changeColon(actorNew->birth->name));
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(ap, ":=");
			cnt = 0;
			for (int i = 0; i < optLen - 1; ++i) {
				if (*(opt + i) == 'm') {
					actorNew->titleCur = actorNew->title;

					fprintf(ap, ":%s", changeColon(actorNew->titleCur->name));

					while (actorNew->titleCur->next != NULL)
					{
						actorNew->titleCur = actorNew->titleCur->next;
						fprintf(ap, ", %s", changeColon(actorNew->titleCur->name));
					}
					fprintf(ap, "\n");
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(ap, ":=");
			cnt = 0;
			puts("@@ Done");
			free(tmpBirth);
			free(tmpactor);
			singleData * deltitle = tmptitle;
			singleData * delNexttitle = tmptitle->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			fclose(ap);
			return;
		}

	}//actor일때
	free(opt);
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
	if (director != NULL) {
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
	}
	if (actor != NULL) {
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
	}

	movieCur = movie;
	directorCur = director;
	actorCur = actor;
	actorCurCnt = 0;

	while (movieCur->next != NULL)
	{
		movieCur = movieCur->next;
		if (director != NULL) {
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
		}
		if (actor != NULL) {
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

}
void linkAnotherDirector(void) {
	int titleCurCnt = 0;
	if (director == NULL || movie == NULL)
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
	if (actor == NULL || movie == NULL)
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
void delete(char* mda, char* num) {

	int deleteNum = (int)atoi(num), check = 0;
	if (strcmp(mda, "m") == 0) {
		Movie* movieBefore = NULL;
    if(movie == NULL){
      printf("@@ No such record!!\n");
      return;
    }
		movieCur = movie;
		if (movieCur->serialNumber == deleteNum)
			++check;
		else {
			while (movieCur->next != NULL) {

				movieCur = movieCur->next;
				if (movieCur->serialNumber == deleteNum) {
					++check;
					break;
				}
			}
		}//
		if (check == 0) {
			printf("@@ No such record!!\n");
			return;
		}
		else {
			if (movieCur == movieTail && movieCur == movie)
				movieTail = movie = NULL;
			else if (movieCur != movieTail && movieCur == movie)
				movie = movieCur->next;
			else {
				movieBefore = movie;
				if (movieBefore->next->serialNumber == deleteNum);
				else {
					while (movieBefore->next != NULL) {

						movieBefore = movieBefore->next;
						if (movieBefore->next->serialNumber == deleteNum)
							break;
					}
				}//
				movieBefore->next = movieCur->next;
			}
			//
			singleData * delActor = movieCur->actor;
			singleData * delNextActor = movieCur->actor->next;
			free(delActor);
			while (delNextActor != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				delActor = delNextActor;
				delNextActor = delNextActor->next;
				free(delActor);    // 두 번째 이후의 노드 삭제
			}
			free(movieCur->title);
			free(movieCur->genre);
			free(movieCur->director);
			free(movieCur);

			fprintf(mp, "delete:%d:=:=:=:=:=:=\n", deleteNum);

			puts("@@ Done");
			fclose(mp);
		}
	}//movie
	else if (strcmp(mda, "d") == 0) {
		Director* directorBefore = NULL;
    if(director == NULL){
      printf("@@ No such record!!\n");
      return;
    }
		directorCur = director;
		if (directorCur->serialNumber == deleteNum)
			++check;
		else {
			while (directorCur->next != NULL) {

				directorCur = directorCur->next;
				if (directorCur->serialNumber == deleteNum) {
					++check;
					break;
				}
			}
		}//
		if (check == 0) {
			printf("@@ No such record!!\n");
			return;
		}
		else {
			if (directorCur == directorTail && directorCur == director)
				directorTail = director = NULL;
			else if (directorCur != directorTail && directorCur == director)
				director = directorCur->next;
			else {
				directorBefore = director;
				if (directorBefore->next->serialNumber == deleteNum);
				else {
					while (directorBefore->next != NULL) {

						directorBefore = directorBefore->next;
						if (directorBefore->next->serialNumber == deleteNum)
							break;
					}
				}//
				directorBefore->next = directorCur->next;
			}
			//
			singleData * deltitle = directorCur->title;
			singleData * delNexttitle = directorCur->title->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			free(directorCur->director);
			free(directorCur->birth);
			free(directorCur);

			fprintf(dp, "delete:%d:=:=:=:=:=:=\n", deleteNum);

			puts("@@ Done");
			fclose(dp);
		}
	}//director
	else if (strcmp(mda, "a") == 0) {
		Actor* actorBefore = NULL;
    if(actor == NULL){
      printf("@@ No such record!!\n");
			return;
    }
		actorCur = actor;
		if (actorCur->serialNumber == deleteNum)
			++check;
		else {
			while (actorCur->next != NULL) {

				actorCur = actorCur->next;
				if (actorCur->serialNumber == deleteNum) {
					++check;
					break;
				}
			}
		}//
		if (check == 0) {
			printf("@@ No such record!!\n");
			return;
		}
		else {
			if (actorCur == actorTail && actorCur == actor)
				actorTail = actor = NULL;
			else if (actorCur != actorTail && actorCur == actor)
				actor = actorCur->next;
			else {
				actorBefore = actor;
				if (actorBefore->next->serialNumber == deleteNum);
				else {
					while (actorBefore->next != NULL) {

						actorBefore = actorBefore->next;
						if (actorBefore->next->serialNumber == deleteNum)
							break;
					}
				}//
				actorBefore->next = actorCur->next;
			}
			//
			singleData * deltitle = actorCur->title;
			singleData * delNexttitle = actorCur->title->next;
			free(deltitle);
			while (delNexttitle != NULL)    // 두 번째 이후의 노드 삭제 위한 반복문
			{
				deltitle = delNexttitle;
				delNexttitle = delNexttitle->next;
				free(deltitle);    // 두 번째 이후의 노드 삭제
			}
			free(actorCur->actor);
			free(actorCur->birth);
			free(actorCur);

			fprintf(ap, "delete:%d:=:=:=:=:=:=\n", deleteNum);

			puts("@@ Done");
			fclose(ap);
		}
	}//actor
}
Movie* addSameMovie(void) {
	if (movie == NULL) { return NULL; }
	int actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0, endCnt = 0;
	movieCur = movie;
	while (movieCur->serialNumber != movieNew->serialNumber) {
		movieNew->actorCur = movieNew->actor;
		movieCur->actorCur = movieCur->actor;
		while (movieNew->actorCur->next != NULL) {
			++actorNewCheck;
			movieNew->actorCur = movieNew->actorCur->next;
		}//새로운 구조체 actor 개수 세기
		while (movieCur->actorCur->next != NULL) {
			++actorCurCheck;
			movieCur->actorCur = movieCur->actorCur->next;
		}//비교 구조체 actor 개수 세기
		if (actorNewCheck != actorCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
		else {//엑터 개수가 같으면 비교 시작
			movieNew->actorCur = movieNew->actor;
			movieCur->actorCur = movieCur->actor;
			for(int i=0; i<actorNewCheck; ++i) {
				if (strcmp(movieNew->actorCur->name, movieCur->actorCur->name) == 0)
					++actorCnt;
				movieNew->actorCur = movieNew->actorCur->next;
				movieCur->actorCur = movieCur->actorCur->next;
			}//actor 비교
		//	printf("%d %d",actorCnt,actorNewCheck);
			if (actorCnt == actorNewCheck){
				++endCnt;
				if (strcmp(movieNew->title->name, movieCur->title->name) == 0)
					++endCnt;
				if (strcmp(movieNew->genre->name, movieCur->genre->name) == 0)
					++endCnt;
        if (strcmp(movieNew->director->name, movieCur->director->name) == 0)
          ++endCnt;
				if (movieNew->year == movieCur->year)
					++endCnt;
				if (movieNew->runTime == movieCur->runTime)
					++endCnt;
				//	printf("%d\n\n",endCnt);
		    if(endCnt == 6)
		          return movieCur;
			}
	//		puts("check\n");
		}
		if (movieCur->next == NULL) { return NULL; }
		else {
			movieCur = movieCur->next;
			actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0;
		}
	} //
}
Director* addSameDirector(void) {
	if (director == NULL) { return NULL; }
	int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
	directorCur = director;
	while (directorCur->serialNumber != directorNew->serialNumber) {
		directorNew->titleCur = directorNew->title;
		directorCur->titleCur = directorCur->title;
		while (directorNew->titleCur->next != NULL) {
			++titleNewCheck;
			directorNew->titleCur = directorNew->titleCur->next;
		}//새로운 구조체 title 개수 세기
		while (directorCur->titleCur->next != NULL) {
			++titleCurCheck;
			directorCur->titleCur = directorCur->titleCur->next;
		}//비교 구조체 title 개수 세기
		if (titleNewCheck != titleCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
		else {//엑터 개수가 같으면 비교 시작
			directorNew->titleCur = directorNew->title;
			directorCur->titleCur = directorCur->title;
			for(int i=0; i<titleNewCheck; ++i) {
				if (strcmp(directorNew->titleCur->name, directorCur->titleCur->name) == 0)
					++titleCnt;
				directorNew->titleCur = directorNew->titleCur->next;
				directorCur->titleCur = directorCur->titleCur->next;
			}//title 비교
		//	printf("%d %d",titleCnt,titleNewCheck);
			if (titleCnt == titleNewCheck){
				++endCnt;
				if (strcmp(directorNew->director->name, directorCur->director->name) == 0)
					++endCnt;
				if (strcmp(directorNew->birth->name, directorCur->birth->name) == 0)
					++endCnt;
				if (directorNew->sex == directorCur->sex)
					++endCnt;
				//	printf("%d\n\n",endCnt);
		    if(endCnt == 4)
		          return directorCur;
			}
	//		puts("check\n");
		}
		if (directorCur->next == NULL) { return NULL; }
		else {
			directorCur = directorCur->next;
			titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
		}
	} //
}
Actor* addSameActor(void) {
	if (actor == NULL) { return NULL; }
	int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
	actorCur = actor;
	while (actorCur->serialNumber != actorNew->serialNumber) {
		actorNew->titleCur = actorNew->title;
		actorCur->titleCur = actorCur->title;
		while (actorNew->titleCur->next != NULL) {
			++titleNewCheck;
			actorNew->titleCur = actorNew->titleCur->next;
		}//새로운 구조체 title 개수 세기
		while (actorCur->titleCur->next != NULL) {
			++titleCurCheck;
			actorCur->titleCur = actorCur->titleCur->next;
		}//비교 구조체 title 개수 세기
		if (titleNewCheck != titleCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
		else {//엑터 개수가 같으면 비교 시작
			actorNew->titleCur = actorNew->title;
			actorCur->titleCur = actorCur->title;
			for(int i=0; i<titleNewCheck; ++i) {
				if (strcmp(actorNew->titleCur->name, actorCur->titleCur->name) == 0)
					++titleCnt;
				actorNew->titleCur = actorNew->titleCur->next;
				actorCur->titleCur = actorCur->titleCur->next;
			}//title 비교
		//	printf("%d %d",titleCnt,titleNewCheck);
			if (titleCnt == titleNewCheck){
				++endCnt;
				if (strcmp(actorNew->actor->name, actorCur->actor->name) == 0)
					++endCnt;
				if (strcmp(actorNew->birth->name, actorCur->birth->name) == 0)
					++endCnt;
				if (actorNew->sex == actorCur->sex)
					++endCnt;
				//	printf("%d\n\n",endCnt);
		    if(endCnt == 4)
		          return actorCur;
			}
	//		puts("check\n");
		}
		if (actorCur->next == NULL) { return NULL; }
		else {
			actorCur = actorCur->next;
			titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
		}
	} //
}
Movie* updateSameMovie(void) {
	if (movie == NULL) { return NULL; }
	int actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0, endCnt = 0;
	movieCur = movie;
	while (1) {
    if(movieCur==NULL){return NULL;}
    if(movieCur->serialNumber != movieNew->serialNumber){
		movieNew->actorCur = movieNew->actor;
		movieCur->actorCur = movieCur->actor;
		while (movieNew->actorCur->next != NULL) {
			++actorNewCheck;
			movieNew->actorCur = movieNew->actorCur->next;
		}//새로운 구조체 actor 개수 세기
		while (movieCur->actorCur->next != NULL) {
			++actorCurCheck;
			movieCur->actorCur = movieCur->actorCur->next;
		}//비교 구조체 actor 개수 세기
		if (actorNewCheck != actorCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
		else {//엑터 개수가 같으면 비교 시작
			movieNew->actorCur = movieNew->actor;
			movieCur->actorCur = movieCur->actor;
			for(int i=0; i<actorNewCheck; ++i) {
				if (strcmp(movieNew->actorCur->name, movieCur->actorCur->name) == 0)
					++actorCnt;
				movieNew->actorCur = movieNew->actorCur->next;
				movieCur->actorCur = movieCur->actorCur->next;
			}//actor 비교
		//	printf("%d %d",actorCnt,actorNewCheck);
			if (actorCnt == actorNewCheck){
				++endCnt;
				if (strcmp(movieNew->title->name, movieCur->title->name) == 0)
					++endCnt;
				if (strcmp(movieNew->genre->name, movieCur->genre->name) == 0)
					++endCnt;
        if (strcmp(movieNew->director->name, movieCur->director->name) == 0)
          ++endCnt;
				if (movieNew->year == movieCur->year)
					++endCnt;
				if (movieNew->runTime == movieCur->runTime)
					++endCnt;
				//	printf("%d\n\n",endCnt);
		    if(endCnt == 6)
		          return movieCur;
			}
	//		puts("check\n");
		  }
    }
			movieCur = movieCur->next;
			actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0;
		}
	} //
	Director* updateSameDirector(void) {
		if (director == NULL) { return NULL; }
		int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
		directorCur = director;
		while (1) {
	    if(directorCur==NULL){return NULL;}
	    if(directorCur->serialNumber != directorNew->serialNumber){
			directorNew->titleCur = directorNew->title;
			directorCur->titleCur = directorCur->title;
			while (directorNew->titleCur->next != NULL) {
				++titleNewCheck;
				directorNew->titleCur = directorNew->titleCur->next;
			}//새로운 구조체 title 개수 세기
			while (directorCur->titleCur->next != NULL) {
				++titleCurCheck;
				directorCur->titleCur = directorCur->titleCur->next;
			}//비교 구조체 title 개수 세기
			if (titleNewCheck != titleCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
			else {//엑터 개수가 같으면 비교 시작
				directorNew->titleCur = directorNew->title;
				directorCur->titleCur = directorCur->title;
				for(int i=0; i<titleNewCheck; ++i) {
					if (strcmp(directorNew->titleCur->name, directorCur->titleCur->name) == 0)
						++titleCnt;
					directorNew->titleCur = directorNew->titleCur->next;
					directorCur->titleCur = directorCur->titleCur->next;
				}//title 비교
			//	printf("%d %d",titleCnt,titleNewCheck);
				if (titleCnt == titleNewCheck){
					++endCnt;
					if (strcmp(directorNew->director->name, directorCur->director->name) == 0)
						++endCnt;
					if (strcmp(directorNew->birth->name, directorCur->birth->name) == 0)
						++endCnt;
					if (directorNew->sex == directorCur->sex)
						++endCnt;
					//	printf("%d\n\n",endCnt);
			    if(endCnt == 4)
			          return directorCur;
				}
		//		puts("check\n");
			  }
	    }
				directorCur = directorCur->next;
				titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
			}
		} //
		Actor* updateSameActor(void) {
		  if (actor == NULL) { return NULL; }
		  int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
		  actorCur = actor;
		  while (1) {
		    if(actorCur==NULL){return NULL;}
		    if(actorCur->serialNumber != actorNew->serialNumber){
		    actorNew->titleCur = actorNew->title;
		    actorCur->titleCur = actorCur->title;
		    while (actorNew->titleCur->next != NULL) {
		      ++titleNewCheck;
		      actorNew->titleCur = actorNew->titleCur->next;
		    }//새로운 구조체 title 개수 세기
		    while (actorCur->titleCur->next != NULL) {
		      ++titleCurCheck;
		      actorCur->titleCur = actorCur->titleCur->next;
		    }//비교 구조체 title 개수 세기
		    if (titleNewCheck != titleCurCheck) { return NULL; } //개수 다르니까 NULL 리턴
		    else {//엑터 개수가 같으면 비교 시작
		      actorNew->titleCur = actorNew->title;
		      actorCur->titleCur = actorCur->title;
		      for(int i=0; i<titleNewCheck; ++i) {
		        if (strcmp(actorNew->titleCur->name, actorCur->titleCur->name) == 0)
		          ++titleCnt;
		        actorNew->titleCur = actorNew->titleCur->next;
		        actorCur->titleCur = actorCur->titleCur->next;
		      }//title 비교
		    //	printf("%d %d",titleCnt,titleNewCheck);
		      if (titleCnt == titleNewCheck){
		        ++endCnt;
		        if (strcmp(actorNew->actor->name, actorCur->actor->name) == 0)
		          ++endCnt;
		        if (strcmp(actorNew->birth->name, actorCur->birth->name) == 0)
		          ++endCnt;
		        if (actorNew->sex == actorCur->sex)
		          ++endCnt;
		        //	printf("%d\n\n",endCnt);
		        if(endCnt == 4)
		              return actorCur;
		      }
		  //		puts("check\n");
		      }
		    }
		      actorCur = actorCur->next;
		      titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
		    }
		  } //
