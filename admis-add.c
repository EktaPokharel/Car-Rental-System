#include <stdio.h>

#define ADMIN_PASSWORD 1234
#define MAX_USERS 100

int main() {
    int choice;
    int adminChoice, customerChoice;
    int password, logginId;
    int running = 1;

    int users = 0;
    int cars = 0;
    int userIDs[MAX_USERS];  // Array to store registered user IDs

    while (running) {
        printf("\n----- Thanks for contacting us. -----\n");
        printf("\n--- Main Menu ---\n");
        printf("1. Administrator\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                printf("\nYou have selected Administrator.\n");
                printf("Enter Admin Password: ");
                scanf("%d", &password);

                if (password == ADMIN_PASSWORD) {
                    printf("Login Successful.\n");

                    int adminRunning = 1;
                    while (adminRunning) {
                        printf("\n--- Admin Panel ---\n");
                        printf("1. Register new user\n");
                        printf("2. Add new car\n");
                        printf("3. Remove car\n");
                        printf("4. View all users\n");
                        printf("5. System stats\n");
                        printf("0. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);

                        switch (adminChoice) {
                            case 1:
                                if (users < MAX_USERS) {
                                    userIDs[users] = users + 1; // assign simple ID
                                    users++;
                                    printf("User registered successfully. User ID: %d\n", users);
                                } else {
                                    printf("User limit reached.\n");
                                }
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
                                for (int i = 0; i < users; i++) {
                                    printf("User ID: %d\n", userIDs[i]);
                                }
                                break;
                            case 5:
                                printf("System Stats:\n");
                                printf("Users: %d\n", users);
                                printf("Cars: %d\n", cars);
                                printf("User-Car Capacity (Users * Cars): %d\n", users * cars);  // using '*'
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
                    printf("Incorrect password. Try again.\n");
                }
                break;
            }

            case 2: {
                printf("\nYou have selected Customer.\n");

                if (users == 0) {
                    printf("No users registered yet. Please contact admin.\n");
                    break;
                }

                printf("\n----- Customer Login -----\n");
                printf("Enter your user ID: ");
                scanf("%d", &logginId);

                int found = 0;
                for (int i = 0; i < users; i++) {
                    if (logginId == userIDs[i]) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Invalid user ID. Please register first.\n");
                    break;
                }

                printf("Welcome, User %d!\n", logginId);

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
                                printf("No cars available for rent.\n");
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
