#include <iostream> //cout exit
#include <map>
#include <vector>
#include <algorithm>
#include "../include/process.h"

/**
 * calculates the waiting time for each process individually, using turn around time and burst time.
 *
 * @param processesList:  original process list
 * @param turnAroundTime: map of proceses id and turn around time for each

 * @returns A map of process id as key and waiting time.
 */
std::map<int, int> waitingTime(std::vector<process> &processesList, std::map<int, int> turnAroundTime) {
    //Waiting time = Turnaround time - Burst time
    //we want to find burst time
    std::map<int, int> waitingTime;
    std::map<int, int>::iterator it;
    for(it=turnAroundTime.begin(); it!=turnAroundTime.end(); ++it){
        int pid = it->first;
        int turnAround = it->second;
        //find process burst time
        auto originalProcess = find_if(processesList.begin(), processesList.end(), [&pid](const process& obj) {return obj.getProcId() == pid;});
        //if id is not defined for any reason -> crash
        if (originalProcess == processesList.end()){
            std::cout<<"Unexpected error happened";
            exit(1);
        }
        waitingTime[pid]= turnAround - originalProcess->getCpuBurst();
    }

    return waitingTime ;
}

/**
 * calculates the response time for each process individually
 *
 * @param plist: scheduled process list
 * @param processesList:  original process list
 * @returns A map of process id as key and response time.
 */
std::map<int, int> responseTime(std::vector<process> plist, std::vector<process> &processesList) {
    std::map<int,int> r;
    std::vector<int> processesId;

    int currentTime = plist[0].getArrivalTime();

    for(int i = 0; i < plist.size(); i++) {
        int pId = plist[i].getProcId();
        //check if process already executed for preemptive scheduling then skip it
        if ( r.count(pId) == 0) {
            //if not set initial response time to 0
            r[pId]=0;
        } else {
            currentTime += plist[i].getCpuBurst();
            continue;
        }
        //find original arrival time
        auto originalProcess = find_if(processesList.begin(), processesList.end(), [&pId](const process& obj) {return obj.getProcId() == pId;});
        //if id is not defined for any reason -> crash
        if (originalProcess == processesList.end()){
            std::cout<<"Unexpected error happened";
            exit(1);
        }
        int arrivalTime = originalProcess->getArrivalTime();
        r[pId] = currentTime - arrivalTime;
        currentTime += plist[i].getCpuBurst();
        //skip idle intervals
        if (i + 1 < plist.size() && currentTime < plist[i + 1].getArrivalTime())
            currentTime = plist[i + 1].getArrivalTime();
    }
    std::map<int, int>::iterator it;
    return r ;
}

/**
 * calculates the response time for each process individually
 *
 * @param plist: scheduled process list
 * @param processesList:  original process list
 * @returns A map of process id as key and Turnaround time.
 */
std::map<int, int> turnAroundTime(std::vector<process> plist, std::vector<process> &processesList) {
    //Turnaround time = End time - Arrival time
    //we want to find End time
    std::map<int, int> turnAroundTime;

    for(int i = 0; i < plist.size(); i++) {
        int pId = plist[i].getProcId();
        if ( turnAroundTime.count(pId) == 0) {
            turnAroundTime[pId]=0;
        } else {
            continue;
        }
        //find original arrival time
        auto originalProcess = find_if(processesList.begin(), processesList.end(), [&pId](const process& obj) {return obj.getProcId() == pId;});
        //if id is not defined for any reason -> crash
        if (originalProcess == processesList.end()){
            std::cout<<"Unexpected error happened";
            exit(1);
        }
        int arrivalTime =originalProcess->getArrivalTime();

        //find exist time
        int currentTime = plist[0].getArrivalTime();
        int exitTime = arrivalTime + originalProcess ->getCpuBurst();
        // check if process excuted after first time for preemptive scheduling.
        for(int j = 0; j < plist.size(); j++){
            currentTime += plist[j].getCpuBurst();
            if(plist[j].getProcId()==pId){
                exitTime = currentTime;
            }
            //skip Idle periods
            if (j + 1 < plist.size() && currentTime < plist[j + 1].getArrivalTime())
                currentTime = plist[j + 1].getArrivalTime();
        }
        turnAroundTime[pId]= exitTime - arrivalTime;
    }
    return turnAroundTime ;
}

/**
 * calculates the throughput for interval specified by THROUGHPUT_TIME
 *
 * @param plist: scheduled process list
 * @param processesList:  original process list
 * @returns throughput.
 */
int throughput(std::vector<process> plist, std::vector<process> &processesList) {
    const int THROUGHPUT_TIME = 10;
    //init
    int throughput =0;
    //scanning interval
    int interval = plist[0].getArrivalTime() + THROUGHPUT_TIME;
    int currentTime = plist[0].getArrivalTime();
    int index = 0 ;
    while(currentTime <= interval){
       auto activeProcess = plist[index++];
       if(currentTime + activeProcess.getRemExecTime() <= interval){
           throughput++;
       }
        currentTime += activeProcess.getRemExecTime();
       //skip idle intervals
        if (index + 1 < plist.size() && currentTime < plist[index + 1].getArrivalTime())
            currentTime = plist[index + 1].getArrivalTime();
    }
    return throughput ;
}
