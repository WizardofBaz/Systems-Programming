#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <libgen.h>
#include <netinet/in.h>
#include <pthread.h>



void garbage(char *path);
pthread_mutex_t lock;
char * s_pathway(char * path,char * projname);
int newest(char *path);
void file_deleter(int socket, char * projname);
char *find_name(char *message);
void *waiter (void *fd);
void file_maker(int socket, char * projname);


typedef struct socket_run {
    int socket;
    struct socket_run* before;
    struct socket_run* link;
}socket_run;

int main(int argc, char *argv[])
{

	if(argc<2)
	{
		printf("Missing port!");
		exit(EXIT_FAILURE);
	}

	//what
	struct sockaddr_in address,placement;



	int descriptor = socket(AF_INET,SOCK_STREAM,0);
	if(descriptor==0)
	{
		printf("ERROR: didn't make socket ");
	  exit(EXIT_FAILURE);
	}
	//what

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port= htons(atoi(argv[1]));

	int word=1;
	

	if (setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&word, sizeof(word)))
	{
        	printf("ERROR: Failed to make setsockopt.");
        	exit(EXIT_FAILURE);
	}

	
	int binder=bind(descriptor ,(struct sockaddr *)&address,sizeof(address));
	if(binder==-1)
	{
		printf("ERROR: Cannot bind to the address.");
		exit(EXIT_FAILURE);
	}


	int listener=listen(descriptor,5);
	if(listener<0)
	{
		printf("ERROR:Cannot listen");
		exit(EXIT_FAILURE);
	}

	int c_sizer=sizeof(placement);
	int socket;

  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("ERROR: mutex for [destroy] hasn't worked\n");
      exit(EXIT_FAILURE);
  }

	while(socket = accept(descriptor, (struct sockaddr *)&placement, &c_sizer))
	{
		pthread_t server_thread;

		pthread_create(&server_thread,NULL,waiter,(void*) &socket);
		
		if(socket==-1)
		{
			printf("ERROR:Can't accept socket");
			exit(EXIT_FAILURE);
		}

	}
	return 0;
}

//HERE
int newest(char *path)
{

 	struct dirent *paw;
 	DIR *directory = opendir(path);
	int newBoys = 0;
	if (directory == NULL)
        {
		printf("no such project");
		return -1;
        }
	while ((paw = readdir(directory)) != NULL)
        {
  		if (newBoys < atoi(paw->d_name))
		{
			newBoys = atoi(paw->d_name);
		}
  	}
	closedir(directory);
	return newBoys;
}

char * s_pathway(char * path,char * projectname){

  char * server_road=malloc(sizeof(path)+30);
  strcpy(server_road,"./server_repo/");
  char * paw= strtok(path,"/");
  int l=0;
  while(paw!=NULL)
  {

    if(l==2)
    {
      char springcress[500];
      strcpy(springcress,"./server_repo/");
      strcat(springcress,projectname);
      
      
      int new_version=newest(springcress);
      char latverschar[5];
      sprintf(latverschar,"%d", new_version);
      
      
      strcat(server_road,latverschar);
      strcat(server_road,"/");

    }
    if(!(l==0))
    {
      strcat(server_road,paw);
      strcat(server_road,"/");
    }

    paw= strtok(NULL,"/");
    l++;
  }

  server_road[strlen(server_road)-1]='\0';
  return server_road;


}

