#ifndef SCHEDULING_ALGORITHMS_TESTBENCH_SCHEDULINGFUNCTIONS_H
#define SCHEDULING_ALGORITHMS_TESTBENCH_SCHEDULINGFUNCTIONS_H

std::vector<process> ScheduleFCFS(std::vector<process>&);
std::vector<process> ScheduleSJF(std::vector<process>&);
std::vector<process> ScheduleRR(std::vector<process>&);
std::vector<process> SchedulePriority(std::vector<process>&);
std::vector<process> SchedulePriorityWithRR(std::vector<process>&);
std::vector <std::vector<process>> sortPriorities(std::vector<process>&);

#endif
