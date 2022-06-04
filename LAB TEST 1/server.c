#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<string.h>

int l_socket; // listen socket
int s_socket; // server socket
int status; // to check success / failure of different functions used in program
struct sockaddr_in* server_addr; // structure to store server address details
struct sockaddr_in* client_addr; // structure to store server address details
char *data; // pointer to buffer going to store recieved data
char *res; // pointer to buffer going to store data going to be sent

/*
 * function to handle interrupt raised by ctrl + c
 * we need to close all the sockets and free all the memory allocated during run time
*/
void int_handle(int sig){
    /*
     * syntax of close:
     * int close(int fd);
     * input: file descriptor to close
     * description: close file descriptor so it no longer point to any file
     * return: 0 on success, -1 if failed
     */
    close(s_socket); // closing server socket
    close(l_socket); // closing listen socket

    /*
     * syntax of printf:
     * int printf(const char* format,...);
     * args: char* format: format
     * args: values to print
     * description: prints values passed in desired format
     * return : number of character printed
     */
    printf("\nSERVER CLOSED........\n"); // Server Closing Prompt

    /*
     * syntax of free:
     * void free(void *ptr);
     * input : pointer / memory to be free
     * **/
    free(server_addr); // Deallocating memory allocated to server address structure
    free(data); // Deallocating the memory allocated to buffer
    free(res); // Deallocating the memory allocated to buffer
    /*
     * syntax of exit:
     * void exit(int status);
     * input : status value to br returned to parent process
     */
    exit(0); //exit
}

/*
 * following function helps in termination of child and it dont create any xombie process
 * **/
