/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Nathan Kong
Student ID#: 150950236
Email      : nkong@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

void displayFormattedPhone(const char* const str) {
    const int REQ_LEN = 10;
    const char* const validChars = "0123456789";
    const char* const invalidDisplay = "(___)___-____";
    
    int allDigits = 0;
    const char* itr = NULL;

    if (str && strlen(str) == REQ_LEN) {
        for (
            allDigits = 1, itr = str;
            *itr != '\0' && allDigits;
            ++itr
        ) {
            if (!strchr(validChars, *itr)) {
                allDigits = 0;
            }
        }
        
        if (allDigits) {
            printf(
                "(%c%c%c)%c%c%c-%c%c%c%c",
                str[0], str[1], str[2], str[3], str[4],
                str[5], str[6], str[7], str[8], str[9]
            );
            return;
        }
    }
    printf("%s", invalidDisplay);
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

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
    int repeat = 1;

    do {
        scanf(" %c", &value);

        if (!strchr(validChars, value) || getchar() != '\n') {
            repeat = 1;
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
        } else {
            repeat = 0;
        }
    } while (repeat);

    return value;
}

void inputCString(char* const str, const int min, const int max) {
    const char* const validChars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM 1234567890";

    char* itr = str;
    int len = 0;
    int repeat = 0, reset = 0, ueqLen = 0;
    char chr = '\0';

    do {
        repeat = 1;
        scanf("%c", &chr);

        // Discard leading '\n'
        // !(itr == str && chr == '\n')
        if (itr != str || chr != '\n') {
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
            repeat = chr != '\n';
            reset = 0;
            ueqLen = 0;

            if (chr == '\n' && len < min) {
                if (min == max) {
                    // Not equal
                    ueqLen = 1;
                } else {
                    // Too short
                    reset = 1;
                    printf("ERROR: String length must be between %d and %d chars: ", min, max);
                }
            } else if ((chr == '\n' && len > max) || (chr != '\n' && len >= max)) {
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

            if (!reset && repeat) {
                // Check if input char is valid
                reset = !strchr(validChars, chr);

                if (reset) {
                    printf("ERROR: Invalid character\n");
                }
            }

            if (reset) {
                strncpy(str, "", max);
                itr = str;
                len = 0;

                // chr != '\n'
                if (repeat) {
                    clearInputBuffer();
                }
            } else if (repeat) {
                // Prevent putting '\n' into the string
                *itr = chr;
                ++itr;
                ++len;
            }
        }
    } while (reset || repeat);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

