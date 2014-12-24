#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for computing execution time
#include "../Include/execute.h"
#include "../Include/compiler.h"
#include "../Include/server.h"
#include <dirent.h> // for getting list file in directory
#include <windows.h> // for threads

const int MAX_LENGTH = 256;
const char *SPACE = " ", *CHECK_POINT_EXE = "CheckPoint\\CheckPoint.exe";
char* file_name_no_ext, *file_name_exe, *file_name_source, *compiler,
*execution_path, *source_path, *compile_command, *data_args, *data_source,
*input_path, *output_path, *sample_path;
int i, ret_run;

FILE *log_file, *log_server;
HANDLE thread;
DWORD dwThread, exit_code;

// Concate two strings to one
char* Concat(char* s1, char* s2)
{
    char* s = (char*)malloc(strlen(s1) + strlen(s2)+ 1); // +1 for zero-end
    strcpy(s, s1);
    strcat(s, s2);
    return s;
}

// Add quotes " for path containing some spaces ' '
char* AddQuotes(char *path)
{
    char *path_with_quotes = Concat("\"", path);
    return Concat(path_with_quotes, "\"");
}

// Write result to log file
void WriteResultLog(char* data)
{
    log_file = fopen(RESULT_LOG, "a+");
    fwrite(data, strlen(data), 1, log_file); // write to log file
    fclose(log_file);
}

// Write server log
void WriteServerLog(char* data)
{
    log_server = fopen(SERVER_LOG, "a+");
    fwrite(data, strlen(data), 1, log_server); // write to log file
    fclose(log_server);
}

// Exatract compiler and file name from arguments. Ex: -c Example.c to -c and Example.c
void ExtractArguments(char* arguments)
{
    char* data_copy = (char*)malloc(strlen(arguments)+ 1);
    strcpy(data_copy, arguments);
    char* first_space = strchr(data_copy, ' '); // point to first space
    file_name_source = first_space + 1; // get file name after first space
    *first_space = '\0'; // get compiler from begining to first space
    compiler = data_copy;
}

// Extract arguments (first line) and source code (next lines) from data received
void ExtractData(char* data)
{
    char* data_copy = (char*)malloc(strlen(data)+ 1);
    strcpy(data_copy, data);
    char* first_line = strchr(data_copy, '\n'); // point to end of first line
    data_source = first_line + 1; // get data from second line
    *first_line = '\0'; // get arguments from first line
    data_args = data_copy;
}

// Return file name without extension. Ex: Example.c -> Example
char *RemoveExtension(char* file_name)
{
    char* name = (char*)malloc(strlen(file_name) + 1);
    strcpy(name, file_name);
    char* last_dot = strrchr(name, '.');
    if (last_dot == NULL)
        return file_name; // if '.' not found
    else
        *last_dot = '\0'; // cut string from begining to last '.' position
    return name;
}

// Save received file
void SaveFile(char* data, int recv_size)
{
    ExtractData(data);
    ExtractArguments(data_args);
    file_name_no_ext = RemoveExtension(file_name_source); // get file name without extension
    char* extension = ".exe"; // extension of execution file
    file_name_exe = Concat(file_name_no_ext, extension); // Ex: Example.exe
    // write source code to file
    FILE* file;
    file = fopen(Concat((char*)SOURCE_DIRECTORY, file_name_source), "wb");
    fwrite(data_source, strlen(data_source), 1, file);
    fclose(file);
    free(data_source); // free allocated memory
    //file_name_source = Concat(file_name_source, (char*)SPACE);
}

// Get numbers from files in input directory to pass as arguments when execute source code
int GetInputData(char** args, int *len)
{
    FILE* file = fopen(input_path, "r");
    if (file != NULL)
    {
        char buffer[MAX_LENGTH];
        while (fgets(buffer, sizeof buffer, file) != NULL)
        {
            //args[c] = (char*)malloc(MAX_LENGTH);
            //strcpy(args[c], buffer);
            *args = (char*)malloc(MAX_LENGTH);
            char* end_of_line = strtok(buffer, "\n"); // remove New Line character
            strcpy(*args, end_of_line);
            args++;
            (*len)++;
        }
    }
    else
    {
        printf("Cannot read input file.\n");
        return 1;
    }
    fclose(file);
    return 0;
}

