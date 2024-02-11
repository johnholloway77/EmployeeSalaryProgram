#include "../headers.h"

int closeProg() {

    printw("\nEnd of program. Press any key to exit\n");
    getch();
    clear();
    endwin();
    exit(0);
}
