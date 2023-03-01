
#include "main_header.h"
#include "func1.h"
#include "func2.h"
#include "labs.h"

#define _GNU_SOURCE

extern char etext, edata, end;

int main(int argc, char *argv[]) {

	int lab = 6;
	
	if(lab==2){
		const char *gnu_get_libc_version(void);
		printf("%s\n",&gnu_get_libc_version);

		int fd = open("pathname", "flags", "mode");
		if (fd == -1) {
			perror("open");
		}

		//140
		for (errno = 0; errno<134; errno++) perror("");
	}

	if(lab==3){

		//ssize_t cl = close(0);

		int fd = open("func1.c",O_RDWR);
		printf("%d\n",fd);

		ssize_t NumTee = tee();

		int copyFile = cp("func1.c","copy.c");

		ssize_t reverse = rev("func1.c");
	}

	if(lab==4){
		printf("%5d%5d\n",getpid(),getppid());
		
		int uninitializedData, initializedData;
		initializedData = &edata - &etext;
		uninitializedData = &end - &edata;
		printf("%5d %5d\n",uninitializedData, initializedData);

		outputVariableMore(argc, argv);
		printAllEnv();

		PrintEnvTable();
    	int DelIndex;
    	printf("Enter the # of the variable you want to delete:\n> ");
    	scanf("%d",&DelIndex);
    	DeleteEnvVar(DelIndex);
    	PrintEnvTable();
	}
	if(lab==5){
		//Ex_5_1();
		//Ex_5_6();
		Ex_5_7(argv);
	}
	if(lab==6){
		int err = nice(-2);
		if(err == -1) perror("nice");
	}
	//sleep(10);

	return 0;
}