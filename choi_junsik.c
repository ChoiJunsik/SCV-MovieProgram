

#include "movieProject.h"

		extern Movie *movie, *movieTail, *movieCur, *movieNew;
		extern Director *director, *directorTail, *directorCur, *directorNew;
		extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

		extern FILE *mp, *dp, *ap;

		extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
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
void linkAnotherMovie(void) {
	int actorCurCnt = 0;
	int check=0;
	if (movie == NULL)
	{
		return;
	}

	movieCur = movie;
	directorCur = director;
	actorCur = actor;
	if (director != NULL) {
		if (strcmp(movieCur->director->name, directorCur->director->name) == 0){
			movieCur->director->linkAnotherD = directorCur;
			++check;}
		else {
			while (directorCur->next != NULL) {
				directorCur = directorCur->next;
				if (strcmp(movieCur->director->name, directorCur->director->name) == 0){
					movieCur->director->linkAnotherD = directorCur;
					++check;}
			}
		}
		directorCur = director;
	}
	if(check == 0)
			movieCur->director->linkAnotherD = NULL;
	check = 0;
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
			if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0){
				movieCur->actorCur->linkAnotherA = actorCur;
				++check;}
			else {
				while (actorCur->next != NULL) {
					actorCur = actorCur->next;
					if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0){
						movieCur->actorCur->linkAnotherA = actorCur;
						++check;}
				}
			}
			if(check == 0)
				movieCur->actorCur->linkAnotherA = NULL;
			check = 0;
			movieCur->actorCur = movieCur->actorCur->next;
			actorCur = actor;
		}
	}

	movieCur = movie;
	directorCur = director;
	actorCur = actor;
	check = actorCurCnt = 0;


	while (movieCur->next != NULL)
	{
		movieCur = movieCur->next;
		if (director != NULL) {
			if (strcmp(movieCur->director->name, directorCur->director->name) == 0){
				movieCur->director->linkAnotherD = directorCur;
				++check;}
			else {
				while (directorCur->next != NULL) {
					directorCur = directorCur->next;
					if (strcmp(movieCur->director->name, directorCur->director->name) == 0){
						movieCur->director->linkAnotherD = directorCur;
						++check;}
				}
			}
			directorCur = director;
		}
		if(check == 0)
				movieCur->director->linkAnotherD = NULL;
		check = 0;

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
				if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0){
					movieCur->actorCur->linkAnotherA = actorCur;
					++check;}
				else {
					while (actorCur->next != NULL) {
						actorCur = actorCur->next;
						if (strcmp(movieCur->actorCur->name, actorCur->actor->name) == 0){
							movieCur->actorCur->linkAnotherA = actorCur;
							++check;}
					}
				}
				if(check == 0)
						movieCur->actorCur->linkAnotherA = NULL;
				check = 0;
				movieCur->actorCur = movieCur->actorCur->next;
				actorCur = actor;
			}

			actorCurCnt = 0;
		}
	}

}
void linkAnotherDirector(void) {
	int titleCurCnt = 0;
	int check = 0;
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
		if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0){
			directorCur->titleCur->linkAnotherM = movieCur;
			++check;}
		else {
			while (movieCur->next != NULL) {
				movieCur = movieCur->next;
				if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0){
					directorCur->titleCur->linkAnotherM = movieCur;
					++check;}
			}
		}
		if(check == 0)
				directorCur->titleCur->linkAnotherM = NULL;
		check = 0;
		directorCur->titleCur = directorCur->titleCur->next;
		movieCur = movie;
	}

	movieCur = movie;
	directorCur = director;

	check = titleCurCnt = 0;

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
			if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0){
				directorCur->titleCur->linkAnotherM = movieCur;
				++check;}
			else {
				while (movieCur->next != NULL) {
					movieCur = movieCur->next;
					if (strcmp(directorCur->titleCur->name, movieCur->title->name) == 0){
						directorCur->titleCur->linkAnotherM = movieCur;
						++check;}
				}
			}
			if(check==0)
					directorCur->titleCur->linkAnotherM = NULL;
			check = 0 ;
			directorCur->titleCur = directorCur->titleCur->next;
			movieCur = movie;
		}
		titleCurCnt = 0;
	}
}
void linkAnotherActor(void) {
	int titleCurCnt = 0;
	int check = 0;
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
		if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0){
			actorCur->titleCur->linkAnotherM = movieCur;
			++check;}
		else {
			while (movieCur->next != NULL) {
				movieCur = movieCur->next;
				if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0){
					actorCur->titleCur->linkAnotherM = movieCur;
					++check;}
			}
		}
		if(check == 0)
				actorCur->titleCur->linkAnotherM = NULL;
		check = 0;
		actorCur->titleCur = actorCur->titleCur->next;
		movieCur = movie;
	}

	movieCur = movie;
	actorCur = actor;

	check = titleCurCnt = 0;

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
			if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0){
				actorCur->titleCur->linkAnotherM = movieCur;
				++check;}
			else {
				while (movieCur->next != NULL) {
					movieCur = movieCur->next;
					if (strcmp(actorCur->titleCur->name, movieCur->title->name) == 0){
						actorCur->titleCur->linkAnotherM = movieCur;
						++check;}
				}
			}
			if(check == 0)
				actorCur->titleCur->linkAnotherM = NULL;
			check = 0;
			actorCur->titleCur = actorCur->titleCur->next;
			movieCur = movie;
		}
		titleCurCnt = 0;

	}
}
Movie* addSameMovie(void) {
	if (movie == NULL) { return NULL; }
	int actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0, endCnt = 0;
	movieCur = movie;
	while (1) {
		if (movieCur == NULL) { return NULL; }
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
		if(actorNewCheck == actorCurCheck) {//엑터 개수가 같으면 비교 시작
			movieNew->actorCur = movieNew->actor;
			movieCur->actorCur = movieCur->actor;
			for (int i = 0; i < actorNewCheck; ++i) {
				if (strcmp(movieNew->actorCur->name, movieCur->actorCur->name) == 0)
					++actorCnt;
				movieNew->actorCur = movieNew->actorCur->next;
				movieCur->actorCur = movieCur->actorCur->next;
			}//actor 비교
			if (actorCnt == actorNewCheck) {
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
				if (endCnt == 6)
					return movieCur;
			}
		}
	}
			movieCur = movieCur->next;
			actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0;
			endCnt = 0;
		}
		return NULL;
	} //
