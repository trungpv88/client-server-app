#include <stdio.h>
#include <stdlib.h>

int CompareFiles(char*, char*);
int CompareResult();

int CompareResult(char *sample, char *result)
{
    return CompareFiles(sample, result);
}

int CompareFiles(char* file1, char* file2)
{
    FILE *fp1, *fp2;
    int ch1, ch2;
    fp1 = fopen(file1, "rb");
    fp2 = fopen(file2, "rb");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Can not open files.\n");
        return 1;
    }
    ch1 = getc(fp1);
    ch2 = getc(fp2);
    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }
    if (ch1 != ch2)
    {
        return 1;
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int main(int argc, char *argv[])
{
    if (CompareResult(argv[1], argv[2]) != 0) exit(1);
    return 0;
}
