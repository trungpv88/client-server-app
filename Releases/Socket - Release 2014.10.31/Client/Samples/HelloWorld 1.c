#include <stdio.h>
#include <stdlib.h>

// Reference: http://stackoverflow.com/questions/1538644/c-determine-if-a-number-is-prime
int IsPrime(unsigned int number) {
    if (number <= 1) return 0; // zero and one are not prime
    unsigned int i;
    // only loop from 2 to sqrt(number)
    for (i = 2; i*i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char* argv[])
{
    int number = atoi(argv[1]);
    if (number < 2)
    {
        return -1;
    }
    else
    {
        printf("2\n");
        int i;
        for (i = 3; i <= number; i = i + 2) // reduce items for looping
        {
            if (IsPrime(i))
                printf("%d\n", i);
        }
    }
    //int a = 1, b = 0, c;
    //c = a/b;
    //printf("%d", c);
    //while (1) {puts("xxx");};
    return 0;
}
