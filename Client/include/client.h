#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

void InitializeWinsock();
void CreateSocket();
void ConnectToServer();
void GetArguments(char**);
void SendData(char**);
void ReceiveMessage();
char* Concat(char*, char*);
void StartConnection(char**);
void ConfigClient(char**);

#endif // CLIENT_H_INCLUDED
