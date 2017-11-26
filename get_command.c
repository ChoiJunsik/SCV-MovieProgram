
void get_command(char* input)
{
	char* commands, *mda, *option, *num;
	gets(input);
	commands = strtok(input, " ");
	mda = strtok(NULL, " ");
	if (strcmp(commands, "add") == 0){
    if (mda == 0) {
      printf("@@ Please input the option!\n\n");
      free(input);
      return ;
    }
		add(mda);
		fclose(mp);
	}
	else if (strcmp(commands, "update") == 0){
    printf("업데이트 코드");
    exit(1);
	}
	else if (strcmp(commands, "delete") == 0){
    printf("딜리트 코드");
    exit(1);
	}
	else if (strcmp(commands, "search") == 0){
    printf("서치 코드");
    exit(1);
	}
	else if (strcmp(commands, "print") == 0){
    printf("프린트 코드");
    exit(1);
	}
	else if (strcmp(commands, "sort") == 0){
    printf("소트 코드");
    exit(1);
	}
	else if (strcmp(commands, "save") == 0){
    printf("세이브 코드");
    exit(1);
	}
	else if (strcmp(commands, "end") == 0){
		exit(1);
	}
}
