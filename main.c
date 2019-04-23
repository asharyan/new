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

/*
 * This program has been created to encrypt & decrypt messages both seen & unseen, using two different cipher algorithms - 
 * rotation & substitution. The program has been created such that the user can select between five different options. This 
 * has been done so using a header file under the name 'task_select.h', in which the user will 
 * enter a number between 1 and 5. The function of each task is decribed below. 
 * 
 * TASK SELECTION
 * 
 *    Task Number 1 - Encrypts a message using a rotation cipher. The key for this cipher can be 
 *                    changed in the RotoEncrypt Function by changing the value of the integer k. The message the user 
 *                    wishes to encrypt should be written in the file 'MyInput.txt' foudn in 'master'. This will then change 
 *                    any lowercase letters to uppercase, before encrypting the message with the given key. The encrypted
 *                    can be found in the file 'MyOutput.txt' after the user runs the program.
 * 
 *    Task Number 2 - Decrypts the message that the user encrypted using Task 1. The decrypted message can be
 *                    found in the file 'MyOutputDecryption.txt'. 
 * 
 *    Task Number 3 - Encrypts a message using a substitution cipher. The key for this cipher can be found in 
 *                    the SubsEncrypt function, and is a type char under the name 'cipher'. The message the user wishes
 *                    to encrypt should again be written in the file 'MyInput.txt'. The letters will be subsituted once the
 *                    program runs, and the encrypted message can be found in the file 'MyOutput.txt'.
 * 
 *    Task Number 4 - Decrypts the messages that the user encrypted in Task 3. The Decrypted messsahe can be found in 
 *                    in the file 'MyOutputDecrypted.txt' once the grogram has run. 
 * 
 *    Task Number 5 - Decrypts an unseen messaged which has been encrypted using a rotation cipher. The unseen message 
 *                    should be placed in the file 'Input.txt' before running the program. Once the program has run, 
 *                    the user can find a list of 26 messages with 25 possible rotations in the file 'output.txt'. Through
 *                    human observation, the message which contains english words can be found, along with the key the 
 *                    message used to encrypt it. 
 * 
 * 
 */


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
    
    FILE * MyInput;
    FILE * MyOutput;
    

    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    MyOutput = fopen("MyOutput.txt", "w"); // this is where the encrypted text will go.

    char message[250];
    char encrypted[250];
    int k = 22;
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i-1] = '\0';
    printf("\n");
    
    
    /*encrypt known message*/
    for (int i=0; i<100; i++) {
        encrypted[i] = RotoEncrypt(message[i], k);
    }
    fprintf(MyOutput, "%s\n", encrypted); // printing enrypted text to MyOutput file
    
    
}

/* this function should ensure the input is uppercase only*/
char RotoEncrypt(char input, int key) {
   
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32;
    } 
    
    /*encrypt*/
    if ((input > 64) && (input < 91)) {
       input += key;
       input -= 65;
       input = (input%26);   
       input += 65;
    } 
 
return input;
}

void RotoDecryption(void) {
    
    char encrypted[250];
    char decrypted[250];
    
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
    
    int k = 22;
    
    /* decrypt encrypted message */
    for (int c=0; c<100; c++) {
        decrypted[c] = RotoDecrypt(encrypted[c], k);
    }
    fprintf(MyOutputDecrypted, "%s\n", decrypted); // printing decrypted text to MyOutputDecrypted file
    
}

void UnseenRotoDecryption(void) {
    
    /*
     * THIS FUNCTION ONLY SEEMS TO BE WORKING FOR odd-numbered shifts... FIX
     * 
     */
    
    FILE * Input;
    FILE * Output;
    
    Input = fopen("Input.txt", "r"); // this is the unseen encrypted cipher.
    Output = fopen("Output.txt", "w"); // this is where the decrypted text of the unseen cipher will go.
    
    char UnseenMessage[300];
    
    int j = 0;
    while (feof(Input) == 0) { 
         fscanf(Input, "%c", &UnseenMessage[j]);
         j++;
    }
    UnseenMessage[j-1] = '\0';
    printf("\n");
    
    /* decrypt unseen message using brute force */
    for (int i=0; i<26; i++) {
        for (j=0; j<(sizeof(UnseenMessage)/sizeof(char)); j++) 
            UnseenMessage[j] = RotoDecrypt(UnseenMessage[j], i);
            fprintf(Output, "%s\t\tkey %d \n", UnseenMessage, i);
    }
    
}


char RotoDecrypt(char input, int key) {
    
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32;
    } 
    
    /*decrypt*/
    if ((input > 64) && (input < 91)) {
       input -= 65;
       input -= key;
       input = (input%26) + 65; 
       /* The next part is to implement wrap-around for letters towards the end of the Alaphabet.  */
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

    char message[250];
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i-1] = '\0';
    
    
    
    char EncryptedMessage[sizeof(message)/sizeof(char)];
    /*implementing function*/
    for (int i = 0; i<(sizeof(message)/sizeof(char)); i++) {
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
    
    char EncryptedMessage[250];
    
    /* scanning myoutput.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyOutput) == 0) {
         fscanf(MyOutput, "%c", &EncryptedMessage[i]); 
         i++;
    }
    EncryptedMessage[i-1] = '\0';
    
    char DecryptedMessage[sizeof(EncryptedMessage)/sizeof(char)];
    /*implementing function*/
    for (int i = 0; i<(sizeof(EncryptedMessage)/sizeof(char)); i++) {
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