//normal way
#include<stdio.h>
void main()
{
    printf("enter the number\n");
    int n,index;
    scanf("%d",&n);
    int count=0;
    for(int i=0;i<=31;i++)
    {
        if(n&(1<<i))
        {
           count++;
           if(count==1)
           index=i+1;
        }
    }
    
    if(count==1)
    printf("%d is pos set",index);
    else
    printf("%d ",-1);
   
}

//bit manipultion way
#include<stdio.h>
int  main()
{
    printf("enter the number\n");
    int n,index;
    scanf("%d",&n);
    if(n>0 && (n&(n-1))!=0){
    printf("%d",-1);
    return 0;
    }
    int pos=1;
    while(n>1)
    {
        n=n>>1;
        pos++;
    }
   printf("%d",pos);
   return 0;
}