void *waiter (void *fd)
{
	int sock = *(int *)fd;

	int reader_s, writer_s;

	char client_message[3000];

  reader_s = recv(sock,client_message,3000,0);
	if(reader_s<=0)
  {
    printf("error");
  }
	char chiller[8];
	int x=0;
	while(x<5)
	{
		chiller[x]=client_message[x];
		x++;
	}
	chiller[8]='\0';

	if(strcmp(chiller,"create")==0)
	{
    char * projnam = find_name(client_message);
		file_maker(sock,projnam);
    free(projnam);
	}

  else if(strcmp(chiller,"comit")==0)
  {

    char * projnam = find_name(client_message);
    char s_path[200];
    snprintf(s_path, sizeof(s_path), "./%s/%s", "server_repo", projnam);
    char new_char[20];
    int new_server = newest(s_path);
    sprintf(new_char,"%d", new_server);
    send(sock,new_char,sizeof(new_char),0);
  }

  else if(strcmp(chiller,"chkot")==0)
  {
    char * projnam = find_name(client_message);
    char ship_path[600];
    strcpy(ship_path,"./server_repo/");
    strcat(ship_path,projnam);
    DIR * currdir;
  	struct dirent *pointer;
    currdir=opendir(ship_path);
  	
  	if (!currdir)
  	{
      printf("ERROR: Project doesn't exist!");
      char *failure="failure";
      if (send(sock,failure,strlen(failure),0) < 0)
  		{
  			printf("error \n");
        exit(EXIT_FAILURE);
  		}


    }
    else
    {
      char *success="success";
      if (send(sock,success,strlen(success),0) < 0)
  		{
  			printf("error \n");
        exit(EXIT_FAILURE);
  		}
      char new_char[10];
      int new_server = newest(ship_path);
      sprintf(new_char,"%d", new_server);
      strcat(ship_path,"/");
      strcat(ship_path,new_char);
      strcat(ship_path,"/.manifest");
      fflush(stdout);
      int wom=open(ship_path,O_RDWR,0644);
      if(wom<0)
      {
        printf("ERROR:manifest not available for checkout ");
        exit(EXIT_FAILURE);;
      }
      char manifesto [2000];

      if((read(wom,manifesto,sizeof(manifesto)))<0)
      {
        exit(EXIT_FAILURE);
      }
    
      if (send(sock,manifesto,strlen(manifesto),0) < 0)
      {
        printf("error \n");
        exit(EXIT_FAILURE);
      }
      char keeper [2000];
      char *waterways;
      int plus=0;
      waterways= strtok(manifesto,"\t \n");
      char *list[25];

      int jump=0;
      while(waterways!=NULL)
			{

				if (jump==0||((jump%3)==0))
				{
					char *thingy=malloc(29);
          strcpy(thingy,waterways);
          list[plus]=thingy;
          plus++;
				}
				waterways= strtok(NULL,"\t \n");
				jump++;
			}
  
  int path_amount=plus;
      char * complete;

      int file_amounts=0;
      char talkers[3000];
      while(plus!=-1)
      {
        complete=list[plus];
        if(complete!=NULL)
        {

         char*stickers=malloc(sizeof(&complete));
         strcpy(stickers,complete);
        
         char *s_ways=s_pathway(stickers,projnam);
        
        
          int file_disc=open(s_ways,O_CREAT|O_RDWR,0644);
          char holder[300];

          read(file_disc,holder,sizeof(holder));

          if(!(file_disc<0))
          {
            file_amounts++;
          }

          off_t begin = lseek(file_disc, 0, SEEK_CUR);
          int large_f = lseek(file_disc, 0, SEEK_END);
          lseek(file_disc, begin, SEEK_SET);
          close(file_disc);
          char large_c[8];
          sprintf(large_c, "%d", large_f);
          

          int pathlen = strlen(complete);
          char pathlenchar[5];
          sprintf(pathlenchar, "%d", pathlen);
          strcat(talkers,pathlenchar);
          strcat(talkers,":");
          strcat(talkers,complete);
          strcat(talkers,":");
          strcat(talkers,large_c);
          strcat(talkers,":");
          strcat(talkers,holder);
          strcat(talkers,":");

          free(stickers);
          free(s_ways);

      }
        plus--;
      }

      strcat(talkers,"\0");
      send(sock,talkers,sizeof(talkers),0);
      while(path_amount!=-1)
      {
        free(list[path_amount]);
      }


    }

  }

  else if(strcmp(chiller,"destr")==0)
	{
    char * projnam = find_name(client_message);
   
    file_deleter(sock,projnam);

    free(projnam);
  }



  return 0;
}


