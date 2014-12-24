#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#define COMPILER_CPP "-cpp"
#define COMPILER_C "-c"
#define COMPILER_JAVA "-j"
#define COMPILER_PHP "-p"
#define COMPILER_VC "-vc"
#define COMPILER_VB "-vb"

char* CompileCpp(char*, char*);
char* CompileC(char*, char*);
char* CompileJava(char*, char*);
char* CompilePHP(char*, char*);
char* CompileVC(char*, char*);
char* CompileVB(char*, char*);
void AllocateMemory(int, int);

#endif // COMPILER_H_INCLUDED
