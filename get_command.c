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

	}
	else if (strcmp(commands, "delete") == 0){

	}
	else if (strcmp(commands, "search") == 0){

	}
	else if (strcmp(commands, "print") == 0){

	}
	else if (strcmp(commands, "sort") == 0){

	}
	else if (strcmp(commands, "save") == 0){

	}
	else if (strcmp(commands, "end") == 0){
		exit(1);
	}
}
