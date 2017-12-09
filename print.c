void print(char* mda, char* num) {


	int printNum = (int)atoi(num), check = 0;
	if (strcmp(mda, "m") == 0) {
		if (movie == NULL) {
			printf("@@ No such record!!\n");
			return;
		}
		movieCur = movie;
		if (movieCur->serialNumber == printNum)
			++check;
		else {
			while (movieCur->next != NULL) {

				movieCur = movieCur->next;
				if (movieCur->serialNumber == printNum) {
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
			printf("%d, %s, %s\n", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name);
			printf("    D :%s", movieCur->director->name);
			if (movieCur->director->linkAnotherD != NULL)
				printf("(%s)\n", movieCur->director->linkAnotherD->birth->name);
			else
				printf("(-)\n");
			movieCur->actorCur = movieCur->actor;
			int i = 0;
			while (movieCur->actorCur != NULL) {
				++i;
				printf("    A%d:%s", i, movieCur->actorCur->name);
				if (movieCur->actorCur->linkAnotherA != NULL)
					printf("(%s)\n", movieCur->actorCur->linkAnotherA->birth->name);
				else
					printf("(-)\n");
				movieCur->actorCur = movieCur->actorCur->next;
			}
		}
	}//movie
	else if (strcmp(mda, "d") == 0) {
		if (director == NULL) {
			printf("@@ No such record!!\n");
			return;
		}
		directorCur = director;
		if (directorCur->serialNumber == printNum)
			++check;
		else {
			while (directorCur->next != NULL) {

				directorCur = directorCur->next;
				if (directorCur->serialNumber == printNum) {
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
			printf("%d, %s, %c, %s\n", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

			directorCur->titleCur = directorCur->title;
			int i = 0;
			while (directorCur->titleCur != NULL) {
				++i;
				printf("    T%d:%s", i, directorCur->titleCur->name);
				if (directorCur->titleCur->linkAnotherM != NULL)
					printf(", %d, %d\n", directorCur->titleCur->linkAnotherM->year, directorCur->titleCur->linkAnotherM->runTime);
				else
					printf(", (-), (-)\n");
				directorCur->titleCur = directorCur->titleCur->next;
			}
		}
	}//director
	else if (strcmp(mda, "a") == 0) {
		if (actor == NULL) {
			printf("@@ No such record!!\n");
			return;
		}
		actorCur = actor;
		if (actorCur->serialNumber == printNum)
			++check;
		else {
			while (actorCur->next != NULL) {

				actorCur = actorCur->next;
				if (actorCur->serialNumber == printNum) {
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
			printf("%d, %s, %c, %s\n", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

			actorCur->titleCur = actorCur->title;
			int i = 0;
			while (actorCur->titleCur != NULL) {
				++i;
				printf("    T%d:%s", i, actorCur->titleCur->name);
				if (actorCur->titleCur->linkAnotherM != NULL)
					printf(", %d, %d\n", actorCur->titleCur->linkAnotherM->year, actorCur->titleCur->linkAnotherM->runTime);
				else
					printf(", (-), (-)\n");
				actorCur->titleCur = actorCur->titleCur->next;
			}
		}
	}//actor

}
