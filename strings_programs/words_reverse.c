#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    int i, j, len, startIndex, endIndex;

    printf("Enter String: ");
    fgets(str, sizeof(str), stdin);

    len = strlen(str);

    // Remove newline added by fgets
    if(str[len-1] == '\n')
    {
        str[len-1] = '\0';
        len--;
    }

    endIndex = len - 1;

    printf("Reversed words:\n");

    for(i = len - 1; i >= 0; i--)
    {
        if(str[i] == ' ' || i == 0)
        {
            startIndex = (i == 0) ? 0 : i + 1;

            for(j = startIndex; j <= endIndex; j++)
            {
                printf("%c", str[j]);
            }

            printf(" ");
            endIndex = i - 1;
        }
    }

    return 0;
}
