#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include <pthread.h>

#include <string.h>
#include <stdio.h>
int sock;
char buf[1024];
void *func(){

	while(1){
		read(sock,buf,sizeof(buf));
		printf("%s\n",buf);
	}		
}

int main(int argc,char **argv){

	struct sockaddr_in addr;
	struct epoll_event *events, ev,ev2;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_family=AF_INET;

	sock = socket(AF_INET,SOCK_STREAM,0);
	connect(sock,(struct sockaddr *)&addr,sizeof(addr));
	
	pthread_t thread;
	pthread_create(&thread, NULL, func,NULL);	

	while(1){
		scanf("%s",buf);
		write(sock,buf,sizeof(buf));
	}
	return 0;
}


	
		
