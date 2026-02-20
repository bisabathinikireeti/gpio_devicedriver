#include <stdio.h>

int main() {
    int arr[] = {1, 1, 1, 2, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Repeated elements are:\n");

    for(int i = 0; i < n; i++) {

        int alreadyPrinted = 0;

        for(int k = 0; k < i; k++) {
            if(arr[i] == arr[k]) {
                alreadyPrinted = 1;
                break;
            }
        }

        if(alreadyPrinted)
            continue;

        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }

    return 0;
}
