#include "movieProject.h"

		extern Movie *movie, *movieTail, *movieCur, *movieNew;
		extern Director *director, *directorTail, *directorCur, *directorNew;
		extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

		extern FILE *mp, *dp, *ap;

		extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
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
void end(void) {
		printf("\nGood Bye...\n\n");
		exit(-1);
}

void interrupt(int signo){
	char* YorN = (char*)malloc(10);
	printf("\nControl+C\nGet Interrupt Signal.\nDo you want to exit myMOVIE program? (Y/N) ");
	scanf("%s",YorN);
	if(*YorN == 'Y' ||*YorN == 'y')
			exit(-1);
	else{
			free(YorN);
			return;
		}

}
