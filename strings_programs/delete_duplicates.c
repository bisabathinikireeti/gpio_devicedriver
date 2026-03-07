#include<stdio.h>
#include<string.h>

int main()
{
    char str[50];
    scanf("%s",str);
    for(int i=0;str[i]!='\0';i++)
    {
        for(int j=i+1;str[j]!='\0';j++)
        {
            if(str[j]==str[i])
            {
                for(int k=j;str[k]!='\0';k++)
                    str[k]=str[k+1];
            }
        }
    }
    printf("the final string after deleted duplicates is: %s:\n",str);
    return 0;

}
