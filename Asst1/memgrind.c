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
	//clock_t start,end;
	double returnTime = 0;
	struct timeval start,end;
	//start = clock();
	gettimeofday(&start,NULL);
	int p = 0;
	//double time_used;

	void* arr[200];

	while (p < 150){

		arr[p] = malloc(1);
		free(arr[p]);
		p++;

	}

	//        cleanUp();
	//	end = clock();
	//	returnTime = ((double) (end - start))/ CLOCKS_PER_SEC;
	gettimeofday(&end,NULL);

	returnTime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	return returnTime;
	return 0;
}

double testB()
{
	// clock_t start, end;
	double totaltime=0;
	// start=clock();
	struct timeval start,end;

	void* pointers[150];
	int index=0;
	int temp=0;
	gettimeofday(&start,NULL);

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
	//  end = clock();
	gettimeofday(&end,NULL);
	totaltime= ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	return totaltime;
}//end of test B

double testC(){

	//clock_t start,end;
	double time = 0;
	//start = clock();

	struct timeval start,end;

	int mallocI,freeI;

	void* arr[50];

	mallocI = 0;
	freeI = 0;

	arr[0] = malloc(1);
	gettimeofday(&start,NULL);

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
			return 0;
		}

	}
	//end = clock();
	gettimeofday(&end,NULL);
	time = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));


	return time;
}

double testD(){
	//clock_t start,end;
	double totaltime = 0;
	//start = clock();
	struct timeval start,end;

	int i,randB,randS,malC,size,freeC,randI;  
	//random bit, random size,malloc counter,size used,free counter,random index
	void* arr[500];
	// why on earth was this 6500?
	randS=0;
	randS++;

	gettimeofday(&start,NULL);

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
	//        end = clock();
	gettimeofday(&end,NULL);
	totaltime = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	return totaltime;
}

/*double testE()
{
	// we keep focusing onerrors that might be thrown in this test we
	// will make sure that the data that we malloced out isnt edited
	// and if it is an error will be thrown

	double totaltime = 0;
	//struct timeval start,end;
	clock_t start,end;
		

	int* temp[100];
	int i=0;


	//gettimeofday(&start,NULL);
	start = clock();

	while(i<100)
	{
		temp[i]= (int*) malloc(sizeof(int));
		//int* b = malloc(sizeof(int));
		if(temp[i] == NULL){
			printf("testE returned NULL \n");
			break;
		}

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

	//gettimeofday(&end,NULL);
	end = clock();

	//totaltime= ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	totaltime = ((double) (end-start))/CLOCKS_PER_SEC;	

	return totaltime;
}*/


double testE()
{
	// we keep focusing onerrors that might be thrown in this test we
	// will make sure that the data that we malloced out isnt edited
	// and if it is an error will be thrown
	cleanUp();
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
	//cleanUp();
	// this last test will test to make sure that mymalloc will  assure you can mlalloc more memory then needed

	//clock_t start,end;
	//start= clock();

	struct timeval start,end;
	gettimeofday(&start,NULL);

	double totaltime =0;
	void * temp=malloc(5000);

	free(temp);
	//end = clock();
	totaltime= ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	return totaltime;
}


int main(){
	clock_t start, end;
	start= clock();
	double A=0;
	double B=0;
	double C=0;
	double D=0;
	double E=0;
	double F=0; 

	int g=0;
	for(g = 0; g < 100; g++){

		A = testA();
		B = testB();
		C = testC();
		D = testD();
		E = testE();
		F = testF();

	}
	printf("Time for A: %f mean time (microseconds): %f  \n",(A),(A/1000));
	printf("Time for B: %f mean time (microseconds): %f  \n",(B),(B/1000));
	printf("Time for C: %f mean time (microseconds): %f  \n",(C),(C/1000));
	printf("Time for D: %f mean time (microseconds): %f  \n",(D),(D/1000));
	printf("Time for E: %f mean time (microseconds): %f  \n",(E),(E/1000));
	printf("Time for F: %f mean time (microseconds): %f  \n",(F),(F/-100000000));

	end= clock();
	double timetaken= (double)(end-start)/((double)(CLOCKS_PER_SEC));
	printf("total time taken in main (microseconds) : %f\n",timetaken);

	return 0;

}
