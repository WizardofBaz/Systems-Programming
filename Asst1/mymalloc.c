//just copy and pasted shit basically
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

	  
//now write the macro to text replace

//#define malloc(x) mymalloc(x,_FILE_,_LINE_);
//#define free(x) myfree(x,_FILE_,_LINE_);
/*      
typedef 
struct _NODE
{
  void* address;
  int block;
  struct _NODE* link;
}node;
*/	 

   
static char memory[4096];
static int firsttimein=0;

//static node* metad=NULL;





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
  while(start< end)
    {
      memory[start]=writer;
      start++;
    }
}
void cleanUp()
{
  int tempint=0;
    for(tempint=0;tempint<4096;++tempint)
	 {
	   memory[tempint]='\0';
	 }
    
}
	    
	  
      

// just inclase new malloc does not work
// this is the one we have to use X.X

void* mymalloc( int size,char* file,int line)
{
  int tempint=0;
	//can never be too carefull
	if (size>4091)
	{
	  printf("\nmemory overflow file: %s at line: %d\n",file,line);
	return NULL;
	}
	
// first time through
//printf("\n %c %d %c \n",memory[0],(int) memory[1],memory[5]);

   if(firsttimein==0)	
   {
     firsttimein=1;
       
        // so we are just going to need 5 bytes for use in the meta data
        // the first byte is for if the memory address is in use the next 4 are for how many blocks there are 
        // in the memory block
        
	 // set every value to be free for access
         // remember you cant type '\0' in so its safe to use this in memory

     // printf("firsttime here brosss\n");
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
    //printf("\n %c %d %c \n",memory[0],(int) memory[1],memory[5]);
    tempint=0;
    while(tempint<(4096-size-6))
      {
	// so if the memory is ocupado then move on
	if(memory[tempint]!='\0')
	  {
	    // so i can make this more efficient and less prone to errors by jumping 
	    //by the size of the block
	    tempint+=(((int)memory[tempint+1])+5);
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
		tempint =5000;
		
		return &memory[tempint+5];
	      }// end of check if
	    else
	      {
		//ok if we get here it means the bytes wouldnt fit and we need to move on
		// same thing here we want to jump by the whole block not just by one
	        tempint+=(((int)memory[tempint+1])+5);
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
  //printf("\n %c %d %c \n",memory[0],(int) memory[1],memory[5]);  
/*
  for( tempint=0;tempint<7;++tempint)
    {
      printf("%c",memory[tempint]);
    }
  printf("\n");
  */  
//so our myfree needs to detect many errors 
  //however the proffesor did not say that our code has to differentate 
  //between them so the myfree is just going to check if the address you give it 
  // matches an address in memory[] if it does then we still need to check if it was freed
  // this part isnt that bad luckly

  tempint=0;
  while(tempint <4091)
    {
      // printf(" \nmem: %p and address: %p index: %d\n",(void*)&memory[tempint],(void*)address, tempint);
      // so if it equals then we got shit to do
      if(((void*) &memory[tempint+5])==((void*)address))
	{
	  
	  // printf("\nhey it worked\n");
	  //firstly check if it wasnt already freed
	  if(memory[tempint]=='\0')
	    {
	      printf("\nERROR at line: %d in file: %s already freed pointer cannot free again\n",line,file);
	      tempint=5000;
	      return 0;
	    }
	  else
	    {
	      //  printf ("good free\n");
	      //then if it wasnt  overwrite the blocks
	      writeOver(tempint,(tempint+5+((int)memory[tempint+1])), '\0');
	     
	      //printf("\n %c %d %c \nend of the free\n",memory[0],(int) memory[1],memory[5]);
	      tempint=5000;
		return 1;
	      // this is a successfull free
	    }
	}
      tempint+=(((int)memory[tempint+1])+5);
    }// end of the while looop

  // so if we get here that means the the address given is not an address or it is 
  // not an address made by mymalloc
  if( tempint!=5000)
    {
  printf("\nERROR at line: %d in file: %s address given is not an address or was not maded by mymalloc\n",line,file);
    }
  return 0;

}// end of my free


/*
void* mymalloc(int size, char* file, int line)
{
  if( size >4096)
    {
      printf("\nERROR at line: %d in file: %s memory overflow\n",line,file);
    }
  else
    {
  if(metad==NULL)
    {
      cleanUp();
      node* temp= (node*) malloc(sizeof(node));
      temp->address = &memory[0];
      temp->link=NULL;
      temp->block=size;
      return temp->address ;
      // good call to malloc
    }
  else
    {
      int sizeleft =0;
      
      node* temp=metad;
      sizeleft=metad->block;

	while(temp->link !=NULL && sizeleft<=(4096-size))
	{
	  sizeleft+=temp->block;
	  temp=temp->link;
	}
	sizeleft+=temp->block;
	if(sizeleft>(4096-size))
	  {
	   printf("\nERROR at line: %d in file: %s memory overflow\n",line,file);
	// but we still need to return NULL
	return NULL;
	  }
	else
	  {
	    //this is a good call
	    node* tempo = (node*) malloc(sizeof(node));
	    temp->link=tempo;
	    tempo->address= &memory[sizeleft];
	    tempo->block= size;
	    tempo->link=NULL;
	    return tempo->address;
	  }
       }
    }
  return NULL; 
}


void myfree(void* freey, char* file, int line)
{
  node* temp = metad;
  if(temp->address == freey)
    {
      // good free
      temp=temp->link;
      free(metad);
      metad=temp;
    }
  else
    {
      while(temp->link != NULL && temp->link->address != freey)
	{
	  temp=temp->link;
	}
      if(temp->link == NULL)
	{
	  //failure
	   printf("\nERROR at line: %d in file: %s address given is not an address/was not maded by mymalloc/was freed\n",line,file);
	}
      else
	{
	  if(temp->link->address==freey)
	    {
	      //this is a good free
	      node* tempo = temp->link;
	      temp->link=temp->link->link;
	      free(tempo);
	    }
	}
    }
}

*/
	  
	      
	  	    
	
	
	

