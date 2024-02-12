#include "../headers.h"
#include "../models/employee.h"
#include "../models/employeeSalary.h"
#include "close.h"

#include "validFileName.h"

const double cpp_max = 3499.80;
const double ei_max = 952.74;

char lookupSalaryFile(char *file_address) {
  FILE *file;

  file = fopen(file_address, "r");
  char validExt = validFileName(file_address);

  while (file == NULL || validExt != 0) {
    printw("Error opening %s\n", file_address);
    printw("Press q to quit program or any other key to search again\n");
    refresh();

    char i = getchar();
    i = tolower(i);

    if (i == 'q') {
      // printw("Goodbye!\n");
      // endwin();
      // exit(1);
      closeProg();
    } else {
      clear();
      printw("Please select the correct address for Salary file: ");
      getstr(file_address);
      validExt = validFileName(file_address);
      file = fopen(file_address, "r");
    }
  }
  return 0;
}

EmployeeSalary *printEmployeeSalary(char *file_address, const Employee *emp) {

  FILE *file = fopen(file_address, "r");
  char line[256];
  size_t len = 0;
  ssize_t read;
  char empID[10];

  // verify file is valid with gaurd
  if (file == NULL) {
    clear();
    printw("ERORR: Cannot load file\nPress any key to exit\n");
    refresh();
    getchar();
    exit(1);
  }

  while (fgets(line, sizeof(line), file) != NULL) {
    fscanf(file, "%s", empID);

    if (strcmp(empID, emp->empID) == 0) {

      EmployeeSalary *es = (EmployeeSalary *)malloc(sizeof(EmployeeSalary));
      char monthSal[10];
      char monthFed[10];
      char monthAlb[10];
      char monthCPP[10];
      char monthEI[10];
      char monthRSP[10];

      char empLastName[25];
      char empFirstName[25];
      char empID[7];

      strlcpy(empLastName, emp->empLastName, sizeof(empLastName));
      strlcpy(empFirstName, emp->empFirstName, sizeof(empFirstName));
      strlcpy(empID, emp->empID, sizeof(empID));

      fscanf(file, "%s", monthSal);
      fscanf(file, "%s", monthFed);
      fscanf(file, "%s", monthAlb);
      fscanf(file, "%s", monthCPP);
      fscanf(file, "%s", monthEI);
      fscanf(file, "%s", monthRSP);

      strlcpy(es->empID, empID, sizeof(es->empID));
      es->monthSal = atof(monthSal);
      es->monthFed = atof(monthFed);
      es->monthAlb = atof(monthAlb);
      es->monthCPP = atof(monthCPP);
      es->monthEI = atof(monthEI);
      es->monthRSP = atof(monthRSP);

      // strlcpy(es->monthSal, monthSal, sizeof(es->monthSal));
      // strlcpy(es->monthFed, monthFed, sizeof(es->monthFed));
      // strlcpy(es->monthAlb, monthAlb, sizeof(es->monthAlb));
      // strlcpy(es->monthCPP, monthCPP, sizeof(es->monthCPP));
      // strlcpy(es->monthEI, monthEI, sizeof(es->monthEI));
      // strlcpy(es->monthRSP, monthRSP, sizeof(es->monthRSP));

      printw("%.*s\n", 70,
             "------------------------------------------------------------");
      refresh();
      printw("Salary information for %s %s with %s is:\n", empFirstName,
             empLastName, empID);
      refresh();
      printw("%.*s\n", 70,
             "------------------------------------------------------------");
      refresh();
      printw("%-21s$%0.2f\n", "Monthly Salary:", atof(monthSal));
      refresh();
      printw("%-21s$%0.2f\n", "Monthly Federal Tax:", atof(monthFed));
      refresh();
      printw("%-21s$%0.2f\n", "Montly Alberta Tax:", atof(monthAlb));
      refresh();
      printw("%-21s$%0.2f\n", "Monthly CPP:", atof(monthCPP));
      refresh();
      printw("%-21s$%0.2f\n", "Monthly EI:", atof(monthEI));
      refresh();
      printw("%-21s$%0.2f\n", "Monthly Opt. RSP:", atof(monthRSP));
      refresh();
      refresh();
      printw("%.*s\n", 70,
             "------------------------------------------------------------");
      refresh();
      fclose(file);
      return es;
    }
  }

  printw("Could not find salary info\n");
  fclose(file);
  return NULL;
}