// Compile source code
int Compile()
{
    execution_path = Concat((char*)SOURCE_DIRECTORY, file_name_exe); // Ex: C:\Source\Example.exe
    // if path contains some spaces ' '. Ex: C:\Source Code\Example.exe
    execution_path = Concat(AddQuotes(execution_path), (char*)SPACE);
    source_path = AddQuotes(Concat((char*)SOURCE_DIRECTORY, file_name_source)); // "Ex: C:\Source Code\Example.c"
    //source_path = Concat(AddQuotes(source_path), (char*)SPACE);
    AllocateMemory(strlen(source_path), strlen(execution_path)); // allocate memory for compiler command variable
    if (strcmp(compiler, COMPILER_CPP) == 0)
    {
        compile_command = CompileCpp(source_path, execution_path);
    }
    else if (strcmp(compiler, COMPILER_C) == 0)
    {
        compile_command = CompileC(source_path, execution_path);
    }
    else if (strcmp(compiler, COMPILER_JAVA) == 0)
    {
        execution_path = Concat((char*)SOURCE_DIRECTORY, file_name_no_ext); // Ex: C:\Source Code\Example
        // compiler command: javac Example.java
        compile_command = CompileJava(source_path, execution_path);
        // execution command: java -classpath [path with space;] Example
        int offset_command_len = 25; // for options in command
        int execution_command_len = strlen(SOURCE_DIRECTORY) + strlen(file_name_no_ext) + offset_command_len;
        execution_path = (char*)malloc(execution_command_len);
        snprintf(execution_path, execution_command_len, "java -classpath \"%s;\" %s ", SOURCE_DIRECTORY, file_name_no_ext);
    }
    else if (strcmp(compiler, COMPILER_PHP) == 0)
    {
        compile_command = CompilePHP(source_path, execution_path);
    }
    else if (strcmp(compiler, COMPILER_VC) == 0)
    {
        compile_command = CompileVC(source_path, execution_path);
    }
    else if (strcmp(compiler, COMPILER_VB) == 0)
    {
        compile_command = CompileVB(source_path, execution_path);
    }
    else
    {
        printf("Cannot find compiler on server.\n");
        result_log = Concat(result_log, ",Compiler not found");
        server_log = Concat(server_log, "Compiler not found\n");
        return 1;
    }
    // Start compiler from command
    if (strcmp(compiler, COMPILER_PHP) != 0) // PHP dont need to compile
    {
        if (system(compile_command) != 0)
        {
            printf("Compile error.\n");
            result_log = Concat(result_log, ",Compile error");
            server_log = Concat(server_log, "Compiler error\n");
            return 1; // error
        }
    }
    free(source_path); // free allocated memory
    free(file_name_source);
    //free(file_name_exe);
    free(file_name_no_ext);
    return 0;
}

// Run each execution file
DWORD WINAPI RunExecutionFile()
{
    char** args;
    char* command;
    int ret = 0;
    int len = 0;
    args = (char**)malloc(MAX_LENGTH * sizeof(char));
    if (GetInputData(args, &len) != 0) return 1;
    if (strcmp(compiler, COMPILER_PHP) != 0) // PHP dont need to compile
    {
        command = execution_path;
    }
    else
    {
        command = compile_command;
    }
    // append each argument to command
    //while (*args) // ---> sometimes error????? because it takes more time?
    for (i = 0; i < len; i++)
    {
        //printf("%d: ",atoi(*args));
        // [Execution File] [Param1] [Param2] ...
        command = Concat(command, *args);
        command = Concat(command, " ");
        args++;
    }
    // Save result
    char* redirect = "> tmp.txt";
    command = Concat(command, redirect);
//    // [Execution File] [Param1] [Param2] > [Output Path] // cannot use this command if file path contains space ' '?
//    command = Concat(command, output_path);
    ret = system(command);
    // for the case when file path contains space ' '
    int move_command_len_offset = 25; // for options in command
    char move_command_len = strlen(output_path) + move_command_len_offset;
    char* move_command = (char*)malloc(move_command_len);
    // move result temps without print message in command screen
    snprintf(move_command, move_command_len, "move tmp.txt %s > nul", output_path);
    system(move_command);
    free(move_command);
    printf("Done.\n");
    // free allocated memory
    // while (*args) // ---> sometimes error????? because it takes more time?
    for (i = 0; i < len; i++)
    {
        free(*args);
        args--;
    }
    free(args);
    free(command);
    ret_run = ret;
    return ret;
}

