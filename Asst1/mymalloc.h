#ifndef _HEADERFILE_H
#define _HEADERFILE_H

//this file should be good but if you have further functions you want to use
// put the signatures in here


int checkIfFree(int,int);
void writeOver(int,int);
void* mymalloc(int,char*,int);
int myfree(void*,char*,int);
void cleanUp();

	  
#endif

