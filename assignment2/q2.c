#include<stdio.h>
#include<string.h>

void customerInfo(char name[], char CNIC[]){
    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    printf("Enter your CNIC: ");
    scanf(" %s", CNIC);
}

void updateInventory(int stock[], int index, int quantity) {
    stock[index] -= quantity;
}

void displayInventory(int code[], int stock[], float price[]){
    printf("%-20s %-20s %-20s\n","Product code","Quantity in stock","Price per product");
    for(int i=0; i<4; i++){
        printf("%-20d %-20d %-20.2f\n", code[i], stock[i], price[i]);     
    }
}

void addToCart(int cartCodes[], int cartQuantities[], int *cartSize, int stock[], int code[]){
    int prodcode, quantity, found=0, productIndex ;
    if(*cartSize >= 4){
        printf("Cart is full! Cannot add more items.\n");
        return;
    }

    printf("Enter product code to add to cart (1-4): ");
    scanf("%d", &prodcode);
    for(int i = 0; i < 4; i++){
        if(code[i] == prodcode){
            productIndex = i;
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Invalid product code!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    if(quantity <= 0){
        printf("Invalid quantity!\n");
        return;
    }

    if(quantity > stock[productIndex]){
        printf("Insufficient stock! Available: %d\n", stock[productIndex]);
        return;
    }

    for(int i=0; i<*cartSize; i++){
        if(cartCodes[i] == prodcode){
            cartQuantities[i] += quantity;
            printf("Item added to cart successfully!\n");
            updateInventory(stock, productIndex, quantity);
            return;
        }
    }

    cartCodes[*cartSize] = prodcode;
    cartQuantities[*cartSize] = quantity;
    (*cartSize)++;
    printf("Item added to cart successfully!\n");

    updateInventory(stock, productIndex, quantity);
}

void displayTotalBill(int cartCodes[], int cartQuantities[], int cartSize, float price[], int code[], 
                      int *promoApplied, float *finalTotal, float *discount){
    if(cartSize == 0){
        printf("Cart is empty! Add items first.\n");
        return;
    }
    
    float total = 0.0;
    printf("\n========== TOTAL BILL ==========\n");
    printf("%-20s %-20s %-20s\n","Product code","Quantity","Subtotal");
    printf("-----------------------------------------------------------\n");
    
    for(int i=0; i<cartSize; i++){
        int priceIndex = -1;
        for(int j=0; j<4; j++){
            if(code[j] == cartCodes[i]){
                priceIndex = j;
                break;
            }
        }
        
        float subtotal = cartQuantities[i] * price[priceIndex];
        total += subtotal;
        printf("%-20d %-20d %-20.2f\n", cartCodes[i], cartQuantities[i], subtotal);
    }
    
    printf("-----------------------------------------------------------\n");
    printf("Total before discount: %.2f\n", total);
    
    char promo[20];
    printf("\nDo you have a promo code? (Enter code or type 'no'): ");
    scanf("%s", promo);
    
    if(strcmp(promo, "Eid2025") == 0){
        *discount = total * 0.25;
        *finalTotal = total - *discount;
        *promoApplied = 1;
        printf("Promo code applied! 25%% discount: %.2f\n", *discount);
        printf("Final Total: %.2f\n", *finalTotal);
    } else {
        *discount = 0.0;
        *finalTotal = total;
        *promoApplied = 0;
        printf("No discount applied.\n");
        printf("Final Total: %.2f\n", *finalTotal);
    }
    printf("================================\n\n");
}

void showInvoice(char name[], char CNIC[], int cartCodes[], int cartQuantities[], int cartSize, 
                 float price[], int code[], int promoApplied, float finalTotal, float discount){
    if(cartSize == 0){
        printf("No items in cart!\n");
        return;
    }
    
    printf("\n============ INVOICE ============\n");
    printf("Customer Name: %s\n", name);
    printf("CNIC: %s\n", CNIC);
    printf("=================================\n");
    printf("%-20s %-20s %-20s\n","Product code","Quantity","Subtotal");
    printf("-----------------------------------------------------------\n");
    
    float total = 0.0;
    for(int i=0; i<cartSize; i++){
        int priceIndex = -1;
        for(int j=0; j<4; j++){
            if(code[j] == cartCodes[i]){
                priceIndex = j;
                break;
            }
        }
        
        float subtotal = cartQuantities[i] * price[priceIndex];
        total += subtotal;
        printf("%-20d %-20d %-20.2f\n", cartCodes[i], cartQuantities[i], subtotal);
    }
    
    printf("-----------------------------------------------------------\n");
    printf("Total before discount: %.2f\n", total);
    
    if(promoApplied){
        printf("Discount (25%%): %.2f\n", discount);
        printf("Final Total: %.2f\n", finalTotal);
    } else {
        printf("Final Total: %.2f\n", total);
    }
    printf("=================================\n\n");
}

int main(){
    int code[4]={1, 2, 3, 4};
    int stock[4]={50, 10, 20, 8};
    float price[4]={100.0, 200.0, 300.0, 150.0};
    char name[50], CNIC[15];
    int choice;
    int cartCodes[4];
    int cartQuantities[4];
    int cartSize = 0;
    int promoApplied = 0;
    float finalTotal = 0.0;
    float discount = 0.0;
    
    while(1){
        printf("========== MENU ==========\n");
        printf("1. Customer Information\n2. Display Inventory\n3. Add Item to Cart\n4. Display Total Bill\n5. Show Invoice\n6. Exit");
        printf("\n=========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                customerInfo(name, CNIC);
                break;
            case 2:
                displayInventory(code, stock, price);
                break;
            case 3:
                addToCart(cartCodes , cartQuantities, &cartSize, stock, code);
                break;
            case 4: 
                displayTotalBill(cartCodes, cartQuantities, cartSize, price, code, &promoApplied, &finalTotal, &discount);
                break;
            case 5:
                showInvoice(name, CNIC, cartCodes, cartQuantities, cartSize, price, code, promoApplied, finalTotal, discount);
                break;
            case 6:
                printf("Exiting the program.....\n");
                return 0;
            default:    
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
}
