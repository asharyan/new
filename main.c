#include <stdio.h>
#include <string.h>

char RotoEncryptLetter(char input, int key);

int main() {
    char message[100];
    char encrypted[100];
    
    /* scan in input.txt and assign to message*/
    for (int i=0; i<100; i++) {
        scanf("%s", message); 
        encrypted[i] = RotoEncryptLetter(message[i], 3);
    }


    printf("Encrypted String: %s\n", encrypted);
    
}

/* this function should ensure the input is uppercase only*/
char RotoEncryptLetter(char input, int key) {
   
   /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input = input - 32;
    } 
    
    /*encrypt*/
    if ((input > 64) && (input < 91)) {
       input = input + key;
       input -= 65;
       input = (input%26) + 65;       
    } 
 
return input;
}
