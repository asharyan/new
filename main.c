#include <stdio.h>

char RotoEncryptLetter(char input, int key);

int main() {
    char message[] = "abcdefghijklmnopqrstuvwxyz";
    char encrypted[100];

    
    for (int i=0 ; i<26 ; i++) {
      encrypted[i] = RotoEncryptLetter(message[i], 3);
    }

    printf("Encrypted Alphabet: %c %c %c %c\n", encrypted[0], encrypted[1], encrypted[2], encrypted[3]);
    printf("Encrypted String: %s", encrypted);
    
}

/* this function should ensure the input is uppercase only*/
char RotoEncryptLetter(char input, int key) {
   
   if ((input > 64) && (input < 91)){
       input = input + key;
   } else if ((input > 96) && (input < 123)) {
       input = input - 32;
       input = input + key;
   } 
          
return input;
}
