void save(char* mda, char* option, char* fileName) {
	int optLen;
	char* opt;
	if (option != 0) {
		optLen = strlen(option);
		opt = (char*)malloc(optLen);
		strcpy(opt, option + 1);
	}
	FILE* smp, *sdp, *sap;
	smp = sdp = sap = NULL;
	if (strcmp(mda, "m") == 0) {
		if (movie == NULL) {
			printf("@@ No Data!!\n");
			return;
		}
		if (fileName != 0)
			smp = fopen(fileName, "wt");
		else
			smp = fopen("movie_list", "wt");
		if (option == 0) {
			movieCur = movie;
			while (movieCur != NULL) {
				fprintf(smp, "%d", movieCur->serialNumber);
				fprintf(smp, ":%s", movieCur->title->name);
				fprintf(smp, "\n");
				movieCur = movieCur->next;
			}
		}
		else {
			movieCur = movie;
			while (movieCur != NULL) {
				fprintf(smp, "%d", movieCur->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 't') {
						fprintf(smp, ":%s", movieCur->title->name);
					}
					else if (*(opt + i) == 'g') {
						fprintf(smp, ":%s", movieCur->genre->name);
					}
					else if (*(opt + i) == 'd') {
						fprintf(smp, ":%s", movieCur->director->name);
					}
					else if (*(opt + i) == 'y') {
						fprintf(smp, ":%d", movieCur->year);
					}
					else if (*(opt + i) == 'r') {
						fprintf(smp, ":%d", movieCur->runTime);
					}
					else if (*(opt + i) == 'a') {
						movieCur->actorCur = movieCur->actor;
						fprintf(smp, ":%s", movieCur->actorCur->name);
						movieCur->actorCur = movieCur->actorCur->next;
						while (movieCur->actorCur != NULL) {
							fprintf(smp, ", %s", movieCur->actorCur->name);
							movieCur->actorCur = movieCur->actorCur->next;
						}
					}
				}
				fprintf(smp, "\n");

				movieCur = movieCur->next;
			}

			free(opt);
		}
		fclose(smp);
	}//movie
	else if (strcmp(mda, "d") == 0) {
		if (director == NULL) {
			printf("@@ No Data!!\n");
			return;
		}
		if (fileName != 0)
			sdp = fopen(fileName, "wt");
		else
			sdp = fopen("director_list", "wt");
		if (option == 0) {
			directorCur = director;
			while (directorCur != NULL) {
				fprintf(sdp, "%d", directorCur->serialNumber);
				fprintf(sdp, ":%s", directorCur->director->name);
				fprintf(sdp, "\n");
				directorCur = directorCur->next;
			}
		}
		else {
			directorCur = director;
			while (directorCur != NULL) {
				fprintf(sdp, "%d", directorCur->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'n') {
						fprintf(sdp, ":%s", directorCur->director->name);
					}
					else if (*(opt + i) == 's') {
						fprintf(sdp, ":%c", directorCur->sex);
					}
					else if (*(opt + i) == 'b') {
						fprintf(sdp, ":%s", directorCur->birth->name);
					}
					else if (*(opt + i) == 'm') {
						directorCur->titleCur = directorCur->title;
						fprintf(sdp, ":%s", directorCur->titleCur->name);
						directorCur->titleCur = directorCur->titleCur->next;
						while (directorCur->titleCur != NULL) {
							fprintf(sdp, ", %s", directorCur->titleCur->name);
							directorCur->titleCur = directorCur->titleCur->next;
						}
					}
				}
				fprintf(sdp, "\n");

				directorCur = directorCur->next;
			}

			free(opt);
		}
		fclose(sdp);
	}//director
	else if (strcmp(mda, "a") == 0) {
		if (actor == NULL) {
			printf("@@ No Data!!\n");
			return;
		}
		if (fileName != 0)
			sap = fopen(fileName, "wt");
		else
			sap = fopen("actor_list", "wt");
		if (option == 0) {
			actorCur = actor;
			while (actorCur != NULL) {
				fprintf(sap, "%d", actorCur->serialNumber);
				fprintf(sap, ":%s", actorCur->actor->name);
				fprintf(sap, "\n");
				actorCur = actorCur->next;
			}
		}
		else {
			actorCur = actor;
			while (actorCur != NULL) {
				fprintf(sap, "%d", actorCur->serialNumber);
				for (int i = 0; i < optLen - 1; ++i) {
					if (*(opt + i) == 'n') {
						fprintf(sap, ":%s", actorCur->actor->name);
					}
					else if (*(opt + i) == 's') {
						fprintf(sap, ":%c", actorCur->sex);
					}
					else if (*(opt + i) == 'b') {
						fprintf(sap, ":%s", actorCur->birth->name);
					}
					else if (*(opt + i) == 'm') {
						actorCur->titleCur = actorCur->title;
						fprintf(sap, ":%s", actorCur->titleCur->name);
						actorCur->titleCur = actorCur->titleCur->next;
						while (actorCur->titleCur != NULL) {
							fprintf(sap, ", %s", actorCur->titleCur->name);
							actorCur->titleCur = actorCur->titleCur->next;
						}
					}
				}
				fprintf(sap, "\n");

				actorCur = actorCur->next;
			}

			free(opt);
		}
		fclose(sap);
	}//actor
}
