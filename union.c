// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int a[]={1,2,3},b[]={3,2,5},uarr[20];
    int n=3,k=0;
    //assgain the all elements of a array int uarr
    for(int i=0;i<n;i++){
        uarr[k++]=a[i];
    }
    //assign remaining  elements into uarr if not allready presented
    for(int i=0;i<n;i++){
       int flag=0;
        for(int j=0;j<n;j++){
            if(b[i]==uarr[j])
            {
                flag=1;
                break;
            }
        }
        if(!flag)
            uarr[k++]=b[i];
    }
     for(int i=0;i<k;i++){
        printf("%d ",uarr[i]);
    }

    return 0;
}
