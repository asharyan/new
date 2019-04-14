#include <stdio.h>
#include <strings.h>
#include "task_select.h"

void RotoEncryption(void);
void RotoDecryption(void);
char RotoEncrypt(char input, int key);
char RotoDecrypt(char input, int key);
void SubsEncryption(void);
void SubsDecryption(void);
char SubsEncrypt(char input, char *code);
char SubsDecrypt(char input, char *code);
void UnseenRotoDecryption(void);



int main() {
    
    switch(TASK_NUMBER) {
        case 1: RotoEncryption();
            break;
        case 2: RotoDecryption();
            break;
        case 3: SubsEncryption();
            break;
        case 4: SubsDecryption();
            break;
        case 5: UnseenRotoDecryption();
            break;
        default: printf("No Task Was Selected");
    }
    printf("Task Selected: %d\n", TASK_NUMBER);
    
}

void RotoEncryption(void) {
    
    char encrypted[100];
    
    FILE * MyInput;
    FILE * MyOutput;
    

    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    MyOutput = fopen("MyOutput.txt", "w"); // this is where the encrypted text will go.

    char message[100];
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i] = '\0';
    printf("\n");
    
    
    /*encrypt known message*/
    for (int i=0; i<100; i++) {
        encrypted[i] = RotoEncrypt(message[i], 3);
    }
    fprintf(MyOutput, "Encrypted Rotation String: %s\n", encrypted); // printing enrypted text to MyOutput file
    
    
}

void RotoDecryption(void) {
    
    char encrypted[100];
    char decrypted[100];
    
    FILE * MyOutput;
    FILE * MyOutputDecrypted;
    
    MyOutput = fopen("MyOutput.txt", "r"); // this is the encrypted text from the previous function
    MyOutputDecrypted = fopen("MyOutputDecrypted.txt", "w"); // this is where the decrypted text will go
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyOutput) == 0) {
         fscanf(MyOutput, "%c", &encrypted[i]); 
         i++;
    }
    encrypted[i] = '\0';
    printf("\n");
    
    
    /* decrypt encrypted message */
    for (int c=0; c<100; c++) {
        decrypted[c] = RotoDecrypt(encrypted[c], 3);
    }
    fprintf(MyOutputDecrypted, "Decrypted Rotation String: %s\n", decrypted); // printing decrypted text to MyOutputDecrypted file
    
}

void UnseenRotoDecryption(void) {
    
    FILE * Input;
    FILE * Output;
    
    Input = fopen("Input.txt", "r"); // this is the unseen encrypted cipher.
    Output = fopen("Output.txt", "w"); // this is where the decrypted text of the unseen cipher will go.
    
    char UnseenMessage[250];
    
    int j = 0;
    while (feof(Input) == 0) { 
         fscanf(Input, "%c", &UnseenMessage[j]);
         j++;
    }
    UnseenMessage[j] = '\0';
    printf("\n");
    
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

void SubsEncryption(void) {
    
    char cipher[]="QWERTYUIOPASDFGHJKLZXCVBNM";
    
    /*reading message from test file*/
    FILE * MyInput;
    FILE * MyOutput;
    
    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    MyOutput = fopen("MyOutput.txt", "w"); 

    char message[100];
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i-1] = '\0';
    
    
    
    char EncryptedMessage[sizeof(message)/sizeof(char)];
    /*implementing function*/
    for (int i = 0; i<26; i++) {
    EncryptedMessage[i] = SubsEncrypt(message[i], cipher);
    }


    fprintf (MyOutput, "%s", EncryptedMessage);    
    
}

void SubsDecryption(void) {
    
    char cipher[]="QWERTYUIOPASDFGHJKLZXCVBNM";
    
    FILE * MyOutput;
    FILE * MyOutputDecrypted;
    
    MyOutput = fopen("MyOutput.txt", "r");
    MyOutputDecrypted = fopen("MyOutputDecrypted.txt", "w");
    
    char EncryptedMessage[100];
    
    /* scanning myoutput.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyOutput) == 0) {
         fscanf(MyOutput, "%c", &EncryptedMessage[i]); 
         i++;
    }
    EncryptedMessage[i-1] = '\0';
    
    char DecryptedMessage[sizeof(EncryptedMessage)/sizeof(char)];
    /*implementing function*/
    for (int i = 0; i<100; i++) {
    DecryptedMessage[i] = SubsDecrypt(EncryptedMessage[i], cipher);
    }


    fprintf (MyOutputDecrypted,"%s", DecryptedMessage);
    
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

char SubsDecrypt(char input, char *code) {
    /*ensuring the inout ignores spaces etc*/
    if ((input > 64) && (input < 91)) {
       
        /*decrypting message*/
        for (int i = 0; i < 26; i++) {
            if (input == code[i]) {
                return i+65;
            }
        } 
    }

    return input;
}