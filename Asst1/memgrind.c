#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "mymalloc.h"
#include<sys/time.h>
#include<ctype.h>
#include<time.h>



#define malloc(x) mymalloc(x,__FILE__,__LINE__);
#define free(x) myfree(x,__FILE__, __LINE__);


double testA(){
clock_t start,end;
double returnTime;

start = clock();

int p = 0;
//double time_used;

void* arr[200];

while (p < 150){
 
        arr[p] = malloc(1);
	free(arr[p]);
	p++;

	}
 
        cleanUp();
	end = clock();
	returnTime = ((double) (end - start))/ CLOCKS_PER_SEC;
	
        

	return returnTime;
}

double testB()
{
  clock_t start, end;
  double totaltime=0;
  start=clock();


  void* pointers[150];
  int index=0;
  int temp=0;
	
  for(index=0;index<150;++index)
    {
      pointers[index]= malloc(1);

      if(index % 50 == 0 && (index !=0))
	{
	   temp=0;
	  while(temp<50)
	    {
	      //printf("index %d\n",index);
	      free(pointers[temp]);
	      ++temp;
	    }
	}
      
    }
  end = clock();
  totaltime= ((double) (end - start))/CLOCKS_PER_SEC;
  
  return totaltime;
}//end of test B

/*
double testC(){
int c = 0;
double time_used = 0;
struct timeval t1,t2;
void* arr[5000];
int randomizer, freed, randomB,size,malC,rand_ind;//random size, free counter, random bit, size occupied, malloc counter, rand index

gettimeofday(t1,NULL);
int z;
for(malC=0; malC < 150; malC++){
	randomB = (rand() % 2);
i	if(randomB || size == 0) {
		size = ((rand() % 64) + 1);
		arr[size] = malloc(randomizer);
		size++;
} else {
	rand_ind = rand() % size;
	if(rand_ind == (size -1)){
		free(arr[rand_ind]);
		arr[rand_ind] = 0;
		freed++;
		printf("freed\n");
}else {
	free(arr[rand_ind]);
	arr[rand_ind] = arr[size-1];
	arr[size -1] = 0;
	freed++;
	printf("freed\n");

} 

size--;
}
	for(c = size -1 ; c >= 0; c--){
	free(arr[c]);
	freed++;
	printf("freed\n");
}
	gettimeofday(&t2,NULL);
//	time_used = (double)(t2.tv_usec - t1.tv_usec)/1000000 + (double) (t2.tv_usec-t1.tv_usec); 

	printf("mal count %d, free: %d\n", malC,free);
	printf(" in D time_used %f \n", time_used*1000000);
}
return time_used;


}

double testD(){
clock_t start,end;
double totaltime = 0;
start = clock();

 int i,randB,randS,malC,size,freeC,randI;  
//random bit, random size,malloc counter,size used,free counter,random index
void* arr[500];
// why on earth was this 6500?
 randS=0;
 randS++;
for(malC = 0; malC < 150; ++malC){
        randB = (rand() %2);
        if(randB || size == 0){
                randS = ((rand() % 64) + 1);
                arr[size] = malloc (size);
                size++;

}else {
        randI = rand() % size;
        if(randI == (size -1)){
                free(arr[randI]);
                arr[randI] = 0;
                freeC++;



        } else {
                free(arr[randI]);
                arr[randI] = arr[size - 1];
                arr[size - 1] = 0;
                freeC++;
                size--;
        }
}
}
        i = size -1;
        while (i >= 0){
                free(arr[i]);
                freeC++;
                --i;
        }
        end = clock();
        totaltime = ((double) (end-start));
        return totaltime;
}
		
double testE()
{
	// we keep focusing onerrors that might be thrown in this test we
	// will make sure that the data that we malloced out isnt edited
	// and if it is an error will be thrown
	
	clock_t start,end;
	start= clock();
	double totaltime =0;
	int* temp[100];
	int i=0;
	while(i<100)
	{
		temp[i]= (int*) malloc(sizeof(int));
		*temp[i]=i;
		++i;
	}
	
	i=0;
	while(i<100)
	{
		if(*temp[i] != i)
		{
			printf("ERROR: data altered");
		}
		++i;
	}
	i=0;
	while(i<100)
	{
	  free(temp[i]);
		++i;
	}
	
	
	
	end = clock();
	totaltime= ((double) (end - start))/CLOCKS_PER_SEC;
	return totaltime;
}

double testF()
{
	
	// this last test will test to make sure that mymalloc will not
	//incorrectly say that memory is out of space when it isn;t it will also take a long time 
	// to run i am sure
	
	clock_t start,end;
	start= clock();
	double totaltime =0;
	int i=0;
	char* temp[1024];
	while(i<1024)
	{
		temp[i]= (char*) malloc(4);
	
		++i;
	}
	//now mem should be full so free once 4096 times then remalloc then free all
	i=0;
	while(i<1024)
	{
		free(temp[i]);
		temp[i]=(char*) malloc(4);
		
		++i;
	}
	//free all
	i=0;
	while(i<4096)
	{
		free(temp[i]);
	}
	
	
	end = clock();
	totaltime= ((double) (end - start))/CLOCKS_PER_SEC;
	return totaltime;
}
*/	

int main(){

double A=0;
double B=0;
//double C=0;
//double D=0;
//double E=0;
//double F=0; 

int g=0;
for(g = 0; g < 100; g++){

	A = testA();
		B = testB();
		//	C += testC();
		//	D = testD();
		//E += testE()  ;
	//	F += testF()  ;

}
 printf("total Time for A: %f seconds. mean time: %f  \n",(A),(A/100));
  printf("Time for B: %f seconds. mean time: %f  \n",(B), (B/100));
//printf("Time for C: %f seconds. mean time: %f  \n" ,(C), (C/100));
 //printf("Time for D: %f seconds. mean time: %f  \n" , (D),(D/100));
 // printf("Time for E: %f seconds. mean time: %f  \n",(E), (E/100));
//printf("Time for F: %f seconds. mean time: %f  \n",(F), (F/100));
	

	return 0;

}


