// Bank Depositor 
//  Entry and Display
//     Data:                +
//        Client Number
//        Name
//        Date of Birth
//        Account Number
//        Account Balance
// Condition: Should be stored in a file

// Features:
// Log In of Registered Accounts
//      Validation:
//          Rejects Unregistered Accounts (username and pass)
//          Inputs of digits (username and password)
// Registration, Automatically Generated Client and Account number
//      Validation:
//          Rejects Registered Name
// Hidden Admin LogIn (displays whole database). Press 0 in menu: username: admin, password: nelson. palitan nalang

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void display() {
    gotoxy(2, 11); printf("Client\n             #");
    gotoxy(2, 33); printf("Name");
    gotoxy(2, 53); printf("Date of Birth");
    gotoxy(2, 73); printf("Account Number");
    gotoxy(2, 93); printf("Account Balance");

    //getch();
}

int menu() {
    int op;

    system("cls");
    gotoxy(9, 47); printf("Welcome to Bank Depositor");
    gotoxy(11, 50); printf("1. Log In");
    gotoxy(12, 50); printf("2. Register");
    gotoxy(13, 50); printf("3. Exit");
    gotoxy(15, 48); printf("Choose only [1-3]: ");
    scanf("%d", &op);

    return op;
}

void generateClientNumber(char *clientNumber) {
    //srand(time(NULL));
    int num = rand() % 1000; // Generates a random number between 0 and 999
    sprintf(clientNumber, "%03d", num); // Formats the number with leading zeros to make it 3 digits
}

void generateAccountNumber(char *accountNumber) {
    //srand(time(NULL));
    int num = rand() % 1000000; // Generates a random number between 0 and 999999
    sprintf(accountNumber, "69-%03d-%03d-%03d", num / 100000, (num / 1000) % 1000, num % 1000); // Formats the number as "03-XXX-XXX-XXX"
}

void registerAccount() {
    FILE *file;
    file = fopen("accounts.txt", "a"); // Opens the file in append mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    system("cls");
    char clientNumber[4];
    char accountNumber[15];
    char name[100];
    char dob[11];
    double balance;

    generateClientNumber(clientNumber);
    generateAccountNumber(accountNumber);

    gotoxy(9, 50); printf("Register Account");
    gotoxy(11, 40); printf("Client Number: %s", clientNumber);
    gotoxy(12, 40); printf("Account Number: %s", accountNumber);

    gotoxy(14, 40); printf("Enter Name: ");
    fflush(stdin);
    int i = 0;
    char c;
    while ((c = getchar()) != '\n' && i < sizeof(name) - 1) {
        name[i++] = c;
    }
    name[i] = '\0';

    // Split the name into first name and last name
    char *firstName = strtok(name, " ");
    char *lastName = strtok(NULL, "");

    // Check if the entered name is already registered
    if (isNameRegistered(name)) {
        gotoxy(16, 38); printf("The entered name is already registered.");
        fclose(file);
        getch();
        return;
    }
    
    gotoxy(15, 40); printf("Enter Date of Birth (DD-MM-YYYY): ");
    fflush(stdin);
    gets(dob);

    gotoxy(16, 40); printf("Enter Account Balance: ");
    scanf("%lf", &balance);

    fprintf(file, "%s\t%s\t%s\t%s\t%s\t%.2lf\n", clientNumber, firstName, lastName, dob, accountNumber, balance); // Writes the account details to the file
    fclose(file);

    gotoxy(18, 44); printf("Account Registered Successfully!");
    getch(); 
}

