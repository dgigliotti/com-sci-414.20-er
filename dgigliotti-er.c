//
// Assignment 4
// Daniela Gigliotti
// COM SCI X 414.20 (Fall 2018)
//

// Include libraries
#include <stdio.h>
#include <string.h>

// Define function prototypes
void getEmpInfo(void);      // Prompt user for employee details and store info
void makeCalc(void);        // Calculate employee totals and aggregate totals for the period
void printEmpInfo(void);    // Print employee details to output file row by row
void printTotals(void);     // Print aggregate totals to output file
int clear(void);            // Allows program to execute gets() after scanf()

// Define variables
const float OTRATE = 1.5;   // Overtime pay rate used to multiply regular pay
const float MAXREG = 40;    // Maximum number of working hours designated as regular working hours

char projectName[21];   // Name of project
char firstName[15];     // Employee's first name
char lastName[15];      // Employee's last name
char reportName[30];    // Employee's full name
float empHours;         // Employee's total hours worked for period
float empRegHours;      // Employee's hours worked for period
float empOTHours;       // Employee's overtime hours worked for period
float empRegWage;       // Employee's regular wage
float empOTWage ;        // Employee's overtime wage
float empRegPay;        // Employee's overtime pay
float empOTPay;         // Employee's overtime pay
float empGrossPay;      // Employee's gross pay
float totalHours = 0;       // Total hours worked for all employees for period
float totalRegHours = 0;    // Total regular hours worked for all employees for period
float percentOTRegHours;    // Percent of totalhours that are overtime for all employees for period
float totalOTHours = 0;     // Total overtime hours worked for all employees for period
float totalRegPay = 0;      // Total regular pay for all employees for period
float totalOTPay = 0;       // Total OT pay for all employees for period
float totalGrossPay = 0;    // Total gross pay for all employees for period
char answer;            // User's response to continue prompt
int counter = 1;        // Counts number of employees user has provided details for

// Declare output files
FILE *outputfile;

// Main function to open report and call other functions
float main(void){

    // Open and write output file
    outputfile = fopen ("c:\\class\\dgigliotti-er.txt","w");

    // Print program header
    printf("NetworkHaus Information Technology, LLC\n");
    printf("Staff Earnings Report Generator\n\n");
    printf("Please enter the project name: ");
    gets(projectName);
    printf("\n");
    
   // Print report header
    fprintf(outputfile, "NetworkHaus Information Technology, LLC\n");
    fprintf(outputfile, "Weekly Staff Earnings Report\n\n");
    fprintf(outputfile, "Project: %s\n\n", projectName);
    fprintf(outputfile, "Staff Member                     Reg Hrs        Overtime Hrs       Gross\n");
    fprintf(outputfile, "------------------------------------------------------------------------\n");


    // Call getEmpInfo, makeCalc, and printEmpInfo functions while user response is to continue entering data for employees
    do {
        getEmpInfo();   // Prompt user for employee details and store info
        makeCalc();     // Calculate employee totals and aggregate totals for the period
        printEmpInfo(); // Print employee details to output file row by row
        counter++;

        // Prompt user to continue to enter data for additional employee
        printf("\nThank you. Process another employee? ");
        scanf("%s", &answer);
        clear();
        printf("\n");
        
    } while (answer == 'y' || answer == 'Y');

    // Print program ending statement
    printf("End of processing.");
    
    // Print line separator to report
    fprintf(outputfile, "------------------------------------------------------------------------");
      
    // Print details at end of report
    printTotals();
    
    // Close output file
    fclose(outputfile);
    
    return 0;
}


// Prompt user for employee details and store info
 void getEmpInfo(void) {
    printf("Enter staff member #%d's first name: ", counter);
    gets(firstName);
    printf("Enter staff member #%d's last name: ", counter);
    gets(lastName);
    printf("Enter the hourly wage of %s %s: ", firstName, lastName);
    scanf("%f", &empRegWage);
    clear();
    printf("Enter total number of hours: ", firstName, lastName);
    scanf("%f", &empHours);
    clear();
}


// Calculate employee totals and aggregate totals for the period
void makeCalc(void){
    
    // Set employee's overtime wage equal to regular wage * overtime rate
    empOTWage = empRegWage * OTRATE;
    
    // If total employee hours exceeds maximum regular hours, set regular hours to the maximum and set the excess to overtime hours
    if (empHours > MAXREG){
        empRegHours = MAXREG;
        empOTHours = empHours - MAXREG;
    }
    
    // else, set employee's regular hours equal to total employee hours
    else {
    empRegHours = empHours;
    empOTHours = 0;
    }
    
    // Calculate employee regular pay, overtime pay, and gross pay
    empRegPay = empRegHours * empRegWage;
    empOTPay = empOTHours * empOTWage;
    empGrossPay = empRegPay + empOTPay;

    // Calculate total hours, regular hours, overtime hours, and percent overtime hours for all employees
    totalHours = totalHours + empHours;
    totalRegHours = totalRegHours + empRegHours;
    totalOTHours = totalOTHours + empOTHours;
    percentOTRegHours = 100*(totalOTHours / totalHours);

    // Calculate total regular pay and overtime pay, and total gross pay for all employees
    totalRegPay = totalRegPay + empRegPay;
    totalOTPay = totalOTPay + empOTPay;
    totalGrossPay = totalGrossPay + empGrossPay;
}

// Print employee details to output file row by row
void printEmpInfo(void){
    strcpy(reportName, lastName);
    strcat(reportName, ", ");
    strcat(reportName, firstName);
    fprintf(outputfile,"%-30s %4.1f ($%5.2f)   %4.1f ($%5.2f)    $%7.2f\n", reportName, empRegHours, empRegWage, empOTHours, empOTWage, empGrossPay);
}

// Print aggregate totals to output file
void printTotals(void){
    fprintf(outputfile, "\n\nTotal Regular Hours Worked: %4.1f\n", totalRegHours);
    fprintf(outputfile, "Total Overtime Hours Worked: %4.1f\n", totalOTHours);
    fprintf(outputfile, "Percentage of Total Hours That Are Overtime: %3.1f%%",percentOTRegHours);
    
    fprintf(outputfile, "\n\nTotal Regular Wages: $%6.2f", totalRegPay);
    fprintf(outputfile, "\nTotal Overtime Wages: $%6.2f", totalOTPay);
    fprintf(outputfile, "\n\nTotal Wages This Period: $%6.2f", totalGrossPay);
}

// Allows program to execute gets() after scanf()
int clear()  {
    while ((getchar())^'\n');    
}

