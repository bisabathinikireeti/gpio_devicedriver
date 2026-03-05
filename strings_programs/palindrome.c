
#include <stdio.h>
#include<string.h>

void strrev(char *str)
{
    int end_index=strlen(str)-1;
    int start_index=0;
    while(start_index<end_index)
    {
        char temp=str[start_index];
        str[start_index]=str[end_index];
        str[end_index]=temp;
        start_index++;
        end_index--;
    }
}

int main()
{
    char str[50]="malayalam";
    char temp[50];
    strcpy(temp,str);
    strrev(temp);
    printf("%s\n",temp);
    int len=strlen(str);
    int flag=0;
    for(int i=0;i<len;i++)
    {
        if(str[i]!=temp[i])
        {
            flag=1;
            break;
        }
    }
    if(!flag)
        printf("%s is palindrome\n",str);
    else
        printf("%s is not palindrome\n",str);
    return 0;
}
