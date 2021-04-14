//
// Created by Abdelrahman on 4/12/2021.
//

#ifndef SCHEDULING_ALGORITHMS_TESTBENCH_FUNCTIONS_H
#define SCHEDULING_ALGORITHMS_TESTBENCH_FUNCTIONS_H

#endif //SCHEDULING_ALGORITHMS_TESTBENCH_FUNCTIONS_H
class process;
int readIntInput(int, int, std::string);
void processChoice(int);
void showProcessesSet();
void setShellColor(int);
template<typename T>
void printTimeline(std::vector<T>);
int ejectProcess(int, int, int);
int ejectIdle(int, int);
void SchedulePriorityWithRR();
std::vector <std::vector<process>> sortPriorities(std::vector<process> &priority);
void readChoice();





