//just copy and pasted shit basically
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

	  
//now write the macro to text replace

//#define malloc(x) mymalloc(x,_FILE_,_LINE_);
//#define free(x) myfree(x,_FILE_,_LINE_);
      
		
	    
static char memory[4096]="P";




int checkIfFree(int start, int end)
{
  while(start<=end)
    {
      if(memory[start]!='\0')
	{
	  return 0;
	}
      ++start;
    }
  return 1;
}
void writeOver(int start,int end, char writer)
{
  
  while(start<=end)
    {
      memory[start]=writer;
      ++start;
    }
}
void cleanUp()
{
  int tempint=0;
    for(tempint=0;tempint<4096;++tempint)
	 {
	   memory[tempint]='\0';
	 }
    memory[0]='P';
}
  
void* mymalloc( int size,char* file,int line)
{
  int tempint=0;
	//can never be too carefull
	if (size>4091)
	{
	printf("\nmemory overflow\n");
	return NULL;
	}
	
// first time through


   if(memory[0]=='P')	
   {
       
        // so we are just going to need 5 bytes for use in the meta data
        // the first byte is for if the memory address is in use the next 4 are for how many blocks there are 
        // in the memory block
        
	 // set every value to be free for access
         // remember you cant type '\0' in so its safe to use this in memory


        cleanUp();

       //now the whole memory block should be good for use '1' will mean the memory block is
       //not free to use it doesnt have to be 1 it could be anything

       memory[0]='1';

       //now copy how many bytes arent free after
       memcpy(&memory[1],&size,4);
       
       // we also want to make sure that when we use free the next chuck of data is in use
       // so lets do that

       for(tempint=0;tempint<size;++tempint)
	 {
	   memory[5+tempint]='1';
	 }
       
       
       // now return a referance to the memory you can write over

       return &memory[5];
   }
else//first else to keep tract of }
  {
    // i am just going to try to use a while loop
    // to say find the next open space in the memory that can fit size +5 bytes
    // and if you cant then its memory overflow
    
    tempint=0;
    while(tempint<(4096-size-6))
      {
	// so if the memory is ocupado then move on
	if(memory[tempint]!='\0')
	  {
	    // so i can make this more efficient and less prone to errors by jumping 
	    //by the size of the block
	    tempint++;
	  }
	else
	  // else if the memory isnt ocupado then try to fit the bytes
	  {
	    // if this ' if' is true then the bytes will fit and then put them in
	    if(checkIfFree(tempint,tempint+size+5)>0)
	      {
		// first make sure they arent '\0'
		writeOver(tempint,tempint+size+5,'1');

		//copy over the byte block
		memcpy(&memory[tempint+1],&size,4);

		// just to make sure we can ++
		++tempint;
		
		return &memory[tempint-1+5];
	      }// end of check if
	    else
	      {
		//ok if we get here it means the bytes wouldnt fit and we need to move on
		// same thing here we want to jump by the whole block not just by one
		tempint++;
	      }
	   }// this ends the first else
	  }//end of while else
	//
	//
	// now we are exiting the while this means
	//if we get here that 
	//  we went through the entire memory and the bytes will not fit so ERROR!
	
    printf("\nERROR at line: %d in file: %s memory overflow\n",line,file);
	// but we still need to return NULL
	return NULL;

  }//end of else after the first time through if
	
}// end of mymalloc

//now for free......

int  myfree( void* address,char* file,int line)
{
  int tempint=0;
  //so our myfree needs to detect many errors 
  //however the proffesor did not say that our code has to differentate 
  //between them so the myfree is just going to check if the address you give it 
  // matches an address in memory[] if it does then we still need to check if it was freed
  // this part isnt that bad luckly


  while(tempint <4091)
    {
      // printf(" \nmem: %p and address: %p index: %d\n",(void*)&memory[tempint],(void*)address, tempint);
      // so if it equals then we got shit to do
      if(((void*) &memory[tempint])==((void*)address))
	{
	  
	  //printf("\nhey it worked\n");
	  //firstly check if it wasnt already freed
	  if(memory[tempint]=='\0')
	    {
	      printf("\nERROR at line: %d in file: %s already freed pointer cannot free again\n",line,file);
	      tempint=5000;
	      return 0;
	    }
	  else
	    {
	      
	      //then if it wasnt  overwrite the blocks
	      writeOver(tempint,tempint+5+((int)memory[tempint+1]), '\0');
	      tempint=5000;
		return 1;
	      // this is a successfull free
	    }
	}
      tempint++;
    }// end of the while looop

  // so if we get here that means the the address given is not an address or it is 
  // not an address made by mymalloc
  printf("\nERROR at line: %d in file: %s address given is not an address or was not maded by mymalloc\n",line,file);
  return 0;

}// end of my free

	
	
	

