#include <stdio.h>
#include <string.h>

int timeStamp = 0; // Global timestamp to track last accessed time

struct Books {
    int id;
    int popularity;
    int lastAccessedTime;
};

// Function to add or update a book
void ADD(struct Books library[], int id, int pop, int cap) {
    // Check if book already exists; if yes, update popularity and access time
    for(int i = 0; i < cap; i++) {
        if(library[i].id == id) {
            library[i].popularity = pop;
            library[i].lastAccessedTime = timeStamp++;
            return;
        }
    }

    // Check for empty slot to add new book
    for(int i = 0; i < cap; i++) {
        if(library[i].id == -1) {
            library[i].id = id;
            library[i].popularity = pop;
            library[i].lastAccessedTime = timeStamp++;
            return;
        }
    }

    // Shelf full: find least recently used (LRU) book to replace
    int lru = 0;
    for(int i = 1; i < cap; i++) {
        if(library[i].lastAccessedTime < library[lru].lastAccessedTime) {
            lru = i;
        }
    }

    // Replace LRU book with new book
    library[lru].id = id;
    library[lru].popularity = pop;
    library[lru].lastAccessedTime = timeStamp++;
}

// Function to access a book's popularity
int ACCESS(struct Books library[], int cap, int id) {
    for(int i = 0; i < cap; i++) {
        if(library[i].id == id) {
            library[i].lastAccessedTime = timeStamp++; // Update last accessed time
            return library[i].popularity;
        }
    }
    return -1; // Book not found
}

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Books library[100]; // Array to store books

    // Initialize library slots as empty
    for(int i = 0; i < capacity; i++) {
        library[i].id = -1;
        library[i].popularity = 0;
        library[i].lastAccessedTime = -1;
    }

    // Process operations
    while(Q--) {
        char op[10];
        scanf("%s", op);

        if(strcmp(op, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            ADD(library, x, y, capacity);
        }
        else if(strcmp(op, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            int res = ACCESS(library, capacity, x);
            printf("%d\n", res);
        }
    }

    return 0;
}
