#include <iostream>
#include <map>
#include <vector>
#include "process.h"


std::map<int, int> waitingTime(std::vector<process> &processesList, std::map<int, int> turnAroundTime) {
    //Waiting time = Turnaround time - Burst time
    //we want to find End time
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

std::map<int, int> responseTime(std::vector<process> plist, std::vector<process> &processesList) {
    double singleResponseTime = 0;
    std::map<int,int> r;
    std::vector<int> processesId;
    int currentTime = plist[0].getArrivalTime();
    for(int i = 0; i < plist.size(); i++) {
        int pId = plist[i].getProcId();
        //check if process already executed
        if ( r.count(pId) == 0) {
            r[pId]=0;
        } else {
            continue;
        }
        //find original arrival time
        auto originalProcess = find_if(processesList.begin(), processesList.end(), [&pId](const process& obj) {return obj.getProcId() == pId;});
        if (originalProcess == processesList.end()){
            std::cout<<"Unexpected error happened";
            exit(1);
        }
        int arrivalTime =originalProcess->getArrivalTime();
        r[pId] = currentTime - arrivalTime;
        currentTime += plist[i].getCpuBurst();
        if (i + 1 < plist.size() && currentTime < plist[i + 1].getArrivalTime())
            currentTime = plist[i + 1].getArrivalTime();
    }
    std::map<int, int>::iterator it;
    return r ;
}

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

int throughput(std::vector<process> plist, std::vector<process> &processesList) {
    const int THROUGHPUT_TIME = 10;
    int throughput =0;
    int interval = plist[0].getArrivalTime() + THROUGHPUT_TIME;
    int currentTime = plist[0].getArrivalTime();
    int index = 0 ;
    while(currentTime <= interval){
       auto activeProcess = plist[index++];
       if(activeProcess.getRemExecTime() + currentTime <= interval){
           throughput++;
       }
        currentTime += activeProcess.getRemExecTime();
        if (index + 1 < plist.size() && currentTime < plist[index + 1].getArrivalTime())
            currentTime = plist[index + 1].getArrivalTime();
    }
    return throughput ;
}
