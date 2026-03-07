#include<stdio.h>
#include<string.h>
int main()
{
    char str[50],sub[50];
    int flag=0,i,j;
    int count=0;
    int n;
    fgets(str,sizeof(str),stdin);
    fgets(sub,sizeof(sub),stdin);
    n=strlen(str);
    if(str[n-1]=='\n')
        str[n-1]='\0';
    n=strlen(sub);
    if(sub[n-1]=='\n')
        sub[n-1]='\0';
    for(i=0;str[i]!='\0';i++)
    {
        for( j=0;sub[j]!='\0';j++)
        {
            if(str[i+j]!=sub[j])
            {
                break;
            }
        }
            if(sub[j]=='\0')
            {

             count++;

            }
        }
        printf("the number of substrings are %d\n",count);

    return 0;
    }


