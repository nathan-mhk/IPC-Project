/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Nathan Kong
Student ID#: 150950236
Email      : nkong@mysenaca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void) {
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n') {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt() {
    char newLine = 0;
    int value = 0;

    while (newLine != '\n') {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }

    return value;
}

int inputIntPositive() {
    int value = 0;
    int repeat = 0;

    do {
        value = inputInt();
        
        if (value <= 0) {
            repeat = 1;

            // Since we captured \n inside inputInt(), buffer is already cleared
            // clearInputBuffer();

            printf("ERROR! Value must be > 0: ");
        } else {
            repeat = 0;
        }
    } while (repeat);

    return value;
}

int inputIntRange(const int min, const int max) {
    int value = 0;
    int repeat = 0;

    do {
        value = inputInt();
        
        if (value < min || value > max) {
            repeat = 1;
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        } else {
            repeat = 0;
        }
    } while (repeat);

    return value;
}

char inputCharOption(const char validChars[]) {
    char value = 0;
    int i = 0;
    int repeat = 1;

    do {
        scanf(" %c", &value);

        for (i = 0; validChars[i] != '\0'; ++i) {
            if (value == validChars[i]) {
                repeat = 0;
            }
        }
        if (repeat) {
            clearInputBuffer();
            printf("ERROR: Character must be one of [");
            for (i = 0; validChars[i] != '\0'; ++i) {
                printf("%c", validChars[i]);
            }
            printf("]: ");
        }
    } while (repeat);

    return value;
}

void inputCString(char* const str, const int min, const int max) {
    const char* const validChars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";

    char* i = str;
    const char* validChar = validChars;
    int len = 0;
    int repeat = 0, reset = 0;
    int ueqLen = 0;
    char alphbt = '\0';

    do {
        repeat = 1;
        scanf("%c", &alphbt);

        // Discard leading '\n'
        // !(i == str && alphbt == '\n')
        if (i != str || alphbt != '\n') {
            /**
             * Too short:
             *      '\n' && len < min
             * Too long:
             *      '\n' && len > max
             *      !'\n' && len == max
             *      !'\n' && len > max
             * Not equal:
             *      Any of above && min == max 
            */
            repeat = alphbt != '\n';
            reset = 0;
            ueqLen = 0;

            if (alphbt == '\n' && len < min) {
                if (min == max) {
                    // Not equal
                    ueqLen = 1;
                } else {
                    // Too short
                    reset = 1;
                    printf("ERROR: String length must be between %d and %d chars: ", min, max);
                }
            } else if ((alphbt == '\n' && len > max) || (alphbt != '\n' && len >= max)) {
                if (min == max) {
                    // Not equal
                    ueqLen = 1;
                } else {
                    // Too long
                    reset = 1;
                    printf("ERROR: String length must be no more than %d chars: ", max);
                }
            }

            if (ueqLen) {
                reset = 1;
                printf("ERROR: String length must be exactly %d chars: ", min);
            }

            // Assume always valid?
            if (!reset && repeat) {
                // Check if input char is valid
                reset = 1;
                for (validChar = validChars; *validChar != '\0' && reset; ++validChar) {
                    reset = alphbt != *validChar;
                }
                if (reset) {
                    printf("ERROR: Invalid character\n");
                }
            }

            if (reset) {
                for (i = str; *i != '\0'; ++i) {
                    *i = '\0';
                }
                i = str;
                len = 0;
                if (repeat) {
                    clearInputBuffer();
                }
            } else if (repeat) {
                // Prevent putting '\n' into the string
                *i = alphbt;
                ++i;
                ++len;
            }
        }
    } while (reset || repeat);

    // do {
    //     scanf(" %[^\n]", str);

    //     // Expand this for loop to handle the strLen
    //     // Might get SegFault if input is longer than the length of str
    //     for (i = str; *i != '\0'; ++i, ++len);

    //     if (min == max && len != min) {
    //         repeat = 1;
    //         printf("ERROR: String length must be exactly %d chars: ", min);
    //     } else if (len < min) {
    //         repeat = 1;
    //         printf("ERROR: String length must be between %d and %d chars: ", min, max);
    //     } else if (len > max) {
    //         repeat = 1;
    //         printf("ERROR: String length must be no more than %d chars: ", max);
    //     } else {
    //         repeat = 0;
    //     }

    //     if (repeat) {
    //         clearInputBuffer();
    //     }

    // } while (repeat);

}

void displayFormattedPhone(const char* const str) {
    // TODO
}
