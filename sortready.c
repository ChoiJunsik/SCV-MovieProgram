#include "movieProject.h"

		extern Movie *movie, *movieTail, *movieCur, *movieNew;
		extern Director *director, *directorTail, *directorCur, *directorNew;
		extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

		extern FILE *mp, *dp, *ap;

		extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
		void sort(char* mda, char* option) {

			FILE* smp, *sdp, *sap;
			smp = sdp = sap = NULL;
			Movie** sortMovie = NULL;
			Director** sortDirector = NULL;
			Actor** sortActor = NULL;
			int cnt = 0;
			if (strcmp(mda, "m") == 0) {
				if (movie == NULL) {
					printf("No such record!!\n");
					return;
				}
				movieCur = movie;
				while (movieCur != NULL) {
					++cnt;
					movieCur = movieCur->next;
				}

				movieCur = movie;
				sortMovie = (Movie**)malloc(cnt);

				for (int i = 0; i < cnt; ++i) {
					*(sortMovie + i) = movieCur;

					movieCur = movieCur->next;
				}


				qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);

				for (int i = 0; i < cnt; ++i) {
					printf("%d:%s:%s:%s:%d:%d:", (*(sortMovie + i))->serialNumber, (*(sortMovie + i))->title->name, (*(sortMovie + i))->genre->name, (*(sortMovie + i))->director->name, (*(sortMovie + i))->year, (*(sortMovie + i))->runTime);

					(*(sortMovie + i))->actorCur = (*(sortMovie + i))->actor;

					printf("%s", (*(sortMovie + i))->actorCur->name);

					while ((*(sortMovie + i))->actorCur->next != NULL)
					{
						(*(sortMovie + i))->actorCur = (*(sortMovie + i))->actorCur->next;
						printf(", %s", (*(sortMovie + i))->actorCur->name);
					}

					printf("\n");
				}
			}
		}
