#include <stdio.h>
#include <strings.h>

void Roto(void);
char RotoEncrypt(char input, int key);
char RotoDecrypt(char input, int key);
void Subs(void);
char SubsEncrypt(char input, char *code);



int main() {
    
    Roto();
    
    Subs();
    
}

void Roto(void) {
    char encrypted[100];
    char decrypted[100];
    
    FILE * MyInput;
    FILE * Input;
    FILE * Output;

    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    Input = fopen("Input.txt", "r"); // this is the unseen encrypted cipher.
    Output = fopen("Output.txt", "w"); // this is where the decrypted text will go.

    char message[100];
    char UnseenMessage[250];
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]);
         printf("%c", message[i]); 
         i++;
    }
    message[i] = '\0';
    printf("\n");

    int j = 0;
    while (feof(Input) == 0) { 
         fscanf(Input, "%c", &UnseenMessage[j]);
         printf("%c", UnseenMessage[j]);
         j++;
    }
    UnseenMessage[j] = '\0';
    printf("\n");
    
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
    
  
    
    /* decrypt unseen message using brute force */
    for (int i=0; i<26; i++) {
        for (j=0; j< (sizeof(UnseenMessage)/sizeof(char)); j++)
      
            UnseenMessage[j] = RotoDecrypt(UnseenMessage[j], i);
            fprintf(Output, "Decrypted Unseen Rotation String: %s\t\tkey %d \n", UnseenMessage, i);
    }
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
       if ((input < 65) && (input > 0)) {
            input += 26; 
        }
    
    }    
return input;
}

void Subs(void) {
     char cipher[]="QWERTYUIOPASDFGHJKLZXCVBNM";
    
    /*reading message from test file*/
    FILE * MyInput;
    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.

    char message[100];
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i] = '\0';
    
    
    
    char EncryptedMessage[sizeof(message)/sizeof(char)];
    /*implementing function*/
    for (int i = 0; i<26; i++) {
    EncryptedMessage[i] = SubsEncrypt(message[i], cipher);
    }


    printf ("Original message: %s \nEncrypted message: %s\n", message, EncryptedMessage);
    
}

char SubsEncrypt(char input, char *code){
    
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32; 
    } 
    /*ensuring the inout ignores spaces etc*/
    if ((input > 64) && (input < 91)) {
       
       input -= 65;
       input = (input%26) + 65; 
       if ((input < 65) && (input > 0)) {
            input += 26; 
        }
    /*encrypting message*/
    int number_in_alpha = input - 65;
    input = code[number_in_alpha];
    
    }  

    return input;
}