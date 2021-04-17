#ifndef SCHEDULING_ALGORITHMS_TESTBENCH_HELPERFUNCTIONS_H
#define SCHEDULING_ALGORITHMS_TESTBENCH_HELPERFUNCTIONS_H
#include <vector>
#include <string>
#include <map>
#include "process.h"

void setShellColor(int);
int readIntInput(int, int, std::string);
void showMenu();
void readChoice(std::vector<process>&);
void showProcessesSet(std::vector<process>&);
std::vector<process> createProcess(int);
void printTimeline(std::vector<process> plist);
int ejectProcess(int, int, int);
int ejectIdle(int, int);
void showMetrics(std::vector<process>, std::vector<process>&, std::string);

#endif //SCHEDULING_ALGORITHMS_TESTBENCH_HELPERFUNCTIONS_H



