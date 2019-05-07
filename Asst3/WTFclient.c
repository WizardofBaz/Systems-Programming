#include <dirent.h>
#include <openssl/sha.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include<unistd.h>

typedef struct noders
{
	int current;
	char *path;
	char *brown;
	struct noders *link;
} node;

void address_finder(char* addr[]);

void configure(char * IP, char * port);

node *man_list(char *projName);
int updated(char *path);
void update(char *projName);
void commit(char *projName,int new_server);
void recent(char *projName);
char * sub_d(char * path);


int connection();
int done_config();
void add(char * pathname, char * filer);
void remover(char *pathname, char * filer);
char *hash_func(char * path);




int main(int argc, char *argv [])
{
	if(argc<2)
	{
		printf("Wrong number of arguments!");
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[1],"configure")==0)
	{
		if(argc!=4)
		{
			printf("Wrong number of arguments or format! \n");
			return 0;
		}
		configure(argv[2],argv[3]);
		printf("[configure] done\n");
		return 0;
	}

	if (done_config()==-1)
	{
		printf("Need configure first!");
		return 0;
	}

	else if(strcmp(argv[1],"create")==0)
	{
		if(argc!=3)
		{
			printf("format inccorect!.\n");
			return 0;
		}

		char messenger[1600];
		char length[10];
		sprintf(length, "%d", strlen(argv[2]));
		strcpy(messenger,"create:");
		strcat(messenger,length);
		strcat(messenger,":");
		strcat(messenger,argv[2]);
		strcat(messenger,"\0");

		int socket=connection();
		if (send(socket,messenger,strlen(messenger),0) < 0)
		{
			printf("Error \n");
			return 1;
		}
		char s_answer[1600];
		int r_length;


		r_length== recv(socket,s_answer,sizeof(s_answer),0);
		if(r_length < 0)
		{
			printf("Error");
		}


		if(strcmp(s_answer,"create was success")==0)
		{
			char new_path[1600];
			strcpy(new_path,"./");
			strcat(new_path,argv[2]);
			int success = mkdir(new_path, S_IRWXU | S_IRWXG | S_IRWXO);
			if(success==-1)
			{
				printf("ERROR was not successful");
				close(socket);
				exit(EXIT_FAILURE);
			}

			strcat(new_path,"/.Manifest");
			success=open(new_path,O_CREAT,0644);
			if(success<0)
			{
				printf("ERROR: answers not made");
				close(socket);
				exit(EXIT_FAILURE);
			}
			printf("client [create] was successful\n");
			fflush(stdout);
		}
		else
		{
			printf("create failed, project was same name exists\n");
			close(socket);
			exit(EXIT_SUCCESS);
		}

		return 0;
	}

	else if(strcmp(argv[1],"destroy")==0)
	{
		if(argc!=3)
		{
			printf("wrong number of arguments for this command\n");
			return 0;
		}
		char messenger[1600];
		char length[5];
		sprintf(length, "%d", strlen(argv[2]));
		strcpy(messenger,"destr:");
		strcat(messenger,length);
		strcat(messenger,":");
		strcat(messenger,argv[2]);
		strcat(messenger,"\0");

		int socket=connection();
		if (send(socket,messenger,strlen(messenger),0) < 0)
		{
			printf("Error \n");
			return 1;
		}
		char s_answer[1600];
		int r_length;

		r_length== recv(socket,s_answer,sizeof(s_answer),0);
		if(r_length < 0)
		{
			printf("Error");
		}


		if(strcmp(s_answer,"destr:success")==0)
		{
			printf("client [destroy] command was successful\n");
			fflush(stdout);
		}
		else
		{
			printf("client request[destory] has failed. check name of file\n");
			fflush(stdout);
			close(socket);
			exit(EXIT_SUCCESS);
		}

		return 0;
	}

	else if(strcmp(argv[1],"add")==0)
	{
		if(argc!=4)
		{
			printf("wrong number of arguments.\n");
			return 0;
		}
		add(argv[2],argv[3]);
	}

	else if(strcmp(argv[1],"remove")==0)
	{
		if(argc!=4)
		{
			printf("wrong number of arguments.\n");
			return 0;
		}
		remover(argv[2],argv[3]);
	}

	else if(strcmp(argv[1],"commit")==0)
	{
		if(argc!=3)
		{
			printf("wrong number of arguments\n");
			return 0;
		}
		char messenger[1600];
		char length[5];
		sprintf(length, "%d", strlen(argv[2]));
		strcpy(messenger,"comit:");
		strcat(messenger,length);
		strcat(messenger,":");
		strcat(messenger,argv[2]);
		strcat(messenger,"\0");

		
		int socket=connection();
		if(socket==-1)
		{
			printf("ERROR: can't connect! \n");
			return 0;
		}
		if (send(socket,messenger,strlen(messenger),0) < 0)
		{
			printf("Error: Can't send message \n");
			return 1;
		}
		char new_server[10];
		recv(socket,new_server,sizeof(new_server),0);
		int server2=atoi(new_server);
		commit(argv[2],server2);
	}

	else if(strcmp(argv[1],"checkout")==0)
	{
		if(argc!=3)
		{
			printf("wrong number of arguments.\n");
			return 0;
		}
		char new_path[300];
		strcpy(new_path,"./");
		strcat(new_path,argv[2]);
		DIR * current;
	  	current=opendir(new_path);
		
		if (current)
		{
			printf("ERROR: project is here\n");
			return 0;
		}
		char messenger[1600];
		char length[7];
		sprintf(length, "%d", strlen(argv[2]));
		strcpy(messenger," :");
		strcat(messenger,length);
		strcat(messenger,":");
		strcat(messenger,argv[2]);
		strcat(messenger,"\0");

		
		int socket=connection();
		if(socket==-1)
		{
			printf("ERROR: can't connect! \n");
			return 0;
		}
		if (send(socket,messenger,strlen(messenger),0) < 0)
		{
			printf("Error: can't send message \n");
			return 1;
		}
		char working[20];
		recv(socket,working,sizeof(working),0);
		
		if(strcmp(working,"chkot:failure")==0)
		{
			printf("ERROR: [checkout] has failed\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			char main_manif[1600];
			if(recv(socket,main_manif,sizeof(main_manif),0)<0)
			{
				printf("ERROR: [checkout] client failed to get the answers\n");
				return;
			}

			
			char * working_path;
			int skip=0;
			working_path= strtok(main_manif,"\t \n");
			while(working_path!=NULL)
			{

				if (skip==0||((skip%3)==0))
				{
					
					char * subpaths=malloc(sizeof(&working_path));
					
					strcpy(subpaths,working_path);
					dirname(subpaths);
					sub_d(subpaths);
					
					int newfd=open(working_path,O_CREAT|O_APPEND);
					
					fflush(stdout);
					close(newfd);
					free(subpaths);
				}
				working_path= strtok(NULL,"\t \n");
				skip++;
			}
			strcat(new_path,"/.Manifest");
			int man_details=open(new_path,O_CREAT|O_APPEND);
			write(man_details,main_manif,strlen(main_manif));

			char svr[1600];
			recv(socket,svr,sizeof(svr),0);
			

			

			int counter=0;
			char *array[50];
			char * s_information;
			int indexer=0;
			s_information= strtok(svr,":");
			while(s_information!=NULL)
			{


				char *fpath=malloc(50);
				strcpy(fpath,s_information);
				array[indexer]=fpath;
				indexer++;
				
				s_information= strtok(NULL,":");
				
				++counter;
				
			}
			indexer--;
			int speed=indexer-2;
			while(!(speed<0))
			{
				FILE *file=fopen(array[speed],"w");
				
				
				
					
				
				fprintf(file,"%s", array[indexer]);


				
				speed=speed-4;
				indexer=indexer-4;
				fclose(file);
			}

		}


	}

	else if(strcmp(argv[1],"update")==0)
	{
		if(argc!=3)
		{
			printf("wrong number of arguments.\n");
			return 0;
		}
		update(argv[2]);
	}

	return 0;
}



