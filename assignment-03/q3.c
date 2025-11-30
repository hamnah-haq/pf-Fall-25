#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_DESIGNATION_LENGTH 50
#define SALARY_THRESHOLD 50000
#define BONUS_PERCENTAGE 0.10

struct recordOfEmployees
{
    int EmployeeID;
    char name[MAX_NAME_LENGTH];
    char Designation[MAX_DESIGNATION_LENGTH];
    float Salary;
};

void displaySingleEmployee(struct recordOfEmployees emp) {
    printf("\nEmployee Details:\n");
    printf("ID: %d\n", emp.EmployeeID);
    printf("Name: %s\n", emp.name);
    printf("Designation: %s\n", emp.Designation);
    printf("Salary: %.2f\n", emp.Salary);
    printf("----------------------------\n");
}

void displayEmployees(struct recordOfEmployees emp[], int count){
    if(count == 0) {
        printf("No employees to display.\n");
        return;
    }
    
    printf("\n------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-15s |\n", "EmployeeID", "Name", "Designation", "Salary");
    printf("------------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++) {
        printf("| %-10d | %-20s | %-20s | %-15.2f |\n",
        emp[i].EmployeeID,
        emp[i].name, 
        emp[i].Designation, 
        emp[i].Salary);
    }
    printf("------------------------------------------------------------------------------\n");
}


void findHighestSalary(struct recordOfEmployees emp[], int count){
    if(count == 0) {
        printf("No employees to analyze.\n");
        return;
    }
    
    // First find the maximum salary
    float maxSalary = emp[0].Salary;
    for(int i = 1; i < count; i++) {
        if(emp[i].Salary > maxSalary) {
            maxSalary = emp[i].Salary;
        }
    }
    
    // Now count how many have this maximum salary
    int highestCount = 0;
    for(int i = 0; i < count; i++) {
        if(emp[i].Salary == maxSalary) {
            highestCount++;
        }
    }

    printf("\nEmployees with highest salary (%.2f):\n", maxSalary);
    if(highestCount == 1) {
        
        for(int i = 0; i < count; i++) {
            if(emp[i].Salary == maxSalary) {
                displaySingleEmployee(emp[i]);
                break;
            }
        }
    } else {
        
        printf("------------------------------------------------------------------------------\n");
        printf("| %-10s | %-20s | %-20s | %-15s |\n", "EmployeeID", "Name", "Designation", "Salary");
        printf("------------------------------------------------------------------------------\n");
        for(int i = 0; i < count; i++) {
            if(emp[i].Salary == maxSalary) {
                printf("| %-10d | %-20s | %-20s | %-15.2f |\n",
                    emp[i].EmployeeID,
                    emp[i].name, 
                    emp[i].Designation, 
                    emp[i].Salary);
            }
        }
        printf("------------------------------------------------------------------------------\n");
        printf("Total employees with highest salary: %d\n", highestCount);
    }
}


void searchEmployee(struct recordOfEmployees emp[], int count, int searchKey){
    if(searchKey == 1) {
    
        int id;
        printf("Enter Employee ID to search: ");
        scanf("%d", &id);
        int found = 0;
        
        for(int i = 0; i < count; i++) {
            if(emp[i].EmployeeID == id) {
                printf("\nEmployee Found:\n");
                displaySingleEmployee(emp[i]);  
                found = 1;
                break;
            }
        }
        if(!found) {
            printf("No employee found with ID: %d\n", id);
        }
    } else if(searchKey == 2) {
        
        char name[MAX_NAME_LENGTH];
        printf("Enter Name to search: ");
        scanf(" %49[^\n]", name);
        int found = 0;
        int matchCount = 0;
        
        printf("\nSearch Results for '%s':\n", name);
        for(int i = 0; i < count; i++) {
            if(strcmp(emp[i].name, name) == 0) {
                if(matchCount == 0) {
                    
                    printf("------------------------------------------------------------------------------\n");
                    printf("| %-10s | %-20s | %-20s | %-15s |\n", "EmployeeID", "Name", "Designation", "Salary");
                    printf("------------------------------------------------------------------------------\n");
                }
                printf("| %-10d | %-20s | %-20s | %-15.2f |\n",
                    emp[i].EmployeeID,
                    emp[i].name, 
                    emp[i].Designation, 
                    emp[i].Salary);
                found = 1;
                matchCount++;
            }
        }
        
        if(found) {
            printf("------------------------------------------------------------------------------\n");
            printf("Total matches found: %d\n", matchCount);
        } else {
            printf("No employee found with name: %s\n", name);
        }
    } else {
        printf("Invalid choice. Please enter 1 or 2.\n");
    }
}


int isEmployeeIDUnique(struct recordOfEmployees emp[], int count, int id) {
    for(int i = 0; i < count; i++) {
        if(emp[i].EmployeeID == id) {
            return 0; 
        }
    }
    return 1; 
}

void applyBonusToLowSalary(struct recordOfEmployees emp[], int count){
    int updatedCount = 0;
    for(int i = 0; i < count; i++){
        if(emp[i].Salary < SALARY_THRESHOLD){
            float oldSalary = emp[i].Salary;
            emp[i].Salary += emp[i].Salary * BONUS_PERCENTAGE;
            printf("Applied bonus to %s: %.2f -> %.2f\n", 
                   emp[i].name, oldSalary, emp[i].Salary);
            updatedCount++;
        }
    }
    printf("\nTotal employees receiving bonus: %d\n", updatedCount);
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    if(n <= 0 || n > 1000) {
        printf("Invalid number of employees. Please enter a number between 1 and 1000.\n");
        return 1;
    }
    
    struct recordOfEmployees emp[1000];                      
    
    for(int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        
        int id;
        do {
            printf("Employee ID: ");
            scanf("%d", &id);
            if(!isEmployeeIDUnique(emp, i, id)) {
                printf("Error: Employee ID %d already exists! Please enter a unique ID.\n", id);
            }
        } while(!isEmployeeIDUnique(emp, i, id));
        emp[i].EmployeeID = id;
        
        printf("Name: ");
        scanf(" %49[^\n]", emp[i].name);          
        printf("Designation: ");
        scanf(" %49[^\n]", emp[i].Designation);   
        printf("Salary: ");
        scanf("%f", &emp[i].Salary);        
    }

    printf("\n--- All Employees Details ---\n");
    displayEmployees(emp, n);
    
    findHighestSalary(emp, n);
    
    int searchKey;
    printf("\nSearch Options:\n1. By ID (Unique)\n2. By Name (Can have multiple matches)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &searchKey);
    searchEmployee(emp, n, searchKey);
    
    printf("\nApplying bonus to employees with salary below %d...\n", SALARY_THRESHOLD);
    applyBonusToLowSalary(emp, n);
    
    printf("\n--- Employees Details after applying bonus ---\n");
    displayEmployees(emp, n);

    return 0;
}
