#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* b = NULL;
    char* a = (char*)malloc(strlen(("ssadasdasdas")+1) * sizeof(char));
    memcpy( a, "ssadasdasdas\n", strlen(("ssadasdasdas")+1));
    b = a;
    a = NULL;
    free(a);
    printf("%s ",b);
}