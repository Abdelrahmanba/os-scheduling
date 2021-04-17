#pragma once
#include <iostream>
#include "../include/process.h"

// CLASS PROCESS

int process::getProcId() const {
    return proc_id;
}

int process::getCpuBurst() const{
    return cpuBurst;
}

int process::getArrivalTime() const{
    return arrivalTime;
}

int process::getStaticPriority() const{
    return staticPriority;
}

int process::getRemExecTime(){
    return remExecTime;
}

void process::setRemExecTime(int remExecTime) {
    this->remExecTime = remExecTime;
}

process::process(int id) {
    const int MAX_ARRIVAL_TIME = 15;
    const int MAX_CPU_BURST_TIME = 10;
    const int MAX_PRIORITY_NO = 5;
    proc_id = id;
    cpuBurst = remExecTime = (rand() % MAX_CPU_BURST_TIME) + 1;
    arrivalTime = rand() % (MAX_ARRIVAL_TIME + 1);
    staticPriority = (rand() % MAX_PRIORITY_NO) + 1;
}

process::process(int proc_id, int arrivalTime, int runPeriod) {
    this->proc_id = proc_id;
    this->cpuBurst = runPeriod;
    this->arrivalTime = arrivalTime;
}
process::process(int proc_id, int cpuBurst, int arrivalTime, int priority) {
    this->proc_id =  proc_id;
    this->cpuBurst = this->remExecTime = cpuBurst;
    this->arrivalTime = arrivalTime;
    this->staticPriority = priority;
}

