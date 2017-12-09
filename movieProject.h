#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
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
void print(char* mda, char* num);
void sort(char* mda, char* option, char* fileName);
int compareChar(const void *a, const void *b);
int compareInt(const void *a, const void *b);
int compareTitle(const void *a, const void *b);
int compareGenre(const void *a, const void *b);
int compareDirector(const void *a, const void *b);
int compareYear(const void *a, const void *b);
int compareRuntime(const void *a, const void *b);
int compareActor(const void *a, const void *b);
int compareNameD(const void *a, const void *b);
int compareSexD(const void *a, const void *b);
int compareBirthD(const void *a, const void *b);
int compareMovieD(const void *a, const void *b);
int compareNameA(const void *a, const void *b);
int compareSexA(const void *a, const void *b);
int compareBirthA(const void *a, const void *b);
int compareMovieA(const void *a, const void *b);
void makeMovieList(void);
void makeDirectorList(void);
void makeActorList(void);
void save(char* mda, char* option, char* fileName);
void end(void);
void search(char* mda, char* string);
void interrupt(int);
