#include "labs.h"

#define MAXNAMELEN 20
#define MAXVALUELEN 1024

extern char ** environ;

void printAllEnv(){
    for (char ** ep = environ; *ep!=NULL; ep++){
        puts(*ep);
    }
}

void outputVariable(char * variable){
    char * i = variable;
    while (*i!='\0'){
        if (*i=='='){
            *i='\0';
            if (setenv(variable,(i+1),1)) {
                perror("SetEnv");
                return 1;
            }
            return;
        }
        i++;
    }
    char * data = getenv(variable);
    if(data==-1){
        perror("getenv");
        return 1;
    }
    printf("%s = %s\n", variable, data);
    
}
void outputVariableMore(int argc, char *argv[]){
    for(int i=1; i<argc; i++) {
        outputVariable(argv[i]);
    }
}





char** CleanSplit(char* inString, char** outSplit) {
    outSplit = malloc(sizeof(char)*2);
    outSplit[0] = malloc(sizeof(char)*(MAXNAMELEN+1));
    outSplit[1] = malloc(sizeof(char)*(MAXVALUELEN+1));
    char* currentPos = inString-1;
    int count = 0;
    while(*(++currentPos)!='=') {
        if (count == MAXNAMELEN) break;
        outSplit[0][count++] = *currentPos;
    }
    outSplit[0][count+1] = '\0';
    count = 0;
    while(*(++currentPos)) {
        if (count == MAXVALUELEN) break;
        outSplit[1][count++] = *currentPos;
    }
    outSplit[1][count+1] = '\0';
    return outSplit;
}

void PrintEnvTable() {
    char** split;
    int i = 0;
    printf("--- All environment variables ----\n\n");
    printf("#   Environment_Variable   Value\n");
    for (char** oneVar = environ; *oneVar; oneVar++) {
        split = CleanSplit(*oneVar,split);
        printf("%-*d %-*s %-*s\n",3,i,20,split[0],2,split[1]);
        free(split[0]);
        free(split[1]);
        free(split);
        i++;
    }
    printf("\n");
}

int DeleteEnvVar(int inIndex) {
    extern char** environ;
    char** split;
    split = CleanSplit(environ[inIndex],split);
    int result = unsetenv(split[0]);
    free(split[0]);
    free(split[1]);
    free(split);
    return result;
}