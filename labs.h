#ifndef LAB_HDR_H
#define LAB_HDR_H 
#include "main_header.h"

ssize_t tee ();
int cp (const char* pathname1, const char* pathname2);
ssize_t rev (const char* pathname);

void outputVariable(char * variable);
void printAllEnv();

void Ex_5_1();

#endif 