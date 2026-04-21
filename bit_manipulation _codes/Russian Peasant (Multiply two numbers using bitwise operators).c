
#include <stdio.h>

int main()
{
    int n;
    printf("enter the numbers\n");
    int a,b,res=0;
    scanf("%d %d",&a,&b);
    while(b>0){
    if(b&1){
    res+=a;
    }
    a=a<<1;
    b=b>>1;
    }
    
   printf("result is %d",res); 
return 0;
}
