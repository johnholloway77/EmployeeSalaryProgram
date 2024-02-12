#ifndef SALARY_H
#define SALARY_H

#include "../models/employee.h"
#include "../models/employeeSalary.h"

// char printEmployeeSalary(const Employee *e, char *file_address);
EmployeeSalary *printEmployeeSalary(char *file_address, const Employee *emp);
char lookupSalaryFile(char *file_address);
// char lookupEmployeeSalary(char *file_address, const Employee *emp);

char printCompanyPaySchedule(char *file_address);
char printPaySchedule(EmployeeSalary *es);

#endif // SALARY_H
