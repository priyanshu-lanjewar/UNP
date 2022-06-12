#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>
// signal(signal_id, function_name)
int net_socket;
void int_handel(int sig)
{
	printf("\n Exit from client .....\n");
	close(net_socket);
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, int_handel);
	net_socket = socket (AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	connect(net_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    fd_set* read_set = malloc(sizeof(fd_set));
    FD_ZERO(read_set);
    int maxfd;
	char data[201];
	int n;
	while(1)
	{
        FD_SET(fileno(stdin),read_set);
        FD_SET(net_socket,read_set);
        maxfd = 1 + (net_socket > fileno(stdin) ? net_socket : fileno(stdin));
        select(maxfd,read_set,NULL,NULL,NULL);
        if(FD_ISSET(fileno(stdin),read_set)){
            if(fgets(data,200,stdin)==NULL){
                printf("Client Terminated The connection..");
                break;
            }
            else{
                write(net_socket,data, strlen(data));
            }
        }
        if(FD_ISSET(net_socket,read_set)){
            n = recv(net_socket,data,200,0);
            if(n==0){
                printf("Server Terminated The Connections ......");
                break;
            }
            else{
                data[n] = '\0';
                printf("%s\n",data);
            }
        }
	}
	//close the connection
	close(net_socket);
	return(0);
}