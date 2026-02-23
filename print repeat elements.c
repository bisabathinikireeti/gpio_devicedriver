#include <stdio.h>

int main() {

    // Array containing elements
    int arr[] = {1, 1, 1, 2, 2};

    // Calculate number of elements in array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Print heading
    printf("Repeated elements are:\n");

    // Outer loop: pick each element one by one
    for(int i = 0; i < n; i++) {

        // Flag to check if this element was already printed earlier
        int alreadyPrinted = 0;

        // Check if current element appeared before index i
        for(int k = 0; k < i; k++) {
            if(arr[i] == arr[k]) {
                alreadyPrinted = 1; // mark as already printed
                break;
            }
        }

        // If already printed, skip this element
        if(alreadyPrinted)
            continue;

        // Compare current element with remaining elements
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                // If duplicate found, print element once
                printf("%d ", arr[i]);
                break;  // avoid printing same number multiple times
            }
        }
    }

    return 0;
}
