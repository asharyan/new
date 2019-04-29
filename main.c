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
 * can been done so using the header file 'task_select.h', in which the user can 
 * enter a number between 1 and 5. The function of each task is described below. 
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
    

    MyInput = fopen("MyInput.txt", "r"); // this is where the plain text i have written to encrypt is located
    MyOutput = fopen("MyOutput.txt", "w"); // this is where the encrypted text will go

    char message[250];// this is the vaiable i will assign my message to - limit of 250 chars
    char encrypted[250];// this is the variable i will give the encrypted message - limit of 250 chars
    int k = 21; // this is the key. Its value will determine the shift of the cipher letters.
    
    /* scanning input.txt file and assigning to variable 'message'*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i-1] = '\0';
    printf("\n");
    
    
    /*encrypt known message using the value of the integer 'k'*/
    for (int i=0; i<100; i++) {
        // going through the message character by character and encrypting - limit of 100 characters
        encrypted[i] = RotoEncrypt(message[i], k);
    }
    fprintf(MyOutput, "%s\n", encrypted); // printing enrypted text to 'MyOutput.txt' file
    
    
}

/* 
 * this function should ensure the input is uppercase only
 * then will encrypt the message using the key provided above
 * 
 * this is done by taking each character and adding the key value to their ASCII value
 */
char RotoEncrypt(char input, int key) {
   
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32;
    } 
    
    /*encrypt*/
    if ((input > 64) && (input < 91)) {
       input += key;// adding the key value to encrypt
       input -= 65;// "zeroing" the characters so that A=0, B=1, C=3... etc 
       input = (input%26);   
       input += 65;
    } 
 
return input;
}

void RotoDecryption(void) {
    
    FILE * MyOutput;
    FILE * MyOutputDecrypted;
    
    MyOutput = fopen("MyOutput.txt", "r"); // this is the encrypted text from the previous function
    MyOutputDecrypted = fopen("MyOutputDecrypted.txt", "w"); // this is where the decrypted text will go
    
    char encrypted[250];// this is the variable that the encrypted message will be assigned to - limit of 250 chars
    char decrypted[250];// this is the variable that the decrypted message will be assigned to - limit of 250 chars
    int k = 21; // this should match the value of int k in the function RotoEncryption to ensure correct decryption.
    
    /* scanning input.txt file and assigning to the variable 'encrypted'*/
    int i = 0;
    while (feof(MyOutput) == 0) {
         fscanf(MyOutput, "%c", &encrypted[i]); 
         i++;
    }
    encrypted[i] = '\0';
    printf("\n");

    
    /* decrypt encrypted message */
    for (int c=0; c<100; c++) {
        // going through the message character by character and encrypting - limit of 100 characters
        decrypted[c] = RotoDecrypt(encrypted[c], k);
    }
    fprintf(MyOutputDecrypted, "%s\n", decrypted); // printing decrypted text to 'MyOutputDecrypted.txt' file
    
}

void UnseenRotoDecryption(void) {
    
    FILE * Input;
    FILE * Output;
    
    Input = fopen("Input.txt", "r"); // this is the unseen encrypted cipher.
    Output = fopen("Output.txt", "w"); // this is where the decrypted text of the unseen cipher will go.
    
    char UnseenMessage[700], decrypted[700];// this is the vaiable the unseen message in 'Input.txt' will be assigned to - limit of 300 chars
    
    /* scanning 'Input.txt' file and assigning message to the variable 'UnseenMessage'*/
    int j = 0;
    while (feof(Input) == 0) { 
         fscanf(Input, "%c", &UnseenMessage[j]);
         j++;
    }
    UnseenMessage[j-1] = '\0';
    printf("\n");
    
    /* decrypt unseen message using brute force */
    for (int i=0; i<26; i++) {
        //going through 25 possible rotations (hence i<26) to find the key which gives the correct english message
        for (j=0; UnseenMessage[j]; j++) 
            // going through each char and implementing the RotoDecrypt function
            decrypted[j] = RotoDecrypt(UnseenMessage[j], i);
        decrypted[j] = 0;
            // printing decrypted message possibilities to 'Output.txt' file
            fprintf(Output, "%s\t\tkey %d \n", decrypted, i);
            
    }
    
}

/*
 * this function "undoes" the encrypt function
 * this is done so by subrtracting the original key value from the encrypted message characters
 */
