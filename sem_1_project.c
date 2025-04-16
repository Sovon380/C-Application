#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EMAIL 100
#define MAX_PASS 50
#define MAX_USERS 100
#define FILE_NAME "users.txt"

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASS];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file) {
        while (fscanf(file, "%s %s", users[user_count].email, users[user_count].password) == 2) {
            user_count++;
        }
        fclose(file);
    }
}

void save_user(const char *email, const char *password) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file) {
        fprintf(file, "%s %s\n", email, password);
        fclose(file);
    }
}

int is_email_registered(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int validate_password(const char *password, char *error) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    int len = strlen(password);
    const char special_chars[] = ".!@#$*.";

    if (len < 6) {
        strcat(error, "Password length must be >=6.\n");
    }

    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else {
            for (int j = 0; special_chars[j]; j++) {
                if (password[i] == special_chars[j]) {
                    has_special = 1;
                    break;
                }
            }
        }
    }

    if (!has_upper) strcat(error, "Password must contain at least one uppercase character.\n");
    if (!has_lower) strcat(error, "Password must contain at least one lowercase character.\n");
    if (!has_digit) strcat(error, "Password must contain at least one digit character.\n");
    if (!has_special) strcat(error, "Password must contain at least one special character.\n");

    return error[0] == '\0';
}

void signup() {
    char email[MAX_EMAIL], password[MAX_PASS], re_password[MAX_PASS];
    char error[200] = "";

    printf("Enter email: ");
    scanf("%s", email);
    if (is_email_registered(email)) {
        printf("There is an account using this email.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);
    printf("Re-type password: ");
    scanf("%s", re_password);

    if (strcmp(password, re_password) != 0) {
        printf("Passwords do not match!\n");
        return;
    }

    if (!validate_password(password, error)) {
        printf("%s", error);
        return;
    }

    strcpy(users[user_count].email, email);
    strcpy(users[user_count].password, password);
    user_count++;
    save_user(email, password);
    printf("Account created successfully!\n");
}

int login() {
    char email[MAX_EMAIL], password[MAX_PASS];
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful!\n");
                return 1;
            } else {
                printf("Enter Correct Password!\n");
                return 0;
            }
        }
    }
    printf("There is no such email!\n");
    return 0;
}

