#include <stdio.h>
#include <strings.h>

char RotoEncrypt(char input, int key);
char RotoDecrypt(char input, int key);
char BruteForceDecrypt(char input, int key);


int main() {
    
    char encrypted[100];
    
    FILE * database;
    char message[100];

    database = fopen("input.txt", "r");

    if (NULL == database){
         perror("opening database");
         return (-1);
    }

    while (EOF != fscanf(database, "%30[^\n]\n", message)){
         printf("input.txt reads: %s\n", message);
    }

    fclose(database);

    for (int i=0; i<100; i++) {
        encrypted[i] = RotoEncrypt(message[i], 3);
    }
    printf("Encrypted Rotation String: %s\n", encrypted);
    
    char decrypted[100];
    
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