void address_finder(char ** addr)
{
	char *IP=malloc(16);
	char *port=malloc(6);
	char currchar;
	int config_fd=open("config",O_RDONLY,0644);
	int IPend=0;
	off_t end=lseek(config_fd,0,SEEK_END);
	lseek(config_fd,0,SEEK_SET);

	while(currchar!='\t')
	{
		read(config_fd,&currchar,1);
		IPend++;
	}
	lseek(config_fd,0,SEEK_SET);
	read(config_fd,IP,IPend-1);
	read(config_fd,&currchar,1);
	read(config_fd,port,end-IPend);
	IP[IPend-1]='\0';
	port[end-IPend]='\0';
	addr[0]=IP;
	addr[1]=port;
	return;
}


void add(char * pathname, char * filer)
{
	DIR * current;
	struct dirent *ents;
	char path [1600];
	memset( path, 0, 1600 );
	strcpy(path,"./");
	strcat(path,pathname);
  current=opendir(path);
	
	if (!current)
	{
		printf("[add] not got");
		return;
	}
	else
	{
		strcat(path,"/.Manifest");
		int manifest_fd=open(path,O_RDWR|O_APPEND,0644);
		if(manifest_fd<0)
		{
			printf("ERROR: can't open file to add\n");
			exit(EXIT_FAILURE);
		}
		printf("pathname:%s\n",pathname);
		write(manifest_fd,pathname,strlen(pathname));
		write(manifest_fd,"\t",1);
		write(manifest_fd,"1",1);
		write(manifest_fd,"\t",1);
		char * brown=hash_func(path);
		write(manifest_fd,brown,sizeof(brown));
		write(manifest_fd,"\n",1);
		printf("[add] successful\n");
		close(manifest_fd);
		return;
	}
}

