#include "validFileName.h"
#include "../headers.h"
#include "../services/close.h"

//;



char loadEmployees(char *file_address) {
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
            printw("Please select the correct address for Employee file: ");
            getstr(file_address);
            validExt = validFileName(file_address);
            file = fopen(file_address, "r");
        }
    }

    fclose(file);
    clear();
    return 0;
}

