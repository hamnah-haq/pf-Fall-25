#include <stdio.h>
#define ROWS 5
#define COLS 5

void updateSectorStatus(int grid[ROWS][COLS]){
    int row, col, status, bit, value;
    printf("Enter sector row (1-5): ");
    scanf("%d", &row);
    printf("Enter sector column (1-5): ");
    scanf("%d", &col);
    row--;
    col--;
    if(row < 0 || row > 4 || col < 0 || col > 4){
        printf("Invalid sector coordinates!\n");
        return;
    }
    printf("\nwhich satus do you want to change?\n");
    printf("1. Power Status\n2. Overload Warning\n3. Maintenance Required\n");
    printf("Enter status choice (1-3): ");
    scanf("%d", &status);
    if(status < 1 || status > 3){
    printf("Invalid status choice!\n");
    return;
    }

    printf("Set to ON (1) or OFF (0): ");
    scanf("%d", &value);
    if(value != 0 && value != 1){
        printf("Invalid value!\n");
        return;
    }

    bit = 1 << (status - 1);
    if(value == 1){
        grid[row][col] |= bit;
    } else {
        grid[row][col] &= ~bit;
    }
    printf("Sector (%d,%d) updated successfully!\n\n", row+1, col+1);

}

void printSectorStatus(int sector) {
    printf("Power: %s | ", (sector & 1) ? "ON" : "OFF");
    printf("Overload: %s | ", (sector & 2) ? "YES" : "NO");
    printf("Maintenance: %s\n\n", (sector & 4) ? "YES" : "NO");
}

void querySectorStatus(int grid[ROWS][COLS]){
    int row, col;
    printf("Enter sector row (1-5): ");
    scanf("%d", &row);
    printf("Enter sector column (1-5): ");
    scanf("%d", &col);
    row--;
    col--;
    if(row < 0 || row > 4 || col < 0 || col > 4){
        printf("Invalid sector coordinates!\n");
        return;
    }
    printf("\nSector (%d,%d): \n", row+1, col+1);
    
    printSectorStatus(grid[row][col]);
}

void systemDiagnostic(int grid[ROWS][COLS]){
    int overloaded =0;
    int maintenance = 0;

    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(grid[i][j] & (1<<1)) 
            overloaded++;

            if(grid[i][j] & (1<<2))
            maintenance ++;
        }
    }
    printf("----System Diagnostic Report----\n");
    printf("Total overloaded sectors: %d\n", overloaded);
    printf("Total maintenance sectors: %d\n\n", maintenance);
}

int main(){
    int grid[5][5]={0};
    int choice;

    
    while(1){
        printf("======IESCO POWER GRID MONITORING SYSTEM======\n");
        printf("1. Update Sector Status\n2. Query Sector Status\n3. Run System Diagnostic\n4. Exit\n");
        printf("==============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                systemDiagnostic(grid);
                break;
            case 4:
                printf("Exiting the system..... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
            }
        }
    }