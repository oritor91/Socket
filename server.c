#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#define BUF_LEN 256
// argv[1] = port ||| argv[2] = ip
int main(int argc, char *argv)
{
	int sd, new_sd;    
	char buffer[256],r_buffer[256];     
	struct sockaddr_in serv_addr; 
	struct sockaddr cli_addr; 
	socklen_t clilen;     
	int n,rc,rc_w;  

    	if (argc < 2) {          
		fprintf(stderr,"ERROR, no port provided\n");          
		exit(1);
	}

	sd = socket(AF_INET,SOCK_STREAM,0); 
	if (sd < 0)  
		error("ERROR opening socket"); 

	serv_addr.sin_family = AF_INET;  
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(atoi(argv[1]));   
	

	if (bind(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)                 
		error("ERROR on binding");    
  
	listen(sd,5); 

	while(1)
	{
		new_sd = accept(sd, &cli_addr, &clilen);
		if(new_sd<0)
		{
			fprintf(stderr,"Error on accept\n");
			exit(1);
		}
		rc = read(new_sd,buffer,BUF_LEN);
		if(rc == 0)
			break;
		else if( rc > 0)
		{
			printf("Client: %s\nServer: ",buffer);
			scanf("%s",r_buffer);
			rc_w = write(new_sd,r_buffer,sizeof(r_buffer));
		}
		else
		{
			fprintf(stderr,"read() failed\n");
			exit(1);
		}
	}

		close(new_sd);
		close(sd);
		return 0;	
}