Director* addSameDirector(void) {
	if (director == NULL) { return NULL; }
	int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
	directorCur = director;
	while (1) {
		if (directorCur == NULL) { return NULL; }
		if (directorCur->serialNumber != directorNew->serialNumber) {
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
		if(titleNewCheck == titleCurCheck) {//엑터 개수가 같으면 비교 시작
			directorNew->titleCur = directorNew->title;
			directorCur->titleCur = directorCur->title;
			for (int i = 0; i < titleNewCheck; ++i) {
				if (strcmp(directorNew->titleCur->name, directorCur->titleCur->name) == 0)
					++titleCnt;
				directorNew->titleCur = directorNew->titleCur->next;
				directorCur->titleCur = directorCur->titleCur->next;
			}//title 비교
			if (titleCnt == titleNewCheck) {
				++endCnt;
				if (strcmp(directorNew->director->name, directorCur->director->name) == 0)
					++endCnt;
				if (strcmp(directorNew->birth->name, directorCur->birth->name) == 0)
					++endCnt;
				if (directorNew->sex == directorCur->sex)
					++endCnt;
				if (endCnt == 4)
					return directorCur;
			}
		}
	}
			directorCur = directorCur->next;
			titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
			endCnt = 0;

		}
		return NULL;
	} //
	Actor* addSameActor(void) {
		if (actor == NULL) { return NULL; }
		int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
		actorCur = actor;
		while (1) {
			if (actorCur == NULL) { return NULL; }
			if (actorCur->serialNumber != actorNew->serialNumber) {
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
			if(titleNewCheck == titleCurCheck) {//엑터 개수가 같으면 비교 시작
				actorNew->titleCur = actorNew->title;
				actorCur->titleCur = actorCur->title;
				for (int i = 0; i < titleNewCheck; ++i) {
					if (strcmp(actorNew->titleCur->name, actorCur->titleCur->name) == 0)
						++titleCnt;
					actorNew->titleCur = actorNew->titleCur->next;
					actorCur->titleCur = actorCur->titleCur->next;
				}//title 비교
				if (titleCnt == titleNewCheck) {
					++endCnt;
					if (strcmp(actorNew->actor->name, actorCur->actor->name) == 0)
						++endCnt;
					if (strcmp(actorNew->birth->name, actorCur->birth->name) == 0)
						++endCnt;
					if (actorNew->sex == actorCur->sex)
						++endCnt;
					if (endCnt == 4)
						return actorCur;
				}
			}
		}
				actorCur = actorCur->next;
				titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
				endCnt = 0;

			}
			return NULL;
		} //
