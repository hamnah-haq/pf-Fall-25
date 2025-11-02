#include <stdio.h>
#define Max 100

void push(int stack[], int *top, int max){
    if(*top == max-1){
        printf("Stack Overflow! Cannot push more elements.\n");
        return;
    }
        int value;
        printf("Enter value to push: ");
        scanf("%d", &value);

    (*top)++;
    stack[*top] = value;
    printf("%d pushed to stack.\n", value);
    }

void pop(int stack[], int*top){
    if(*top==-1){
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }
        int removed = stack[*top];
        (*top)--;
        printf("%d popped from stack.\n", removed);
}

void peek(int stack[], int top){
    if(top==-1){
        printf("Stack is empty! No elements to peek.\n");
        return;
    }
    printf("Top element is: %d\n", stack[top]);
}

void display(int stack[], int top){
    if(top==-1){
        printf("Stack is empty! No elements to display.\n");
        return;
    }
    printf("Stack elements are:\n");
    for(int i=top; i>=0; i--){
        printf("%d\n", stack[i]);
    }
}

int main(){
    int choice, stack[Max], top = -1;
    while(1){
        printf("1. PUSH\n2. POP\n3. PEEK\n4. DISPLAY\n5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                push(stack, &top, Max);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;  
            case 4:
                display(stack, top);
                break;
            case 5:
            printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
    return 0;
}