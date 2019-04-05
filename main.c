#include <stdio.h>

char RotoEncryptLetter(char input, int key);

int main() {
    char message[100];
    /* scan in input.txt and assign to message*/
    scanf("%s", message); 
    printf("the input is: %s\n", message);
    
    char encrypted[100];
    
    for (int i=0 ; i<100 ; i++) {
      encrypted[i] = RotoEncryptLetter(message[i], 3);
    }

    printf("Encrypted Input: %c %c %c %c\n", encrypted[0], encrypted[1], encrypted[2], encrypted[3]);
    printf("Encrypted String: %s", encrypted);
    
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
