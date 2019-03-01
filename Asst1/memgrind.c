#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
//#include<"mymalloc.h">
#include<sys/time.h>
#include<ctype.h>
#include<time.h>


struct timer {
	int t1,t2;
};

double testA(){
clock_t start,end;
double returnTime;

start = clock();

int p = 0;
double time_used;
//struct timer t1,t2;
void* arr[5000];
//gettimeofday(&
//gettimeofday(t1,NULL);
while (p < 150){
	arr[p] = malloc(1);
	free(arr[p]);
	p++;
//	printf("malloc: %p\n", &arr[p]);

}
	

//	printf("free: \n");

//	gettimeofday(t2,NULL);
//	time_used = (double) (t2.t_usec- t1.t_usec)/1000000 + (double) (t2.t_sec-t1.t_sec);
//	trying to get time
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
  for(index=0;index<150;++index)
    {

      if(index % 50 == 0)
	{
	  int temp=0;
	  while(temp<50)
	    {
	      free(pointers[temp]);
	      ++temp;
	    }
	}
      pointers[index]= (void*)malloc(1);
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
*/
int main(){

double A,B,C,D,E,F;

int g;
for(g = 0; g < 100; g++){

	A = testA();
//	B += testB() = 0;
//	C += testC() = 0;
//	D += testD() = 0;
//	E += testE() = 0;
//	F += testF() = 0;

}
	printf("Time for A: %f in seconds \n",A);
//	printf("Time for B: %f in seconds \n", B);
//	printf("Time for C: %f in seconds \n" , C);
//	printf("Time for D: %f in seconds \n" , D);
//	printf("Time for E: %f in seconds \n", E);
//	printf("Time for F: %f in seconds \n", F);
	

	return 0;

}