char *hash_func(char * path)
{
	FILE *fPath = fopen(path,"r");
        if (!fPath)
        {
            remove(".Commit");
            printf("error");
            return;

        }
        unsigned char brown[SHA_DIGEST_LENGTH];
        SHA256_CTX ctx;
         SHA256_Init(&ctx);
         int byte = 0;
        char currChar[10];
        while((fread(currChar, 1, sizeof(currChar), fPath)))
        {
            SHA256_Update(&ctx, currChar, byte);
        }
        SHA256_Final(brown, &ctx);
        char *liveHash=malloc(200);
        int p;
        for (p = 0; p < SHA_DIGEST_LENGTH; p++)
        {
            sprintf(liveHash + (p*2), "%02x", brown[p]);
        }
				return liveHash;
        fclose(fPath);
}

void configure(char * IP, char * port)
{
	int config_fd=open("config",O_CREAT|O_WRONLY|O_TRUNC,0644);
	config_fd=open("config",O_WRONLY|O_APPEND,0644);
	write(config_fd,IP,strlen(IP));
	write(config_fd,"\t",1);
	write(config_fd,port,strlen(port));
	return;
}

int connection()
{

		int sock_fd;
		sock_fd=socket(AF_INET,SOCK_STREAM,0);

		if(socket<0)
		{
			printf("client socked failed");
			exit(EXIT_FAILURE);
		}
		char * addr[2];
		address_finder(addr);
		char *IP=addr[0];
		char *port=addr[1];
		struct sockaddr_in serv_addr;
		serv_addr.sin_family =AF_INET;
		serv_addr.sin_port=htons(atoi(port));
		serv_addr.sin_addr.s_addr=inet_addr(IP);
		int conn_success=connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
		if(conn_success<0)
		{
			printf("Server could not connect");
			return 0;
		}
		free(IP);
		free(port);
		return sock_fd;
}

void remover(char *pathname, char * filer)
{
	DIR * current;
	struct dirent *ents;
	char path [1600];
	memset( path, 0, 1600 );
	strcpy(path,"./");
	strcat(path,pathname);

  current=opendir(path);
	
	if (!current)
	{
		printf("ERROR: [remove] has failed");
		return;
	}
	else
	{
		char path2[1600];
		strcpy(path2,path);
		strcat(path2,"/.Manifestcpy");
		strcat(path,"/.Manifest");
		
		FILE* file=fopen(path,"r");
		FILE* filecpy=fopen(path2,"a+");
		char line[1600];
		char * tok;
		while(fgets(line,sizeof(line),file))
		{
			tok=strtok(line,"\t");
			if(!(strcmp(tok,pathname)==0))
			{
				fputs(tok,filecpy);
				while((tok=strtok(NULL,"\t"))!=NULL)
				{
					fputs("\t",filecpy);

					fputs(tok,filecpy);
					

				}
				
			}


		}
		remove(path);
		rename(path2,path);
		fclose(filecpy);
		fclose(file);
		printf("remove successful\n");
		return;
	}
}


int done_config()
{
	if((open("config",O_RDONLY,0644))==-1)
	{
		return -1;
	}
	return 1;
}



