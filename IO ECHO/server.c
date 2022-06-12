#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/select.h>
#define  MAX(a,b) (a>b ? a : b)
int l_socket, s_socket;
void stop(int sig)
{
	printf("Server exiting .....\n");
	close(l_socket);
	close(s_socket);
	exit(0);
}
void do_nothing(int sig)
{
	pid_t childid;
	childid = wait(NULL);
	printf("%d child has terminated....\n", childid);
}
int main(int argc, char *argv[])
{
	signal(SIGCHLD, do_nothing);
	signal(SIGINT, stop);
	// listening socket
	l_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY) ;//inet_addr(argv[1])i;
	int len = sizeof(struct sockaddr_in);
	//bind the socket to port
	bind( l_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
	getsockname(l_socket, (struct sockaddr *)&server_addr, &len);
	printf("Port number is : %d\n", (int)ntohs(server_addr.sin_port));

	listen(l_socket, 10);

	struct sockaddr_in client_addr;
	int client_sz= sizeof(struct sockaddr);
    fd_set* read_set = malloc(sizeof(fd_set));
    FD_ZERO(read_set);
    int maxFd;
	char data[200];
	int n;

	while(1)
    {
		s_socket = accept( l_socket, (struct sockaddr *) &client_addr, &client_sz);
		if ( fork()==0)
		{
			///
			close(l_socket);
			while(1)
	                {
        	                n = recv(s_socket, data, 199, 0);
                	        if(n == 0)
                        	        break;
                        	data[n] = '\0';
                        printf("%s\n",data);
                        	write(s_socket, data, sizeof(data));
                	}
			getpeername(s_socket, (struct sockaddr *) &client_addr, &client_sz);
			printf("%s is the ip exiting... \n", inet_ntoa(client_addr.sin_addr));
			printf("%d is the port of client \n", ntohs(client_addr.sin_port));
			// sockaddr_in -> sin_family
			// sockaddr_in -> sin_port
			// sockaddr_in -> sin_addr -> s_addr
                	close(s_socket);
			exit(0);
		}
		else
		{
			close(s_socket);
		}
	}
	return(0);
}