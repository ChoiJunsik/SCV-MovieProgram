#include "movieProject.h"

		extern Movie *movie, *movieTail, *movieCur, *movieNew;
		extern Director *director, *directorTail, *directorCur, *directorNew;
		extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

		extern FILE *mp, *dp, *ap;

		extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
void update(char* mda, char* option, char* num) {

	int optLen = strlen(option) + 1, actorCnt = 0, cnt = 0, check = 0;
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
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(mp, ":=");
				fprintf(mp, "\n");
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
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(mp, ":=");
			fprintf(mp, "\n");
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
				if (directorNew->serialNumber == updateNum) {
					++check;
					break;
				}
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
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(dp, ":=");
				fprintf(dp, "\n");
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
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(dp, ":=");
			fprintf(dp, "\n");
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
				if (actorNew->serialNumber == updateNum) {
					++check;
					break;
				}
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
					}
					else ++cnt;
				}
				if (cnt == optLen - 1)
					fprintf(ap, ":=");
				fprintf(ap, "\n");
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
				}
				else ++cnt;
			}
			if (cnt == optLen - 1)
				fprintf(ap, ":=");
			fprintf(ap, "\n");
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
void delete(char* mda, char* num) {

	int deleteNum = (int)atoi(num), check = 0;
	if (strcmp(mda, "m") == 0) {
		Movie* movieBefore = NULL;
		if (movie == NULL) {
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
			if (movieCur == movieTail && movieCur != movie){
											movieTail = movieBefore;
											movieBefore->next = NULL;}
			else {
				movieBefore->next = movieCur->next;}
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
		if (director == NULL) {
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
				if (directorCur == directorTail && directorCur != director){
												directorTail = directorBefore;
												directorBefore->next = NULL;}
				else {
					directorBefore->next = directorCur->next;}
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
		if (actor == NULL) {
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
				if (actorCur == actorTail && actorCur != actor){
												actorTail = actorBefore;
												actorBefore->next = NULL;}
				else {
					actorBefore->next = actorCur->next;}
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
