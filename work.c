#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD_LENGTH 12

void welcomeMessage() {
    printf("===========================================\n");
    printf("   Welcome to the Password Strength Checker\n");
    printf("   and Strong Password Generator Program!  \n");
    printf("===========================================\n");
    printf("You can check your password's strength or generate\n");
    printf("a strong password to improve your online security.\n");
    printf("Password should include a mix of:\n");
    printf(" - Uppercase letters\n");
    printf(" - Lowercase letters\n");
    printf(" - Digits\n");
    printf(" - Special characters\n");
    printf("===========================================\n\n");
}

void generatePassword(char *password) {
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digits[] = "0123456789";
    const char special[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    srand(time(0));

    password[0] = lower[rand() % (sizeof(lower) - 1)];
    password[1] = upper[rand() % (sizeof(upper) - 1)];
    password[2] = digits[rand() % (sizeof(digits) - 1)];
    password[3] = special[rand() % (sizeof(special) - 1)];

    for (int i = 4; i < PASSWORD_LENGTH; i++) {
        int choice = rand() % 4;
        if (choice == 0)
            password[i] = lower[rand() % (sizeof(lower) - 1)];
        else if (choice == 1)
            password[i] = upper[rand() % (sizeof(upper) - 1)];
        else if (choice == 2)
            password[i] = digits[rand() % (sizeof(digits) - 1)];
        else
            password[i] = special[rand() % (sizeof(special) - 1)];
    }
    password[PASSWORD_LENGTH] = '\0';
}

int checkPassword(char password[]) {
    int length = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    if (length < 8) {
        printf("Password is too short. Must be at least 8 characters.\n");
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (ispunct(password[i])) hasSpecial = 1;
    }

    if (hasUpper && hasLower && hasDigit && hasSpecial) {
        printf("Password Strength: Strong\n");
        return 1;
    } else if (hasUpper && hasLower && hasDigit) {
        printf("Password Strength: Moderate\n");
        return 2;
    } else {
        printf("Password Strength: Weak\n");
        return 3;
    }
}

int main() {
    char password[100];
    int strength = 0;

    welcomeMessage();

    do {
        printf("Enter your password: ");
        scanf("%s", password);

        strength = checkPassword(password);

        if (strength == 0) {
            printf("Please try again with a stronger password.\n\n");
        }
    } while (strength == 0);

    if (strength == 1) {
        printf("Your password meets the required criteria for security!\n");
    } else if (strength == 2) {
        printf("Your password is moderately strong. Consider adding a special character to improve security.\n");
    } else {
        printf("Your password is weak. Try to include a mix of uppercase, lowercase, digits, and special characters.\n");
    }

    if (strength != 1) {
        printf("\nGenerating a strong password for you...\n");
        char strongPassword[PASSWORD_LENGTH + 1];
        generatePassword(strongPassword);
        printf("Generated Strong Password: %s\n", strongPassword);
    }

    return 0;
}
