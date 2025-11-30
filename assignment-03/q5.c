#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char** lines = NULL;
size_t line_count = 0;
size_t capacity = 0;

// just declaring functions here
void initialize_editor(size_t initial_capacity);
int ensure_capacity();
int insert_line(size_t index, const char* text);
int delete_line(size_t index);
void print_all_lines();
int shrink_to_fit();
int save_to_file(const char* filename);
int load_from_file(const char* filename);
void free_all();
void demo_efficiency();

void initialize_editor(size_t initial_capacity) {
    capacity = initial_capacity;
    line_count = 0;
    
    // make space for given number of line pointers
    lines = (char**)malloc(capacity * sizeof(char*));
    
    if (lines == NULL) {
        fprintf(stderr, "Error: Failed to allocate initial memory for editor\n");
        exit(EXIT_FAILURE);
    }
    
    // set all pointers to NULL for safety
    for (size_t i = 0; i < capacity; i++) {
        lines[i] = NULL;
    }
    
    printf("Editor initialized with capacity for %zu lines\n", capacity);
}

int ensure_capacity() {
    // if no more space, then grow the pointer array
    if (line_count >= capacity) {
        size_t new_capacity = capacity * 2;
        if (new_capacity == 0) new_capacity = 1;
        
        printf("Expanding capacity from %zu to %zu\n", capacity, new_capacity);

        // try to increase memory for pointer array
        char** new_lines = (char**)realloc(lines, new_capacity * sizeof(char*));
        
        if (new_lines == NULL) {
            fprintf(stderr, "Error: Failed to expand buffer capacity\n");
            return 0;
        }
        
        lines = new_lines;
        capacity = new_capacity;

        // set newly added pointer slots to NULL
        for (size_t i = line_count; i < capacity; i++) {
            lines[i] = NULL;
        }
    }
    return 1;
}

int insert_line(size_t index, const char* text) {
    // invalid index check
    if (index > line_count) {
        fprintf(stderr, "Error: Index %zu out of bounds (current lines: %zu)\n", index, line_count);
        return 0;
    }

    // make sure we have space to add a new line
    if (!ensure_capacity()) {
        return 0;
    }

    // allocate just enough memory for the given text
    size_t text_length = strlen(text);
    char* new_line = (char*)malloc((text_length + 1) * sizeof(char));
    
    if (new_line == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for line text\n");
        return 0;
    }

    strcpy(new_line, text);

    // if insertion is not at the end, shift pointers to move forward
    if (index < line_count) {
        memmove(&lines[index + 1], &lines[index], (line_count - index) * sizeof(char*));
    }
    
    // now place the new line
    lines[index] = new_line;
    line_count++;
    
    printf("Line inserted at position %zu\n", index);
    return 1;
}

int delete_line(size_t index) {
    // basic bounds checking
    if (index >= line_count) {
        fprintf(stderr, "Error: Index %zu out of bounds (current lines: %zu)\n", index, line_count);
        return 0;
    }

    // free the actual text of that line
    free(lines[index]);
    lines[index] = NULL;
    
    // shift remaining pointers backward
    if (index < line_count - 1) {
        memmove(&lines[index], &lines[index + 1], (line_count - index - 1) * sizeof(char*));
    }
    
    line_count--;

    // keep last pointer clean
    if (line_count < capacity) {
        lines[line_count] = NULL;
    }
    
    printf("Line deleted from position %zu\n", index);
    return 1;
}

void print_all_lines() {
    printf("\n=== CURRENT BUFFER (%zu lines) ===\n", line_count);
    
    if (line_count == 0) {
        printf("[Empty buffer]\n");
        return;
    }
    
    // simply print everything
    for (size_t i = 0; i < line_count; i++) {
        printf("%3zu: %s\n", i, lines[i]);
    }
    printf("=== END OF BUFFER ===\n\n");
}

