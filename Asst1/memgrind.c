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

double testC(){

clock_t start,end;
double time = 0;
start = clock();

int mallocI,freeI;
int p = 0;
void* arr[50];

mallocI = 0;
freeI = 0;

arr[0] = malloc(1);

while(1){
        int random = rand()%2;
        if(random ==0){
                if(mallocI<49){
                        mallocI++;
                        arr[mallocI] = malloc(1);

        }
}
        if(random == 1){
                if(freeI<mallocI){
                        freeI++;
                        free(arr[freeI]);
                }
                }
                if((mallocI == 49)&&(freeI == 49)){
                        return;
        }

        }
        end = clock();
        time = ((double)(end - start))/CLOCKS_PER_SEC;

        return time;
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
        totaltime = ((double) (end-start))/CLOCKS_PER_SEC;
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
	
	// this last test will test to make sure that mymalloc will  assure you can mlalloc more memory then needed
	
	clock_t start,end;
	start= clock();
	double totaltime =0;
	void * temp=malloc(5000);
	//now mem should be full so free once 4096 times then remalloc then free all
	
	end = clock();
	totaltime= ((double) (end - start))/CLOCKS_PER_SEC;
	return totaltime;
}


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