void file_deleter(int socket, char * projname)
{
  DIR * thisdir;
	struct dirent *pointer;
	char path [2000];
	strcpy(path,"./server_repo/");
	strcat(path,projname);
  	thisdir=opendir(path);
	
	if (!thisdir)
	{
    char *failure="destroy was a failure";
    if (send(socket,failure,strlen(failure),0) < 0)
		{
			printf("Error \n");
      exit(EXIT_FAILURE);
		}
    printf("Client request was a failure, file does not exist\n");
    fflush(stdout);
    closedir(thisdir);
		return;
  }

  else
  {
   
    char *success="destr:success";
    if (send(socket,success,strlen(success),0) < 0)
    {
      printf("error \n");
      exit(EXIT_FAILURE);
    }
    printf("Destroy has succeeded\n");
    fflush(stdout);
  }
  return;
}

//HERE	HERE	HERE
char *find_name(char *message)
{
  int w=0;
  int missed=3;
  int b=5;
  char *project =malloc(3000);
  memset( project, '\0', sizeof(char)*3000);
  int placeholder=atoi(&message[b+1]);
  
  int runner=placeholder;
  int digitcount = 0;
 while (runner != 0) {
     runner = runner / 10;
     ++digitcount;
 }
 missed+=(digitcount-1);
 
   while(w<placeholder)
  {
    project[w]=message[b+missed+w];
    w++;
  }
  return project;

}


void file_maker(int socket, char * projname)
{
	DIR * thisdir;
	struct dirent *pointer;
	thisdir= opendir("./server_repo");
	char path [4000];
	
	strcpy(path,"./server_repo/");
	strcat(path,projname);
	
	
	if (!thisdir)
	{

		int maker = mkdir("./server_repo", S_IRWXU | S_IRWXG | S_IRWXO);
		if(maker==-1)
		{
			printf("ERROR:Didn't make director");
			exit(EXIT_FAILURE);
		}
		maker = mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
		if(maker==-1)
		{
			printf("ERROR:Didn't make paw");
			exit(EXIT_FAILURE);
		}
		strcat(path,"/1");
		maker = mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
		if(maker==-1)
		{
			printf("ERROR:Didn't make paw");
			exit(EXIT_FAILURE);
		}
		strcat(path,"/.Manifest");

		maker=open(path,O_CREAT,0644);
		if(maker<0)
		{
			printf("ERROR:Didn't make manifest!");
			exit(EXIT_FAILURE);
		}
		char *success="create was success";
    if (send(socket,success,strlen(success),0) < 0)
		{
			printf("Error \n");
      exit(EXIT_FAILURE);
		}
    printf("Create was successful\n");
    fflush(stdout);
    closedir(thisdir);
		return;
	}

	closedir(thisdir);
	thisdir=opendir(path);
	
	if(!thisdir)
	{

		int maker = mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
		if(maker==-1)
		{
			printf("ERROR:Did not make paw");
			exit(EXIT_FAILURE);
		}
		strcat(path,"/1");
		maker = mkdir(path,S_IRWXU | S_IRWXG | S_IRWXO);
		if(maker==-1)
		{
			printf("ERROR:Did not make paw ");
			exit(EXIT_FAILURE);
		}
		strcat(path,"/.Manifest");
		maker=open(path,O_CREAT,0644);
		if(maker<0)
		{
			printf("ERROR:Could not make manifest");
			exit(EXIT_FAILURE);
		}
    char *success="create was a success";
    if (send(socket,success,strlen(success),0) < 0)
		{
			printf("Error \n");
      exit(EXIT_FAILURE);

		}
    printf(" Create was successful\n");
    fflush(stdout);
		closedir(thisdir);
		return;
	}
	else
	{
    char *success="create was a failure";
    if (send(socket,success,strlen(success),0) < 0)
		{
			printf("error \n");
			exit(EXIT_FAILURE);
		}
		printf("Create has failed, project must already exist\n");
    fflush(stdout);
		return;
	}

	return;
}

