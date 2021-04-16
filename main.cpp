#include <iostream>
#include "helperFunctions.h"
#include "schedulingFunctions.h"
#include "textTable.h"
#include "process.h"

#define MAX_NUM_PROC 20

int main() {
    std::vector<process> processesList;
    int noOfProcesses, choice;

    srand(time(0));
    noOfProcesses = readIntInput(1, MAX_NUM_PROC, "Please enter the number of process you want to create");
    processesList = createProcess(noOfProcesses);
    showMenu();
    readChoice(processesList);
    return 0;
}



