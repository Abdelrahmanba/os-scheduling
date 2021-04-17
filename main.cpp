#include <ctime>
#include "include/helperFunctions.h"

#define MAX_NUM_PROC 20

int main() {
    std::vector<process> processesList;
    int noOfProcesses;

    srand(std::time(0));
    //read no of processes
    noOfProcesses = readIntInput(1, MAX_NUM_PROC, "Please enter the number of process you want to create");
    //create processes
    processesList = createProcess(noOfProcesses);

    showMenu();
    readChoice(processesList);
    return 0;
}



