#include <stdio.h>

void viewCarList()
{
    printf("\n--- Car List ---\n");
    printf("1. Toyota Corolla - $50/day\n");
    printf("2. Honda Civic - $55/day\n");
    printf("3. Ford Mustang - $100/day\n");
    printf("4. Tesla Model 3 - $120/day\n");
    printf("----------------------\n");
}

void administratorMenu()
{
    int adminChoice;

    printf("\nAdministrator Menu:\n");
    printf("1. View Car List\n");
    printf("2. Other Administrator Function\n");
    printf("3. Back to Main Menu\n");

    printf("Enter your choice: ");
    scanf("%d", &adminChoice);

    switch (adminChoice)
    {
    case 1:
        viewCarList();
        break;
    case 2:
        printf("This is a placeholder for another administrator function.\n");
        break;
    case 3:
        return; // Go back to the main menu
    default:
        printf("Invalid choice. Please try again.\n");
    }
}

int main()
{
    int choice;
    int code = 1234;
    int input_code; // Define input_code before using it

    printf("Thanks for contacting us.\n");
    printf("Welcome to the Car Rental Management System\n");

    printf("1. Administrator\n");
    printf("2. Customer\n");
    printf("3. Exit\n");

    printf("Please select your role: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("You have selected Administrator.\n");
        printf("Enter your code: ");
        scanf("%d", &input_code);
        if (input_code == code)
        {
            printf("Access granted. Redirecting to administrator menu...\n");
            administratorMenu();
        }
        else
        {
            printf("Invalid code. Access denied.\n");
        }
        break;
    case 2:
        printf("You have selected Customer.\n");
        // Call customer functions here
        break;
    case 3:
        printf("Exiting the program. Thank you!\n");
        return 0;
    default:
        printf("Invalid choice. Please try again.\n");
    }

    return 0;
}
