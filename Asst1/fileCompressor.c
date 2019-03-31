#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>

#define inter 1
#define leaf 0

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
static node* root=NULL;

int isDelim(char temp)
{
  if(temp==' ' || temp=='\n' || temp=='\t' 
     || temp=='\a' || temp=='\b' || temp=='\f'
      || temp=='\r' || temp=='\v')
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

void printHeap(node* temp)
{
  node* printer =temp;
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
void freeHeap()
{
  node* temp=head;
  while(head !=NULL)
    {
      head=head->link;
      free(temp);
      temp=head;
    }
}
int isFound(char* comparer, int times)
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
	      holder->num = holder->num + times;
	      return 1;
	    }
	  else
	    {
	      holder=holder->link;
	    }
	}//end of while
      if(strcmp(holder->word,comparer)==0)
	{
	  holder->num= holder->num + times;
	  return 1;
	}
      else
	{
	  return -1;
	}
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

void heapatize(char* filename)
{
  // this functions take the file of frequences and words
  // and sorts them into a heap theheap pt is head
FILE* fp=NULL;
fp= fopen(filename,"r");

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
       if(isFound(tok,times)<0)
	 {
     node* newthing= (node*)malloc(sizeof(node));
     newthing->num=times;
     strcpy(newthing->word,tok);
     newthing->link=NULL;
     // printf("after new node\n");
     push(newthing);
	 }
     }
  fclose(fp);
}	      
void tokentize(char** files)
{
  int numoffiles=0; 
  char *over1="\\t";
  char *over2="\\n";
  char *over3="\\s";
  char *over4="\\a";
  char *over5="\\b";
  char *over6="\\f";
  char *over7="\\r";
  char *over8="\\v";
  
  char* textfile="asst2test.txt";
  
  FILE* fp= fopen(files[numoffiles],"r");
  
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
	       
	   if(string[0]!='\0' && isFound(string,1)>0)
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
	       if(isFound("\\s",1)<0)
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
		    if(isFound("\\t",1)<0)
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
		   if(isFound("\\n",1)<0)
		    {
		      //printf("do we get here LASTLY\n");
		     node* insertig= (node*)malloc(sizeof(node));
		      insertig->num=1;
	        	strcpy(insertig->word,over2);
	        	insertig->link=NULL;
			//	printf("inserting\n");
			insert(insertig);
		    }
		   else
		     {
		       if((tempchar=='\a'))
			 {
			   if(isFound("\\a",1)<0)
			     {
		     
			       node* inserting= (node*)malloc(sizeof(node));
			       inserting->num=1;
			       
			       strcpy(inserting->word,over4);
			       inserting->link=NULL;
			       insert(inserting);
			     }
			 }
		       else
		       {
		       if((tempchar=='\b'))
			 {
			   if(isFound("\\b",1)<0)
			     {
		     
			       node* inserting= (node*)malloc(sizeof(node));
			       inserting->num=1;
			       
			       strcpy(inserting->word,over5);
			       inserting->link=NULL;
			       insert(inserting);
			     }
			 }
		        else
		       {
		       if((tempchar=='\f'))
			 {
			   if(isFound("\\f",1)<0)
			     {
		     
			       node* inserting= (node*)malloc(sizeof(node));
			       inserting->num=1;
			       
			       strcpy(inserting->word,over6);
			       inserting->link=NULL;
			       insert(inserting);
			     }
			 }
		        else
		       {
		       if((tempchar=='\r'))
			 {
			   if(isFound("\\r",1)<0)
			     {
		     
			       node* inserting= (node*)malloc(sizeof(node));
			       inserting->num=1;
			       
			       strcpy(inserting->word,over7);
			       inserting->link=NULL;
			       insert(inserting);
			     }
			 }
		        else
		       {
		       if((tempchar=='\v'))
			 {
			   if(isFound("\\v",1)<0)
			     {
		     
			       node* inserting= (node*)malloc(sizeof(node));
			       inserting->num=1;
			       
			       strcpy(inserting->word,over8);
			       inserting->link=NULL;
			       insert(inserting);
			     }
			 }
		     }
		     }
		     }
		     }
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
	  fp= fopen(files[numoffiles],O_RDONLY);
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
void appendToTotal( char* file)
{
  FILE *appending= fopen("totaltext.txt","a");
  FILE *appender = fopen(file,"r");
  
  if( appending==NULL || appender ==NULL)
    {
      printf("the file %s\n",file);
    }
  char tempchar ;
 
  while((tempchar = fgetc(appender))!= EOF)
    {
      fputc(tempchar,appending);
    }
  
  fclose(appending);
  fclose(appender);
  
}
void remakeHeap()
{
  FILE*fp = fopen("asst2test2.txt","w");
  if (fp==NULL)
    {
      printf("error opening\n");
    }
  else
    {
     node* popping;
     
   while(head !=NULL)
    {
      popping= pop();
      fprintf(fp,"%d\t%s\n",popping->num,popping->word);
      free(popping);
    }
 
  fclose(fp);
} 

}
void buildCodebook(char* file)
{
  char* temp[] = {file, NULL};
  tokentize(temp);
  remove("totaltext.txt");
  heapatize("asst2test.txt");
  remakeHeap();
  freeHeap();
  heapatize("asst2test2.txt");
  remove("asst2test.txt");
  remove("asst2test2.txt");
  //at this point in the code head has the min heap in it of tokens
  // so after this line u can build the tree.
  node* temp1;
  node* temp2;
  while( head != NULL)
    {
      

}
void compress( char* file, char* book)
{
  // what ever your compression agoritim is
}
void decompress( char* file, char* book)
{
  // what ever your decompresion is
}

void dashRBuild(char* dir)
{
  if(dir==NULL)
    {
     
    }
    else
      {

  struct dirent *tempdir=NULL;
  DIR* d=opendir(dir);
 

  if(d==NULL)
    {
     
      //exit(0);
    }
  else
    {
   
      while( (tempdir=readdir(d)) !=NULL)
	{
	  if(tempdir != NULL)
	    {
	  if(tempdir->d_type == DT_DIR)
	    {
	      char extrapathname[250];
	      if( strcmp(tempdir->d_name,"..")==0 || strcmp(tempdir->d_name,".")==0 )
		 {
		   // we need this or it wil keep calling the same directory
		 }
	       else
		 {
		   // printf("%s\n", extrapathname);
		   snprintf(extrapathname , sizeof(extrapathname),"%s/%s", dir, tempdir->d_name);
		   dashRBuild(extrapathname);
		 }
	    }
	  else
	    {
	      if( tempdir->d_type == DT_REG)
		{
		  char tempname[250];
		  snprintf( tempname, sizeof(tempname),"%s/%s", dir, tempdir->d_name);
		  appendToTotal(tempname);
		  
		}
	    }


	    }// if not null
	    }//end of while
      closedir(d);
    }
  
      }
}
 int endsInHCZ(char* comp)
 {
   if(comp[strlen(comp)]=='\0' &&
      comp[strlen(comp)-1]=='z' &&
      comp[strlen(comp)-2]=='c' &&
      comp[strlen(comp)-3]=='h' &&
      comp[strlen(comp)-4]=='.' )
     {
       return 1;
     }
   else
     {
       return 0;
     }
 }
void dashRCompress( char* dir, char* book)
{
  
  if(dir==NULL)
    {
     
    }
    else
      {

  struct dirent *tempdir=NULL;
  DIR* d=opendir(dir);
 

  if(d==NULL)
    {
     
      //exit(0);
    }
  else
    {
   
      while( (tempdir=readdir(d)) !=NULL)
	{
	  if(tempdir != NULL)
	    {
	  if(tempdir->d_type == DT_DIR)
	    {
	      char extrapathname[250];
	      if( strcmp(tempdir->d_name,"..")==0 || strcmp(tempdir->d_name,".")==0 )
		 {
		   // we need this or it wil keep calling the same directory
		 }
	       else
		 {
		   //printf("%s\n", extrapathname);
		   snprintf(extrapathname , sizeof(extrapathname),"%s/%s", dir, tempdir->d_name);
		   dashRCompress(extrapathname,book);
		 }
	    }
	  else
	    {
	      if( tempdir->d_type == DT_REG)
		{
		  char tempname[250];
		  snprintf( tempname, sizeof(tempname),"%s/%s", dir, tempdir->d_name);
		  compress(tempname,book);
		  
		}
	    }


	    }// if not null
	    }//end of while
      closedir(d);
    }
  
      }
  
}
void dashRDecompress( char* dir, char* book)
{
 
  if(dir==NULL)
    {
     
    }
    else
      {

  struct dirent *tempdir=NULL;
  DIR* d=opendir(dir);
 

  if(d==NULL)
    {
     
      //exit(0);
    }
  else
    {
   
      while( (tempdir=readdir(d)) !=NULL)
	{
	  if(tempdir != NULL)
	    {
	  if(tempdir->d_type == DT_DIR)
	    {
	      char extrapathname[250];
	      if( strcmp(tempdir->d_name,"..")==0 || strcmp(tempdir->d_name,".")==0 )
		 {
		   // we need this or it wil keep calling the same directory
		 }
	       else
		 {
		   //printf("%s\n", extrapathname);
		   snprintf(extrapathname , sizeof(extrapathname),"%s/%s", dir, tempdir->d_name);
		   dashRDecompress(extrapathname,book);
		 }
	    }
	  else
	    {
	      if( tempdir->d_type == DT_REG)
		{
		  char tempname[250];
		  snprintf( tempname, sizeof(tempname),"%s/%s", dir, tempdir->d_name);
		  if(endsInHCZ(tempname) >0)
		    {
		  decompress(tempname,book);
		    }
		  
		}
	    }


	    }// if not null
	    }//end of while
      closedir(d);
    }
  
      }   
}

int main( int args, char** argv)
{
  
  if(args  <3)
    {
      printf("too few command line arguments to run compressor\n");
      exit(0);
    }
  if( args > 5)
    {
       printf("too many command line arguments to run compressor\n");
       exit(0);
    }
  // if there are R


  if(argv[1][0] =='-' && argv[2][0] =='-')
    {
      if((argv[1][1] !='R' && argv[2][1] !='R') ||
	 (argv[1][1] =='R' && argv[2][1] =='R'))
	{
	   printf("error weird flags please try again\n");
	   exit(0);
	}
      if(argv[1][1]== 'R')
	{
	  switch( argv[2][1])
	    {
	    case 'b': 
	      {
		      
	              dashRBuild(argv[3]);
		      buildCodebook("totaltext.txt");
		      
		      //remove("totaltext.txt");
	      }
	      break;
	    case 'c': dashRCompress(argv[3],argv[4]);
	      break;
	    case 'd': dashRDecompress(argv[3],argv[4]);
	      break;
	    default:  printf("error with flags\n");
	             exit(0);
	     break;
	    }
	}
      else{
	switch(argv[1][1])
	  {
	  case 'b':
	    {
	              dashRBuild(argv[3]);
		      buildCodebook("totaltext.txt");
		      // printHeap(head);
		      // printHeap(head);
		      //remove("totaltext.txt");
	    }
	      break;
	  case 'c': dashRCompress(argv[3],argv[4]);
	      break;
	  case 'd': dashRDecompress(argv[3],argv[4]);
	      break;
	  default: printf("error with flags\n");
                   exit(0);
	     break;
	  }
      }
    }
  else
    {

  // if no R s are here
  // this should just be files
  switch( argv[1][1] )
    {
    case 'b': buildCodebook(argv[2]);
      //printHeap(head);
      // printHeap(HEAD);
      break;
    case 'c': compress(argv[2], argv[3]);
      break;
    case 'd': decompress(argv[2], argv[3]);
      break;

    default: printf("error with flags\n");
             exit(0);
	     break;
    }
    }
  //printHeap(head);

  freeHeap();
  //remove("totaltext.txt");
	return 0; 
}