int shrink_to_fit() {
    // nothing to shrink
    if (line_count == capacity) {
        printf("No unused capacity to shrink\n");
        return 1;
    }
    
    // if buffer is empty, free everything
    if (line_count == 0) {
        free(lines);
        lines = NULL;
        capacity = 0;
        printf("Buffer completely freed (no lines)\n");
        return 1;
    }
    
    // reduce capacity to match line_count
    size_t new_capacity = line_count;
    char** new_lines = (char**)realloc(lines, new_capacity * sizeof(char*));
    
    if (new_lines == NULL) {
        fprintf(stderr, "Warning: Shrink operation failed, keeping current capacity\n");
        return 0;
    }
    
    lines = new_lines;
    capacity = new_capacity;
    
    printf("Buffer shrunk to exactly %zu slots\n", capacity);
    return 1;
}

int save_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing: %s\n", 
                filename, strerror(errno));
        return 0;
    }
    
    // write each line as text
    for (size_t i = 0; i < line_count; i++) {
        if (fprintf(file, "%s\n", lines[i]) < 0) {
            fprintf(stderr, "Error: Failed to write to file\n");
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    printf("Successfully saved %zu lines to '%s'\n", line_count, filename);
    return 1;
}

int load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for reading: %s\n", 
                filename, strerror(errno));
        return 0;
    }
    
    // reset editor before loading
    free_all();
    initialize_editor(10);
    
    char buffer[1024];

    // read line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);

        // remove newline from fgets
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        if (!insert_line(line_count, buffer)) {
            fprintf(stderr, "Error: Failed to load line from file\n");
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    printf("Successfully loaded %zu lines from '%s'\n", line_count, filename);
    return 1;
}

void free_all() {
    // free every line first
    if (lines == NULL) return;

    for (size_t i = 0; i < line_count; i++) {
        if (lines[i] != NULL) {
            free(lines[i]);
            lines[i] = NULL;
        }
    }

    // then free pointer array
    free(lines);
    lines = NULL;
    line_count = 0;
    capacity = 0;
    
    printf("All memory freed\n");
}

void demo_efficiency() {
    printf("\n=== MEMORY EFFICIENCY DEMONSTRATION ===\n");

    // just showing approx memory usage difference
    printf("FIXED ARRAY APPROACH:\n");
    printf("  char lines[1000][256] = 256,000 bytes total\n\n");

    printf("DYNAMIC ALLOCATION APPROACH:\n");
    printf("  Pointer array: %zu pointers * 8 bytes\n", capacity);
    
    size_t text_memory = 0;
    for (size_t i = 0; i < line_count; i++) {
        text_memory += strlen(lines[i]) + 1;
    }
    
    printf("  Actual text memory: %zu bytes\n", text_memory);
}

int main() {
    printf("=== MINIMAL LINE-BASED TEXT EDITOR ===\n");

    initialize_editor(2);
    
    int choice;
    size_t index;
    char text[1024];
    char filename[256];
    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Shrink to Fit\n");
        printf("7. Show Memory Efficiency\n");
        printf("8. Stress Test\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter position (0-%zu): ", line_count);
                scanf("%zu", &index);
                getchar();
                printf("Enter text: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = 0;
                insert_line(index, text);
                break;
                
            case 2:
                printf("Enter position to delete (0-%zu): ", line_count - 1);
                scanf("%zu", &index);
                delete_line(index);
                break;
                
            case 3:
                print_all_lines();
                break;
                
            case 4:
                printf("Enter filename: ");
                scanf("%255s", filename);
                save_to_file(filename);
                break;
                
            case 5:
                printf("Enter filename: ");
                scanf("%255s", filename);
                load_from_file(filename);
                break;
                
            case 6:
                shrink_to_fit();
                break;
                
            case 7:
                demo_efficiency();
                break;
                
            case 8:
                printf("Performing stress test...\n");
                for (int i = 0; i < 20; i++) {
                    char test_text[50];
                    sprintf(test_text, "This is test line %d for stress testing", i);
                    insert_line(line_count, test_text);
                }
                printf("Stress test completed.\n");
                break;
                
            case 0:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
        
    } while (choice != 0);
    
    free_all();
    return 0;
}
