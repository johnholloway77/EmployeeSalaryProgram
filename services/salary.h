#ifndef SALARY_H
#define SALARY_H

#include "../models/employee.h"
#include "../models/employeeSalary.h"

char printEmployeeSalary(const Employee *e, char *file_address);
char lookupEmployeeSalary(char *file_address, const Employee *emp);
char printScheduleYear(char *file_address);

#endif // SALARY_H
