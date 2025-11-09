// Car rental Management System, a simple C program to manage car rentals. This is the main file of this project. 1. administrator can add, delete, update and view cars. 2. customer can view available cars and renta car. 


#include <stdio.h>

int main() {

    int choice, userPin;
    int pin = 1234;
    printf("Thanks for contacting us.\n");
    printf("Welcome to the Mero Car Rental Management System\n");

    printf("1. Administrator\n");
    printf("2. Customer\n");
    printf("3. Exit\n");
    
    
    printf("Please select your role: \n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You have selected Administrator.\n");
            printf("Enter you code: \n");
            scanf("%d", &userPin);
            if (userPin == pin) {
                printf("Yes, You can re-direct the administrator pages.\n");
            } else {
                printf("Invalid code. Access denied.\n");
            }
            // Here you can add code to verify administrator credentials
            // Call administrator functions here
            break;
        case 2:
            printf("You have selected Customer.\n");
            // Call customer functions here
            break;
            case 3: 
            printf("Exiting the program. Thank you!\n");
            return 0; // Exit the program
        default:
            printf("Invalid choice. Please try again.\n");
            
    }
    

    return 0;
}