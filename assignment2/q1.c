#include <stdio.h>
#include <string.h>
#define Max 100
void addBooks(int isbns[], char titles[][50], int quantities[], float prices[], int *count){
    if(*count >= Max){
        printf("Inventory full. Cannot add more books.\n");
        return;
    }
        int isbn, i, dublicate = 0;
        printf("Enter ISBN: ");
        scanf("%d", &isbn);
        for(i=0; i<*count; i++){
            if(isbns[i] == isbn){
                dublicate = 1;
                break;
            }
        }
        if(dublicate ==1){
            printf("Book with ISBN %d already exists in inventory.\n", isbn);   
        }else{
            isbns[*count] = isbn;
            printf("Enter Title: ");
            scanf(" %[^\n]", titles[*count]);
            printf("Enter Quantity: ");
            scanf("%d", &quantities[*count]);
            printf("Enter Price: ");
            scanf("%f", &prices[*count]);
            printf("Book added successfully!\n");
            (*count)++;
        }
    
}

void processSales(int isbns[],  int quantities[], int count){
    int isbn, quantity, found = 0;
    printf("Enter ISBN of the book to sell: ");
    scanf("%d", &isbn);
    for(int i=0; i<count; i++){
        if (isbns[i] == isbn){
            found = 1;
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);
            if(quantities[i] >= quantity){
                quantities[i] -= quantity;
                printf("Sale processed successfully! %d Book(s) left\n", quantities[i]);
            }else{
                printf("Insufficient stock. Available quantity: %d\n", quantities[i]);  
            } 
            break;
        }
    }
    if(!found){
        printf("Book with ISBN %d not found in inventory.\n", isbn);
    }
}

void lowStockReport(int isbns[], char titles[][50], int quantities[], float prices[], int count){
    int LowStockFound = 0;
    for(int i=0; i<count; i++){
        if(quantities[i] < 5){
            LowStockFound = 1;
            break;
        }
    }if(!LowStockFound){
        printf("No books with low stock.\n");
        return;
    }else{
    printf("Book(s) with Low Stock (less than 5):\n");
    for(int i=0; i<count; i++){
        if(quantities[i] < 5){
            printf("ISBN: %d, Title: %s, Quantity: %d, Price: %.2f\n", isbns[i], titles[i], quantities[i], prices[i]);
        }
    }
    }
}

int main(){
    int isbns[100];
    char titles[100][50];
    int quantities[100];
    float prices[100];

    int count = 0;
    int choice;
    while(1){
        printf("===============Welcome to Book Inventory Management System===============\n");
        printf("1. Add Books\n2. Process sales\n3. low stock report\n4. Exit\n");
        printf("-------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                addBooks(isbns, titles, quantities, prices, &count);
                break;
            case 2:
                processSales(isbns, quantities, count);
                break;
            case 3:
                lowStockReport(isbns, titles, quantities, prices, count);
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
    }
}
}