Movie* updateSameMovie(void) {
	if (movie == NULL) { return NULL; }
	int actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0, endCnt = 0;
	movieCur = movie;
	while (1) {
		if (movieCur == NULL) { return NULL; }
		if (movieCur->serialNumber != movieNew->serialNumber) {
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
			if(actorNewCheck == actorCurCheck) {//엑터 개수가 같으면 비교 시작
				movieNew->actorCur = movieNew->actor;
				movieCur->actorCur = movieCur->actor;
				for (int i = 0; i < actorNewCheck; ++i) {
					if (strcmp(movieNew->actorCur->name, movieCur->actorCur->name) == 0)
						++actorCnt;
					movieNew->actorCur = movieNew->actorCur->next;
					movieCur->actorCur = movieCur->actorCur->next;
				}//actor 비교
				 //	printf("%d %d",actorCnt,actorNewCheck);
				if (actorCnt == actorNewCheck) {
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
					if (endCnt == 6)
						return movieCur;
				}
			}
		}
		movieCur = movieCur->next;
		actorNewCheck = 1, actorCurCheck = 1, actorCnt = 0;
		endCnt = 0;
	}
	return NULL;
} //
Director* updateSameDirector(void) {
	if (director == NULL) { return NULL; }
	int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
	directorCur = director;
	while (1) {
		if (directorCur == NULL) { return NULL; }
		if (directorCur->serialNumber != directorNew->serialNumber) {
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
			if(titleNewCheck == titleCurCheck) {//엑터 개수가 같으면 비교 시작
				directorNew->titleCur = directorNew->title;
				directorCur->titleCur = directorCur->title;
				for (int i = 0; i < titleNewCheck; ++i) {
					if (strcmp(directorNew->titleCur->name, directorCur->titleCur->name) == 0)
						++titleCnt;
					directorNew->titleCur = directorNew->titleCur->next;
					directorCur->titleCur = directorCur->titleCur->next;
				}//title 비교
				if (titleCnt == titleNewCheck) {
					++endCnt;
					if (strcmp(directorNew->director->name, directorCur->director->name) == 0)
						++endCnt;
					if (strcmp(directorNew->birth->name, directorCur->birth->name) == 0)
						++endCnt;
					if (directorNew->sex == directorCur->sex)
						++endCnt;
					if (endCnt == 4)
						return directorCur;
				}
			}
		}
		directorCur = directorCur->next;
		titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
		endCnt = 0;
	}
	return NULL;
} //
Actor* updateSameActor(void) {
	if (actor == NULL) { return NULL; }
	int titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0, endCnt = 0;
	actorCur = actor;
	while (1) {
		if (actorCur == NULL) { return NULL; }
		if (actorCur->serialNumber != actorNew->serialNumber) {
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
			if(titleNewCheck == titleCurCheck) {//엑터 개수가 같으면 비교 시작
				actorNew->titleCur = actorNew->title;
				actorCur->titleCur = actorCur->title;
				for (int i = 0; i < titleNewCheck; ++i) {
					if (strcmp(actorNew->titleCur->name, actorCur->titleCur->name) == 0)
						++titleCnt;
					actorNew->titleCur = actorNew->titleCur->next;
					actorCur->titleCur = actorCur->titleCur->next;
				}//title 비교
				if (titleCnt == titleNewCheck) {
					++endCnt;
					if (strcmp(actorNew->actor->name, actorCur->actor->name) == 0)
						++endCnt;
					if (strcmp(actorNew->birth->name, actorCur->birth->name) == 0)
						++endCnt;
					if (actorNew->sex == actorCur->sex)
						++endCnt;
					if (endCnt == 4)
						return actorCur;
				}
			}
		}
		actorCur = actorCur->next;
		titleNewCheck = 1, titleCurCheck = 1, titleCnt = 0;
		endCnt = 0;
	}
	return NULL;
} //
void makeMovieList(void) {
	int fileSize;
	FILE* lmp = fopen("movie_list", "rt");
	if (lmp != NULL) {
		char* keyword = (char*)malloc(255);
		char* copyName = (char*)malloc(30);
		char* day = (char*)malloc(30);
		strcpy(copyName, "movie_list.");
		struct tm *t;
		time_t now;
		now = time(NULL);
		t = localtime(&now);
		sprintf(day, "%d%d%02d%d%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
		strcat(copyName, day);
		FILE* tmp = fopen(copyName, "wt");
		fseek(lmp, 0L, SEEK_END);
		fileSize = ftell(lmp);
		rewind(lmp);
		while (1) {
			if (ftell(lmp) == fileSize) { break; }
			fgets(keyword, 255, lmp);
			fputs(keyword, tmp);
		}
		fclose(tmp);
	} /////////////////////////////////
	fclose(lmp);
	lmp = fopen("movie_list", "wt");
	movieCur = movie;
	while (movieCur != NULL) {
		fprintf(lmp, "%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, changeColon(movieCur->title->name), changeColon(movieCur->genre->name), changeColon(movieCur->director->name), movieCur->year, movieCur->runTime);

		movieCur->actorCur = movieCur->actor;

		fprintf(lmp, "%s", changeColon(movieCur->actorCur->name));

		while (movieCur->actorCur->next != NULL)
		{
			movieCur->actorCur = movieCur->actorCur->next;
			fprintf(lmp, ", %s", changeColon(movieCur->actorCur->name));
		}

		fprintf(lmp, "\n");
		movieCur = movieCur->next;
	}

	fclose(lmp);
}
void makeDirectorList(void) {
	int fileSize;
	FILE* ldp = fopen("director_list", "rt");
	if (ldp != NULL) {
		char* keyword = (char*)malloc(255);
		char* copyName = (char*)malloc(30);
		char* day = (char*)malloc(30);
		strcpy(copyName, "director_list.");
		struct tm *t;
		time_t now;
		now = time(NULL);
		t = localtime(&now);
		sprintf(day, "%d%d%02d%d%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
		strcat(copyName, day);
		FILE* tmp = fopen(copyName, "wt");
		fseek(ldp, 0L, SEEK_END);
		fileSize = ftell(ldp);
		rewind(ldp);
		while (1) {
			if (ftell(ldp) == fileSize) { break; }
			fgets(keyword, 255, ldp);
			fputs(keyword, tmp);
		}
		fclose(tmp);
	} /////////////////////////////////
	fclose(ldp);
	ldp = fopen("director_list", "wt");
	directorCur = director;
	while (directorCur != NULL) {
		fprintf(ldp, "%d:%s:%c:%s:", directorCur->serialNumber, changeColon(directorCur->director->name), directorCur->sex, changeColon(directorCur->birth->name));

		directorCur->titleCur = directorCur->title;

		fprintf(ldp, "%s", changeColon(directorCur->titleCur->name));

		while (directorCur->titleCur->next != NULL)
		{
			directorCur->titleCur = directorCur->titleCur->next;
			fprintf(ldp, ", %s", changeColon(directorCur->titleCur->name));
		}

		fprintf(ldp, "\n");
		directorCur = directorCur->next;
	}

	fclose(ldp);
}
void makeActorList(void) {
	int fileSize;
	FILE* lap = fopen("actor_list", "rt");
	if (lap != NULL) {
		char* keyword = (char*)malloc(255);
		char* copyName = (char*)malloc(30);
		char* day = (char*)malloc(30);
		strcpy(copyName, "actor_list.");
		struct tm *t;
		time_t now;
		now = time(NULL);
		t = localtime(&now);
		sprintf(day, "%d%d%02d%d%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
		strcat(copyName, day);
		FILE* tmp = fopen(copyName, "wt");
		fseek(lap, 0L, SEEK_END);
		fileSize = ftell(lap);
		rewind(lap);
		while (1) {
			if (ftell(lap) == fileSize) { break; }
			fgets(keyword, 255, lap);
			fputs(keyword, tmp);
		}
		fclose(tmp);
	} /////////////////////////////////
	fclose(lap);
	lap = fopen("actor_list", "wt");
	actorCur = actor;
	while (actorCur != NULL) {
		fprintf(lap, "%d:%s:%c:%s:", actorCur->serialNumber, changeColon(actorCur->actor->name), actorCur->sex, changeColon(actorCur->birth->name));

		actorCur->titleCur = actorCur->title;

		fprintf(lap, "%s", changeColon(actorCur->titleCur->name));

		while (actorCur->titleCur->next != NULL)
		{
			actorCur->titleCur = actorCur->titleCur->next;
			fprintf(lap, ", %s", changeColon(actorCur->titleCur->name));
		}

		fprintf(lap, "\n");
		actorCur = actorCur->next;
	}

	fclose(lap);
}
