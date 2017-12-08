#include "movieProject.h"

		extern Movie *movie, *movieTail, *movieCur, *movieNew;
		extern Director *director, *directorTail, *directorCur, *directorNew;
		extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

		extern FILE *mp, *dp, *ap;

		extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
void sort(char* mda, char* option, char* fileName) {

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

		if (option == 0)
			qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);
		else {
			if (strcmp(option, "t") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);
			else if (strcmp(option, "g") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareGenre);
			else if (strcmp(option, "d") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareDirector);
			else if (strcmp(option, "y") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareYear);
			else if (strcmp(option, "r") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareRuntime);
			else if (strcmp(option, "a") == 0)
				qsort(sortMovie, cnt, sizeof(Movie*), compareActor);
		}
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
		if (fileName != 0) {
			smp = fopen(fileName, "wt");

			for (int i = 0; i < cnt; ++i) {
				if (i == 3) {
					movieCur = movie;

					for (int i = 0; i < cnt; ++i) {
						*(sortMovie + i) = movieCur;

						movieCur = movieCur->next;
					}

					if (option == 0)
						qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);
					else {
						if (strcmp(option, "t") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);
						else if (strcmp(option, "g") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareGenre);
						else if (strcmp(option, "d") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareDirector);
						else if (strcmp(option, "y") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareYear);
						else if (strcmp(option, "r") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareRuntime);
						else if (strcmp(option, "a") == 0)
							qsort(sortMovie, cnt, sizeof(Movie*), compareActor);
					}
				}
				fprintf(smp, "%d:%s:%s:%s:%d:%d:", (*(sortMovie + i))->serialNumber, (*(sortMovie + i))->title->name, (*(sortMovie + i))->genre->name, (*(sortMovie + i))->director->name, (*(sortMovie + i))->year, (*(sortMovie + i))->runTime);

				(*(sortMovie + i))->actorCur = (*(sortMovie + i))->actor;

				fprintf(smp, "%s", (*(sortMovie + i))->actorCur->name);

				while ((*(sortMovie + i))->actorCur->next != NULL)
				{
					(*(sortMovie + i))->actorCur = (*(sortMovie + i))->actorCur->next;
					fprintf(smp, ", %s", (*(sortMovie + i))->actorCur->name);
				}

				fprintf(smp, "\n");
			}

			fclose(smp);

		}
	}
}

int compareTitle(const void *a, const void *b)
{

	return(strcmp((*(const Movie**)a)->title->name, (*(const Movie**)b)->title->name));
}
int compareGenre(const void *a, const void *b)
{

	return(strcmp((*(const Movie**)a)->genre->name, (*(const Movie**)b)->genre->name));
}
int compareDirector(const void *a, const void *b)
{

	return(strcmp((*(const Movie**)a)->director->name, (*(const Movie**)b)->director->name));
}

int compareYear(const void *a, const void *b)
{
	int num1 = (*(const Movie**)a)->year;
	int num2 = (*(const Movie**)b)->year;

	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;

}
int compareRuntime(const void *a, const void *b)
{
	int num1 = (*(const Movie**)a)->runTime;
	int num2 = (*(const Movie**)b)->runTime;

	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;
}
int compareActor(const void *a, const void *b)
{
	return(strcmp((*(const Movie**)a)->actor->name, (*(const Movie**)b)->actor->name));

}
