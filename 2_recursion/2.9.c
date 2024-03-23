#include <stdio.h>
#include <string.h>

void reverse(char *str)
{
    int length = (int)strlen(str);

    if (length == 0 || length == 1)
    {
        return;
    }

    char tmp = str[0];
    str[0] = str[length - 1];
    str[length - 1] = tmp;

    reverse(str++);
}

int main()
{
    char *name = "hello";

    reverse(name);

    printf("%s\n", name);
}