void calculator() {
    while (1) {
        printf("\n=== Calculator Menu ===\n");
        printf("a. Max\nb. Min\nc. Avg\nd. Mean\ne. Addition\nf. Subtraction\ng. Multiplication\nh. Division\ni. Factorial\nj. Fibonacci\nk. Area Calculator\nl. Number Conversion\nm. Multiplication Table\nn. Sort\no. Back\n");
        printf("Enter choice: ");
        char choice;
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'o') break;

        int n = 0;
        double arr[100];
        // Only prompt for array input for operations that need it
        if (choice >= 'a' && choice <= 'h' || choice == 'n') {
            printf("Enter number of elements (1-100): ");
            if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
                printf("Invalid number of elements! Must be between 1 and 100.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Enter %d numbers: ", n);
            for (int i = 0; i < n; i++) {
                if (scanf("%lf", &arr[i]) != 1) {
                    printf("Invalid input! Please enter valid numbers.\n");
                    while (getchar() != '\n');
                    break;
                }
            }
        }

        switch (choice) {
            case 'a': { // Max
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                double max = arr[0];
                for (int i = 1; i < n; i++) {
                    if (arr[i] > max) max = arr[i];
                }
                printf("Maximum: %.2lf\n", max);
                break;
            }
            case 'b': { // Min
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                double min = arr[0];
                for (int i = 1; i < n; i++) {
                    if (arr[i] < min) min = arr[i];
                }
                printf("Minimum: %.2lf\n", min);
                break;
            }
            case 'c': case 'd': { // Avg/Mean
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                double sum = 0;
                for (int i = 0; i < n; i++) {
                    sum += arr[i];
                }
                printf("Average/Mean: %.2lf\n", sum / n);
                break;
            }
            case 'e': { // Addition
                double sum = 0;
                for (int i = 0; i < n; i++) {
                    sum += arr[i];
                }
                printf("Sum: %.2lf\n", sum);
                break;
            }
            case 'f': { // Subtraction
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                double result = arr[0];
                for (int i = 1; i < n; i++) {
                    result -= arr[i];
                }
                printf("Subtraction Result: %.2lf\n", result);
                break;
            }
            case 'g': { // Multiplication
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                double result = 1;
                for (int i = 0; i < n; i++) {
                    result *= arr[i];
                }
                printf("Multiplication Result: %.2lf\n", result);
                break;
            }
            case 'h': { // Division
                if (n < 2) {
                    printf("At least two numbers are required for division!\n");
                    break;
                }
                double result = arr[0];
                int valid = 1;
                for (int i = 1; i < n; i++) {
                    if (arr[i] == 0) {
                        printf("Division by zero is not allowed!\n");
                        valid = 0;
                        break;
                    }
                    result /= arr[i];
                }
                if (valid) {
                    printf("Division Result: %.2lf\n", result);
                }
                break;
            }
            case 'i': { // Factorial
                int num;
                printf("Enter a non-negative integer: ");
                if (scanf("%d", &num) != 1 || num < 0) {
                    printf("Invalid input! Please enter a non-negative integer.\n");
                    while (getchar() != '\n');
                    break;
                }
                unsigned long long fact = 1;
                for (int i = 1; i <= num; i++) {
                    fact *= i;
                    if (fact == 0) { // Overflow check
                        printf("Factorial too large to compute!\n");
                        fact = 0;
                        break;
                    }
                }
                if (fact != 0) {
                    printf("Factorial of %d: %llu\n", num, fact);
                }
                break;
            }
            case 'j': { // Fibonacci
                int num;
                printf("Enter number of Fibonacci terms (1-50): ");
                if (scanf("%d", &num) != 1 || num < 1 || num > 50) {
                    printf("Invalid input! Must be between 1 and 50.\n");
                    while (getchar() != '\n');
                    break;
                }
                unsigned long long a = 0, b = 1;
                printf("Fibonacci Sequence: ");
                for (int i = 0; i < num; i++) {
                    printf("%llu ", a);
                    unsigned long long temp = a;
                    a = b;
                    b = temp + b;
                    if (b < temp) { // Overflow check
                        printf("\nWarning: Further terms too large to compute!\n");
                        break;
                    }
                }
                printf("\n");
                break;
            }
            case 'k': { // Area Calculator
                while (1) {
                    printf("\n=== Area Calculator ===\na. Triangle\nb. Rectangle\nc. Circle\nd. Back\n");
                    char sub_choice;
                    scanf(" %c", &sub_choice);
                    sub_choice = tolower(sub_choice);
                    if (sub_choice == 'd') break;
                    switch (sub_choice) {
                        case 'a': {
                            double base, height;
                            printf("Enter base and height: ");
                            if (scanf("%lf %lf", &base, &height) != 2 || base <= 0 || height <= 0) {
                                printf("Invalid input! Base and height must be positive.\n");
                                break;
                            }
                            printf("Triangle Area: %.2lf\n", 0.5 * base * height);
                            break;
                        }
                        case 'b': {
                            double length, width;
                            printf("Enter length and width: ");
                            if (scanf("%lf %lf", &length, &width) != 2 || length <= 0 || width <= 0) {
                                printf("Invalid input! Length and width must be positive.\n");
                                break;
                            }
                            printf("Rectangle Area: %.2lf\n", length * width);
                            break;
                        }
                        case 'c': {
                            double radius;
                            printf("Enter radius: ");
                            if (scanf("%lf", &radius) != 1 || radius <= 0) {
                                printf("Invalid input! Radius must be positive.\n");
                                break;
                            }
                            printf("Circle Area: %.2lf\n", 3.14159 * radius * radius);
                            break;
                        }
                        default:
                            printf("Enter Correct Key Again!\n");
                    }
                    while (getchar() != '\n');
                }
                break;
            }
            case 'l': { // Number Conversion
                while (1) {
                    printf("\n=== Number Conversion ===\na. Binary to Decimal\nb. Decimal to Binary\nc. Binary to Hexadecimal\nd. Hexadecimal to Binary\ne. Decimal to Hexadecimal\nf. Hexadecimal to Decimal\ng. Octal to Hexadecimal\nh. Hexadecimal to Octal\ni. Back\n");
                    char sub_choice;
                    scanf(" %c", &sub_choice);
                    sub_choice = tolower(sub_choice);
                    if (sub_choice == 'i') break;
                    switch (sub_choice) {
                        case 'a': {
                            char bin[100];
                            printf("Enter binary number: ");
                            scanf("%s", bin);
                            int valid = 1;
                            for (int i = 0; bin[i]; i++) {
                                if (bin[i] != '0' && bin[i] != '1') {
                                    printf("Invalid binary number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(bin, NULL, 2);
                                printf("Decimal: %ld\n", decimal);
                            }
                            break;
                        }
                        case 'b': {
                            long dec;
                            printf("Enter decimal number: ");
                            if (scanf("%ld", &dec) != 1 || dec < 0) {
                                printf("Invalid input! Please enter a non-negative integer.\n");
                                while (getchar() != '\n');
                                break;
                            }
                            char bin[100] = "";
                            if (dec == 0) {
                                strcpy(bin, "0");
                            } else {
                                while (dec > 0) {
                                    char temp[2] = { (dec % 2) + '0', '\0' };
                                    strcat(temp, bin);
                                    strcpy(bin, temp);
                                    dec /= 2;
                                }
                            }
                            printf("Binary: %s\n", bin);
                            break;
                        }
                        case 'c': {
                            char bin[100];
                            printf("Enter binary number: ");
                            scanf("%s", bin);
                            int valid = 1;
                            for (int i = 0; bin[i]; i++) {
                                if (bin[i] != '0' && bin[i] != '1') {
                                    printf("Invalid binary number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(bin, NULL, 2);
                                printf("Hexadecimal: %lX\n", decimal);
                            }
                            break;
                        }
                        case 'd': {
                            char hex[100];
                            printf("Enter hexadecimal number: ");
                            scanf("%s", hex);
                            int valid = 1;
                            for (int i = 0; hex[i]; i++) {
                                if (!isxdigit(hex[i])) {
                                    printf("Invalid hexadecimal number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(hex, NULL, 16);
                                char bin[100] = "";
                                if (decimal == 0) {
                                    strcpy(bin, "0");
                                } else {
                                    while (decimal > 0) {
                                        char temp[2] = { (decimal % 2) + '0', '\0' };
                                        strcat(temp, bin);
                                        strcpy(bin, temp);
                                        decimal /= 2;
                                    }
                                }
                                printf("Binary: %s\n", bin);
                            }
                            break;
                        }
                        case 'e': {
                            long dec;
                            printf("Enter decimal number: ");
                            if (scanf("%ld", &dec) != 1 || dec < 0) {
                                printf("Invalid input! Please enter a non-negative integer.\n");
                                while (getchar() != '\n');
                                break;
                            }
                            printf("Hexadecimal: %lX\n", dec);
                            break;
                        }
                        case 'f': {
                            char hex[100];
                            printf("Enter hexadecimal number: ");
                            scanf("%s", hex);
                            int valid = 1;
                            for (int i = 0; hex[i]; i++) {
                                if (!isxdigit(hex[i])) {
                                    printf("Invalid hexadecimal number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(hex, NULL, 16);
                                printf("Decimal: %ld\n", decimal);
                            }
                            break;
                        }
                        case 'g': {
                            char oct[100];
                            printf("Enter octal number: ");
                            scanf("%s", oct);
                            int valid = 1;
                            for (int i = 0; oct[i]; i++) {
                                if (oct[i] < '0' || oct[i] > '7') {
                                    printf("Invalid octal number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(oct, NULL, 8);
                                printf("Hexadecimal: %lX\n", decimal);
                            }
                            break;
                        }
                        case 'h': {
                            char hex[100];
                            printf("Enter hexadecimal number: ");
                            scanf("%s", hex);
                            int valid = 1;
                            for (int i = 0; hex[i]; i++) {
                                if (!isxdigit(hex[i])) {
                                    printf("Invalid hexadecimal number!\n");
                                    valid = 0;
                                    break;
                                }
                            }
                            if (valid) {
                                long decimal = strtol(hex, NULL, 16);
                                char oct[100];
                                sprintf(oct, "%lo", decimal);
                                printf("Octal: %s\n", oct);
                            }
                            break;
                        }
                        default:
                            printf("Enter Correct Key Again!\n");
                    }
                    while (getchar() != '\n');
                }
                break;
            }
            case 'm': { // Multiplication Table
                int num;
                printf("Enter an integer: ");
                if (scanf("%d", &num) != 1) {
                    printf("Invalid input! Please enter an integer.\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Multiplication Table for %d:\n", num);
                for (int i = 1; i <= 10; i++) {
                    printf("%d x %d = %d\n", num, i, num * i);
                }
                break;
            }
            case 'n': { // Sort
                if (n == 0) {
                    printf("No elements provided!\n");
                    break;
                }
                for (int i = 0; i < n - 1; i++) {
                    for (int j = 0; j < n - i - 1; j++) {
                        if (arr[j] > arr[j + 1]) {
                            double temp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = temp;
                        }
                    }
                }
                printf("Sorted List: ");
                for (int i = 0; i < n; i++) {
                    printf("%.2lf ", arr[i]);
                }
                printf("\n");
                break;
            }
            default:
                printf("Enter Correct Key Again!\n");
        }
        while (getchar() != '\n'); // Clear input buffer
    }
}

void tic_tac_toe() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col;
    char player = 'X';
    int moves = 0;

    while (1) {
        // Print board
        printf("\n");
        for (int i = 0; i < 3; i++) {
            printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
            if (i < 2) printf("---+---+---\n");
        }

        // Get move
        printf("Player %c, enter row (0-2) and column (0-2): ", player);
        scanf("%d %d", &row, &col);

        // Validate move
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make move
        board[row][col] = player;
        moves++;

        // Check win
        int win = 0;
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) win = 1;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) win = 1;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) win = 1;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) win = 1;

        if (win) {
            printf("\n");
            for (int i = 0; i < 3; i++) {
                printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
                if (i < 2) printf("---+---+---\n");
            }
            printf("Player %c wins!\n", player);
            break;
        }

        if (moves == 9) {
            printf("\n");
            for (int i = 0; i < 3; i++) {
                printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
                if (i < 2) printf("---+---+---\n");
            }
            printf("It's a draw!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

void games_zone() {
    while (1) {
        printf("\nGamesZone:\na. Tic Tac Toe\nB. Back\n");
        char choice;
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'b') break;
        if (choice == 'a') {
            tic_tac_toe();
        } else {
            printf("Enter Correct Key Again!\n");
        }
    }
}

void logged_in_menu() {
    while (1) {
        printf("\nPhotobook Menu:\nc. Calculator\ng. GamesZone\nq. Logout\n");
        char choice;
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'q') break;
        switch (choice) {
            case 'c':
                calculator();
                break;
            case 'g':
                games_zone();
                break;
            default:
                printf("Enter Correct Key Again!\n");
        }
    }
}

int main() {
    load_users();
    while (1) {
        printf("\nPhotobook:\na. Signup\nb. Login\nQ. Exit\n");
        char choice;
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'q') break;
        switch (choice) {
            case 'a':
                signup();
                break;
            case 'b':
                if (login()) {
                    logged_in_menu();
                }
                break;
            default:
                printf("Enter Correct Key Again!\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}
