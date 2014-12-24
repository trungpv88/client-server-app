#ifndef COMPILE_H_INCLUDED
#define COMPILE_H_INCLUDED

#define RESULT_LOG "result.log"
#define SERVER_LOG "server.log"

void ExtractArguments(char*);
void SaveFile(char*, int);
int GetInputData(char**, int*);
int ExecuteSource();
char* Concat(char*, char*);
char *RemoveExtension(char*);
int TestResult();
void TerminateRunningThread();
void WriteResultLog();
void WriteServerLog();
char* AddQuotes(char*);
char* WriteLogFiless(char*, char*, char*);

#endif // COMPILE_H_INCLUDED
