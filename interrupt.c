void interrupt(int sig){//enter 두번 쳐야 나가지는 원인 모르겠음
	char YorN=0;
	printf("\nControl+C\nGet Interrupt Signal.\nDo you want to exit myMOVIE program? (Y/N) ");
	scanf("%c",&YorN);
	if((YorN=='y') ||(YorN=='Y'))
			exit(-1);
}
