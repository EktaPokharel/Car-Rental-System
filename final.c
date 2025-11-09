#include <stdio.h>
#include <string.h>

#define PIN 1234
#define USERS 100
#define CARS 100

struct Car {
    char name[30];
    char model[30];
    int price;
    char fuel[10];
    int available;
};

struct User {
    char name[30];
    int pin;
    char userId[10];
};

int main() {
    int choice, adminChoice, customerChoice;
    int password, running = 1;

    struct Car cars[CARS];
    int carCount = 0;

    // Default cars
    cars[carCount++] = (struct Car){"Tesla", "Model_S", 150, "Electric", 1};
    cars[carCount++] = (struct Car){"Toyota", "Corolla", 80, "Petrol", 1};
    cars[carCount++] = (struct Car){"Hyundai", "Ioniq", 90, "Electric", 1};
    cars[carCount++] = (struct Car){"Honda", "Civic", 85, "Petrol", 1};
    cars[carCount++] = (struct Car){"Kia", "EV6", 120, "Electric", 1};

    // Load additional cars from file
    FILE *carFileRead = fopen("cars.txt", "r");
    if (carFileRead) {
        while (carCount < CARS && fscanf(carFileRead, "%s %s %d %s %d",
            cars[carCount].name,
            cars[carCount].model,
            &cars[carCount].price,
            cars[carCount].fuel,
            &cars[carCount].available) == 5) {
            carCount++;
        }
        fclose(carFileRead);
    }

    struct User users[USERS];
    int userCount = 0;

    while (running) {
        printf("\n===== Car Rental Management System =====\n");
        printf("1. Administrator\n2. Customer Login\n3. Customer Registration\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("\n-- Administrator Login --\nEnter Admin Password: ");
            scanf("%d", &password);

            if (password == PIN) {
                printf("Admin Login Successful.\n");
                int adminRunning = 1;
                while (adminRunning) {
                    printf("\n--- Admin Panel ---\n1. View all users\n2. View all cars\n3. Remove car (coming soon)\n4. Logout\n5. (reserved)\n6. Add new car to cars.txt\nEnter your choice: ");
                    scanf("%d", &adminChoice);

                    switch (adminChoice) {
                    case 1:
                        printf("\n-- Registered Users --\n");
                        for (int i = 0; i < userCount; i++)
                            printf("User %d: %s\n", i + 1, users[i].name);
                        break;
                    case 2:
                        printf("\n---------------------------------------------------------------\n");
                        printf(" No |     Car Name     |  Model  |  Price  |   Fuel Type   | Status\n");
                        printf("---------------------------------------------------------------\n");
                        for (int i = 0; i < carCount; i++)
                            printf(" %2d | %-16s | %-7s | $%-6d | %-13s | %s\n",
                                i + 1, cars[i].name, cars[i].model,
                                cars[i].price, cars[i].fuel,
                                cars[i].available ? "Available" : "Rented");
                        break;
                    case 4:
                        adminRunning = 0;
                        printf("Admin logged out.\n");
                        break;
                    case 6: {
                        FILE *carFile = fopen("cars.txt", "a");
                        if (!carFile) {
                            printf("\u274c Error opening car file.\n");
                            break;
                        }
                        char carName[30], model[30], fuel[10];
                        int price;
                        printf("\n--- Add New Car ---\n");
                        printf("Enter Car Name: ");
                        scanf("%s", carName);
                        printf("Enter Car Model: ");
                        scanf("%s", model);
                        printf("Enter Price: ");
                        scanf("%d", &price);
                        printf("Enter Fuel Type (Petrol/Electric): ");
                        scanf("%s", fuel);

                        fprintf(carFile, "%s %s %d %s 1\n", carName, model, price, fuel);
                        fclose(carFile);

                        if (carCount < CARS) {
                            strcpy(cars[carCount].name, carName);
                            strcpy(cars[carCount].model, model);
                            cars[carCount].price = price;
                            strcpy(cars[carCount].fuel, fuel);
                            cars[carCount].available = 1;
                            carCount++;
                        }

                        printf("\u2705 Car added successfully.\n");
                        break;
                    }
                    default:
                        printf("Invalid choice.\n");
                    }
                }
            } else {
                printf("Incorrect admin password.\n");
            }
            break;
        }
        case 2: {
            if (userCount == 0) {
                printf("No registered users. Please register first.\n");
                break;
            }
            char inputName[30];
            int inputPin, found = -1;
            printf("\n-- Customer Login --\nEnter your name: ");
            scanf("%s", inputName);
            printf("Enter your PIN: ");
            scanf("%d", &inputPin);
            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i].name, inputName) == 0 && users[i].pin == inputPin) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Login failed.\n");
                break;
            }
            printf("Welcome, %s!\n", users[found].name);
            int customerRunning = 1;
            while (customerRunning) {
                printf("\n--- Customer Panel ---\n1. View available cars\n2. Rent a car\n0. Logout\nEnter your choice: ");
                scanf("%d", &customerChoice);
                switch (customerChoice) {
                case 1:
                    printf("\n-- Available Cars --\n");
                    for (int i = 0; i < carCount; i++) {
                        if (cars[i].available)
                            printf("%d. %s %s | $%d | %s\n", i + 1, cars[i].name, cars[i].model, cars[i].price, cars[i].fuel);
                    }
                    break;
                case 2: {
                    int rentChoice;
                    char address[100], date[20];
                    printf("\nEnter car number to rent: ");
                    scanf("%d", &rentChoice);
                    rentChoice--;
                    if (rentChoice < 0 || rentChoice >= carCount || !cars[rentChoice].available) {
                        printf("Invalid or unavailable car.\n");
                        break;
                    }
                    getchar();
                    printf("Enter your address: ");
                    fgets(address, sizeof(address), stdin);
                    address[strcspn(address, "\n")] = '\0';
                    printf("Enter rental date (DD/MM/YYYY): ");
                    scanf("%s", date);
                    cars[rentChoice].available = 0;
                    printf("\n--- Rental Receipt ---\n");
                    printf("Name     : %s\n", users[found].name);
                    printf("Address  : %s\n", address);
                    printf("Date     : %s\n", date);
                    printf("Car      : %s %s\n", cars[rentChoice].name, cars[rentChoice].model);
                    printf("Fuel     : %s\n", cars[rentChoice].fuel);
                    printf("Price    : $%d\n", cars[rentChoice].price);
                    printf("-----------------------------\n");
                    break;
                }
                case 0:
                    customerRunning = 0;
                    break;
                default:
                    printf("Invalid option.\n");
                }
            }
            break;
        }
        case 3: {
            if (userCount < USERS) {
                printf("\n-- Customer Registration --\nEnter your name: ");
                scanf("%s", users[userCount].name);
                printf("Create a 4-digit PIN: ");
                scanf("%d", &users[userCount].pin);
                sprintf(users[userCount].userId, "U1%02d", userCount + 1);
                FILE *ufp = fopen("customer_data.txt", "a");
                if (ufp) {
                    fprintf(ufp, "Name: %s\nPIN: %d\nUserID: %s\n---------------------\n",
                        users[userCount].name,
                        users[userCount].pin,
                        users[userCount].userId);
                    fclose(ufp);
                }
                printf("Registration successful! Your ID: %s\n", users[userCount].userId);
                userCount++;
            } else {
                printf("User limit reached.\n");
            }
            break;
        }
        case 0:
            running = 0;
            printf("Exiting system. Goodbye!\n");
            break;
        default:
            printf("Invalid option.\n");
        }
    }
    return 0;
}
