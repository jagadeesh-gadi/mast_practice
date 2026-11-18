// i need to find the lenght of the string and also i need to insert the a new strng in the middle and also the length of string should be increased
// input main :: "hello mast students !!"
//   substring = moschip
// ouput is :: "hello moschip students !!"

#include <stdio.h>

int my_strlen(char str[])
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }

    return i;
}

int find_word(char str[], char word[])
{
    int i, j;

    for (i = 0; str[i] != '\0'; i++)
    {
        j = 0;

        while (word[j] != '\0' && str[i + j] == word[j])
        {
            j++;
        }

        if (word[j] == '\0')
        {
            return i;
        }
    }

    return -1;
}

void replace_string(char str[], char old[], char new_str[])
{
    int pos;
    int old_len;
    int new_len;
    int str_len;
    int i;

    pos = find_word(str, old);

    if (pos == -1)
    {
        printf("String not found\n");
        return;
    }

    old_len = my_strlen(old);
    new_len = my_strlen(new_str);
    str_len = my_strlen(str);

    if (new_len > old_len)
    {
        for (i = str_len; i >= pos + old_len; i--)
        {
            str[i + new_len - old_len] = str[i];
        }
    }

    for (i = 0; i < new_len; i++)
    {
        str[pos + i] = new_str[i];
    }
}

int main()
{
    char str[100] = "hello mast students !!";
    char old[] = "mast";
    char new_str[] = "moschip";

    printf("Original string: %s\n", str);
    printf("Original length: %d\n", my_strlen(str));

    replace_string(str, old, new_str);

    printf("New string: %s\n", str);
    printf("New length: %d\n", my_strlen(str));

    return 0;
}
