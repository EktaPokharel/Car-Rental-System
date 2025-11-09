#include <stdio.h>

#define key 1234

int main() {
    int choice;
    int admin, customerChoice;
    int pin, logginId;
    int running = 1;

    int users = 0;
    int cars = 0;

    while (running) {
        printf("\n--Welcome to mero car Rental System.--\n");
        printf("-----Thanks for contacting us.------\n");
        printf("\n--- Choose for helpful for You. ---\n");
        printf("1. Administrator\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("You have selected Administrator.\n");
                printf("Enter your Secret Pin for logIn: ");
                scanf("%d", &pin);

                if (pin == key) {
                    printf("Welcome! Admin logIn Successful.\n");

                    int adminRunning = 1;
                    while (adminRunning) {
                        printf("\n--- Select any features ---\n");
                        printf("1. Register new user\n");
                        printf("2. Add new car\n");
                        printf("3. Remove car\n");
                        printf("4. View all users\n");
                        printf("0. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &admin);

                        switch (admin) {
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
                    printf("Incorrect password. Access denied.\n");
                }
                break;
            }

            case 2: {
                printf("Thank you For Contact us.");
                printf("You have selected Customer.\n");

                if (users == 0) {
                    printf("No users registered yet. Please contact admin.\n");
                    break;
                }

                printf("\n----- Customer Login -----\n");
                printf("Enter your user ID: ");
                scanf("%d", &logginId);

                if (logginId < 1 || logginId > users) {
                    printf("Invalid user ID. Please register first.\n");
                    break;
                }

                printf("Welcome, User %d!\n", logginId);
                printf("You can now rent or return cars.\n");

                int customerRunning = 1;
                while (customerRunning) {
                    printf("\n--- Customer Panel ---\n");
                    printf("1. View available cars\n");
                    printf("2. Rent a car\n");
                    printf("3. Return a car\n");
                    printf("0. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &customerChoice);

                    switch (customerChoice) {
                        case 1:
                            printf("Available cars: %d\n", cars);
                            break;
                        case 2:
                            if (cars > 0) {
                                cars--;
                                printf("Car rented successfully. Remaining cars: %d\n", cars);
                            } else {
                                printf("Sorry, there is no cars  was available.\n");
                            }
                            break;
                        case 3:
                            cars++;
                            printf("Car returned successfully. Total cars: %d\n", cars);
                            break;
                        case 0:
                            customerRunning = 0;
                            printf("Logged out from customer panel.\n");
                            break;
                        default:
                            printf("Invalid option. Try again.\n");
                    }
                }
                break;
            }

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
