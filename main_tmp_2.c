#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct singleData {
	char* name;
	struct singleData* next;
} singleData;
typedef struct Director {
	int serialNumber;
	singleData* director;
	char sex;
	singleData* birth;
	singleData* title;
	struct Director* next;
} Director;
typedef struct Actor {
	int serialNumber;
	singleData* actor;
	char sex;
	singleData* birth;
	singleData* title;
	struct Actor* next;
} Actor;
typedef struct Movie {
	int serialNumber,year,runTime;
	singleData* title;
	singleData* genre;
	singleData* director;
	singleData* actor,*actorTail,*actorNew,*actorCur; // 구조체내 또다른 연결리스트
	struct Movie* next;
} Movie;

Movie *movie,*movieTail,*movieCur,*movieNew; // 연결리스트 만들기 위한 변수들
Director *director,*directorTail;
Actor *actorIndex,*actor;

FILE *mp, *dp, *ap;//파일포인터

int MovieSerialNumber, ActorSerialNumber, DirectorSerialNumber; //고유번호
//함수 선언
void add(char*);
void loadMovielogs(void);
Movie* addSameMovie(void);
char* changeColon(char*);
char* changeLogColon(char*);
////main
int main(void)
{
	movie=movieTail=movieCur=movieNew=NULL; //movie 연결리스트 만들기 위한 변수
	char* commands, *mda, *option, *num; // 옵션 받기 위한 변수
	char* input; // 명령어 분해용 변수

	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n"); //로그로부터 연결리스트 구조체 생성
  loadMovielogs();
	printf("You can use add, update, delete, search, sort, save , end commands.\n");
	while(1){
		mp = fopen("movie_log", "at");
		dp = fopen("director_log", "at");
		ap = fopen("actor_log", "at"); /// 파일 이어쓰기 모드로 열기
		input = (char*)malloc(30);
		printf("(movie) ");
  	gets(input);
		commands = strtok(input, " "); // input으로 부터 명령어 뽑아내기
		mda = strtok(NULL, " "); // m|d|a 뽑아내기
  	if (strcmp(commands, "add") == 0){

								++MovieSerialNumber; // add 호출시 전역변수로 선언된 고유번호 하나 증가
		                      add(mda);
                          //printf("add:%d:%s:%s:%s:%d:%d:%s, %s\n", movie->serialNumber, movie->title->name, movie->genre->name, movie->director->name, movie->year, movie->runTime,movie->actor->name,movie->actor->next->name);
													fclose(mp); // add후 파일 닫아서 기록
			}
			free(input); //해제시킨후 다시 받기
	}

	return 0;
}
/////////add
void add(char* mda) {
	char* actorCheck,*actorArray; // actor 연결리스트 만들기 위한 변수
	char* YorN; // 같은 내용의 구조체가 있을 시 물어보기 용
	Movie* ifSame; // 같은 내용의 구조체 주소 값 받는 변수
	if (strcmp(mda, "m") == 0) {
		movieNew = (Movie*)malloc(sizeof(Movie)); // 무비 구조체 메모리 할당
		movieNew->actor=movieNew->actorNew=movieNew->actorTail=movieNew->actorCur=NULL; //actor 연결리스트 위한 변수 NULL배정
    actorArray = (char*)malloc(255); // actor 명단 받기 위한 메모리 할당
		movieNew->serialNumber = MovieSerialNumber; //고유 번호 할당
		printf("title > ");
		movieNew->title = (singleData*)malloc(sizeof(singleData));
    movieNew->title->name = (char *)malloc(30);
		gets(movieNew->title->name); /// title 받는 과정
		printf("genre > ");
		movieNew->genre = (singleData*)malloc(sizeof(singleData));
    movieNew->genre->name = (char *)malloc(30);
		gets(movieNew->genre->name); // genre받는 과정
		printf("director > ");
		movieNew->director = (singleData*)malloc(sizeof(singleData));
    movieNew->director->name = (char *)malloc(30);
		gets(movieNew->director->name); // director 받는 과정
    printf("year > ");
    scanf("%d", &(movieNew->year));
		while (getchar() != '\n');
    printf("run time > ");
    scanf("%d",&(movieNew->runTime));
		while (getchar() != '\n'); // year/runTime 받는 과정
		printf("actors > ");
		gets(actorArray);// actor 명단 받는 과정

		movieNew->next = NULL; // movieNew 구조체는 NULL을 가리키고 있음

		movieNew->actorNew = (singleData*)malloc(sizeof(singleData));// movieNew 안 actorNew 연결리스트 생성
    movieNew->actorNew->name = (char *)malloc(30);
    strcpy(movieNew->actorNew->name,strtok(actorArray, ",")); //배우 명단에서 , 을 \0로 만들고 거기까지 actorNew구조체에 카피

    movieNew->actorNew->next = NULL; //movieNew 안 actorNew 구조체는 NULL을 가리키고 있음

		movieNew->actor = movieNew->actorNew; //actor(head)가 actorNew을 가리킴
		movieNew->actorTail = movieNew->actorNew; // Tail이 actorNew을 가리킴 (구조체 하나 연결리스트)

		while (1){ // actor 연결리스트에 넣는 과정

		actorCheck=strtok(NULL,","); // 배우 명단 ,->\0 만들고 \0 다음 주소 값 actorCheck에 배정

		if(actorCheck == 0) {break;} // 배우 명단을 다 받을 경우 0을 배정하는데 그런 경우 배정과정 탈출
		else if(*actorCheck == ' '){++actorCheck;} // ,다음 공백 있을 경우 다음 주소로 넘어가기

		movieNew->actorNew = (singleData*)malloc(sizeof(singleData)); //movieNew 안 새로운 actorNew 연결리스트 생성
		movieNew->actorNew->name = (char *)malloc(30);
    strcpy(movieNew->actorNew->name,actorCheck); // 2번째배우 이후 배우 카피
		movieNew->actorNew->next = NULL; //새로 만든 actorNew 구조체는 NULL을 가리키고 있음

		movieNew->actorTail->next = movieNew->actorNew; //기존 구조체가 NULL에서 새로 만든 구조체 가리킴
		movieNew->actorTail = movieNew->actorNew; //Tail은 새로 만든 구조체 가리킴
  }// 이 과정을 거치면 actor 연결리스트 완성

///////////////////////////////////////////////////////////////////////////////Movie에 추가할 새로운 구조체 생성파트는 여기까지
    ifSame = (Movie*)addSameMovie(); // NULL일 경우 정상진행 / NULL이 아닐 경우 ifSame주소값 변수 이용 루트
    if(ifSame!=NULL){
      printf("@@ You have the same record in movie list.\n");
      printf("%d:%s:%s:%s:%d:%d:", ifSame->serialNumber, ifSame->title->name, ifSame->genre->name, ifSame->director->name, ifSame->year, ifSame->runTime);

      ifSame->actorCur = ifSame->actor; //actorCur(참조용변수)가 Head가 가리키고 있는 구조체를 가리킴

      printf("%s", ifSame->actorCur->name);   // 첫 번째 actor 출력

      while(ifSame->actorCur->next != NULL)    // 마지막 actor구조체변수까지 while문은 돈다.
      {
        ifSame->actorCur = ifSame->actorCur->next; //참조용 변수가 다음 구조체를 가리킴
        printf(", %s", ifSame->actorCur->name); //두 번째 이후 actor 출력
      }

      printf("\n");
      printf("@@ Do you want to add any way? ");
      YorN=(char*)malloc(10);
			gets(YorN);
			if(strcmp(YorN,"No")==0||strcmp(YorN,"NO")==0||strcmp(YorN,"no")==0||strcmp(YorN,"nO")==0){
                                                     printf("\n");
			                                               free(actorArray);
                                                     free(YorN);
                                                     --MovieSerialNumber;
                                                     return;}
      else{
          ///////////////////////////////////
          		if(movie==NULL)//연결리스트 초기 생성 단계
          			movie = movieNew; //movie(head)가 movieNew를 가리킴
          		else
          			movieTail->next = movieNew; //기존 연결리스트가 있다면 Tail이 가리키고 있는 연결리스트가 movieNew를 가리킴

          			movieTail = movieNew; //Tail도 movieNew를 가리킴 (연결리스트 연결)

          		fprintf(mp, "add:%d:%s:%s:%s:%d:%d:", movieNew->serialNumber, changeColon(movieNew->title->name), changeColon(movieNew->genre->name), changeColon(movieNew->director->name), movieNew->year, movieNew->runTime);

              movieNew->actorCur = movieNew->actor; //actorCur(참조용변수)가 Head가 가리키고 있는 구조체를 가리킴

              fprintf(mp,"%s", changeColon(movieNew->actorCur->name));   // 첫 번째 actor 출력

              while(movieNew->actorCur->next != NULL)    // 마지막 actor구조체변수까지 while문은 돈다.
          		{
          			movieNew->actorCur = movieNew->actorCur->next; //참조용 변수가 다음 구조체를 가리킴
          			fprintf(mp,", %s", changeColon(movieNew->actorCur->name)); //두 번째 이후 actor 출력
          		}

          		fprintf(mp,"\n"); // log에 저장하면 개행시킴
          			puts("@@ Done");
          		 free(actorArray);
               free(YorN);}//movie 받는 과정,samerecord 답이 yes일 경우
             }//ifSame이 주소 값일 경우
   else{
       ///////////////////////////////////
           if(movie==NULL)//연결리스트 초기 생성 단계
             movie = movieNew; //movie(head)가 movieNew를 가리킴
           else
             movieTail->next = movieNew; //기존 연결리스트가 있다면 Tail이 가리키고 있는 연결리스트가 movieNew를 가리킴

             movieTail = movieNew; //Tail도 movieNew를 가리킴 (연결리스트 연결)

           fprintf(mp, "add:%d:%s:%s:%s:%d:%d:", movieNew->serialNumber, changeColon(movieNew->title->name), changeColon(movieNew->genre->name), changeColon(movieNew->director->name), movieNew->year, movieNew->runTime);

           movieNew->actorCur = movieNew->actor; //actorCur(참조용변수)가 Head가 가리키고 있는 구조체를 가리킴

           fprintf(mp,"%s", changeColon(movieNew->actorCur->name));   // 첫 번째 actor 출력

           while(movieNew->actorCur->next != NULL)    // 마지막 actor구조체변수까지 while문은 돈다.
           {
             movieNew->actorCur = movieNew->actorCur->next; //참조용 변수가 다음 구조체를 가리킴
             fprintf(mp,", %s", changeColon(movieNew->actorCur->name)); //두 번째 이후 actor 출력
           }

           fprintf(mp,"\n"); // log에 저장하면 개행시킴
             puts("@@ Done");
            free(actorArray);   }//movie 받는 과정,samerecord 답이 yes일 경우

   }//movie일 경우

}//함수 종료
///////////////
void loadMovielogs(void){
	int fileSize;
	mp = fopen("movie_log", "rt");//함수 호출시 읽기용으로 파일을 연다
	if(mp==NULL)
      return; // 파일이 없어서 새로 생성한 경우
	fseek(mp,0L,SEEK_END);
	fileSize = ftell(mp);
	if(fileSize==0){return;}
	rewind(mp);
	char* keyword; // 파일 한줄 읽어오기용 변수
  char *check,*actorCheck;
	while(1){
		if(ftell(mp)==fileSize) {break;}
		keyword =(char*)malloc(255); // 파일 한줄 읽기 위해 메모리 동적할당
		fgets(keyword,255,mp); //읽었다.
		strtok(keyword,"\n");//개행을 \0으로 바꾼다.
    check = strtok(keyword,":");//keyword배열에서 첫번째 :을 \0으로 바꾼다,check가 tag를 가리킨다.
		if(strcmp(check,"add")==0){ //tag가 add일 때.
			movieNew = (Movie*)malloc(sizeof(Movie)); //movieNew구조체 형성
			movieNew->actor=movieNew->actorNew=movieNew->actorTail=movieNew->actorCur=NULL; //actor 연결리스트 위한 변수들 NULL배정
			check = strtok(NULL,":"); //keyword배열에서 serialNumber 추출
			movieNew->serialNumber = (int)atoi(check);//고유번호 저장
			MovieSerialNumber = (movieNew->serialNumber);//add시 고유번호 중복할당 방지

			movieNew->title = (singleData*)malloc(sizeof(singleData));
	    movieNew->title->name = (char *)malloc(30);
			check = strtok(NULL,":");
			strcpy(movieNew->title->name,check);//title 이름 삽입
      strcpy(movieNew->title->name,changeLogColon(movieNew->title->name));

			movieNew->genre = (singleData*)malloc(sizeof(singleData));
	    movieNew->genre->name = (char *)malloc(30);
			check = strtok(NULL,":");
			strcpy(movieNew->genre->name,check); //장르 삽입
      strcpy(movieNew->genre->name,changeLogColon(movieNew->genre->name));

			movieNew->director = (singleData*)malloc(sizeof(singleData));
	    movieNew->director->name = (char *)malloc(30);
			check = strtok(NULL,":");
			strcpy(movieNew->director->name,check); //director삽입
			strcpy(movieNew->director->name,changeLogColon(movieNew->director->name));

			check = strtok(NULL,":");
	    movieNew->year = (int)atoi(check);
			check = strtok(NULL,":");
	    movieNew->runTime = (int)atoi(check); //year,runTime 삽입

			movieNew->next = NULL; //새로 만들어진 movieNew는 NULL가리킴

			movieNew->actorNew = (singleData*)malloc(sizeof(singleData));
			movieNew->actorNew->name = (char *)malloc(30);
			strcpy(movieNew->actorNew->name,strtok(NULL, ",")); //첫 번째 배우 이름 삽입
			strcpy(movieNew->actorNew->name,changeLogColon(movieNew->actorNew->name));

			movieNew->actor = movieNew->actorNew;
			movieNew->actorTail = movieNew->actorNew; //첫 번째 구조체 연결
			//
			while (1) // 두 번째 이후 구조체 actor 연결리스트에 넣는 과정
			{
			actorCheck=strtok(NULL,","); //// 배우 명단 ,->\0 만들고 \0 다음 주소 값 actorCheck에 배정
			//printf("1%s",actorCheck);
			if(actorCheck == 0) {break;}//// 배우 명단을 다 받을 경우 0을 배정하는데 그런 경우 배정과정 탈출
			else if(*actorCheck == ' '){++actorCheck;}//// ,다음 공백 있을 경우 다음 주소로 넘어가기

      movieNew->actorNew = (singleData*)malloc(sizeof(singleData)); ////movieNew 안 새로운 actorNew 연결리스트 생성
			movieNew->actorNew->name = (char *)malloc(30);
	    strcpy(movieNew->actorNew->name,actorCheck);// // 2번째배우 이후 배우 카피
      strcpy(movieNew->actorNew->name,changeLogColon(movieNew->actorNew->name));


      movieNew->actorNew->next = NULL; //새로 만든 actorNew 구조체는 NULL을 가리키고 있음

      movieNew->actorTail->next = movieNew->actorNew; //기존 구조체가 NULL에서 새로 만든 구조체 가리킴
			movieNew->actorTail = movieNew->actorNew; ////Tail은 새로 만든 구조체 가리킴
		}//// 이 과정을 거치면 actor 연결리스트 완성

    if(movie==NULL)//연결리스트 초기 생성 단계
    			movie = movieNew; //movie(head)가 movieNew를 가리킴
    		else
    			movieTail->next = movieNew; //기존 연결리스트가 있다면 Tail이 가리키고 있는 연결리스트가 movieNew를 가리킴

    			movieTail = movieNew; //Tail도 movieNew를 가리킴 (연결리스트 연결)
		}//if문 끝
    free(keyword);
  }//while문 끝
  fclose(mp);
}
///////////////파일 불러오기

