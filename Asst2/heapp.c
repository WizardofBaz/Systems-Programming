#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>



typedef
struct _node
{
	int num;
	char word[50];
        struct _node* link;
}node;

int compareTo(node* temp1, node* temp2)
{
  if(temp1->num < temp2->num)
    {
      return -1;
    }
  else
    {
  if (temp1->num > temp2->num)
    {
      return 1;
    }
  else
    {
      return 0;
    }
    }
}
static node* head=NULL;
int isDelim(char temp)
{
  if(temp==' ' || temp=='\n' || temp=='\t')
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
void push(node* mid)
{

  node* switcher = head;
	if(head==NULL)
	{
		head=mid;
	}
	else
	{
	  if(head->link ==NULL)
	    {
	      if(compareTo(head,mid)<=0)
		{
		  head->link=mid;
		  mid->link=NULL;
		}
	      else
		{
		  mid->link =head;
		  head->link=NULL;
		    head=mid;
		}
	    }
	  else
	    {
	              switcher=head;
		      while(switcher->link !=NULL &&
			    compareTo(switcher->link,mid)<=0)
			{
			  
			  switcher= switcher->link;
			}
		      if(switcher->link ==NULL)
			{
			  switcher->link= mid;
			}
		      else
			{
			  if(switcher == head)
			    {
			      mid->link=switcher->link;
			      head->link=mid;
			    }
			  else
			    {
			     mid->link=switcher->link;
			     switcher->link=mid;
			    }
			}
	      }
	}
}

void printHeap()
{
  node* printer =head;
  while(printer !=NULL)
    {
      printf(" %d %s\n",printer->num,printer->word);
      printer =printer->link;
    }
}
void printNode(node* printer)
{
   printf(" %d %s\n",printer->num,printer->word);
}

node* pop()
{
  if(head==NULL)
    {
      return NULL;
    }
  else
    {
  node* heapp=head;
  head=head->link;
  return heapp;
    }
}
void heapatize(char* filename)
{
  // this functions take the file of frequences and words
  // and sorts them into a heap theheap pt is head
FILE* fp=NULL;
fp=fopen(filename,"r");

if(fp==NULL)
{  
   printf("file is not found\n");
   exit(0);
}

 int times=0;
 char tok[50]="";
 //node* head=NULL;

  while( fscanf(fp,"%d\t%46[^\n]",&times,&tok[0])==2)
     {
 // printf("before f scanf\n");
    
     node* newthing= (node*)malloc(sizeof(node));
     newthing->num=times;
     strcpy(newthing->word,tok);
     newthing->link=NULL;
     // printf("after new node\n");
     push(newthing);
     }
}
void insert(node* temp)
{
  //printf("do we get here\n");
  node* switcher=head;
  if(switcher ==NULL)
    {
      //  printf("do we get here\n");
      head=temp;
      // printf("do we get here\n");
      head->link=NULL;
    }
  else
    {
      // printf("do we get here\n");
      while(switcher->link !=NULL)
	{
	  switcher=switcher->link;
	}
    
      switcher->link=temp;
      temp->link=NULL;
    }
}
int isFound(char* comparer)
{
  // seacheres the nodees thnig for a given wordthen
  // adds one to the frequence
  node* holder=head;
  if(holder==NULL)
    {
      return -1;
    }
  else
    {
      while(holder->link!=NULL )
	{
	  if(strcmp(holder->word,comparer)==0 )
	    {
	      holder->num = holder->num + 1;
	      return 1;
	    }
	  else
	    {
	      holder=holder->link;
	    }
	}//end of while
      if(strcmp(holder->word,comparer)==0)
	{
	  holder->num= holder->num + 1;
	  return 1;
	}
      else
	{
	  return -1;
	}
    }
}
	      
	  
  
void tokentize(char** files)
{
  int numoffiles=0; 
  char *over1="\\t";
  char *over2="\\n";
  char *over3="\\s";
 
  char* textfile="test.txt";
  FILE* fp = NULL;
  fp=fopen(files[numoffiles],"r");
  
  char tempchar;
  char string[50];
  int place =0;
  string[0]='\0';

  while(files[numoffiles] != NULL && fp != NULL)
    {
      string[0]='\0';
      place=0;
      while((tempchar= fgetc(fp))!=EOF)
     {
       
       if(isDelim(tempchar)>0)
	 {
	   
	   string[place]='\0';
	   place=0;
	       
	   if(string[0]!='\0' && isFound(string)>0)
	     {
	       // do nothing
	       string[0]='\0';
	     }
	   else
	     {
	       if(string[0]=='\0')
		 {

		 }
	       else
		 {
	       node* inserting1= (node*)malloc(sizeof(node));
	       inserting1->num=1;
	       strcpy(inserting1->word,string);
	       inserting1->link=NULL;
	       insert(inserting1);
	       string[0]='\0';
		 }
	      }
	     

	   // and you need to tokenize the delimner
	   if((tempchar==' '))
	     {
	       if(isFound("\\s")<0)
		 {
	        node* insertin= (node*)malloc(sizeof(node));
	       insertin->num=1;
	        
		strcpy(insertin->word,over3);
	       insertin->link=NULL;
	       insert(insertin);
		 }
	     }
	   else{
	     if((tempchar=='\t'))
		  {
	       if(isFound("\\t")<0)
		 {
		    node* inserting= (node*)malloc(sizeof(node));
		    inserting->num=1;
		    strcpy(inserting->word,over1);
		    inserting->link=NULL;
		    insert(inserting);
		 }
		  }
	     else{
	        //printf("do we get here\n");
	        if((tempchar=='\n'))
		 {
		   if(isFound("\\n")<0)
		    {
		      //printf("do we get here LASTLY\n");
		     node* insertig= (node*)malloc(sizeof(node));
		      insertig->num=1;
	        	strcpy(insertig->word,over2);
	        	insertig->link=NULL;
			//	printf("inserting\n");
			insert(insertig);
		    }
	        }
	     }}
	 }
       else
	 {
	   // not a delimner
	   string[place]=tempchar;
	   place++;
	 }
       // }
	   
     }//end of a file
      //printf("after file 1\n");
      fclose(fp);
      ++numoffiles;
      if(files[numoffiles]!=NULL)
	{
	  fp=fopen(files[numoffiles],"r");
	}
      else
	{
	  fp=NULL;
	}
	
    }//end of reading files

    //now start writing
     fp= fopen(textfile,"w");
     node* popping;
     // printf("before writing\n");
   while(head !=NULL)
    {
      popping= pop();
      //  if(strcmp(popping->word,"")!=0)
      //	{
	  fprintf(fp,"%d\t%s\n",popping->num,popping->word);
	  //	}
      free(popping);
    }
 
  fclose(fp);
}


int main( int args, char** argv)
{
  char* stuff[]= {"ugly1.txt", "ugly2.txt"};
  
  tokentize(stuff);
  heapatize("test.txt");
  printHeap(head);

	return 0; 
}
