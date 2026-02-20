// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int arr[]={1,2,2,1,3,4};
    int n=6;
    for(int i=0;i<n;i++)
    {
        int count=0;
        int already=0;
        for(int k=0;k<i;k++)
        {
            if(arr[i]==arr[k]){
                already=1;
                break;
            }
        }
        if(already)
         continue;
         for(int j=0;j<n;j++){
             if(arr[i]==arr[j])
             count++;
         }
        printf("%d i presented in %d/n",arr[i],count);
    }
    return 0;
}