Movie* addSameMovie(void){
	int cnt=0;
	if(movie == NULL)
			{return NULL;}////비교할 구조체 없을 경우 NULL 리턴

		movieCur = movie; //첫 번째 구조체 비교하기 위해 헤드를 참조변수에 배정

		if(movieCur->year != movieNew->year)
																					++cnt;
		else if(movieCur->runTime != movieNew->runTime)
																					++cnt;
		else if(strcmp(movieCur->title->name,movieNew->title->name)!=0)
																					++cnt;
		else if(strcmp(movieCur->genre->name,movieNew->genre->name)!=0)
																					++cnt;
		else if(strcmp(movieCur->director->name,movieNew->director->name)!=0)
																					++cnt;
    if(cnt != 0) {return NULL;}

    movieCur->actorCur = movieCur->actor;
    movieNew->actorCur = movieNew->actor;


		if(strcmp(movieCur->actorCur->name,movieNew->actorCur->name)!=0)
																					 ++cnt;

		while(movieCur->actorCur->next != NULL){
								movieCur->actorCur = movieCur->actorCur->next;
								movieNew->actorCur = movieNew->actorCur->next;
    						if(strcmp(movieCur->actorCur->name,movieNew->actorCur->name)!=0)
																				++cnt;
}

		if(cnt!=0){return NULL;}
    else{return movieCur;}
/////////
		while(movieCur->next != NULL)    // 두 번째 구조체부터 비교(actor제외)
		{
			movieCur = movieCur->next;

			if(movieCur->year != movieNew->year)
																						++cnt;
			else if(movieCur->runTime != movieNew->runTime)
																						++cnt;
			else if(strcmp(movieCur->title->name,movieNew->title->name)!=0)
																						++cnt;
			else if(strcmp(movieCur->genre->name,movieNew->genre->name)!=0)
																						++cnt;
			else if(strcmp(movieCur->director->name,movieNew->director->name)!=0)
																						++cnt;

      if(cnt != 0) {return NULL;}

			movieCur->actorCur = movieCur->actor;
			movieNew->actorCur = movieNew->actor;

			if(strcmp(movieCur->actorCur->name,movieNew->actorCur->name)!=0)
																							++cnt;
			while(movieCur->actorCur->next != NULL){
									movieCur->actorCur = movieCur->actorCur->next;
									movieNew->actorCur = movieNew->actorCur->next;
									if(strcmp(movieCur->actorCur->name,movieNew->actorCur->name)!=0)
																							++cnt;
						}

      if(cnt != 0) {return NULL;}
      else {return movieCur;}
    }
}
////
char* changeColon(char* ifColon){
    char* tmp = (char*)malloc(30);
    int len=strlen(ifColon),check=0,arrTmp;
    strcpy(tmp,ifColon);
    for(int i=0; i< len; ++i){
      if(*(tmp+i)==':'){
          check = i;} }
    if(check!=0){
      for(int i=len+1; i>check; --i){
          *(tmp+i+2) = *(tmp+i);
      }
      *(tmp+check) = '?';
      *(tmp+check+1) = '?';
      *(tmp+check+2) = ';';
      return tmp;
    }
    else{
      free(tmp);
      return ifColon;}
}
char* changeLogColon(char* ifColon){
  char* tmp = (char*)malloc(30);
  int len=strlen(ifColon),check=0;
  strcpy(tmp,ifColon);
  for(int i=0; i<len; ++i)
    if((*(tmp+i)==';')&&(*(tmp+i-1)=='?')&&(*(tmp+i-2)=='?'))
                                   							check = i;
  if(check!=0){

    for(int i=check+1; i<=len+1; ++i){
        *(tmp+i-2) = *(tmp+i);
    }
    *(tmp+check-2) = ':';
    return tmp;
  }
  else{
    free(tmp);
    return ifColon;}
}
