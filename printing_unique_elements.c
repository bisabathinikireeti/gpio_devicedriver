// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int arr[]={1,2,2,1,3,4};
    int n=6;
    printf("the unique elements are\n");
    for(int i=0;i<n;i++)
    {
        int count=0;
           for(int j=0;j<n;j++)
           {
               if(arr[i]==arr[j]) count++;
           }
       if(count==1)
          printf("%d ",arr[i]);
    }
    return 0;
}
