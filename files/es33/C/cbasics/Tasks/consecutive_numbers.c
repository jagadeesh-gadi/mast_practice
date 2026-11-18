// remove the consecutive string values in the string
#include <stdio.h>

int main()
{
    char str[100];
    int j, i;
    fgets(str, 100, stdin);
    for (i = 0; str[i] != '\0'; i++)
    {
        if (i == 0 || str[i] != str[i - 1])
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    printf("modify string :: %s", str);
    return 0;
}