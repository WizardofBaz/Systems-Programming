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

void push(node* mid)
{

  /*
 node* placeholder;
 
	  placeholder= head;

	  // find where to insert
	  
	  
	  if(head == NULL)
	    {
	      head=mid;
	    }
	  else
	    {
		 if(head->link== NULL)
		   {
		     if(compareTo(head,mid)<=0)
		       {
			  head->link=mid;
			}
		      else
			{
			  mid->link=head;
			  head=mid;
			  
			}
		    }
		  else
		    {
		      placeholder=head;
		      while(placeholder->link !=NULL &&
			    compareTo(placeholder,mid)>=0)
			{
			  
			  placeholder= placeholder->link;
			}
		      if(placeholder->link ==NULL)
			{
			  placeholder->link=mid;
			}
		      else
			{
			  if(placeholder == head)
			    {
			      mid->link=head;
			      head=mid;
			    }
			  else
			    {
			  mid->link=placeholder->link;
			  placeholder->link=mid;
			    }
			}
		    }
	         }
     
	  
       }//end of making the head
  */
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
int main( int args, char** argv)
{
   

 char* filename= argv[1];

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

  while( fscanf(fp,"%d %[^\n]",&times,&tok[0])==2)
     {
 // printf("before f scanf\n");
    
     node* newthing= (node*)malloc(sizeof(node));
     newthing->num=times;
     strcpy(newthing->word,tok);
     newthing->link=NULL;
     // printf("after new node\n");
     push(newthing);
     }
     
  printf("\nbefore firstpop\n");
  
   printNode(pop());
   
   printf("\n after pop 1st\n");
   printNode(pop());
  printf("after second pop\n");
  
  printHeap(head);
	return 0; 
}
