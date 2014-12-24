/*
    Server side:
    + Open a socket
    + Bind to address and port
    + Listen for incomming connections
    + Accept connections
    + Read/Send
    Reference: http://www.binarytides.com/winsock-socket-programming-tutorial/
*/

#include <stdio.h>
#include<winsock2.h> // replace for sys/socket.h in Linux
#include "../include/server.h"
#include "../include/execute.h"
#include <unistd.h> // read and close functions
#include <time.h>

#define TRUE 1
#define FALSE 0

const long MAX_SIZE = 1000000;
const long ARGUMENTS_SIZE = 2048;

WSADATA wsa;
SOCKET s, new_socket; // s - master_socket
int i, sd, activity, recv_size, file_size, max_sd, client_socket[30], // master_socket
max_clients, val_read, addrlen;
struct sockaddr_in server, client;
char *message, *data_received, buffer[255], *c_time_string;
fd_set readfds; // set of socket descriptors
FILE *log_file, *log_server;

// Initialising Winsock
void InitializeWinsock()
{
    //printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Initialize Winsock failed. Error Code : %d",WSAGetLastError());
        server_log = "Initialize Winsock failed.\n";
        exit(1);
    }
    server_log = "Initialized Winsock.\n";
    printf("Initialized Winsock.\n");
}

// Create a socket
void CreateSocket()
{
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        server_log = Concat(server_log, "Create socket failed.\n");
        exit(1);
    }
    server_log = Concat(server_log, "Socket created.\n");
    printf("Socket created.\n");
}

// Bind port and address to socket
void Bind()
{
    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT ); // open port

    // reuse "Address in use" (error code: 10084). But "Permision Denied" error (10013) can araise
//    BOOL optval = TRUE;
//    int r = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(BOOL));
//    printf("Reuse address : %d\n" , r);

    // bind port and address
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        server_log = Concat(server_log, "Bind failed.\n");
        exit(1);
    }
    puts("Bind done.");
    server_log = Concat(server_log, "Bind done.\n");
}

// Reference: http://en.wikipedia.org/wiki/C_date_and_time_functions
void GetDateTime()
{
    time_t current_time;

    /* Obtain current time as seconds elapsed since the Epoch. */
    current_time = time(NULL);
    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to compute the current time.");
        return;
    }
    /* Convert to local time format. */
    c_time_string = ctime(&current_time);
    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.");
        return;
    }
}

// Handle multiple connections to server
void HandleMultiConnect()
{
    addrlen = sizeof(struct sockaddr_in);
    while (TRUE)
    {
        FD_ZERO(&readfds); // clear the socket set
        FD_SET(s, &readfds); // add master socket to set
        max_sd = s;
        // add child sockets to set
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i]; // socket descripter
            if (sd > 0)
            {
                FD_SET(sd, &readfds); // add valid socket descriptor to list
            }
            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }
        // wait for an activity
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) // (errno != EINTR) -> just in Linux
        {
            printf("Select error. \n");
        }
        // an incomming connection
        if (FD_ISSET(s, &readfds))
        {
            if ((new_socket = accept(s, (struct sockaddr *)&client, &addrlen))<0)
            {
                perror("accept");
                continue;
                //exit(EXIT_FAILURE);
            }
            GetDateTime();
            puts("--------------------");
            printf("Connection accepted from ");
            char* client_ip = inet_ntoa(client.sin_addr);
            //int client_port =  ntohs(client.sin_port);
            printf("%s.\n", client_ip);
            server_log = Concat(server_log, "--------------------\n");
            server_log = Concat(server_log, "Connection accepted from ");
            server_log = Concat(server_log, client_ip);
            server_log = Concat(server_log, " at ");
            server_log = Concat(server_log, c_time_string);
            // save client IP to log file
            result_log = client_ip;
            // receive data from client
            data_received = (char*)malloc(MAX_SIZE); // allocate memory
            printf("Receive file from client...");
            if((recv_size = recv(new_socket , data_received , MAX_SIZE , 0)) == SOCKET_ERROR)
            {
                printf("Failed.\n"); // next connection
                server_log = Concat(server_log, "Receive failed.\n");
                continue;
            }
            data_received[recv_size] = '\0';
            SaveFile(data_received, recv_size); // save received data to file
            printf("Done.\n");
            // compile, run and compare result
            if (ExecuteSource() == 0)
            {
                message = "Result: OK\n";
                result_log = Concat(result_log, ",Compile run and result OK,OK,");
                server_log = Concat(server_log, "Result: OK\n");
            }
            else
            {
                message = "I received your file. However, I could not compile/run it or the result is NG!\n";
                result_log = Concat(result_log, ",NG,");
            }
            // write result to log file
            result_log = Concat(result_log, c_time_string);
            result_log = Concat(result_log, "\n");
            WriteServerLog(server_log);
            server_log = "";
            WriteResultLog(result_log);
            free(result_log);
            // reply to the client
            send(new_socket , message , strlen(message) + 1 , 0);

            // add new socket to array
            for (i = 0; i < max_clients; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Add to list of sockets %d\n.", i);
                    break;
                }
            }
        }
        // else for some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds))
            {
                if ((val_read = read(sd, buffer, 1024)) == 0)
                {
                    // get detail of sbd disconnected
                    getpeername(sd, (struct sockaddr*)&client, &addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(client.sin_addr) ,
                           ntohs(client.sin_port));

                    // close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }
                else
                {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[val_read] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
}

// Wait for connections
void ListenConnection()
{
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }
    // listen to incoming connections
    listen(s , 3);
    // accept incoming connection
    puts("Waiting for incoming connections...");
    HandleMultiConnect();
    // end session
    closesocket(s);
    WSACleanup();
}

// Start communicate with clients
void StartSession()
{
    InitializeWinsock();
    CreateSocket();
    Bind();
    ListenConnection();
}
