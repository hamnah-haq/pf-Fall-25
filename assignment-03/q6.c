#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int student_id;
    char full_name[50];
    char email[50];
    char dob[20];
    char registration_date[20];
    char batch[20];
    char membership_type[10];
    char interest[20];
} Student;

Student *students = NULL;
int student_count = 0;
int capacity = 0;


/* Making the whole string capital because validation becomes easier */
void to_upper_case(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}


/* Simple input validator for date format (DD/MM/YYYY) */
int is_valid_date(const char *date) {
    if (strlen(date) != 10)
        return 0;
    if (date[2] != '/' || date[5] != '/')
        return 0;
    return 1;
}


/* Batch must be one of the valid CS/SE/CYBER SECURITY/AI */
int is_valid_batch(const char *batch) {
    char temp[20];
    strcpy(temp, batch);
    to_upper_case(temp);

    return (!strcmp(temp, "CS") ||
            !strcmp(temp, "SE") ||
            !strcmp(temp, "CYBER SECURITY") ||
            !strcmp(temp, "AI"));
}


/* Membership type must be IEEE, ACM, or BOTH */
int is_valid_membership(const char *type) {
    char temp[10];
    strcpy(temp, type);
    to_upper_case(temp);

    return (!strcmp(temp, "IEEE") ||
            !strcmp(temp, "ACM") ||
            !strcmp(temp, "BOTH"));
}


/* Interest must be relevant options (IEEE / ACM / BOTH) */
int is_valid_interest(const char *interest) {
    char t[20];
    strcpy(t, interest);
    to_upper_case(t);

    return (!strcmp(t, "IEEE") ||
            !strcmp(t, "ACM") ||
            !strcmp(t, "BOTH"));
}


/* Expands array size when storage gets full */
void resize_array() {
    if (capacity == 0) {
        capacity = 5;
        students = (Student*)malloc(capacity * sizeof(Student));
    } else {
        capacity *= 2;
        students = (Student*)realloc(students, capacity * sizeof(Student));
    }
}


/* Check if the ID is already in the system */
int id_exists(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].student_id == id)
            return 1;
    }
    return 0;
}


/* Load all existing students from file */
void load_database(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;

    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp)) {
        if (student_count == capacity)
            resize_array();
        students[student_count++] = temp;
    }

    fclose(fp);
}


/* Rewrites the entire file with updated student list */
void save_database(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;

    fwrite(students, sizeof(Student), student_count, fp);
    fclose(fp);
}


/* Adds a new student */
void add_student() {
    Student s;

    printf("\nEnter student ID: ");
    scanf("%d", &s.student_id);
    getchar();

    if (id_exists(s.student_id)) {
        printf("This ID already exists.\n");
        return;
    }

    printf("Full name: ");
    fgets(s.full_name, 50, stdin);
    s.full_name[strcspn(s.full_name, "\n")] = 0;

    printf("Email: ");
    fgets(s.email, 50, stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    printf("Date of birth (DD/MM/YYYY): ");
    fgets(s.dob, 20, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;

    printf("Registration date (DD/MM/YYYY): ");
    fgets(s.registration_date, 20, stdin);
    s.registration_date[strcspn(s.registration_date, "\n")] = 0;

    do {
        printf("Batch (CS / SE / CYBER SECURITY / AI): ");
        fgets(s.batch, 20, stdin);
        s.batch[strcspn(s.batch, "\n")] = 0;
    } while (!is_valid_batch(s.batch));

    do {
        printf("Membership type (IEEE / ACM / BOTH): ");
        fgets(s.membership_type, 10, stdin);
        s.membership_type[strcspn(s.membership_type, "\n")] = 0;
    } while (!is_valid_membership(s.membership_type));

    do {
        printf("Interest (IEEE / ACM / BOTH): ");
        fgets(s.interest, 20, stdin);
        s.interest[strcspn(s.interest, "\n")] = 0;
    } while (!is_valid_interest(s.interest));


    if (student_count == capacity)
        resize_array();

    students[student_count++] = s;

    /* New record needs to be appended to file right away */
    FILE *fp = fopen("members.dat", "ab");
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student registered successfully.\n");
}


/* Update specific student information */
void update_student() {
    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (students[i].student_id == id) {

            printf("New email: ");
            fgets(students[i].email, 50, stdin);
            students[i].email[strcspn(students[i].email, "\n")] = 0;

            printf("New membership type (IEEE/ACM/BOTH): ");
            fgets(students[i].membership_type, 10, stdin);
            students[i].membership_type[strcspn(students[i].membership_type, "\n")] = 0;

            save_database("members.dat");
            printf("Record updated.\n");
            return;
        }
    }
    printf("ID not found.\n");
}


/* Completely removes a student from the system */
void delete_student() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (students[i].student_id == id) {

            /* Shifting elements left to fill the gap */
            for (int j = i; j < student_count - 1; j++)
                students[j] = students[j + 1];

            student_count--;

            save_database("members.dat");
            printf("Record deleted.\n");
            return;
        }
    }

    printf("ID not found.\n");
}


/* Shows all stored students */
void show_all_students() {
    printf("\n%-10s %-20s %-12s %-10s %-15s %-15s %-10s\n",
           "ID", "Name", "DOB", "Batch", "Membership", "Interest", "Reg-Date");

    for (int i = 0; i < student_count; i++) {
        printf("%-10d %-20s %-12s %-10s %-15s %-15s %-10s\n",
               students[i].student_id,
               students[i].full_name,
               students[i].dob,
               students[i].batch,
               students[i].membership_type,
               students[i].interest,
               students[i].registration_date);
    }
}


/* Batch-based reporting with membership filter.
   First we match the batch. Then we match the membership filter.
   Only the students who satisfy both conditions are printed.
*/
void generate_batch_report(const char *batch) {
    char search_batch[20];
    strcpy(search_batch, batch);
    to_upper_case(search_batch);

    char membership_filter[10];
    printf("Enter membership filter (IEEE / ACM / BOTH / ALL): ");
    fgets(membership_filter, sizeof(membership_filter), stdin);
    membership_filter[strcspn(membership_filter, "\n")] = 0;
    to_upper_case(membership_filter);

    printf("\nReport for Batch: %s\n", search_batch);
    printf("%-10s %-20s %-12s %-15s %-10s\n",
           "ID", "Name", "Membership", "Reg-Date", "Interest");
    printf("---------------------------------------------------------\n");

    int total = 0;

    for (int i = 0; i < student_count; i++) {

        if (strcmp(students[i].batch, search_batch) != 0)
            continue;

        if (strcmp(membership_filter, "ALL") != 0 &&
            strcmp(students[i].membership_type, membership_filter) != 0)
            continue;

        printf("%-10d %-20s %-12s %-15s %-10s\n",
               students[i].student_id,
               students[i].full_name,
               students[i].membership_type,
               students[i].registration_date,
               students[i].interest);

        total++;
    }

    printf("\nTotal students found: %d\n", total);
}


/* MAIN MENU */
int main() {
    load_database("members.dat");

    int choice;
    char batch[20];

    while (1) {
        printf("\n--- Student Club Management System ---\n");
        printf("1. Register Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Batch Report\n");
        printf("6. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                add_student();
                break;

            case 2:
                update_student();
                break;

            case 3:
                delete_student();
                break;

            case 4:
                show_all_students();
                break;

            case 5:
                printf("Enter batch: ");
                fgets(batch, 20, stdin);
                batch[strcspn(batch, "\n")] = 0;
                generate_batch_report(batch);
                break;

            case 6:
                save_database("members.dat");
                printf("Goodbye.\n");
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }
}
