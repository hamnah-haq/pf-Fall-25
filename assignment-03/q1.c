#include <stdio.h>
#include <math.h>

/*
Recursive function to calculate loan repayment schedule and total amount
Base case: No years remaining or loan fully repaid
Recursive case: Process current year's payment and recurse with updated values
*/
float calculateRepayment(float loan, float interestRate, int years, int currentYear, float extraPayment) {
    // BASE CASE: No years left or loan already fully repaid
    if (years == 0 || loan <= 0) {
        printf("Loan fully repaid after %d years\n", currentYear - 1);
        return 0;
    }
    
    // RECURSIVE CASE: Process current year and recurse for remaining years
    
    // Calculate fixed annual payment using annuity formula
    float annual_payment = (loan * interestRate) / (1 - 1/pow(1 + interestRate, years));
    
    // Calculate interest for current year
    float interest = loan * interestRate;
    
    // Calculate principal repaid (fixed payment minus interest)
    float principal = annual_payment - interest;
    
    // Calculate new balance after principal repayment AND extra payment
    float new_balance = loan - principal - extraPayment;
    
    // Ensure balance doesn't go negative
    if (new_balance < 0) {
        new_balance = 0;
    }
    
    // Print repayment schedule as required
    printf("Year %d: Remaining loan = %.2f\n", currentYear, new_balance);
    
    // Recursive call: Process next year with updated balance and reduced years
    return annual_payment + calculateRepayment(new_balance, interestRate, years - 1, currentYear + 1, extraPayment);
}

int main() {
    float loan;
    float interest_rate;
    int years;
    float extra_payment = 0;

    printf("Enter loan amount: ");
    scanf("%f", &loan);
    printf("Enter annual interest rate (as a decimal): ");
    scanf("%f", &interest_rate);
    printf("Enter number of years to repay: ");
    scanf("%d", &years);
    printf("Enter extra yearly payment (0 if none): ");
    scanf("%f", &extra_payment);

    printf("\n--- Repayment Schedule ---\n");
    float total = calculateRepayment(loan, interest_rate, years, 1, extra_payment);
    printf("\nTotal repayment: %.2f\n", total);

    /*
    WHY RECURSION IS SUITABLE FOR THIS PROBLEM:
    
    1. NATURAL TIME PROGRESSION: Each recursive call represents one year passing,
       making the temporal progression explicit in the code structure.
    
    2. STATE TRACKING: The loan balance and remaining years are automatically
       tracked through function parameters without external variables.
    
    3. CLEAR TERMINATION: Base cases naturally handle when the loan is fully
       repaid or the term ends.
    
    4. EASY EXTENSIBILITY: Adding features like extra payments only requires
       adding parameters without changing the recursive structure.
    
    5. READABILITY: The recursive approach closely mirrors the mathematical
       definition of amortization over multiple periods.
    
    6. INCREMENTAL CALCULATION: Each year's calculation depends only on the
       previous year's balance, which matches the recursive pattern perfectly.
    */

    return 0;
}
