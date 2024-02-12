#ifndef EMPLOYEESALARY_H
#define EMPLOYEESALARY_H

typedef struct {
  char empID[10];
  double monthSal;
  double monthFed;
  double monthAlb;
  double monthCPP;
  double monthEI;
  double monthRSP;
} EmployeeSalary;

#endif // EMPLOYEESALARY_H
