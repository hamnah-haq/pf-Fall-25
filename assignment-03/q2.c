#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
    // BASE CASE: If we have reached the last planet, no more fuel is needed
    if (planet > totalPlanets) {
    // Mission SUCCESS - visited all planets
    return 1;
    }
    if (fuel <= 0) {
    // Mission FAILED - ran out of fuel
    return 0;
    }
    
    // RECURSIVE CASE: Calculate fuel needed for the current planet and recurse for the next planet
    
    //Apply the fixed fuel consumption
    fuel -= consumption;
    
    //Check for gravitational recharge
    int gravityZone = 0; 
    if(planet % 2 == 0){
        gravityZone = 1; 
    } 
    if(gravityZone == 1){
        fuel += recharge;
    }

    //Check for solar bonus after every 4th planet
    if (planet > 1 && (planet - 1) % 4 == 0){
        fuel += solarBonus;
    }

    // Ensure fuel doesn't go negative
    if (fuel < 0) {
        fuel = 0;
    }

    // Print fuel status for current planet
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    //Make the recursive call for the next planet
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);   
}

int main(){
    int initialFuel;
    int consumption;
    int recharge;
    int solarBonus;
    int totalPlanets;

    printf("Enter initial fuel amount: ");
    scanf("%d", &initialFuel);
    printf("Enter fixed fuel consumption per planet: ");
    scanf("%d", &consumption);
    printf("Enter fuel recharge amount in high gravity zones: ");
    scanf("%d", &recharge);
    printf("Enter solar bonus fuel amount after every 4th planet: ");
    scanf("%d", &solarBonus);
    printf("Enter total number of planets to traverse: ");
    scanf("%d", &totalPlanets);

    printf("\n--- Fuel Consumption Schedule ---\n");
    int success = calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);  

    if (success) {
    printf("Mission SUCCESSFUL! Spacecraft completed the journey.\n");
    } else {
    printf("Mission FAILED! Spacecraft ran out of fuel.\n");
    }

    return 0;
}
