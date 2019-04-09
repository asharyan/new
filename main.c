#include <stdio.h>
#include <strings.h>

char RotoEncryptLetter(char input, int key);
char RotoDecryptLetter(char input, int key);


int main() {
    char message[100];
    char encrypted[100];
    
    FILE *input;
    input = fopen("input.txt", "r");
    while(feof (input) == 0) {
        char t;
        //read a character
        fscanf(input, "%c", &t);
        // print that character to the console 
        printf("%c\n", t);
    }
    
    /* scan in input.txt and assign to message for rotation cipher*/
    for (int i=0; i<100; i++) {
        scanf("%[^\n]s", message); 
        encrypted[i] = RotoEncryptLetter(message[i], 3);
    }
    printf("Encrypted Rotation String: %s\n", encrypted);
    
    char decrypted[100];
    
    /* decrypt encrypted message */
    for (int c=0; c<100; c++) {
        decrypted[c] = RotoDecryptLetter(encrypted[c], 3);
    }
    printf("Decrypted Rotation String: %s\n", decrypted);
    
}

/* this function should ensure the input is uppercase only*/
char RotoEncryptLetter(char input, int key) {
   
   /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32;
    } 
    
    /*encrypt*/
    if ((input > 64) && (input < 91)) {
       input = input + key;
       input -= 65;
       input = (input%26) + 65;       
    } 
 
return input;
}

char RotoDecryptLetter(char input, int key) {
    /*decrypt*/
    if ((input > 64) && (input < 91)) {
       input = input - key;
       input -= 65;
       input = (input%26) + 65;       
    } 
    /* ensuring letters remain in the uppercase range of ascii characters*/
    if ((input > 62) && (input < 65)) {
       input += 26; // do i need to worry about !@#$% etc??
    }
    
return input;
}

