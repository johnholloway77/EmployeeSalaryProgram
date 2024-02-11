#include "../headers.h"
#include "../models/employee.h"

Employee *lookupEmployeeID(char *file_address, char *firstName,
                           char *lastName) {

  FILE *file = fopen(file_address, "r");
  char line[256];
  size_t len = 0;
  ssize_t read;
  char lname[256];
  // char lineTxt2[256];
  // char *tokens[MAX_TOKENS];

  // verify file is valid with gaurd
  if (file == NULL) {
    clear();
    printw("ERORR: Cannot load file\nPress any key to exit\n");
    refresh();
    getchar();
    exit(1);
  }


  while (fgets(line, sizeof(line), file) != NULL) {

    char fname[20];

    fscanf(file, "%s", lname);
    fscanf(file, "%s", fname);
    if (strcmp(lname, lastName) == 0) {
      if (strcmp(fname, firstName) == 0) {
        char birthday[11];
        char startDate[11];
        char empID[7];

        fscanf(file, "%s", birthday);
        fscanf(file, "%s", startDate);
        fscanf(file, "%s", empID);

        Employee *emp = (Employee *)malloc(sizeof(Employee));

        strlcpy(emp->empLastName, lname, sizeof(emp->empLastName));
        strlcpy(emp->empFirstName, fname, sizeof(emp->empFirstName));
        strlcpy(emp->birthday, birthday, sizeof(emp->birthday));
        strlcpy(emp->serviceStartDate, startDate, sizeof(emp->serviceStartDate));
        strlcpy(emp->empID, empID, sizeof(emp->empID));

        fclose(file);

        return emp;
      }
    }
  }

  fclose(file);
  return NULL;
}
