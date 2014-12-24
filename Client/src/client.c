/*
    Client side:
    + Create a socket
    + Connect to server
    + Send data
    + Receive data
    Base on reference: http://www.binarytides.com/winsock-socket-programming-tutorial/
*/
#include<stdio.h>
#include "../include/client.h"
#include<winsock2.h>
#include<libgen.h> // to get basename from full path

#define MESSAGE_SIZE 256
const int NAME_SIZE = 100;
const char *SPACE = " ";
char *RemoveExtension(char* mystr), server_reply[MESSAGE_SIZE], *file_data, *file_name, *arguments,
*SERVER_IP;
int recv_size, PORT;
long file_len;
FILE *file;

WSADATA wsa;
SOCKET s;
struct sockaddr_in server;

// Concate two strings to one
char* Concat(char* s1, char* s2)
{
    char* s = (char*)malloc(strlen(s1) + strlen(s2)+ 1); // +1 for zero-end
    strcpy(s, s1);
    strcat(s, s2);
    return s;
}

// Initialize Winsock
void InitializeWinsock()
{
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Initialize Winsock failed. Error Code : %d",WSAGetLastError());
        exit(1);
    }
    printf("Initialized Winsock.\n");
}

// Create a socket
void CreateSocket()
{
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(1);
    }
    printf("Socket created.\n");
}

// Connect to server
void ConnectToServer()
{
    // configure server
    server.sin_addr.s_addr = inet_addr(SERVER_IP); // server ip address
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT ); // port to connect

    // connect to server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Connect error.");
        exit(1);
    }
    puts("Connected to server.");
}

// Example: "xxx" -> xxx
char* RemoveQuotes(char* path)
{
    char* sub_str = (char*)malloc(strlen(path) - 1);
    memcpy(sub_str, &path[1], strlen(path) - 2);
    sub_str[strlen(path) - 2] = '\0';
    return sub_str;
}

// Get arguments from command line. Ex: -c C:\Example.c
void GetArguments(char *argv[])
{
    arguments = argv[3]; // compiler
    arguments = Concat(arguments, (char*)SPACE); // -c
    file_name = (char*)malloc(strlen(argv[4]) + 1);
    strcpy(file_name, argv[4]); // file path
    file_name[strlen(argv[4])] = '\0';
    //file_name = (argv[4]); // source file
    // if use file_name = (argv[4]), it can lead a bug with free() with path contains ' ' !!!
    file = fopen(file_name, "rb");
    if (file != NULL)
    {
        file_name = basename(file_name); // get file name from path. Ex: get Example.c from C:\Example.c
        arguments = Concat(arguments, file_name);
        arguments = Concat(arguments, "\n"); // arguments data to send. Ex: -c Example.c \n
        fseek(file, 0L, SEEK_END);
        file_len = ftell(file); // length of file
        fseek(file, 0L, SEEK_SET);
        file_data = (char*)malloc(file_len + strlen(arguments) + 1); // allocate memory for sending data
        fread(file_data, file_len, 1, file);
        file_data = Concat(arguments, file_data); // arguments saved at first line, then sending data
        file_data[file_len + strlen(arguments)] = '\0'; // end of char array
    }
    else
    {
        printf("Cannot open source file.\n");
        exit(1);
    }
    fclose(file);
}

// Send data to server
void SendData(char *argv[])
{
    GetArguments(argv);
    puts("--------------------------");
    printf("Sending file to server...");
    /*
    Struct of the sending data
    arguments (first line) + content of source file
    Ex:
    -c C:\Example.c
    #include<stdio.h>
    ...
    */
    if (send(s, file_data, file_len + strlen(arguments) + 1, 0) < 0)
    {
        puts("Send data failed.");
        exit(1);
    }
    free(file_data); // free allocated memory
//    free(file_name); // prob with path contaning some spaces ' ' if free these variables ...
//    free(arguments);
    printf("Done.\n");
}

// Receive message form server
void ReceiveMessage()
{
    // receive a reply from the server
    if((recv_size = recv(s , server_reply , MESSAGE_SIZE , 0)) == SOCKET_ERROR)
    {
        puts("Cannot receive reply from server.");
        exit(1);
    }
    printf("Receive reply from server: ");
    // add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);

    // end connection
    closesocket(s);
    WSACleanup();
}

// Set server information
void ConfigClient(char *argv[])
{
    SERVER_IP = argv[1];
    PORT = atoi(argv[2]);
}

// Start connection to server
void StartConnection(char *argv[])
{
    ConfigClient(argv);
    InitializeWinsock();
    CreateSocket();
    ConnectToServer();
    SendData(argv);
    ReceiveMessage();
}