void do_nothing(int sig){

    pid_t child_id; // process - child

    /*
     * syntax of wait:
     * pid_t wait(int * wstatus):
     * input: different status to wait
     * returns : pid of terminated or -1 in case of error
     * **/
    child_id = wait(NULL); // waiting for child

    // prompt message for client disconnected
    /*
     * functions used:
     *      inet_ntoa::
     *      syntax : int inet_aton(const char *cp, struct in_addr *inp);
     *      description : converts the Internet host address cp from the IPv4 numbers-and-dots notation  into
     *                    binary  form  (in network byte order) and stores it in the structure that inp points
     *                    to.  inet_aton()
     *      returns : nonzero if the address is valid, zero if not.
     *
     *      htons::
     *      syntax : uint16_t htons(uint16_t hostshort);
     *      description : The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
     **/
    printf("Disconnected: Client %s:%d\n", inet_ntoa(client_addr->sin_addr),ntohs(client_addr->sin_port));
}
int main(int argc, char *argv[])
{
    /*
     * syntax : sighandler_t signal(int signum, sighandler_t handler);
     * to handle signal
     * return: signal() returns the previous value of the signal handler, or SIG_ERR on error.  In the event of an  error,  errno
       is set to indicate the cause.
     * **/

    signal(SIGCHLD, do_nothing); // handeling ending of child
    signal(SIGINT,int_handle); // handeling closing of server


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

    status = l_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(status == -1){ // checking if socket created successfully or not
        printf("Error while creating socket!!\n"); // prompt message if not created
        exit(0); //exit if not creating
    }

    server_addr = malloc(sizeof(struct sockaddr_in)); // allocation of memory to struct server_addr
    server_addr->sin_family = AF_INET; // server address family =ipv4
    server_addr->sin_port = htons(0); // port : let it select by own
    server_addr->sin_addr.s_addr = htonl(INADDR_ANY) ;// address = ip


    /*
     * syntax of sizeof
     * sizeof(exp or datatype)
     * returns : size of datatype or expresion
     * **/
    int len = sizeof(struct sockaddr_in); // size of sockaddr_in

    /*
     * syntax of bind:
     *  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     *  input : int sockfd : file descriptor of socket
     *          const char struct sockaddr *addr : pointer to variable of sockaddr type
     *          socklen_t : size of sockaddr
     * description: When a socket is created with socket(2), it exists in a name space (address family) but has no address assigned to
       it.  bind() assigns the address specified by addr to the socket referred to by the file  descriptor  sockfd.   ad‐
       drlen specifies the size, in bytes, of the address structure pointed to by addr.  Traditionally, this operation is
       called “assigning a name to a socket”.
       return : -1 if failed 0 on success
     * **/
    status = bind(l_socket, (struct sockaddr *) server_addr, sizeof(*server_addr));
    if(status == -1){ // checking if bind is successful or not
        printf("Error while binding...\n"); // prompt message if bind fails
        exit(0); // exit if bind fails
    }

    /*
     * syntax of getsockname:
     * int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     * input : int sockfd : file descriptor of socket
     *          const char struct sockaddr *addr : pointer to variable of sockaddr type
     *          socklen_t : size of sockaddr
     * description :  getsockname()  returns  the current address to which the socket sockfd is bound, in the buffer pointed to by addr.
       The addrlen argument should be initialized to indicate the amount of space (in bytes) pointed to by addr.  On  re‐
       turn it contains the actual size of the socket address.
       return : -1 if failed , 0 if success
     * **/
    status = getsockname(l_socket, (struct sockaddr *) server_addr, &len);
    if(status == -1){ // checking if getsockname is successful
        printf("Error while getting socket information!!\n"); // prompt message if getsockname is failed
        exit(0); // exiting if getsockname fails
    }

    // since we let the server choose the port by own we need to display it so we can connect.
    printf("Port number is : %d\n", (int)ntohs(server_addr->sin_port));

    /*
     * listen function syntax:
     *  int listen(int sockfd, int backlog);
     * description: listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to ac‐
       cept incoming connection requests using accept(2)
     * return : 0 if success and -1 if failed
     * **/
    status = listen(l_socket, 10);
    if(status == -1){ // checking if listen is successful
        printf("Error while listening!!\n"); // prompt if listen fails
        exit(0); // exit if listen fails
    }

    client_addr = malloc(sizeof(struct sockaddr_in)); // allocation of memory to client addr structure
    int client_sz= sizeof(struct sockaddr); // getting size of sockaddr
    data = malloc(200); // Allocating the memory to buffer
    res = malloc(200); // Allocating the memory to buffer
    int n;

    while(1)
    {
        /*
         * syntax of accept:
         * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
         * description:he  accept()  system  call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts
            the first connection request on the queue of pending connections for the listening socket, sockfd, creates  a  new
            connected  socket, and returns a new file descriptor referring to that socket.  The newly created socket is not in
            the listening state.  The original socket sockfd is unaffected by this call.
        * return : non negative int (fd ) on success or -1 if failed

         * **/
        status = s_socket = accept( l_socket, (struct sockaddr *) client_addr, &client_sz);
        if(status == -1){ // checking if accepted successfully
            printf("Error while accepting connection!!\n"); // prompt if failed
            exit(0); // exit if accept fails
        }
        if ( fork()==0)
        {
            close(l_socket);

            while(1)
            {
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
                status = n = recv(s_socket, data, 199, 0);
                if(status == -1){ // checking if recv is successful
                    printf("Error while reciveing data!!\n"); // prompt if recv fails
                    exit(0); // exit if recv fails
                }
                if(n == 0)
                    break;
                data[n] = '\0';

                /*
                 * syntax of getpeername
                 * int getpeername(int  sockfd,  struct sockaddr *addr, socklen_t *addrlen);
                 * input : int sockfd : file descriptor of socket
                 *                      const char struct sockaddr *addr : pointer to variable of sockaddr type
                 *                      socklen_t : size of sockaddr
                 * description : returns  the address of the peer connected to the socket sockfd, in the buffer
                                 pointed to by addr.  The addrlen argument should be initialized to indicate
                                 the amount of space pointed to by  addr.   On return  it  contains  the actual
                                 size of the name returned (in bytes).  The name is truncated if the buffer
                                 provided is too small.
                 * return : 0 on success , -1 on failure
                 * **/
                status = getpeername(s_socket, (struct sockaddr *) client_addr, &client_sz);
                if(status == -1){ // checking if getpeername is successul or not
                    printf("Error : no response from client!\n"); // prompt message if getpeername fails
                    exit(0); // exit if getpeername fails
                }

                // Printing Message received from client
                printf("Message from client@%s:%d => %s\n",inet_ntoa(client_addr->sin_addr),ntohs(client_addr->sin_port),data);

                // Prompt for user to ask for a reply message
                printf("Type Reply Here : ");

                // reading reply
                scanf("%s",res);

                /*
                 * syntax of write
                 * ssize_t write(int socket, void* buffer, size_t length)
                 * input : int socket : specifies socket file descriptor
                 *         void* buffer : pointer to buffer where the message will be stored
                 *         size_t length : specifies the length of buffer in byte
                 * description : writes up to the length bytes from buffer starting at buffer to file reffered by socket
                 * return :  message length on success , -1 if failed
                 * **/
                status = write(s_socket, res, strlen(res));
                if(status == -1){ // checking if write is successful
                    printf("Error while writing data!!\n"); // prompt if write fails
                    exit(0); // exit if write fails
                }
            }

            //closing the socket and exiting
            close(s_socket);
            exit(0);
        }
        else
        {
            // closing the socket
            close(s_socket);
        }
    }
    return(0);
}