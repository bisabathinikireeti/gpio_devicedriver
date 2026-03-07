#include<stdio.h>
int main()
{
    char str[50],sub[50];
    int flag=0,i,j;
    fgets(str,sizeof(str),stdin);
    fgets(sub,sizeof(sub),stdin);
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

             flag=1;
             break;

            }
        }
        if(flag)
            printf("substring found at %d",i);
        else
            printf("not found\n");

    return 0;
    }


