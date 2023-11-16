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