void update(char *projName)
{
	char serverPath[150];
	char c_road[150];
	snprintf(serverPath, sizeof(serverPath), "%s/%s", "server_repo", projName);
	snprintf(c_road, sizeof(c_road), "%s", projName);

	int new_server = updated(serverPath);
	int latestClient = updated(c_road);
	if (new_server == -1 || latestClient == -1)
	{
		fprintf(stdout, "no such project on server");
		return;
	}
	int sameMan = 0;
	if (new_server == latestClient)
	{
		sameMan = 1;
	}
	char serverVersion[50];
	char clientVersion[50];
	sprintf(serverVersion, "%d", new_server);
	sprintf(clientVersion, "%d", latestClient);

	char serverMan[200];
	char clientMan[200];
	snprintf(serverMan, sizeof(serverMan), "%s/%s/%s", serverPath, serverVersion, ".Manifest");
	snprintf(clientMan, sizeof(clientMan), "%s/%s/%s", c_road, clientVersion, ".Manifest");

	node *frontServer = man_list(serverMan);
	node *frontClient = man_list(clientMan);

	node *serverPtr = frontServer;
	node *clientPtr;

	char updatePath[200];
	snprintf(updatePath, sizeof(updatePath), "%s/%s", c_road, ".Update");
  	int new_filer =open(updatePath, O_CREAT|O_WRONLY|O_APPEND, 0644);
	char stmt[200];

	int perfect = 1;
	int conflict = 0;

	while (serverPtr != NULL)
	{
		clientPtr = frontClient;
		while (clientPtr != NULL)
		{
			if (strcmp(serverPtr->path, clientPtr->path) == 0)
			{
				FILE *fPath = fopen(serverPtr->path, "r");
				if (!fPath)
				{
					conflict = 1;
					perfect = 0;
					fprintf(stdout, "%s\n", clientPtr->path);
					return;
				}
				unsigned char brown[SHA_DIGEST_LENGTH];
				SHA256_CTX ctx;
				SHA256_Init(&ctx);
				int byte = 0;
				char currChar[10];
				while((byte = fread(currChar, 1, sizeof(currChar), fPath)))
				{
					SHA256_Update(&ctx, currChar, byte);
				}
				SHA256_Final(brown, &ctx);
				char liveHash[200];
				int p;
				for (p = 0; p < SHA_DIGEST_LENGTH; p++)
				{
					sprintf(liveHash + (p*2), "%02x", brown[p]);
				}
				fclose(fPath);
				
				if ((strcmp(liveHash, serverPtr->brown) != 0) && sameMan == 1)
				{
					perfect = 0;
					snprintf(stmt, sizeof(stmt), "U %s %s\n", clientPtr->path, clientPtr->brown);
               				write(new_filer, stmt, strlen(stmt));
					break;
				}
				
				else if ((strcmp(liveHash, clientPtr->brown) == 0) && (serverPtr->current != clientPtr->current))
				{
					perfect = 0;
					snprintf(stmt, sizeof(stmt), "M %s %s\n", serverPtr->path, serverPtr->brown);
               				write(new_filer, stmt, strlen(stmt));
					break;
				}
				else if ((sameMan == 1 && (serverPtr->current != clientPtr->current)) || (sameMan == 0 && (serverPtr->current != clientPtr->current) && (strcmp(liveHash, clientPtr->brown) != 0 || strcmp(liveHash, serverPtr->brown) != 0)))
				{
					conflict = 1;
					perfect = 0;
					fprintf(stdout, "%s\n", clientPtr->path);
					return;
				}
			}
			
			if (clientPtr->link == NULL && sameMan == 0)
			{
				perfect = 0;
				snprintf(stmt, sizeof(stmt), "A %s %s\n", serverPtr->path, serverPtr->brown);
               			write(new_filer, stmt, strlen(stmt));
			}
			clientPtr = clientPtr->link;
		}
		serverPtr = serverPtr->link;
	}

	clientPtr = frontClient;
	while (clientPtr != NULL)
	{
		int got = 0;
		serverPtr = frontServer;
		while (serverPtr != NULL)
		{
			if (strcmp(serverPtr->path, clientPtr->path) == 0)
			{
				got = 1;
			}
			serverPtr = serverPtr->link;
		}
		
		if (got == 0 && sameMan == 0)
		{
			perfect = 0;
			snprintf(stmt, sizeof(stmt), "D %s %s\n", clientPtr->path, clientPtr->brown);
               		write(new_filer, stmt, strlen(stmt));
		}
		
		else if (got == 0 && sameMan == 1)
		{
			perfect = 0;
			snprintf(stmt, sizeof(stmt), "U %s %s\n", clientPtr->path, clientPtr->brown);
               		write(new_filer, stmt, strlen(stmt));
		}
		clientPtr = clientPtr->link;
	}
	if (conflict == 1)
	{
		remove(updatePath);
		fprintf(stdout, "fix problems before update\n");
		return;
	}
	if (perfect == 1)
	{
		fprintf(stdout, "no further updates\n");
		return;
	}
}

