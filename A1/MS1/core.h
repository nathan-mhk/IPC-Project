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

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

int inputInt();

int inputIntPositive();

int inputIntRange(int min, int max);

//                         FIXME
char inputCharOption(const char* const validChars);

void inputCString(char* const str, int min, int max);

void displayFormattedPhone(const char* const str);
