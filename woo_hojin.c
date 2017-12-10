#include "movieProject.h"

extern Movie *movie, *movieTail, *movieCur, *movieNew;
extern Director *director, *directorTail, *directorCur, *directorNew;
extern Actor *actor, *actorTail, *actor, *actorCur, *actorNew;

extern FILE *mp, *dp, *ap;

extern int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber;
void sort(char* mda, char* option, char* fileName) {

	FILE* smp, *sdp, *sap;
	smp = sdp = sap = NULL;  // 소트만을 위한 파일포인터 선언 및 NULL 저장
	Movie** sortMovie = NULL;
	Director** sortDirector = NULL;
	Actor** sortActor = NULL;         // 포인터배열을 만들기 위한 더블 포인터변수 선언
	int cnt = 0;
	if (strcmp(mda, "m") == 0) {
		if (movie == NULL) {         // 정렬할게 없을 시 종료
			printf("No such record!!\n");
			return;
		}
		movieCur = movie;
		while (movieCur != NULL) {
			++cnt;
			movieCur = movieCur->next;
		}                  // 노드가 몇갠지 세기

		movieCur = movie;
		sortMovie = (Movie**)malloc(cnt);      //포인터 배열 동적할당

		for (int i = 0; i < cnt; ++i) {
			*(sortMovie + i) = movieCur;

			movieCur = movieCur->next;
		}                                  //포인터 배열 주소 값 저장

		if (option == 0)
			qsort(sortMovie, cnt, sizeof(Movie*), compareTitle);      // 필드 지정안하면 제목으로 정렬
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
		}                                                                       // 필드에 따라 정렬
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
		}                                                                //정렬 화면에 출력
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

		}                //정렬 파일에 저장
	}//movie일때
	else if (strcmp(mda, "d") == 0) {
		if (director == NULL) {					// 정렬할게 없을 시 종료
			printf("No such record!!\n");
			return;
		}
		directorCur = director;
		while (directorCur != NULL) {
			++cnt;
			directorCur = directorCur->next;
		}
		// 노드가 몇갠지 세기
		directorCur = director;
		sortDirector = (Director**)malloc(cnt);					//포인터 배열 동적할당

		for (int i = 0; i < cnt; ++i) {
			*(sortDirector + i) = directorCur;

			directorCur = directorCur->next;
		}																								//포인터 배열 주소 값 저장
		if (option == 0)
			qsort(sortDirector, cnt, sizeof(Director*), compareNameD);	 // 필드 지정안하면 이름으로 정렬
		else {
			if (strcmp(option, "n") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareNameD);
			else if (strcmp(option, "s") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareSexD);
			else if (strcmp(option, "b") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareBirthD);
			else if (strcmp(option, "m") == 0)
				qsort(sortDirector, cnt, sizeof(Director*), compareMovieD);
		}																																						 // 필드에 따라 정렬
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
		}																																								//정렬 화면에 출력

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
		}																	 //정렬 파일에 저장

	}//director일때
	else if (strcmp(mda, "a") == 0) {
		if (actor == NULL) {																	// 정렬할게 없을 시 종료
			printf("No such record!!\n");
			return;
		}
		actorCur = actor;
		while (actorCur != NULL) {
			++cnt;
			actorCur = actorCur->next;
		}																			 // 노드가 몇갠지 세기

		actorCur = actor;
		sortActor = (Actor**)malloc(cnt);							//포인터 배열 동적할당

		for (int i = 0; i < cnt; ++i) {
			*(sortActor + i) = actorCur;

			actorCur = actorCur->next;						//포인터 배열 주소 값 저장
		}
		if (option == 0)
			qsort(sortActor, cnt, sizeof(Actor*), compareNameA);					// 필드 지정안하면 이름으로 정렬
		else {
			if (strcmp(option, "n") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareNameA);
			else if (strcmp(option, "s") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareSexA);
			else if (strcmp(option, "b") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareBirthA);
			else if (strcmp(option, "m") == 0)
				qsort(sortActor, cnt, sizeof(Actor*), compareMovieA);
		}																																			// 필드에 따라 정렬
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
		//정렬 화면에 출력

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
		}																												//정렬 파일에 저장
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

///////////////////////////////////////////////퀵소트를 위한 함수들


