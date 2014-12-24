#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

void InitializeWinsock();
void CreateSocket();
void Bind();
void ListenConnection();
void StartSession();
char* SOURCE_DIRECTORY, *INPUT_DIR, *OUTPUT_DIR, *CHECK_POINT_DIR, *result_log, *server_log;
int PORT, TIME_EXECUTION_LIMIT;
void GetDateTime();

#endif // SERVER_H_INCLUDED
