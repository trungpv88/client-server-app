#include "../Include/compiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *space = " ", *command;
const int OFFSET_COMMAND_LENGTH = 15; // for compiler and options in command
int command_length;

void AllocateMemory(int source_length, int execution_length)
{
    command_length = source_length + execution_length + OFFSET_COMMAND_LENGTH;
    command = (char*)malloc(command_length);
}

// g++ Example.c -o "Example.exe"
char* CompileCpp(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "g++ %s -o %s", source_path, execution_path);
    return command;
}

// gcc Example.c -o "Example.exe"
char* CompileC(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "gcc %s -o %s", source_path, execution_path);
    return command;
}

// javac "Example.java"
char* CompileJava(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "javac %s", source_path);
    return command;
}

// php "Example.php"
char* CompilePHP(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "php %s ", source_path);
    return command;
}

// csc /out:"Example.exe" "Example.cs"
char* CompileVC(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "csc /out:%s %s", execution_path, source_path);
    return command;
}

// vbc /out:"Example.exe" "Example.vb"
char* CompileVB(char* source_path, char* execution_path)
{
    snprintf(command, command_length, "vbc /out:%s %s", execution_path, source_path);
    return command;
}

