#ifndef _HEADERFILE_H
#define _HEADERFILE_H

//this file should be good but if you have further functions you want to use
// put the signatures in here

#define malloc(x) mymalloc(x,_FILE_,_LINE_);
#define free(x) myfree(x,_FILE_,_LINE_);
int checkIfFree(int,int);
void writeOver(int,int);
void* mymalloc(int,char*,int);
int myfree(void*,char*,int);

	  
#endif