int updated(char *path)
{
 	struct dirent *drct;
  DIR *directory = opendir(path);
	int latest = 0;
	if (directory == NULL)
  {
	printf("no such project");
	return -1;
  }
	while ((drct = readdir(directory)) != NULL)
        {
  		if (latest < atoi(drct->d_name))
		{
			latest = atoi(drct->d_name);
		}
  	}
	closedir(directory);
	return latest;
}



void currentVersion(char *projName)
{
	char p_road[300];
	snprintf(p_road, sizeof(p_road), "%s/%s", "server_repository", projName);
        DIR *directory = opendir(p_road);
	if (directory == NULL)
        {
		printf("no such project");
		return;
        }
	printf("%s\n", projName);
	int latest = updated(p_road);
	char current[70];
	sprintf(current, "%d", latest);
	char answers[200];
	snprintf(answers, sizeof(answers), "%s/%s/%s", p_road, current, ".Manifest");

	int fd = open(answers, O_RDONLY);
	char currChar;
	int pos = 2;
	off_t end = lseek(fd, 0, SEEK_END);
	lseek(fd, pos, SEEK_SET);

	while (pos < end)
	{
		
		read(fd, &currChar, 1);
		while (currChar != ' ' )
		{
			printf("%c", currChar);
			pos++;
			lseek(fd, pos, SEEK_SET);
			read(fd, &currChar, 1);
		}
		printf(" ");
		pos+=2;
		lseek(fd, pos, SEEK_SET);
		int lastSlash = pos;
		int wc = 0;
		
		while (1)
		{
			read(fd, &currChar, 1);
			if (currChar == ' ')
			{
				lseek(fd, lastSlash + 1, SEEK_SET);
				char *filer = malloc(sizeof(char) * wc+1);
				read(fd, filer, wc);
				printf("%s\n", filer);
				
				while (currChar != '\n')
				{
					pos++;
					lseek(fd, pos, SEEK_SET);
					read(fd, &currChar, 1);
				}
				break;
			}
			else if (currChar == '/')
			{
				lastSlash = pos;
				wc = 0;
			}
			pos++;
			wc++;
		}
		pos++;
		lseek(fd, pos, SEEK_SET);
	}
	closedir(directory);
}

char * sub_d(char * path)
{
	if(strcmp(path,".")==0)
	{
		return ".";
	}
	else
	{
		char *cpy=malloc(sizeof(&path));
		strcpy(cpy,path);
		sub_d(dirname(path));
		
		mkdir(cpy,S_IRWXU | S_IRWXG | S_IRWXO);
		free(cpy);
	}

	return;
}



node *man_list(char *p_road)
{
	FILE *man = fopen(p_road, "r");
	if (man == NULL)
	{
		printf("error");
	}
	char curr[300];
	fscanf(man, "%s", curr);
	node *front = NULL;
	while (fscanf(man, "%s", curr) != EOF)
	{
		node *newNode = malloc(sizeof(node));
		int current = atoi(curr);
		newNode->current = current;

		fscanf(man, "%s", curr);
		char *path = malloc(sizeof(curr));
		strcpy(path, curr);
		newNode->path = path;

		fscanf(man, "%s", curr);
		char *brown = malloc(sizeof(curr));
		strcpy(brown, curr);
		newNode->brown = brown;

		if (front == NULL)
		{
			front = newNode;
		}
		else
		{
			newNode->link = front;
			front = newNode;
		}
	}
	return front;
}

void commit(char *projName,int new_server)
{
	char c_road[150];
	snprintf(c_road, sizeof(c_road), "%s", projName);

	int latestClient = updated(c_road);
	if (new_server == -1 || latestClient == -1)
	{
		fprintf(stdout, "ERROR: no such project\n");
		return;
	}
	if (new_server != latestClient)
	{
		fprintf(stdout, "ERROR: need to update\n");
		return;
	}

	char did_update[200];
	snprintf(did_update, sizeof(did_update), "%s/%s", c_road, ".Update");
	printf("c_road:%s",did_update);
	FILE *new_filer = fopen(did_update, "r");
	if (new_filer != NULL)
	{
		fseek(new_filer, 0, SEEK_END);
		int size = ftell(new_filer);
		if (size != 0)
		{
			fprintf(stdout, "ERROR: file exists.\n");
			return;
		}
	}
}


