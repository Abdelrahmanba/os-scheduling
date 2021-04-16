//
// Created by babaa on 4/16/2021.
//

#ifndef SCHEDULING_ALGORITHMS_TESTBENCH_METRICS_H
#define SCHEDULING_ALGORITHMS_TESTBENCH_METRICS_H

#include <vector>
#include "process.h"

std::map<int, int> responseTime(std::vector<process>, std::vector<process> &processesList);
std::map<int, int> turnAroundTime(std::vector<process> plist, std::vector<process> &processesList);
std::map<int, int> waitingTime(std::vector<process> &processesList, std::map<int, int>);
int throughput(std::vector<process> plist, std::vector<process> &processesList);
#endif //SCHEDULING_ALGORITHMS_TESTBENCH_METRICS_H
