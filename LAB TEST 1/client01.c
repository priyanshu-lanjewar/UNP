#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
int net_socket; // socket fd
struct sockaddr_in *server_address; // structure to store server details
char *buffer; // pointer to buffer going to receive data
char *data; // pointer to buffer going to store data going to be sent
int status; // to check success / failure of different functions used in program


void int_handel(int sig)
{
    printf("\nConnection Terminated\nExiting...\n"); // Client Closing Prompt
    free(server_address); // Deallocating the memory allocated to structure
    free(buffer); // Deallocating the memory allocated to buffer
    free(data); // Deallocating the memory allocated to buffer
    close(net_socket); // closing server socket
    exit(0); // exiting
}

int main(int argc, char *argv[])
{

    /*
     * syntax : sighandler_t signal(int signum, sighandler_t handler);
     * to handle signal
     * return: signal() returns the previous value of the signal handler, or SIG_ERR on error.  In the event of an  error,  errno
       is set to indicate the cause.
     * **/
    signal(SIGINT, int_handel);

    /*
     * syntax : int socket(int domain, int type, int protocol);
     * input : domain: type of ip => ipv4, ipv6, sets protocols
     *         type : specifies connection type
     *         protocol : protocol to be used
     * socket()  creates  an  endpoint for communication and returns a file descriptor that refers to that endpoint.  The
       file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently  open  for
       the process.
     * return : file descriptor on success else -1
     **/
    status = net_socket = socket (AF_INET, SOCK_STREAM, 0);
    if(status == -1){ // checking if socket is successful or not
        printf("Error while creating socket...\n"); // prompt message if socket fails
        exit(0); // exit if socket fails
    }

    server_address = malloc(sizeof(struct sockaddr_in)); // allocating memory to sockaddr_in structure
    server_address->sin_family = AF_INET; // assigning IP family = ipv4 / ipv6
    server_address->sin_port = htons(atoi(argv[2])); // reading port
    server_address->sin_addr.s_addr = inet_addr(argv[1]); // reading ip


    /*
     * syntax of connect:
     * int connect(int socket, const struct sockaddr * address, socklen_t adress_len);
     * input :  int socket : file descriptor of socket
     *          const char struct sockaddr *address : pointer to variable of sockaddr type
     *          socklen_t : size of sockaddr
     * description: connect function makes an attempt to make a connection on a socket
     * return : 0 if successful else -1
     * **/
    status = connect(net_socket, (struct sockaddr *) server_address, sizeof(*server_address));
    if(status == -1){ // checking if connect is successful or not
        printf("Error while Connecting...\n"); // prompt message if connect fails
        exit(0); // exit if connect fails
    }

    data = malloc(201); // Allocating memory to buffer
    int n;
    buffer = malloc(200); // Allocating memory to buffer
    while(1)
    {

        // prompt for user to enter data to send
        printf("\nEnter Message to Sent : ");

        // scanning input
        scanf("%s", data);

        /*
        * syntax of write
        * ssize_t write(int socket, void* buffer, size_t length)
        * input : int socket : specifies socket file descriptor
        *         void* buffer : pointer to buffer where the message will be stored
        *         size_t length : specifies the length of buffer in byte
        * description : writes up to the length bytes from buffer starting at buffer to file reffered by socket
        * return :  message length on success , -1 if failed
        * **/
        status = write(net_socket, data, strlen(data));
        if(status == -1){ // checking if write is successful or not
            printf("Error while write...\n"); // prompt message if write fails
            exit(0); // exit if write fails
        }

        /*
        * syntax of recv
        * ssize_t recv(int socket, void* buffer, size_t length, int flags)
        * input : int socket : specifies socket file descriptor
        *         void* buffer : pointer to buffer where the message will be stored
        *         size_t length : specifies the length of buffer in bytes
        *         int flags : specifies the type of message reception.
        * description : recieve the message and store in buffer
        * return :  message length on success , -1 if failed
        * **/
        status = n = recv(net_socket, buffer, 200, 0);
        if(status == -1){ // checking if recv is successful or not
            printf("Error while receiving...\n"); // prompt message if recv fails
            exit(0); // exit if recv fails
        }

        // appending null character at end of data to show end of string
        buffer[n] = '\0';

        // printing message recieved from server
        printf("Message from server@%s:%d => %s\n",inet_ntoa(server_address->sin_addr),ntohs(server_address->sin_port),buffer);

    }
    //close the connection
    close(net_socket);
    return(0);
}