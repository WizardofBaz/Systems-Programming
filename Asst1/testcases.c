#include<stdlib.h>
#include<stdio.h>
#include<time.h>


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
