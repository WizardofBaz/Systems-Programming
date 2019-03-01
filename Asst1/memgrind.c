#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
//#include<"mymalloc.h">
#include<sys/time.h>
#include<ctype.h>


struct timer {
	int t1,t2;
};

double testA(){

int p = 0;
double time_used;
struct timer t1,t2;
void* arr[5000];
//gettimeofday(&
gettimeofday(&t1,NULL);
while (p < 150){
	arr[p] = malloc(1);
	p++;
	printf("malloc: %p\n", &arr[p]);

}
	free(arr[p]);
	printf("free: \n");

	gettimeofday(&t2,NULL);
//	time_used = (double) (t2.t_usec- t1.t_usec)/1000000 + (double) (t2.t_sec-t1.t_sec);
//	trying to get time

	return time_used;
}

double testC(){
int c = 0;
double time_used = 0;
struct timeval t1,t2;
void* arr[5000];
int randomizer, freed, randomB,size,malC,rand_ind;//random size, free counter, random bit, size occupied, malloc counter, rand index

gettimeofday(&t1,NULL);
int z;
for(malC=0; malC < 150; malC++){
	randomB = (rand() % 2);
	if(randomB || size == 0) {
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
	time_used = (double)(t2.tv_usec - t1.tv_usec)/1000000 + (double) (t2.tv_usec-t1.tv_usec); 

	printf("mal count %d, free: %d\n", malC,free);
	printf(" in D time_used %f \n", time_used*1000000);
}
return time_used;


}







