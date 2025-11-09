#include <stdio.h>
#include <string.h>

#define ADMIN_PASSWORD 1234
#define MAX_USERS 100
#define MAX_CARS 100

// --- Structs ---
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

// --- Load Cars From File ---
int loadCars(struct Car cars[]) {
    FILE *fp = fopen("cars.txt", "r");
    if (!fp) return 0;

    int count = 0;
    while (fscanf(fp, "%s %s %d %s %d", 
        cars[count].name, 
        cars[count].model, 
        &cars[count].price, 
        cars[count].fuel, 
        &cars[count].available) == 5) {
        count++;
    }

    fclose(fp);
    return count;
}

int main() {
    int choice, adminChoice, customerChoice;
    int password, running = 1;

    struct Car cars[MAX_CARS];
    int carCount = loadCars(cars);

    struct User users[MAX_USERS];
    int userCount = 0;

    while (running) {
        printf("\n===== Car Rental Management System =====\n");
        printf("1. Administrator\n");
        printf("2. Customer Login\n");
        printf("3. Customer Registration\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("\n-- Administrator Login --\n");
            printf("Enter Admin Password: ");
            scanf("%d", &password);

            if (password == ADMIN_PASSWORD) {
                printf("Admin Login Successful.\n");
                int adminRunning = 1;
                while (adminRunning) {
                    printf("\n--- Admin Panel ---\n");
                    printf("1. View all users\n");
                    printf("2. View all cars\n");
                    printf("3. Remove car (coming soon)\n");
                    printf("4. Logout\n");
                    printf("5. (reserved)\n");
                    printf("6. Add new car to cars.txt\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);

                    switch (adminChoice) {
                    case 1:
                        printf("\n-- Registered Users --\n");
                        for (int i = 0; i < userCount; i++) {
                            printf("User %d: %s\n", i + 1, users[i].name);
                        }
                        break;
                    case 2:
                        printf("\n-- Car List --\n");
                        for (int i = 0; i < carCount; i++) {
                            printf("%d. %s %s | $%d | %s | %s\n", i + 1,
                                cars[i].name, cars[i].model,
                                cars[i].price, cars[i].fuel,
                                cars[i].available ? "Available" : "Rented");
                        }
                        break;
                    case 4:
                        adminRunning = 0;
                        printf("Logged out from admin panel.\n");
                        break;
                    case 6: {
                        FILE *carFile = fopen("cars.txt", "a");
                        if (carFile == NULL) {
                            printf("Error opening car file.\n");
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
                        carCount = loadCars(cars);
                        printf("Car added successfully.\n");
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
            printf("\n-- Customer Login --\n");
            printf("Enter your name: ");
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
                printf("\n--- Customer Panel ---\n");
                printf("1. View available cars\n");
                printf("2. Rent a car\n");
                printf("0. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &customerChoice);

                switch (customerChoice) {
                case 1:
                    printf("\n-- Available Cars --\n");
                    for (int i = 0; i < carCount; i++) {
                        if (cars[i].available) {
                            printf("%d. %s %s | $%d | %s\n", i + 1,
                                cars[i].name, cars[i].model,
                                cars[i].price, cars[i].fuel);
                        }
                    }
                    break;
                case 2: {
                    int rentChoice;
                    char address[100], date[20];
                    printf("Enter car number to rent: ");
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
                    printf("Name: %s\n", users[found].name);
                    printf("Address: %s\n", address);
                    printf("Date: %s\n", date);
                    printf("Car: %s %s\n", cars[rentChoice].name, cars[rentChoice].model);
                    printf("Fuel: %s\n", cars[rentChoice].fuel);
                    printf("Price: $%d/day\n", cars[rentChoice].price);
                    break;
                }
                case 0:
                    customerRunning = 0;
                    printf("Logged out from customer panel.\n");
                    break;
                default:
                    printf("Invalid option.\n");
                }
            }
            break;
        }

        case 3: {
            if (userCount < MAX_USERS) {
                printf("\n-- Customer Registration --\n");
                printf("Enter your name: ");
                scanf("%s", users[userCount].name);
                printf("Create a 4-digit PIN: ");
                scanf("%d", &users[userCount].pin);
                sprintf(users[userCount].userId, "U1%02d", userCount + 1);
                FILE *fp = fopen("users.txt", "a");
                if (fp != NULL) {
                    fprintf(fp, "Name: %s\nPIN: %d\nUserID: %s\n---------------------\n",
                        users[userCount].name, users[userCount].pin, users[userCount].userId);
                    fclose(fp);
                }
                printf("Registration successful!\n");
                printf("Welcome, %s. Your UserID is: %s\n",
                    users[userCount].name, users[userCount].userId);
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