char printCompanyPaySchedule(char *file_address) {

  FILE *file = fopen(file_address, "r");
  char line[256];
  size_t len = 0;
  ssize_t read;
  int isFirstLine = 1;

  // verify file is valid with gaurd
  if (file == NULL) {
    clear();
    printw("ERORR: Cannot load file\nPress any key to exit\n");
    refresh();
    getchar();
    exit(1);
  }

  int salaryTotal = 0;
  double fedTaxTotal = 0.0;
  double albTaxTotal = 0.0;
  double cppTotal = 0.0;
  double eiTotal = 0.0;
  double rspTotal = 0.0;
  double taxTotal;
  double netDblTotal;

  while (fgets(line, sizeof(line), file) != NULL) {

    if (isFirstLine) {
      isFirstLine = 0;
      continue; // skip the first line
    }

    char empID[10];
    char monthSal[10];
    char monthFed[10];
    char monthAlb[10];
    char monthCPP[10];
    char monthEI[10];
    char monthRSP[10];

    fscanf(file, "%s", empID);
    fscanf(file, "%s", monthSal);
    fscanf(file, "%s", monthFed);
    fscanf(file, "%s", monthAlb);
    fscanf(file, "%s", monthCPP);
    fscanf(file, "%s", monthEI);
    fscanf(file, "%s", monthRSP);

    salaryTotal += atoi(monthSal);
    fedTaxTotal += atof(monthFed);
    albTaxTotal += atof(monthAlb);
    cppTotal += atof(monthCPP);
    eiTotal += atof(monthEI);
    rspTotal += atof(monthRSP);
  }

  taxTotal = fedTaxTotal + albTaxTotal;
  netDblTotal = salaryTotal - (taxTotal + cppTotal + eiTotal + rspTotal);

  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");
  refresh();

  printw("%20s%40s%10s\n", "Gross", "Optional", "Net");
  printw("%8s%12s%10s%10s%10s%10s%10s\n", "Month", "Salary", "Tax", "CPP", "EI",
         "RSP", "Salary");
  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");
  refresh();
  for (int i = 1; i <= 12; i++) {

    printw("%8d%12.2f%10.2f%10.2f%10.2f%10.2f%10.2f\n", i, salaryTotal / 12.0,
           taxTotal / 12.0, cppTotal / 12.0, eiTotal / 12.0, rspTotal / 12.0,
           netDblTotal / 12.0);
  }
  refresh();
  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");
  printw("%8s%12.2f%10.2f%10.2f%10.2f%10.2f%10.2f\n", "Total:", salaryTotal,
         taxTotal, cppTotal, eiTotal, rspTotal, netDblTotal);

  refresh();
  fclose(file);
  return 0;
}

char printPaySchedule(EmployeeSalary *es) {

  double yearSal = 0;
  double yearTax = 0;
  double yearCPP = 0;
  double yearEI = 0;
  double yearRSP = 0;
  double yearNet = 0;

  double taxTotal = es->monthFed + es->monthAlb;
  double netTotal =
      es->monthSal - (taxTotal + es->monthCPP + es->monthEI + es->monthRSP);

  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");
  refresh();

  printw("%20s%40s%10s\n", "Gross", "Optional", "Net");
  printw("%8s%12s%10s%10s%10s%10s%10s\n", "Month", "Salary", "Tax", "CPP", "EI",
         "RSP", "Salary");
  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");
  refresh();
  for (int i = 1; i <= 12; i++) {

    yearSal += es->monthSal;
    yearTax += taxTotal;
    yearRSP += es->monthRSP;
    yearNet += netTotal;

    double cpp;
    double ei;

    if ((yearCPP + es->monthCPP) >= cpp_max) {
      cpp = cpp_max - yearCPP;
      yearCPP = cpp_max;
    } else {
      cpp = es->monthCPP;
        yearCPP += es->monthCPP;
    }

    if ((yearEI + es->monthEI) >= ei_max) {
      ei = ei_max - yearEI;
      yearEI = ei_max;
    } else {
      ei = es->monthEI;
        yearEI += es->monthEI;
    }

    printw("%8d%12.2f%10.2f%10.2f%10.2f%10.2f%10.2f\n", i, es->monthSal,
           taxTotal, cpp, ei, es->monthRSP, netTotal);
  }
  refresh();
  printw(
      "%.*s\n", 70,
      "----------------------------------------------------------------------");

  printw("%8s%*c%.2f%*c%.2f%*c%.2f%*c%.2f%*c%.2f%*c%.2f\n",
         "Total:", 9 - (int)(log10(yearSal)) - 1, '$', yearSal,
         7 - (int)(log10(yearTax)) - 1, '$', yearTax,
         7 - (int)(log10(yearCPP)) - 1, '$', yearCPP,
         7 - (int)(log10(yearEI)) - 1, '$', yearEI,
         7 - (int)(log10(yearRSP)) - 1, '$', yearRSP,
         7 - (int)(log10(yearNet)) - 1, '$', yearNet);

  refresh();

  return 0;
}
