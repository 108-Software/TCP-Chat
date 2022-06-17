#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "erproc.h"


int main(){
	int server = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr = {0};    
	adr.sin_family = AF_INET;
	adr.sin_port = htons(23543);   
	Bind(server, (struct sockaddr *) &adr, sizeof adr);
	printf("Server is ready!");
	Listen(server, 5);
	socklen_t addrlen = sizeof adr;
	int fd = Accept(server, (struct sockaddr *) &adr, &addrlen);
	while (1){ 
		ssize_t nread;
		char buf[256];
		nread = read(fd, buf, 256);  
		if (nread == -1 ){
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		if (nread == 0){
			printf("END OF FILE");
		}
		write(STDOUT_FILENO, buf, nread);
		write(fd, buf, nread);
		printf("\n");
	}

	
	return 0;
}