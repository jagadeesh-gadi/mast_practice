
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n, j, count;
    int max = 0, min = 9999;
    char max_char, min_char;

    printf("Enter size of string: ");
    scanf("%d", &n);

    char *arr = (char *)malloc((n + 1) * sizeof(char));

    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter string: ");
    scanf("%s", arr);

    // Character frequency
    for (i = 0; arr[i] != '\0'; i++)
    {
        count = 0;

        // Check whether character was already counted
        for (j = 0; j < i; j++)
        {
            if (arr[i] == arr[j])
            {
                break;
            }
        }

        if (j < i)
        {
            continue;
        }

        // Count character
        for (j = 0; arr[j] != '\0'; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }

        printf("%c = %d\n", arr[i], count);

        // Most repeated character
        if (count > max)
        {
            max = count;
            max_char = arr[i];
        }

        // Least repeated character
        if (count < min)
        {
            min = count;
            min_char = arr[i];
        }
    }

    printf("\nMost repeated character: %c\n", max_char);
    printf("Least repeated character: %c\n", min_char);

    // Toggle characters
    for (i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            arr[i] = arr[i] - 32;
        }
        else if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            arr[i] = arr[i] + 32;
        }
    }

    printf("\nAfter toggling:\n");
    printf("%s\n", arr);

    free(arr);

    return 0;
}
