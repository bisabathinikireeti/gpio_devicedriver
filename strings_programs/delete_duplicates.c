#include <stdio.h>
#include <string.h>

int main() {
    char str[50];
    
    printf("Enter a string: ");
    // Use fgets instead of scanf to allow spaces in the input
    fgets(str, sizeof(str), stdin);

    // Outer loop picks a character
    for (int i = 0; str[i] != '\0'; i++) {
        
        // Inner loop compares it with all characters after it
        for (int j = i + 1; str[j] != '\0'; j++) {
            
            // If a duplicate is found
            if (str[j] == str[i]) {
                
                // Shift all characters to the left to "delete" the duplicate
                for (int k = j; str[k] != '\0'; k++) {
                    str[k] = str[k + 1];
                }
                
                /* CRITICAL FIX: 
                   Since we shifted the string, a NEW character is now at index j.
                   We must decrement j so the loop checks this new character 
                   before moving forward.
                */
                j--; 
            }
        }
    }

    printf("String after deleting duplicates: %s", str);
    return 0;
}
