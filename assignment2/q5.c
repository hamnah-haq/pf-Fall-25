#include <stdio.h>
#include <string.h>

void reverseString(char str[]){
    int len = strlen(str);
    for(int i=0; i<len/2; i++){
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void toggleBits(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = message[i] ^ (1 << 1);  
        message[i] = message[i] ^ (1 << 4);  
    }
}

void encodeMessage(char message[]){
    reverseString(message);
    toggleBits(message);    
    printf("Encoded Message: %s\n", message);
}

void decodeMessage(char message[]){
    toggleBits(message);
    reverseString(message);
    printf("Decoded Message: %s\n", message);
}

int main(){
    char message[100];
    int choice;

    while(1){
       printf("\n===== TCS Secure Message System =====\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0'; 
                encodeMessage(message);
                break;
            case 2:
                printf("Enter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decodeMessage(message);
                break;
            case 3:
                printf("Exiting system... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}