char RotoDecrypt(char input, int key) { /// count frequency of most common letter 
   
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32;
    } 
    
    /*decrypt*/
    if ((input > 64) && (input < 91)) {
       input -= 65;// "zeroing" the characters so that A=0, B=1, C=3... etc 
       input -= key;// subtracting the key to return the character to its inital value
       
       input = (input%26) + 65; 
       /* The next part is to implement wrap-around for letters towards the end of the Alaphabet.  */
       if ((input < 65) && (input > 0)) {
            input += 26; 
        }
    }
   
return input;
}

void SubsEncryption(void) {
    
    /* the variable "cipher" acts as a key for the message
     * such that A=Q, B=W, C=E, ... etc
     */
    
    char cipher[]="QWERTYUIOPASDFGHJKLZXCVBNM";
    
    /*reading message from test file*/
    FILE * MyInput;
    FILE * MyOutput;
    
    MyInput = fopen("MyInput.txt", "r"); // this is the plain text i have written to encrypt.
    MyOutput = fopen("MyOutput.txt", "w"); // this is where the encrypted message will appear after the function has run

    char message[250];// this is the variable the message will be assigned to - limit of 250 chars
    
    /* scanning input.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyInput) == 0) {
         fscanf(MyInput, "%c", &message[i]); 
         i++;
    }
    message[i-1] = '\0';
    
    // this is the variable the encrypted message will be assigned to - the size of which is precisely the size of the var 'message'    
    char EncryptedMessage[sizeof(message)/sizeof(char)]; 
    /*implementing function*/
    for (int i = 0; i<(sizeof(message)/sizeof(char)); i++) {
    EncryptedMessage[i] = SubsEncrypt(message[i], cipher);
    }


    fprintf (MyOutput, "%s", EncryptedMessage);    
    
}

/*
 * the following function encrypts the message using a substitution cipher
 * 
 */
char SubsEncrypt(char input, char *code){
    
    /*converting lowercase to uppercase*/
    if ((input > 96) && (input < 123)) {
       input -= 32; 
    } 
    /*ensuring the inout ignores spaces etc*/
    if ((input > 64) && (input < 91)) {
       
       input -= 65;// "zeroing" the message, A=0, B=1, ... etc
       input = (input%26) + 65; 
       if ((input < 65) && (input > 0)) {
            input += 26; // implementing wrap-around for letters towards the end of the alphabet 
        }
    /*encrypting message*/
    int number_in_alpha = input - 65;// "zeroing" the message A=0, B=1, ... etc
    input = code[number_in_alpha]; // assigning each char to its matching letter in "cipher" i.e. A=Q, B=W, C=E, ... etc
    
    }  

    return input;
}

void SubsDecryption(void) {
    
     /* the variable "cipher" acts as a key for the message
     * such that A=Q, B=W, C=E, ... etc
     */
    char cipher[]="QWERTYUIOPASDFGHJKLZXCVBNM";
    
    FILE * MyOutput;
    FILE * MyOutputDecrypted;
    
    MyOutput = fopen("MyOutput.txt", "r");// this is where the encrypted message is located 
    MyOutputDecrypted = fopen("MyOutputDecrypted.txt", "w");// this is where the decrypted message will be writted to
    
    char EncryptedMessage[250];// this is the variable the encrypted message will be assigned to - limit of 250 chars
    
    /* scanning myoutput.txt file and assigning to variable*/
    int i = 0;
    while (feof(MyOutput) == 0) {
         fscanf(MyOutput, "%c", &EncryptedMessage[i]); 
         i++;
    }
    EncryptedMessage[i-1] = '\0';
    
    char DecryptedMessage[sizeof(EncryptedMessage)/sizeof(char)]; // limit of precisely the size of the variable 'EncryptedMessage'
    
    /*implementing SubsDecrypt function*/
    for (int i = 0; i<(sizeof(EncryptedMessage)/sizeof(char)); i++) {
    DecryptedMessage[i] = SubsDecrypt(EncryptedMessage[i], cipher);
    }


    fprintf (MyOutputDecrypted,"%s", DecryptedMessage); // printing the decrypted message to the file 'MyOutputDecrypted'
    
}

/* this function will reverse the encryption function by re-assigning the chars in
 * the message to their original alphabet value
 */
char SubsDecrypt(char input, char *code) {
    /*ensuring the input ignores spaces etc*/
    if ((input > 64) && (input < 91)) {
       
        /*decrypting message*/
        for (int i = 0; i < 26; i++) {
            // here, the function looks at the chars in the message individually and reassigns them to their alphabetic value
            if (input == code[i]) { // i.e. if the char is 'Q', that aligns to '0' in the cipher
                return i+65;// 65 is then added to the vaiable 'i' to return the ASCII value for 'A'
            }
        } 
    }

    return input;
}