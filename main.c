#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main_exit;

// Function prototypes
void menu(void);
void new_acc(void);
void edit(void);
void transact(void);
void erase(void);
void see(void);
void close(void);
float interest(float, float, int);

// Structs for storing customer data
struct date {
    int month, day, year;
};

// Structure to hold account information
struct {
    int acc_no;
    char name[60];
    int age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add, upd, check, rem, transaction;

// Main menu function
void menu(void) {
    int choice;
    printf("\n\n\t\t\t\tNSU COMMERCIAL BANK\n");
    printf("\n\n\t\t\tWELCOME TO THE MAIN MENU\n");
    printf("\n\t\t1. Create new account");
    printf("\n\t\t2. Update information of existing account");
    printf("\n\t\t3. For transactions");
    printf("\n\t\t4. Check the details of existing account");
    printf("\n\t\t5. Removing existing account");
    printf("\n\t\t6. Exit");

    printf("\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            new_acc();
            break;
        case 2:
            edit();
            break;
        case 3:
            transact();
            break;
        case 4:
            see();
            break;
        case 5:
            erase();
            break;
        case 6:
            close();
            break;
        default:
            printf("Invalid choice!");
            menu();
    }
}

// Function to calculate interest
float interest(float t, float amount, int rate) {
    float SI;
    SI = (rate * t * amount) / 100.0;
    return SI;
}

// Function for creating a new account
void new_acc(void) {
    int choice;
    FILE *ptr;

    // Opening file in append mode
    ptr = fopen("record.txt", "a+");
account_no:
    system("cls");
    printf("\t\t\tADD RECORD\n");
    printf("\nEnter today's date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
    printf("\nEnter the account number: ");
    scanf("%d", &check.acc_no);

    // Checking if the account number already exists
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (check.acc_no == add.acc_no) {
            printf("Account number already in use!\n");
            goto account_no;
        }
    }

    // Assigning account number
    add.acc_no = check.acc_no;
    printf("\nEnter the name: ");
    getchar(); // to consume the newline left by scanf
    fgets(add.name, sizeof(add.name), stdin);
    add.name[strcspn(add.name, "\n")] = 0; // remove the newline character
    printf("\nEnter the date of birth (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("\nEnter the age: ");
    scanf("%d", &add.age);
    printf("\nEnter the address: ");
    getchar(); // to consume the newline left by scanf
    fgets(add.address, sizeof(add.address), stdin);
    add.address[strcspn(add.address, "\n")] = 0; // remove the newline character
    printf("\nEnter the citizenship number: ");
    fgets(add.citizenship, sizeof(add.citizenship), stdin);
    add.citizenship[strcspn(add.citizenship, "\n")] = 0; // remove the newline character
    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);
    printf("\nEnter the amount to deposit: $");
    scanf("%f", &add.amt);
    printf("\nType of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n\n\tEnter your choice: ");
    getchar(); // to consume the newline left by scanf
    fgets(add.acc_type, sizeof(add.acc_type), stdin);
    add.acc_type[strcspn(add.acc_type, "\n")] = 0; // remove the newline character

    // Writing data to file
    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    fclose(ptr);
    printf("\nAccount created successfully!");

add_invalid:
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else {
        printf("\nInvalid!");
        goto add_invalid;
    }
}

// Function for editing account information
void edit(void) {
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

    printf("Enter the account no. of the customer whose info you want to change: ");
    scanf("%d", &upd.acc_no);

    // Loop through file to find account to edit
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == upd.acc_no) {
            test = 1;
            printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice (1 for address and 2 for phone): ");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1) {
                printf("Enter the new address: ");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                system("cls");
                printf("Changes saved!");
            } else if (choice == 2) {
                printf("Enter the new phone number: ");
                scanf("%lf", &upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                system("cls");
                printf("Changes saved!");
            }
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");

    if (test != 1) {
        printf("\nRecord not found!!");
        edit_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            edit();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else {
            printf("\nInvalid!");
            goto edit_invalid;
        }
    } else {
        printf("\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

// Function for handling transactions
void transact(void) {
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");
    printf("Enter the account no. of the customer: ");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == transaction.acc_no) {
            test = 1;
            if (strcmp(add.acc_type, "fixed1") == 0 || strcmp(add.acc_type, "fixed2") == 0 || strcmp(add.acc_type, "fixed3") == 0) {
                printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");

                system("cls");
                menu();
            }
            printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice (1 for deposit and 2 for withdraw): ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter the amount you want to deposit: $");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nDeposited successfully!");
            } else {
                printf("Enter the amount you want to withdraw: $");
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\nWithdrawn successfully!");
            }
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (test != 1) {
        printf("\nRecord not found!!");
        transact_invalid:
        printf("\n\n\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    } else {
        printf("\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

// Function for erasing an account
void erase(void) {
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");
    printf("Enter the account no. of the customer you want to delete: ");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no != rem.acc_no)
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        else {
            test = 1;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (test != 1) {
        printf("\nRecord not found!!");
        erase_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            erase();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else {
            printf("\nInvalid!");
            goto erase_invalid;
        }
    } else {
        printf("\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

// Function for viewing account details
void see(void) {
    FILE *ptr;
    int test = 0;
    int choice;
    ptr = fopen("record.txt", "r");
    printf("Do you want to check by\n1.Account no\n2.Name\nEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter the account number: ");
        scanf("%d", &check.acc_no);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
            if (add.acc_no == check.acc_no) {
                system("cls");
                test = 1;
                printf("\nAccount NO.: %d\nName: %s\nDOB: %d/%d/%d\nAge: %d\nAddress: %s\nCitizenship No: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
        }
    } else if (choice == 2) {
        printf("Enter the name: ");
        scanf("%s", check.name);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
            if (strcmp(add.name, check.name) == 0) {
                system("cls");
                test = 1;
                printf("\nAccount NO.: %d\nName: %s\nDOB: %d/%d/%d\nAge: %d\nAddress: %s\nCitizenship No: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
        }
    }
    fclose(ptr);
    if (test != 1) {
        printf("\nRecord not found!!");
        see_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            see();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else {
            printf("\nInvalid!");
            goto see_invalid;
        }
    } else {
        printf("\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            close();
    }
}


int main() {
    char pass[10], password[10] = "admin";
    int i = 0;
    printf("\n\n\t\tEnter the password to login: ");
    scanf("%s", pass);
    if (strcmp(pass, password) == 0) {
        printf("\n\nPassword Match!\nLOADING");
        for (i = 0; i <= 6; i++) {

            printf(".");
        }
        system("cls");
        menu();
    } else {
        printf("\n\nWrong password!!");
        login_try:
        printf("\nEnter 1 to try again and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            system("cls");
            main();
        } else if (main_exit == 0) {
            system("cls");
            close();
        } else {
            printf("\nInvalid!");

            system("cls");
            goto login_try;
        }
    }
    return 0;
}
