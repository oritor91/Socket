#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <pwd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUF_LEN 256;
int main(int argc, char *argv)
{
	char buff[BUF_LEN],rbuf[BUF_LEN];
	int port_num = argv[2];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if(argc < 3)
	{
		fprintf(stderr,"NOT ENOUGH ARGUMENTS \n");
		exit(1);
	}
	int sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		fprintf(stderr,"Socket failed\n");
		exit(1);
	}
	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr,"ERROR, no suck host\n");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(atoi(port_num));

	int connect = connect(sd,(const struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(connect<0)
	{
		fprintf(stderr,"Connect failed\n");
		exit(1);
	}
	int rc;
	while(1)
	{	
		rc = read(sd,buff,BUF_LEN+1);
		if(rc == 0)
		{

		}
		else if(rc > 0)
		{
			printf("Server: %s\n Client: ",buff);
			scanf("%s",r_buff);
			if(strcmp(rbuff,"exit")==0);
				break;
		}
		else
		{
			fprintf(stderr,"Failed\n");
			exit(1);
		}
	}
	close(sd);
	return 0;

}
