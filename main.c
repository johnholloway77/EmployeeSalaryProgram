#include "headers.h"

#include "./models/employee.h"
#include "./models/employeeSalary.h"
#include "./services/close.h"
#include "./services/fileLoader.h"
#include "./services/lookup.h"
#include "./services/salary.h"

// extern FILE *file;

int main(void) {

  char file_address[256];
  char firstName[50];
  char lastName[50];
  char yn;
  Employee *emp;
  EmployeeSalary *es;

  initscr(); // initalize ncurses window
  cbreak();  // disable line buffering
  echo();    // disable echo from user

  // get screen size
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  printw("Assignment 2 - revisited\nLets make this app in C\n\n");

  printw("Enter employee filename (full path): ");
  getstr(file_address);
  loadEmployees(file_address);

  printw("Enter employee first name: ");
  getstr(firstName);

  printw("Enter employee last name: ");
  getstr(lastName);

  noecho();
  clear();

  emp = lookupEmployeeID(file_address, firstName, lastName);

  if (emp == NULL) {
    clear();

    printw("%s %s not found :(", firstName, lastName);
    refresh();
    closeProg();
  }
  clear();

  printw("Employee information found for: %s %s\nAnd employee ID is: %s\n",
         emp->empFirstName, emp->empLastName, emp->empID);
  printw(
      "Would you like to retreive the employee's salary information? (Y/N):\n");
  refresh();

  yn = getchar();
  yn = tolower(yn);

  while (yn != 'n' && yn != 'y') {
    printw("\nPlease enter Y or N\n");
    refresh();
    yn = getchar();
  }
  if (yn == 'n') {
    free(emp);
    closeProg();
    exit(0);
  }


  echo();
  printw("Enter employee salaray filename (full path): ");

  getstr(file_address);
  noecho();
  clear();

  lookupSalaryFile(file_address);

  es = printEmployeeSalary(file_address, emp);

  refresh();

  printw("Would you like to caculate decutions & print salary schedule/year? "
         "(Y/N):\n");
  refresh();

  yn = getchar();
  yn = tolower(yn);

  while (yn != 'n' && yn != 'y') {
    printw("\nPlease enter Y or N\n");
    refresh();
    yn = getchar();
  }
  if (yn == 'n') {
    free(emp);
    free(es);
    closeProg();
    exit(0);
  }

  clear();


  // printCompanyPaySchedule(file_address);
  printPaySchedule(es);

  refresh();

  free(emp);
  free(es);
  closeProg();
  return 0;
}