int isNameRegistered(char *name) {
    FILE *file;
    file = fopen("accounts.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "\t");
        // Username matches, check the password
        char *temp = token; //temp get the 1st variable in file and to proceed to second data
        token = strtok(NULL, "\t"); // Gets the name
        char *try = token;
        if (strcmp(try, name) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int validateInput(char *input, char *format) {
    if (strlen(input) != strlen(format)) {
        return 0;
    }
    for (int i = 0; i < strlen(input); i++) {
        if (format[i] == 'd' && !isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

int login() {
    char username[4];
    char password[15];

    system("cls");
    gotoxy(9, 55); printf("Log In");

    // Prompt the user for the username
    do {
        gotoxy(11, 40); printf("Enter Username (Client Number): ");
        fflush(stdin);
        gets(username);
        if (!validateInput(username, "ddd")) {
            gotoxy(11, 40); printf("Enter Username (Client Number):                    "); //system("cls");
            gotoxy(12, 38); printf("Invalid input. Please enter a 3-digit number.");
        }
    } while (!validateInput(username, "ddd"));
    gotoxy(12, 38); printf("                                              ");

    // Prompt the user for the password
    do {
        gotoxy(13, 40); printf("Enter Password (Account Number): ");
        fflush(stdin);
        gets(password);
        if (!validateInput(password, "99-999-999-999")) {
            gotoxy(13, 40); printf("Enter Password (Account Number):                     "); //system("cls");
            gotoxy(14, 25); printf("Invalid input. Please enter the account number in the format 69-XXX-XXX-XXX.");
        }
    } while (!validateInput(password, "99-999-999-999"));
    gotoxy(14, 25); printf("                                                                            ");

    // Check if the account exists in the file
    FILE *file;
    int found = 0;
    file = fopen("accounts.txt", "r"); // Opens the file in read mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "\t");
        if (strcmp(token, username) == 0) {
            // Username matches, check the password
            char *clientNumber = token;
            token = strtok(NULL, "\t"); // Gets the name
            char *firstName = token;
            token = strtok(NULL, "\t");
            char *lastName = token;
            token = strtok(NULL, "\t"); // Gets the date of birth
            char *dob = token;
            token = strtok(NULL, "\t"); // Gets the account number
            char *accountNumber = token;
            token = strtok(NULL, "\t"); // Gets the account balance
            double balance = atof(token); // Converts the balance to double
            if (strcmp(accountNumber, password) == 0) {
                // Password matches, login successful
                system("cls");
                gotoxy(9, 50); printf("Account Details");
                gotoxy(11, 43); printf("Client Number: %s", clientNumber);
                gotoxy(12, 43); printf("Name: %s %s", firstName, lastName);
                gotoxy(13, 43); printf("Date of Birth: %s", dob);
                gotoxy(14, 43); printf("Account Number: %s", accountNumber);
                gotoxy(15, 43); printf("Account Balance: %.2lf", balance);
                getch();
                fclose(file);
                return 1;
            }
            found++;
        }
    }

    fclose(file);
    if (found == 0) {
        gotoxy(16, 50); printf("Invalid username.");
    }
    else {
        gotoxy(16, 50); printf("Invalid password.");
    }
    getch();
    return 0;
}

void adminLogin() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "nelson") == 0) {
        FILE *file = fopen("accounts.txt", "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        system("cls");
        display();
        char clientNumber[4], name[100], dob[11], accountNumber[15];
        double balance;
        int row = 4; // starting row to display the account details
        int counter = 0; // to keep track of the number of accounts displayed
        int num = 1;
        char line[100];

        while (fgets(line, sizeof(line), file)) {
            char *token = strtok(line, "\t");
            char clientNumber[4];
            char firstName[100];
            char lastName[100];
            char dob[11];
            char accountNumber[15];
            double balance;

            strcpy(clientNumber, token);

            token = strtok(NULL, "\t");
            strcpy(firstName, token);

            token = strtok(NULL, "\t");
            strcpy(lastName, token);

            token = strtok(NULL, "\t");
            strcpy(dob, token);

            token = strtok(NULL, "\t");
            strcpy(accountNumber, token);

            token = strtok(NULL, "\t");
            balance = atof(token);

            gotoxy(row, 4); printf("%d", num);
            gotoxy(row, 12); printf("%s", clientNumber);
            gotoxy(row, 25); printf("%s %s", firstName, lastName);
            gotoxy(row, 55); printf("%s", dob);
            gotoxy(row, 73); printf("%s", accountNumber);
            gotoxy(row, 96); printf("%.2lf", balance);
            
            row++;
            counter++;
            num++;
        }

        if (counter == 0) {
            gotoxy(13, 40); printf("No accounts found.");
            getch();
        }

        fclose(file);

        getch();
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    srand(time(NULL));

    while (1) {
        switch (menu()) {
            case 1:
                system("cls");
                login();
                break;
            case 2:
                system("cls");
                registerAccount();
                break;
            case 3:
                exit(0);
            case 0:
                system("cls");
                adminLogin();
                break;
            default:
                gotoxy(18, 49); printf("Only Choose 1 to 3");
                gotoxy(14, 48); printf("Choose only [1-3]:   ");
                break;
        }
    }
}