// Compare result and sample
int TestResult()
{
    int result;
    int command_len_offset = 10; // for options in command
    int command_len = strlen(CHECK_POINT_EXE) + strlen(sample_path) + strlen(output_path) + command_len_offset;
    char *command = (char*)malloc(command_len);
    snprintf(command, command_len, "%s %s %s", CHECK_POINT_EXE, sample_path, output_path);
    result = system(command);
    free(command);
    return result;
}

// Kill running execution file when timeout
void TerminateRunningThread()
{
    char *terminate_thread_command = "TASKKILL /F /IM ";
    terminate_thread_command = Concat(terminate_thread_command, AddQuotes(file_name_exe));
    system(terminate_thread_command);
}

// Write to result and server log file
void WriteLogFiles(char* input_file_name, char* result_msg, char* server_msg)
{
    // allocate memory for log message
    int log_msg_len_offset = 20;
    int log_msg_len = strlen(input_file_name) + log_msg_len_offset;
    char* log_message = (char*)malloc(log_msg_len);
    snprintf(log_message, log_msg_len, "%s at %s", result_msg, input_file_name);
    // write to result log file
    result_log = Concat(result_log, log_message);
    snprintf(log_message, log_msg_len, "%s at %s\n", server_msg, input_file_name);
    // write to server log file
    server_log = Concat(server_log, log_message);
    free(log_message); // free allocated memory
}

// Run execution file
int Run()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(INPUT_DIR)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL )
        {
            char* input_file_name = ent->d_name;
            // ignore current directory and
            if (strcmp(input_file_name, ".") != 0 && strcmp(input_file_name, "..") != 0)
            {
                input_path = Concat((char*)INPUT_DIR, input_file_name); // not need quotes for fopen function
                output_path = AddQuotes(Concat((char*)OUTPUT_DIR, input_file_name));
                sample_path = AddQuotes(Concat((char*)CHECK_POINT_DIR, input_file_name));
                // run execution file using thread
                thread = CreateThread(NULL, 0, RunExecutionFile, NULL, 0, &dwThread);
                DWORD dwWaitResult;
                // wait until time out
                dwWaitResult  = WaitForSingleObject(thread, TIME_EXECUTION_LIMIT);
                GetExitCodeThread(thread, &exit_code);
                // case time out when time execution exceeds TIME_EXECUTION_LIMIT
                if (dwWaitResult == WAIT_TIMEOUT)
                {
                    printf("Timeout at %s \n", input_file_name);
                    WriteLogFiles(input_file_name, ",Timeout", "Timeout");
                    CloseHandle(thread);
                    TerminateRunningThread(); // kill execution file
                    // using TerminateThread can evoke error code 10048 in socket
                    // TerminateThread(thread, exit_code)
                    return 1;
                }
                else if (ret_run !=0 ) // if program runs incorrectly
                {
                    printf("Run error.\n");
                    WriteLogFiles(input_file_name, ",Run error", "Run error");
                    return 1;
                }
                // compare result received with sample
                if (TestResult() != 0)
                {
                    printf("Result NG.\n");
                    WriteLogFiles(input_file_name, ",Result NG", "Result NG");
                    return 1; // just for test
                }
            }
            free(input_file_name);
        }
        closedir(dir);
    }
    else
    {
        printf("Cannot find directory of input files.");
        result_log = Concat(result_log, ",Input files not found");
        server_log = Concat(server_log, "Input files not found\n");
        return 1;
    }
    free(compile_command); // free allocated memory
    free(execution_path);
    free(data_args);
    return 0;
}

// Compile and execute source code
int ExecuteSource()
{
    printf("Compile and run source file...");
    if (Compile() != 0) return 1;
    if (Run() != 0) return 1;
    return 0;
}
