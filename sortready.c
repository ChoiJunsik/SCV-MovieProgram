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
				}// for문 마지막에 주소 값이 변경되는 기이한 현상, 고로 하드코딩으로 대처..
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
	}//movie일때
	else if (strcmp(mda, "d") == 0) {
		if (director == NULL) {
			printf("No such record!!\n");
			return;
		}
		directorCur = director;
		while (directorCur != NULL) {
			++cnt;
			directorCur = directorCur->next;
		}

		directorCur = director;
		sortDirector = (Director**)malloc(cnt);

		for (int i = 0; i < cnt; ++i) {
			*(sortDirector + i) = directorCur;

			directorCur = directorCur->next;
		}
		if (option == 0)
			qsort(sortDirector, cnt, sizeof(Director*), compareNameD);
		else {
			if (strcmp(option, "n") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareNameD);
			else if (strcmp(option, "s") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareSexD);
			else if (strcmp(option, "b") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareBirthD);
			else if (strcmp(option, "m") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareMovieD);
		}
		for (int i = 0; i < cnt; ++i) {
			printf("%d:%s:%c:%s:", (*(sortDirector + i))->serialNumber, (*(sortDirector + i))->director->name, (*(sortDirector + i))->sex, (*(sortDirector + i))->birth->name);

			(*(sortDirector + i))->titleCur = (*(sortDirector + i))->title;

			printf("%s", (*(sortDirector + i))->titleCur->name);

			while ((*(sortDirector + i))->titleCur->next != NULL)
			{
				(*(sortDirector + i))->titleCur = (*(sortDirector + i))->titleCur->next;
				printf(", %s", (*(sortDirector + i))->titleCur->name);
			}

			printf("\n");
		}

		if (fileName != 0) {


			sdp = fopen(fileName, "wt");

			for (int i = 0; i < cnt; ++i) {
				if (i == 3) {
					directorCur = director;
					for (int i = 0; i < cnt; ++i) {
						*(sortDirector + i) = directorCur;

						directorCur = directorCur->next;
					}
					if (option == 0)
						qsort(sortDirector, cnt, sizeof(Director*), compareNameD);
					else {
						if (strcmp(option, "n") == 0)
							qsort(sortDirector, cnt, sizeof(Director*), compareNameD);
						else if (strcmp(option, "s") == 0)
							qsort(sortDirector, cnt, sizeof(Director*), compareSexD);
						else if (strcmp(option, "b") == 0)
							qsort(sortDirector, cnt, sizeof(Director*), compareBirthD);
						else if (strcmp(option, "m") == 0)
							qsort(sortDirector, cnt, sizeof(Director*), compareMovieD);
					}
				}// for문 마지막에 주소 값이 변경되는 기이한 현상, 고로 하드코딩으로 대처..
				fprintf(sdp, "%d:%s:%c:%s:", (*(sortDirector + i))->serialNumber, (*(sortDirector + i))->director->name, (*(sortDirector + i))->sex, (*(sortDirector + i))->birth->name);

				(*(sortDirector + i))->titleCur = (*(sortDirector + i))->title;

				fprintf(sdp, "%s", (*(sortDirector + i))->titleCur->name);

				while ((*(sortDirector + i))->titleCur->next != NULL)
				{
					(*(sortDirector + i))->titleCur = (*(sortDirector + i))->titleCur->next;
					fprintf(sdp, ", %s", (*(sortDirector + i))->titleCur->name);
				}

				fprintf(sdp, "\n");
			}
			fclose(sdp);
		}

	}//director일때
	else if (strcmp(mda, "a") == 0) {
		if (actor == NULL) {
			printf("No such record!!\n");
			return;
		}
		actorCur = actor;
		while (actorCur != NULL) {
			++cnt;
			actorCur = actorCur->next;
		}

		actorCur = actor;
		sortActor = (Actor**)malloc(cnt);

		for (int i = 0; i < cnt; ++i) {
			*(sortActor + i) = actorCur;

			actorCur = actorCur->next;
		}
		if (option == 0)
			qsort(sortActor, cnt, sizeof(Actor*), compareNameA);
		else {
			if (strcmp(option, "n") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareNameA);
			else if (strcmp(option, "s") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareSexA);
			else if (strcmp(option, "b") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareBirthA);
			else if (strcmp(option, "m") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareMovieA);
		}
		for (int i = 0; i < cnt; ++i) {
			printf("%d:%s:%c:%s:", (*(sortActor + i))->serialNumber, (*(sortActor + i))->actor->name, (*(sortActor + i))->sex, (*(sortActor + i))->birth->name);

			(*(sortActor + i))->titleCur = (*(sortActor + i))->title;

			printf("%s", (*(sortActor + i))->titleCur->name);

			while ((*(sortActor + i))->titleCur->next != NULL)
			{
				(*(sortActor + i))->titleCur = (*(sortActor + i))->titleCur->next;
				printf(", %s", (*(sortActor + i))->titleCur->name);
			}

			printf("\n");
		}


		if (fileName != 0) {


			sap = fopen(fileName, "wt");
			for (int i = 0; i < cnt; ++i) {
				if (i == 3) {
					actorCur = actor;
					for (int i = 0; i < cnt; ++i) {
						*(sortActor + i) = actorCur;

						actorCur = actorCur->next;
					}
					if (option == 0)
						qsort(sortActor, cnt, sizeof(Actor*), compareNameA);
					else {
						if (strcmp(option, "n") == 0)
							qsort(sortActor, cnt, sizeof(Actor*), compareNameA);
						else if (strcmp(option, "s") == 0)
							qsort(sortActor, cnt, sizeof(Actor*), compareSexA);
						else if (strcmp(option, "b") == 0)
							qsort(sortActor, cnt, sizeof(Actor*), compareBirthA);
						else if (strcmp(option, "m") == 0)
							qsort(sortActor, cnt, sizeof(Actor*), compareMovieA);
					}
				}// for문 마지막에 주소 값이 변경되는 기이한 현상, 고로 하드코딩으로 대처..

				fprintf(sap, "%d:%s:%c:%s:", (*(sortActor + i))->serialNumber, (*(sortActor + i))->actor->name, (*(sortActor + i))->sex, (*(sortActor + i))->birth->name);

				(*(sortActor + i))->titleCur = (*(sortActor + i))->title;

				fprintf(sap, "%s", (*(sortActor + i))->titleCur->name);

				while ((*(sortActor + i))->titleCur->next != NULL)
				{
					(*(sortActor + i))->titleCur = (*(sortActor + i))->titleCur->next;
					fprintf(sap, ", %s", (*(sortActor + i))->titleCur->name);
				}

				fprintf(sap, "\n");
			}
			fclose(sap);
		}
	}//Actor일때
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
int compareNameD(const void *a, const void *b)
{

	return(strcmp((*(const Director**)a)->director->name, (*(const Director**)b)->director->name));
}
int compareSexD(const void *a, const void *b)
{
	char sex1 = (*(const Director**)a)->sex;
	char sex2 = (*(const Director**)b)->sex;

	if (sex1 < sex2)
		return -1;

	if (sex1 > sex2)
		return 1;

	return 0;
}
int compareBirthD(const void *a, const void *b)
{

	return(strcmp((*(const Director**)a)->birth->name, (*(const Director**)b)->birth->name));
}
int compareMovieD(const void *a, const void *b)
{

	return(strcmp((*(const Director**)a)->title->name, (*(const Director**)b)->title->name));
}
int compareNameA(const void *a, const void *b)
{

	return(strcmp((*(const Actor**)a)->actor->name, (*(const Actor**)b)->actor->name));
}
int compareSexA(const void *a, const void *b)
{
	char sex1 = (*(const Actor**)a)->sex;
	char sex2 = (*(const Actor**)b)->sex;

	if (sex1 < sex2)
		return -1;

	if (sex1 > sex2)
		return 1;

	return 0;
}
int compareBirthA(const void *a, const void *b)
{

	return(strcmp((*(const Actor**)a)->birth->name, (*(const Actor**)b)->birth->name));
}
int compareMovieA(const void *a, const void *b)
{

	return(strcmp((*(const Actor**)a)->title->name, (*(const Actor**)b)->title->name));
}
