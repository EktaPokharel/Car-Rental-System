#include <stdio.h>

#define passwordAdmin 1234

int main() {
    int choice;
    int adminChoice;
    int password;
    int running = 1;

    
    int users = 0;
    int cars = 0;

    while (running) {
        printf("\n----- Thanks for contacting us. ------\n");
        printf("--Welcome to the Car Rental Management System --\n");
        printf("1. Administrator\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            printf("You have selected Administrator.\n");
                printf("Enter Admin Password: ");
                scanf("%d", &password);

                if (password == passwordAdmin) {
                    printf("Login Successful.\n");

                    int adminRunning = 1;
                    while (adminRunning) {
                        printf("\n--- Admin Panel ---\n");
                        printf("1. Register new user\n");
                        printf("2. Add new car\n");
                        printf("3. Remove car\n");
                        printf("4. View all users\n");
                        printf("0. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);

                        switch (adminChoice) {
                            case 1:
                                users++;
                                printf("User registered successfully. Total users: %d\n", users);
                                break;
                            case 2:
                                cars++;
                                printf("Car added successfully. Total cars: %d\n", cars);
                                break;
                            case 3:
                                if (cars > 0) {
                                    cars--;
                                    printf("Car removed. Total cars: %d\n", cars);
                                } else {
                                    printf("No cars to remove.\n");
                                }
                                break;
                            case 4:
                                printf("Total registered users: %d\n", users);
                                break;
                            case 0:
                                adminRunning = 0;
                                printf("Logged out from admin panel.\n");
                                break;
                            default:
                                printf("Invalid option. Try again.\n");
                        }
                    }

                } else {
                    printf("Incorrect password. Returning to main menu...\n");
                }
                break;

            case 2:
                printf("Customer section is under development.\n");
                printf("You can try again later after complete customer functionality.\n");
                break;

            case 0:
                running = 0;
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}
