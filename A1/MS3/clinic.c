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


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    if (patient[0].patientNumber) {

        int itr = 0;

        displayPatientTableHeader();

        for (itr = 0; itr < max; ++itr) {
            if (patient[itr].patientNumber) {
                displayPatientData(&patient[itr], fmt);
            }
        }
        putchar('\n');
    } else {
        printf("*** No records found ***\n");
    }
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
    int opt = 0;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");

        opt = inputIntRange(0, 2);
        putchar('\n');
        
        if (opt == 1) {
            searchPatientByPatientNumber(patient, max);
        } else if (opt == 2) {
            searchPatientByPhoneNumber(patient, max);
        }

        if (opt) {
            putchar('\n');
            suspend();
        }
    } while (opt);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int itr = 0;
    
    for (itr = 0; itr < max; ++itr) {
        if (!patient[itr].patientNumber) {

            patient[itr].patientNumber = nextPatientNumber(patient, max);

            inputPatient(&patient[itr]);

            printf("*** New patient record added ***\n\n");
            return;
        }
    }
    printf("ERROR: Patient listing is FULL!\n\n");
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
    int patientNum = 0, index = 0;
    
    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index != -1) {
        menuPatientEdit(&patient[index]);
    } else {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
    int patientNum = 0, index = 0;
    char opt = '\0';
    
    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');

        printf("Are you sure you want to remove this patient record? (y/n): ");
        opt = inputCharOption("yn");

        if (opt == 'y') {
            strncpy(patient[index].name, "", NAME_LEN + 1);
            patient[index].patientNumber = 0;
            strncpy(patient[index].phone.description, "", PHONE_DESC_LEN + 1);
            strncpy(patient[index].phone.number, "", PHONE_LEN + 1);

            printf("Patient record has been removed!\n\n");
        } else {
            printf("Operation aborted.\n\n");
        }
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData* const data) {
    int itr = 0, dataItr = 0;
    int aptPatNum = 0, patIndex = 0;

    // Both arrays might not be full
    const struct Appointment* appoints[MAX_APPOINTMENTS] = { NULL };
    const struct Patient* patients[MAX_APPOINTMENTS] = { NULL };

    const struct Appointment* appoint = NULL;

    displayScheduleTableHeader(NULL, 1);

    for (dataItr = 0; dataItr < MAX_APPOINTMENTS; ++dataItr) {
        
        appoint = (data->appointments) + dataItr;


        aptPatNum = appoint->patientNumber;

        patIndex = findPatientIndexByPatientNum(aptPatNum, data->patients, MAX_PETS);

        if (patIndex != -1) {
            appoints[itr] = appoint;
            patients[itr] = (data->patients) + patIndex;
            ++itr;
        }
    }
    sortAppointmentsByDate(appoints, patients, 0, itr - 1);
    displayAppointments(appoints, patients, itr, 1);
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData* const data) {
    struct Date date = { 0, 0, 0 };
    int itr = 0, dataItr = 0;
    int aptPatNum = 0, patIndex = 0;

    // Both arrays might not be full
    const struct Appointment* appoints[MAX_APPOINTMENTS] = { NULL };
    const struct Patient* patients[MAX_APPOINTMENTS] = { NULL };

    const struct Appointment* appoint = NULL;

    inputDate(&date);
    putchar('\n');
    displayScheduleTableHeader(&date, 0);

    for (dataItr = 0; dataItr < MAX_APPOINTMENTS; ++dataItr) {
        
        appoint = (data->appointments) + dataItr;

        if (
            appoint->date.year == date.year &&
            appoint->date.month == date.month &&
            appoint->date.day == date.day
        ) {
            aptPatNum = appoint->patientNumber;

            patIndex = findPatientIndexByPatientNum(aptPatNum, data->patients, MAX_PETS);

            if (patIndex != -1) {
                appoints[itr] = appoint;
                patients[itr] = (data->patients) + patIndex;
                ++itr;
            }
        }
    }
    sortAppointmentsByDate(appoints, patients, 0, itr - 1);
    displayAppointments(appoints, patients, itr, 0);
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(
    struct Appointment* const appoint, const int maxAppoint,
    const struct Patient* const patient, const int maxPatient
) {
    int itr = 0;
    int slotAvail = 0;
    struct Appointment newAppoint = { 0, { 0, 0 }, { 0, 0, 0 }};

    // Need to ensure empty slots == -1 first
    // itr = getAppointIndex(appoint, maxAppoint, -1, NULL);

    // if (itr != -1) {

    // }

    for (itr = 0; itr < maxAppoint && !slotAvail; ++itr) {
        if (appoint[itr].patientNumber < 1) {
            slotAvail = 1;
            --itr;  // Compensate for the ++itr
        }
    }
    if (slotAvail) {
        printf("Patient Number: ");
        newAppoint.patientNumber = inputIntPositive();

        inputTimeslot(appoint, &newAppoint, maxAppoint);

        appoint[itr].patientNumber = newAppoint.patientNumber;
        appoint[itr].date.year = newAppoint.date.year;
        appoint[itr].date.month = newAppoint.date.month;
        appoint[itr].date.day = newAppoint.date.day;
        appoint[itr].time.hour = newAppoint.time.hour;
        appoint[itr].time.min = newAppoint.time.min;

        printf("\n*** Appointment scheduled! ***\n\n");
    } else {
        printf("ERROR: No appointment timeslots available!\n");
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(
    struct Appointment* const appoint, const int maxAppoint,
    const struct Patient* const patient, const int maxPatient
) {
    int patientNum = 0;
    int appointIndex = 0, patientIndex = 0;
    struct Date date = { 0, 0, 0 };
    char opt = '\0';

    printf("Patient Number: ");
    patientNum = inputIntPositive();

    appointIndex = getAppointIndex(appoint, maxAppoint, patientNum, NULL);
    patientIndex = findPatientIndexByPatientNum(patientNum, patient, maxPatient);

    if (appointIndex != -1 || patientIndex != -1) {
        inputDate(&date);
        putchar('\n');

        appointIndex = getAppointIndex(appoint, maxAppoint, patientNum, &date);

        if (appointIndex != -1) {
            displayPatientData(patient + patientIndex, FMT_FORM);

            printf("Are you sure you want to remove this appointment (y,n): ");
            opt = inputCharOption("yn");
            putchar('\n');

            if (opt == 'y') {
                appoint[appointIndex].patientNumber = -1;
                appoint[appointIndex].date.year = 0;
                appoint[appointIndex].date.month = 0;
                appoint[appointIndex].date.day = 0;
                appoint[appointIndex].time.hour = 0;
                appoint[appointIndex].time.min = 0;

                printf("Appointment record has been removed!\n\n");
            } else {
                // Not present in sample output
                printf("Operation aborted.\n\n");
            }
        } else {
            // Not present in sample output
            printf("ERROR: Appointment record not found!\n\n");
        }
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patientNum = 0, index = 0;

    printf("Search by patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM);
    } else {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    char phoneNum[PHONE_LEN + 1] = {"\0"};
    int itr = 0, found = 0;

    printf("Search by phone number: ");
    inputCString(phoneNum, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();
    
    for (itr = 0; itr < max; ++itr) {
        if (!strcmp(patient[itr].phone.number, phoneNum)) {
            found = 1;
            displayPatientData(&patient[itr], FMT_TABLE);
        }
    }
    if (!found) {
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int itr = 0, maxPatientNum = 0;

    for (itr = 0; itr < max; ++itr) {
        if (patient[itr].patientNumber > maxPatientNum) {
            maxPatientNum = patient[itr].patientNumber;
        }
    }
    return maxPatientNum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(
    int patientNumber, const struct Patient patient[], int max
) {
    int itr = 0;

    for (itr = 0; itr < max; ++itr) {
        if (patientNumber == patient[itr].patientNumber) {
            return itr;
        }
    }
    return -1;
}


// Additional Custom Function
// Merge two sorted half arrays together
void merge(
    const struct Appointment* appoints[], 
    const struct Patient* patients[],
    const int minIndex, const int midIndex, const int maxIndex
) {
    // Sorted LHS: [minIndex, midIndex]
    // Sorted RHS: (midIndex, maxIndex]
    int itrL = minIndex;
    int itrR = midIndex + 1;
    int left = 0, skip = 0;

    const struct Date* dateL = NULL;
    const struct Time* timeL = NULL;
    const struct Date* dateR = NULL;
    const struct Time* timeR = NULL;

    const int tmpArrSize = maxIndex - minIndex + 1;
    const struct Appointment* tmpAppoints[tmpArrSize];
    const struct Patient* tempPatients[tmpArrSize];
    int itr = 0, tmpItr = 0;

    // Sort each half into a temp array
    for (tmpItr = 0; tmpItr < tmpArrSize; ++tmpItr) {

        // LHS exhausted
        if (itrL > midIndex) {
            left = 0;
            skip = 1;
        }

        // RHS exhausted
        if (itrR > maxIndex) {
            left = 1;
            skip = 1;
        }

        // Comparison: YYYY->MM->DD->HH->MM
        if (!skip) {
            dateL = &(appoints[itrL]->date);
            dateR = &(appoints[itrR]->date);

            timeL = &(appoints[itrL]->time);
            timeR = &(appoints[itrR]->time);

            if (dateL->year < dateR->year) {
                left = 1;

            } else if (dateL->year > dateR->year) {
                left = 0;

            } else if (dateL->month < dateR->month) {
                left = 1;

            } else if (dateL->month > dateR->month) {
                left = 0;

            } else if (dateL->day < dateR->day) {
                left = 1;

            } else if (dateL->day > dateR->day) {
                left = 0;

            } else if (timeL->hour < timeR->hour) {
                left = 1;

            } else if (timeL->hour > timeR->hour) {
                left = 0;

            } else if (timeL->min < timeR->min) {
                left = 1;

            } else /* if (timeL->min > timeR->min) */ {
                left = 0;
            }
        }

        if (left) {
            // LHS < RHS
            tmpAppoints[tmpItr] = appoints[itrL];
            tempPatients[tmpItr] = patients[itrL];
            ++itrL;
        } else {
            // RHS > LHS
            tmpAppoints[tmpItr] = appoints[itrR];
            tempPatients[tmpItr] = patients[itrR];
            ++itrR;
        }
    }

    // "Copy" the temp array back
    for (tmpItr = 0, itr = minIndex; tmpItr < tmpArrSize; ++tmpItr, ++itr) {
        appoints[itr] = tmpAppoints[tmpItr];
        patients[itr] = tempPatients[tmpItr];
    }
}

// Additional Custom Function
// Sort the appointments by date in ascending order
void sortAppointmentsByDate(
    const struct Appointment* appoints[], 
    const struct Patient* patients[],
    const int minIndex, const int maxIndex
) {
    int midIndex = 0;

    if (minIndex < maxIndex) {

        midIndex = minIndex + (maxIndex - minIndex) / 2;

        // Sort LHS [minIndex, midIndex]
        sortAppointmentsByDate(appoints, patients, minIndex, midIndex);

        // Sort RHS (midIndex, maxIndex]
        sortAppointmentsByDate(appoints, patients, midIndex + 1, maxIndex);

        // Merge the two sorted halves tgt
        merge(appoints, patients, minIndex, midIndex, maxIndex);
    }
}

// Additional Custom Function
// Display a specific number of appointments
void displayAppointments(
    const struct Appointment* appoints[], 
    const struct Patient* patients[],
    const int numAppoints,
    const int includeDateField
) {
    int itr = 0;
    for (itr = 0; itr < numAppoints; ++itr) {
        displayScheduleData(patients[itr], appoints[itr], includeDateField);
    }
    putchar('\n');
}

// Additional Custom Function
// Check if the given timeslot is occupied (same YYYY-MM-DD HH:MM)
int timeslotOccupied(
    const struct Appointment* const currAppoints,
    const struct Appointment* const newAppoint,
    const int maxAppoint
) {
    int itr = 0;
    const struct Appointment* appoint = NULL;

    for (itr = 0; itr < maxAppoint; ++itr) {
        appoint = currAppoints + itr;
        if (
            appoint->date.year == newAppoint->date.year &&
            appoint->date.month == newAppoint->date.month &&
            appoint->date.day == newAppoint->date.day &&
            appoint->time.hour == newAppoint->time.hour &&
            appoint->time.min == newAppoint->time.min
        ) {
            return 1;
        }
    }
    return 0;
}

// Additional Custom Function
// Get the index of the appointment by patient number
int getAppointIndex(
    const struct Appointment* const appoints,
    const int maxAppoint,
    const int patientNum,
    const struct Date* const date
) {
    int itr = 0;

    for (itr = 0; itr < maxAppoint; ++itr) {
        
        // patNum && (date == NULL || YMD)
        if (
            appoints[itr].patientNumber == patientNum &&
            (!date || (appoints[itr].date.year == date->year &&
                       appoints[itr].date.month == date->month &&
                       appoints[itr].date.day == date->day)
            )
        ) {
            return itr;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");

    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');

    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
    int opt = 0;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    opt = inputIntRange(1, 5);
    putchar('\n');

    switch (opt) {
        case 1:
            strncpy(phone->description, "CELL", PHONE_DESC_LEN + 1);
            break;
        case 2:
            strncpy(phone->description, "HOME", PHONE_DESC_LEN + 1);
            break;
        case 3:
            strncpy(phone->description, "WORK", PHONE_DESC_LEN + 1);
            break;
        default:
            strncpy(phone->description, "TBD", PHONE_DESC_LEN + 1);
            return;
    }
    
    printf("Contact: %s\n", phone->description);
    inputPhoneNum(phone->number);

    putchar('\n');
}

// Additional Custom Function
// Get user input for date information (YYYY-MM-DD)
void inputDate(struct Date* const date) {
    int dInM = 0;

    printf("Year        : ");
    date->year = inputIntPositive();

    printf("Month (%d-%d): ", MIN_MON, MAX_MON);
    date->month = inputIntRange(MIN_MON, MAX_MON);

    switch (date->month) {
        case JAN:
        case MAR:
        case MAY:
        case JUL:
        case AUG:
        case OCT:
        case DEC:
            dInM = DAYS_31;
            break;
        case APR:
        case JUN:
        case SEP:
        case NOV:
            dInM = DAYS_30;
            break;
        case FEB:
            // Every year that is exactly divisible by four is a leap year, 
            // except for years that are exactly divisible by 100, 
            // but these centurial years are leap years if 
            // they are exactly divisible by 400
            if (
                date->year % 4 == 0 &&
                (date->year % 100 != 0 || date->year % 400 == 0)
            ) {
                dInM = FEB_DAYS_LEAP;
            } else {
                dInM = FEB_DAYS;
            }
            break;
    }
    printf("Day (%d-%d)  : ", MIN_DAY, dInM);
    date->day = inputIntRange(MIN_DAY, dInM);
}

// Additional Custom Function
// Get user input for time information (HH:MM)
void inputTime(struct Time* time) {
    printf("Hour (%d-%d)  : ", MIN_HR, MAX_HR);
    time->hour = inputIntRange(MIN_HR, MAX_HR);

    printf("Minute (%d-%d): ", MIN_MIN, MAX_MIN);
    time->min = inputIntRange(MIN_MIN, MAX_MIN);
}

// Additional Custom Function
// Get user input for timeslot information
// Wrapper for inputDate() && inputTime() && validation
void inputTimeslot(
    const struct Appointment* const currAppoints,
    struct Appointment* const newAppoint,
    const int maxAppoint
) {
    int rptDate = 1, rptTime = 1;

    do {
        if (rptDate) {
            inputDate(&newAppoint->date);
        }
        if (rptTime) {
            inputTime(&newAppoint->time);
        }

        // Start time [STR_HR, END_HR] && correct interval
        // Repeat inputTime() if not
        rptTime = (newAppoint->time.hour < STR_HR || 
                    newAppoint->time.hour > END_HR || 
                    newAppoint->time.min > END_MIN ) || 
                    newAppoint->time.min % APPMNT_INTV != 0;

        if (rptTime) {
            printf(
                "ERROR: Time must be between %2d:%02d and %2d:%02d in %d minute intervals.\n\n",
                STR_HR, STR_MIN, END_HR, END_MIN, APPMNT_INTV
            );
        }

        // Check if date && time available
        // Repeat inputDate() && inputTime() if failed
        rptDate = timeslotOccupied(currAppoints, newAppoint, maxAppoint);

        if (rptDate) {
            rptTime = 1;
            printf("\nERROR: Appointment timeslot is not available!\n\n");
        }
    } while (rptDate || rptTime);
}

// Additional Custom Function
// Get user input for phone number
// Stripped down version of inputCString()
void inputPhoneNum(char phoneNum[]) {
    const char* const validChars = "1234567890";

    int reset = 0, repeat = 0, itr = 0;
    char chr = '\0';

    printf("Number : ");
    do {
        scanf("%c", &chr);

        repeat = chr != '\n';
        if (!repeat) {
            if (strlen(phoneNum) == PHONE_LEN) {
                // Eq Len
                phoneNum[itr] = '\0';
                reset = 0;
            } else {
                // Too short
                reset = 1;
            }
        } else /* if (chr != '\n') */ {
            if (strlen(phoneNum) == PHONE_LEN) {
                // Too long
                reset = 1;
            } else {
                // Undertermined
                reset = !strchr(validChars, chr);
            }
        }
        if (reset) {
            printf("Invalid 10-digit number! Number: ");
            strncpy(phoneNum, "", PHONE_LEN + 1);
            itr = 0;

            // chr != '\n'
            if (repeat) {
                // Too long || invalid char
                clearInputBuffer();
            }
        } else if (repeat) {
            // Proceed to next char
            phoneNum[itr] = chr;
            ++itr;
        }
    } while (reset || repeat);
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* fp = NULL;

    int itr = 0, res = 0;

    int patientNum = 0;
    char name[NAME_LEN + 1] = { '\0' };
    char desc[PHONE_DESC_LEN + 1] = { '\0' };
    char num[PHONE_LEN + 1] = { '\0' };

    fp = fopen(datafile, "r");

    if (!fp) {
        printf("ERR Failed to open file\n");
        return 0;
    }

    do {
        res = fscanf(fp, "%d|%[^|\n]|%[^|\n]|%[^\r\n]", &patientNum, name, desc, num);

        if (res == TBD_PHONE || res == VLD_PHONE) {

            patients[itr].patientNumber = patientNum;
            strncpy(patients[itr].name, name, NAME_LEN + 1);
            strncpy(patients[itr].phone.description, desc, PHONE_DESC_LEN + 1);

            if (res == TBD_PHONE) {
                strncpy(num, "", PHONE_LEN + 1);
            }
            strncpy(patients[itr].phone.number, num, PHONE_LEN + 1);
        }
    } while (res > 0 && ++itr < max);

    fclose(fp);
    return itr;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* fp = NULL;

    int itr = 0, res = 0;

    int patientNum = 0;
    int year = 0, month = 0, day = 0;
    int hour = 0, min = 0;

    fp = fopen(datafile, "r");

    if (!fp) {
        printf("ERR Failed to open file\n");
        return 0;
    }

    do {
        res = fscanf(
            fp, "%d,%d,%d,%d,%d,%d",
            &patientNum,
            &year, &month, &day,
            &hour, &min
        );

        if (res > 0) {
            appoints[itr].patientNumber = patientNum;

            appoints[itr].time.hour = hour;
            appoints[itr].time.min = min;

            appoints[itr].date.year = year;
            appoints[itr].date.month = month;
            appoints[itr].date.day = day;
        }
    } while (res > 0 && ++itr < max);

    fclose(fp);
    return itr;
}