void search(char* mda, char* string) {
	int strLen = strlen(string) + 1;
	int optLen = strlen(mda) + 1;
	int cnt = 0, check = 0;
	char* input = (char*)malloc(strLen);
	char* option = (char*)malloc(optLen);
	strcpy(input, string);
	strcpy(option, mda);
	for (int i = 0; i < optLen - 1; ++i) {
		if (*(option + i) == 'm') {
			printf("\n@@ This is movie search result\n");
			if (*input == '*') {
				movieCur = movie;
				if (strlen(input) == 1) {
					while (movieCur != NULL) {
						++check;
						printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

						movieCur->actorCur = movieCur->actor;

						printf("%s", movieCur->actorCur->name);

						while (movieCur->actorCur->next != NULL)
						{
							movieCur->actorCur = movieCur->actorCur->next;
							printf(", %s", movieCur->actorCur->name);
						}

						printf("\n");
						movieCur = movieCur->next;
					}
				}
				else {
					while (movieCur != NULL) {
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(movieCur->title->name + strlen(movieCur->title->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')            // ?일땐 무시하고 무조건 cnt ++
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}

						cnt = 0;
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(movieCur->director->name + strlen(movieCur->director->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?') // ?일땐 무시하고 무조건 cnt ++
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}
						cnt = 0;
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(movieCur->genre->name + strlen(movieCur->genre->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')// ?일땐 무시하고 무조건 cnt ++
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}
						cnt = 0;
						movieCur->actorCur = movieCur->actor;
						while (movieCur->actorCur != NULL) {
							for (int j = 0; j < strLen - 2; ++j) {
								if (*(movieCur->actorCur->name + strlen(movieCur->actorCur->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')
									++cnt;
							}
							if (cnt == strLen - 2) {
								++check;
								printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

								movieCur->actorCur = movieCur->actor;

								printf("%s", movieCur->actorCur->name);

								while (movieCur->actorCur->next != NULL)
								{
									movieCur->actorCur = movieCur->actorCur->next;
									printf(", %s", movieCur->actorCur->name);
								}

								printf("\n");
								break;
							}
							cnt = 0;
							movieCur->actorCur = movieCur->actorCur->next;

						}

						cnt = 0;
						movieCur = movieCur->next;
					}
				}
			}//맨앞 메타문자* 전체출력
			else if (*(input + strLen - 2) == '*') {       //맨뒤가 * 일경우  * 이전만 비교해준다
				movieCur = movie;
				while (movieCur != NULL) {
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(movieCur->title->name + j) == *(input + j) || *(input + j) == '?')            // ?일땐 무시하고 무조건 cnt ++
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

						movieCur->actorCur = movieCur->actor;

						printf("%s", movieCur->actorCur->name);

						while (movieCur->actorCur->next != NULL)
						{
							movieCur->actorCur = movieCur->actorCur->next;
							printf(", %s", movieCur->actorCur->name);
						}

						printf("\n");
						movieCur = movieCur->next;

						cnt = 0;
						continue;
					}

					cnt = 0;
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(movieCur->director->name + j) == *(input + j) || *(input + j) == '?') // ?일땐 무시하고 무조건 cnt ++
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

						movieCur->actorCur = movieCur->actor;

						printf("%s", movieCur->actorCur->name);

						while (movieCur->actorCur->next != NULL)
						{
							movieCur->actorCur = movieCur->actorCur->next;
							printf(", %s", movieCur->actorCur->name);
						}

						printf("\n");
						movieCur = movieCur->next;

						cnt = 0;
						continue;
					}
					cnt = 0;
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(movieCur->genre->name + j) == *(input + j) || *(input + j) == '?')// ?일땐 무시하고 무조건 cnt ++
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

						movieCur->actorCur = movieCur->actor;

						printf("%s", movieCur->actorCur->name);

						while (movieCur->actorCur->next != NULL)
						{
							movieCur->actorCur = movieCur->actorCur->next;
							printf(", %s", movieCur->actorCur->name);
						}

						printf("\n");
						movieCur = movieCur->next;

						cnt = 0;
						continue;
					}
					cnt = 0;
					movieCur->actorCur = movieCur->actor;
					while (movieCur->actorCur != NULL) {
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(movieCur->actorCur->name + j) == *(input + j) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							break;
						}
						cnt = 0;
						movieCur->actorCur = movieCur->actorCur->next;

					}

					cnt = 0;
					movieCur = movieCur->next;
				}
			}//맨뒤가 메타문자 *
			else {
				cnt = 0;
				movieCur = movie;
				while (movieCur != NULL) {
					if (strlen(movieCur->title->name) == strlen(input)) {             //* 메타 문자가 없으면 다 비교해줘야한다
						for (int j = 0; j < strLen - 1; ++j) {
							if ((*(movieCur->title->name + j) == *(input + j)) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 1) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}
					}

					cnt = 0;
					if (strlen(movieCur->director->name) == strlen(input)) {
						for (int j = 0; j < strLen - 1; ++j) {
							if ((*(movieCur->director->name + j) == *(input + j)) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 1) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}
					}
					cnt = 0;
					if (strlen(movieCur->genre->name) == strlen(input)) {
						for (int j = 0; j < strLen - 1; ++j) {
							if ((*(movieCur->genre->name + j) == *(input + j)) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 1) {
							++check;
							printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

							movieCur->actorCur = movieCur->actor;

							printf("%s", movieCur->actorCur->name);

							while (movieCur->actorCur->next != NULL)
							{
								movieCur->actorCur = movieCur->actorCur->next;
								printf(", %s", movieCur->actorCur->name);
							}

							printf("\n");
							movieCur = movieCur->next;

							cnt = 0;
							continue;
						}
					}

					cnt = 0;
					movieCur->actorCur = movieCur->actor;
					while (movieCur->actorCur != NULL) {
						if (strlen(movieCur->actorCur->name) == strlen(input)) {
							for (int j = 0; j < strLen - 1; ++j) {
								if ((*(movieCur->actorCur->name + j) == *(input + j)) || *(input + j) == '?')
									++cnt;
							}
							if (cnt == strLen - 1) {
								++check;
								printf("%d:%s:%s:%s:%d:%d:", movieCur->serialNumber, movieCur->title->name, movieCur->genre->name, movieCur->director->name, movieCur->year, movieCur->runTime);

								movieCur->actorCur = movieCur->actor;

								printf("%s", movieCur->actorCur->name);

								while (movieCur->actorCur->next != NULL)
								{
									movieCur->actorCur = movieCur->actorCur->next;
									printf(", %s", movieCur->actorCur->name);
								}

								printf("\n");
								break;
							}
						}
						movieCur->actorCur = movieCur->actorCur->next;

						cnt = 0;
					}

					cnt = 0;
					movieCur = movieCur->next;
				}//?일경우 + 그냥 비교
			}
			if (check == 0)
				printf("@@ No such record.\n");
			check = 0;
		}//movie
		else if (*(option + i) == 'd') {
			printf("\n@@ This is director search result\n");
			if (*input == '*') {
				directorCur = director;
				if(strlen(input)==1){
				while (directorCur != NULL) {

					++check;
					printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

					directorCur->titleCur = directorCur->title;

					printf("%s", directorCur->titleCur->name);

					while (directorCur->titleCur->next != NULL)
					{
						directorCur->titleCur = directorCur->titleCur->next;
						printf(", %s", directorCur->titleCur->name);
					}

					printf("\n");
					directorCur = directorCur->next;
				}
			}
			else{
				while (directorCur != NULL) {
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(directorCur->director->name + strlen(directorCur->director->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

						directorCur->titleCur = directorCur->title;

						printf("%s", directorCur->titleCur->name);

						while (directorCur->titleCur->next != NULL)
						{
							directorCur->titleCur = directorCur->titleCur->next;
							printf(", %s", directorCur->titleCur->name);
						}

						printf("\n");

						cnt = 0;
						directorCur = directorCur->next;
						continue;
					}
					cnt = 0;
					directorCur->titleCur = directorCur->title;
					while (directorCur->titleCur != NULL) {
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(directorCur->titleCur->name + strlen(directorCur->titleCur->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

							directorCur->titleCur = directorCur->title;

							printf("%s", directorCur->titleCur->name);

							while (directorCur->titleCur->next != NULL)
							{
								directorCur->titleCur = directorCur->titleCur->next;
								printf(", %s", directorCur->titleCur->name);
							}

							printf("\n");
							break;
						}
						cnt = 0;
						directorCur->titleCur = directorCur->titleCur->next;

					}

					cnt = 0;
					directorCur = directorCur->next;
				}

			}
			}//맨앞 메타문자* 전체출력
			else if (*(input + strLen - 2) == '*') {
				directorCur = director;
				while (directorCur != NULL) {
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(directorCur->director->name + j) == *(input + j) || *(input + j) == '?')
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

						directorCur->titleCur = directorCur->title;

						printf("%s", directorCur->titleCur->name);

						while (directorCur->titleCur->next != NULL)
						{
							directorCur->titleCur = directorCur->titleCur->next;
							printf(", %s", directorCur->titleCur->name);
						}

						printf("\n");

						cnt = 0;
						directorCur = directorCur->next;
						continue;
					}
					cnt = 0;
					directorCur->titleCur = directorCur->title;
					while (directorCur->titleCur != NULL) {
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(directorCur->titleCur->name + j) == *(input + j) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

							directorCur->titleCur = directorCur->title;

							printf("%s", directorCur->titleCur->name);

							while (directorCur->titleCur->next != NULL)
							{
								directorCur->titleCur = directorCur->titleCur->next;
								printf(", %s", directorCur->titleCur->name);
							}

							printf("\n");
							break;
						}
						cnt = 0;
						directorCur->titleCur = directorCur->titleCur->next;

					}

					cnt = 0;
					directorCur = directorCur->next;
				}
			}//맨뒤가 메타문자 *
			else {
				cnt = 0;
				directorCur = director;
				while (directorCur != NULL) {
					if (strlen(directorCur->director->name) == strlen(input)) {
						for (int j = 0; j < strLen - 1; ++j) {
							if ((*(directorCur->director->name + j) == *(input + j)) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 1) {
							++check;
							printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

							directorCur->titleCur = directorCur->title;

							printf("%s", directorCur->titleCur->name);

							while (directorCur->titleCur->next != NULL)
							{
								directorCur->titleCur = directorCur->titleCur->next;
								printf(", %s", directorCur->titleCur->name);
							}

							printf("\n");

							cnt = 0;
							directorCur = directorCur->next;
							continue;
						}
					}
					cnt = 0;
					directorCur->titleCur = directorCur->title;
					while (directorCur->titleCur != NULL) {
						if (strlen(directorCur->titleCur->name) == strlen(input)) {
							for (int j = 0; j < strLen - 1; ++j) {
								if ((*(directorCur->titleCur->name + j) == *(input + j)) || *(input + j) == '?')
									++cnt;
							}
							if (cnt == strLen - 1) {
								++check;
								printf("%d:%s:%c:%s:", directorCur->serialNumber, directorCur->director->name, directorCur->sex, directorCur->birth->name);

								directorCur->titleCur = directorCur->title;

								printf("%s", directorCur->titleCur->name);

								while (directorCur->titleCur->next != NULL)
								{
									directorCur->titleCur = directorCur->titleCur->next;
									printf(", %s", directorCur->titleCur->name);
								}

								printf("\n");
								break;
							}
						}
						directorCur->titleCur = directorCur->titleCur->next;

						cnt = 0;
					}

					cnt = 0;
					directorCur = directorCur->next;
				}//?일경우 + 그냥 비교
			}
			if (check == 0)
				printf("@@ No such record.\n");
			check = 0;
		}//director
		else if (*(option + i) == 'a') {
			printf("\n@@ This is actor search result\n");
			if (*input == '*') {
			  actorCur = actor;
			  if(strlen(input)==1){
			  while (actorCur != NULL) {

			    ++check;
			    printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

			    actorCur->titleCur = actorCur->title;

			    printf("%s", actorCur->titleCur->name);

			    while (actorCur->titleCur->next != NULL)
			    {
			      actorCur->titleCur = actorCur->titleCur->next;
			      printf(", %s", actorCur->titleCur->name);
			    }

			    printf("\n");
			    actorCur = actorCur->next;
			  }
			}
			else{
			  while (actorCur != NULL) {
			    for (int j = 0; j < strLen - 2; ++j) {
			      if (*(actorCur->actor->name + strlen(actorCur->actor->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')
			        ++cnt;
			    }
			    if (cnt == strLen - 2) {
			      ++check;
			      printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

			      actorCur->titleCur = actorCur->title;

			      printf("%s", actorCur->titleCur->name);

			      while (actorCur->titleCur->next != NULL)
			      {
			        actorCur->titleCur = actorCur->titleCur->next;
			        printf(", %s", actorCur->titleCur->name);
			      }

			      printf("\n");

			      cnt = 0;
			      actorCur = actorCur->next;
			      continue;
			    }
			    cnt = 0;
			    actorCur->titleCur = actorCur->title;
			    while (actorCur->titleCur != NULL) {
			      for (int j = 0; j < strLen - 2; ++j) {
			        if (*(actorCur->titleCur->name + strlen(actorCur->titleCur->name) - (strLen - 2) + j) == *(input + j + 1) || *(input + j + 1) == '?')
			          ++cnt;
			      }
			      if (cnt == strLen - 2) {
			        ++check;
			        printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

			        actorCur->titleCur = actorCur->title;

			        printf("%s", actorCur->titleCur->name);

			        while (actorCur->titleCur->next != NULL)
			        {
			          actorCur->titleCur = actorCur->titleCur->next;
			          printf(", %s", actorCur->titleCur->name);
			        }

			        printf("\n");
			        break;
			      }
			      cnt = 0;
			      actorCur->titleCur = actorCur->titleCur->next;

			    }
			
			    cnt = 0;
			    actorCur = actorCur->next;
			  }

			}
			}//맨앞 메타문자* 전체출력
			else if (*(input + strLen - 2) == '*') {
				actorCur = actor;
				while (actorCur != NULL) {
					for (int j = 0; j < strLen - 2; ++j) {
						if (*(actorCur->actor->name + j) == *(input + j) || *(input + j) == '?')
							++cnt;
					}
					if (cnt == strLen - 2) {
						++check;
						printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

						actorCur->titleCur = actorCur->title;

						printf("%s", actorCur->titleCur->name);

						while (actorCur->titleCur->next != NULL)
						{
							actorCur->titleCur = actorCur->titleCur->next;
							printf(", %s", actorCur->titleCur->name);
						}

						printf("\n");

						cnt = 0;
						actorCur = actorCur->next;
						continue;
					}
					cnt = 0;
					actorCur->titleCur = actorCur->title;
					while (actorCur->titleCur != NULL) {
						for (int j = 0; j < strLen - 2; ++j) {
							if (*(actorCur->titleCur->name + j) == *(input + j) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 2) {
							++check;
							printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

							actorCur->titleCur = actorCur->title;

							printf("%s", actorCur->titleCur->name);

							while (actorCur->titleCur->next != NULL)
							{
								actorCur->titleCur = actorCur->titleCur->next;
								printf(", %s", actorCur->titleCur->name);
							}

							printf("\n");
							break;
						}
						cnt = 0;
						actorCur->titleCur = actorCur->titleCur->next;

					}

					cnt = 0;
					actorCur = actorCur->next;
				}
			}//맨뒤가 메타문자 *
			else {
				cnt = 0;
				actorCur = actor;
				while (actorCur != NULL) {
					if (strlen(actorCur->actor->name) == strlen(input)) {
						for (int j = 0; j < strLen - 1; ++j) {
							if ((*(actorCur->actor->name + j) == *(input + j)) || *(input + j) == '?')
								++cnt;
						}
						if (cnt == strLen - 1) {
							++check;
							printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

							actorCur->titleCur = actorCur->title;

							printf("%s", actorCur->titleCur->name);

							while (actorCur->titleCur->next != NULL)
							{
								actorCur->titleCur = actorCur->titleCur->next;
								printf(", %s", actorCur->titleCur->name);
							}

							printf("\n");

							cnt = 0;
							actorCur = actorCur->next;
							continue;
						}
					}
					cnt = 0;
					actorCur->titleCur = actorCur->title;
					while (actorCur->titleCur != NULL) {
						if (strlen(actorCur->titleCur->name) == strlen(input)) {
							for (int j = 0; j < strLen - 1; ++j) {
								if ((*(actorCur->titleCur->name + j) == *(input + j)) || *(input + j) == '?')
									++cnt;
							}
							if (cnt == strLen - 1) {
								++check;
								printf("%d:%s:%c:%s:", actorCur->serialNumber, actorCur->actor->name, actorCur->sex, actorCur->birth->name);

								actorCur->titleCur = actorCur->title;

								printf("%s", actorCur->titleCur->name);

								while (actorCur->titleCur->next != NULL)
								{
									actorCur->titleCur = actorCur->titleCur->next;
									printf(", %s", actorCur->titleCur->name);
								}

								printf("\n");
								break;
							}
						}
						actorCur->titleCur = actorCur->titleCur->next;

						cnt = 0;
					}

					cnt = 0;
					actorCur = actorCur->next;
				}//?일경우 + 그냥 비교
			}
			if (check == 0)
				printf("@@ No such record.\n");
			check = 0;
		}//actor
	}
	free(input);
	free(option);
}
