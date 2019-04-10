#include <stdio.h>
#include <strings.h>


char RotoEncrypt(char input, int key);
char RotoDecrypt(char input, int key);
char BruteForceDecrypt(char input, int key);


int main() {
    
    char encrypted[100];
    char decrypted[100];
    
    FILE * MyInput;
    FILE * Input;
    FILE * Output;

    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    Input = fopen("Input.txt", "r"); // this is the unseen encrypted cipher.
    Output = fopen("Output.txt", "w"); // this is where the decrypted text will go.

    char message[100];
    char UnseenCipher[100];
    
    /* scanning input.txt file and assigning to variable*/
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%s", message);
         printf("%s", message); // how to make it print spaces as well? 
    }

    while (feof(Input) == 0) { 
         fscanf(Input, "%s", UnseenCipher);
         printf("%s", UnseenCipher);
         fprintf(Output, "%s", UnseenCipher);
    }
    
    
    /*encrypt known message*/
    for (int i=0; i<100; i++) {
        encrypted[i] = RotoEncrypt(message[i], 3);
    }
    printf("Encrypted Rotation String: %s\n", encrypted); //ONLY USING LAST WORD IN MESSAGE???
    
    
    
    /* decrypt encrypted message */
    for (int c=0; c<100; c++) {
        decrypted[c] = RotoDecrypt(encrypted[c], 3);
    }
    printf("Decrypted Rotation String: %s\n", decrypted);
    
}

/* this function should ensure the input is uppercase only*/
char RotoEncrypt(char input, int key) {
   
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

char RotoDecrypt(char input, int key) {
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

char BruteForceDecrypt(char input, int key) {
    
    /*going through every key and placing them into an output.txt file*/
   if ((input > 64) && (input < 91)) {
       for (int i = 0; i < 26; i++) {
           input += key;
       }
   }
   return input;
}