#include <algorithm>
#include "helperFunctions.h"
#include "schedulingFunctions.h"

using namespace std;

vector<process> ScheduleFCFS(std::vector<process>& processesList) {
    vector<process> FCFS = processesList;
    sort(FCFS.begin(), FCFS.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    return FCFS;
}

vector<process> ScheduleSJF(std::vector<process>& processesList) {
    vector<process> SJF = processesList;
    //sort based on arrival time
    vector<process> executed, available;
    sort(SJF.begin(), SJF.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    //get all available processes at the beginning
    int currentTime = 0;
    while (executed.size() < processesList.size()) {
        //find all available processes
        for (int i = 0; i < SJF.size(); i++) {
            if (SJF[i].getArrivalTime() <= currentTime) {
                available.push_back(SJF[i]);
            }
        }
        if (available.size() == 0) {
            currentTime += 1;
            continue;
        }
        sort(available.begin(), available.end(), [](auto &&l, auto &&r) { return l.getCpuBurst() < r.getCpuBurst(); });
        executed.push_back(available[0]);
        SJF.erase(remove_if(SJF.begin(), SJF.end(),
                            [=](process &p) { return p.getProcId() == available[0].getProcId(); }), SJF.end());

        currentTime += available[0].getCpuBurst();
        available.clear();
    }
    return executed;

}

vector<process> ScheduleRR(std::vector<process>& processesList) {
    const int TIME_SLICE = 4;
    vector<process> RR = processesList;
    vector<process> slices;
    //sort based on arrival time
    sort(RR.begin(), RR.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    //init max
    int currentTime = RR[0].getArrivalTime();
    int maxRemTime = RR[0].getRemExecTime(); //10
    bool skipDueNotAvailable = false;
    while (maxRemTime != 0) {
        maxRemTime = 0;
        for (int i = 0; i < RR.size(); i++) {
            if (RR[i].getRemExecTime() >= maxRemTime) {
                maxRemTime = RR[i].getRemExecTime();
            }
            if (RR[i].getArrivalTime() <= currentTime) {
                if (RR[i].getRemExecTime() > TIME_SLICE) {
                    process slice (RR[i].getProcId(), currentTime, TIME_SLICE);
                    slices.push_back(slice);
                    RR[i].setRemExecTime(RR[i].getRemExecTime() - TIME_SLICE);
                    slice.setRemExecTime(RR[i].getRemExecTime());
                    currentTime += TIME_SLICE;
                } else if (RR[i].getRemExecTime() <= TIME_SLICE && RR[i].getRemExecTime() > 0) {
                    process slice(RR[i].getProcId(), currentTime, RR[i].getRemExecTime());
                    slices.push_back(slice);
                    currentTime += RR[i].getRemExecTime();
                    RR[i].setRemExecTime(0);
                    slice.setRemExecTime(0);
                }

            }
        }
        skipDueNotAvailable = true;
        for (int i = 0; i < RR.size(); i++) {
            if (RR[i].getArrivalTime() <= currentTime && RR[i].getRemExecTime() > 0) {
                skipDueNotAvailable = false;
                break;
            }
        }
        if (skipDueNotAvailable) {
            currentTime += 1;
        }
    }
    return slices;
}

vector<process> SchedulePriority(std::vector<process>& processesList) {
    vector<process> priority = processesList;
    vector<process> executed;
    //sort based on arrival time
    sort(priority.begin(), priority.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    //sort by priority
    vector <vector<process>> priorities= sortPriorities(priority);
    int currentTime = priority[0].getArrivalTime();
    process *activeProcess = &priority[0];
    int activeProcessPriority = -1;
    while (executed.size() < processesList.size()) {
        for (int i = 1; i <= 5; i++) {
            if (priorities[i].size()) {
                if (priorities[i][0].getArrivalTime() <= currentTime) {
                    activeProcess = &priorities[i][0];
                    activeProcessPriority = i;
                }
            }
        }
        if (activeProcess == nullptr) {
            currentTime += 1;
            continue;
        }
        executed.push_back(*activeProcess);
        currentTime += activeProcess->getCpuBurst();
        priorities[activeProcessPriority].erase(priorities[activeProcessPriority].begin());
        activeProcessPriority = -1;
        activeProcess = nullptr;
    }
    return executed;

}

vector<process> SchedulePriorityWithRR(std::vector<process>& processesList) {
    const int TIME_SLICE = 4;
    vector<process> priorityRR = processesList;
    vector<process> slices;
    //sort based on arrival time
    sort(priorityRR.begin(), priorityRR.end(),[](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    vector<vector<process>> priorities = sortPriorities(priorityRR);
    int currentTime = priorityRR[0].getArrivalTime();
    process *activeProcess = &priorityRR[0];
    int activeProcessPriority = -1;
    while (true) {
        bool empty = true;
        activeProcessPriority = -1;
        for (int i = 1; i <= 5; i++) {
            if (!priorities[i].empty()) {
                if (priorities[i][0].getArrivalTime() <= currentTime) {
                    activeProcess = &priorities[i][0];
                    activeProcessPriority = i;
                }
            }
        }
        if (activeProcess == nullptr) {
            currentTime += 1;
            continue;
        }

        if (activeProcess->getRemExecTime() > TIME_SLICE) {
            process s(activeProcess->getProcId(), currentTime, TIME_SLICE);
            slices.push_back(s);
            activeProcess->setRemExecTime(activeProcess->getRemExecTime() - TIME_SLICE);
            s.setRemExecTime(activeProcess->getRemExecTime());

            currentTime += TIME_SLICE;
            int newIndex;
            for (newIndex = 0; newIndex < priorities[activeProcessPriority].size(); newIndex++) {
                if(priorities[activeProcessPriority][newIndex].getArrivalTime() > currentTime )
                    break;
            }
            newIndex --;
            rotate(priorities[activeProcessPriority].begin(), priorities[activeProcessPriority].begin() + 1, priorities[activeProcessPriority].begin() + newIndex + 1);
        } else if (activeProcess->getRemExecTime() <= TIME_SLICE && activeProcess->getRemExecTime() > 0) {
            process s(activeProcess->getProcId(), currentTime, activeProcess->getRemExecTime());
            slices.push_back(s);
            currentTime += activeProcess->getRemExecTime();
            activeProcess->setRemExecTime(0);
            s.setRemExecTime(0);
            auto it = priorities[activeProcessPriority].begin();
            priorities[activeProcessPriority].erase(it);
        }

        for (int i = 1; i <= 5; i++) {
            if (priorities[i].size()!=0) {
                empty = false;
            }
        }
        if(empty)
            break;
        activeProcess = nullptr;
    }
    return slices;
}

//helper function to sort each process to different arrays based on its priority
vector <vector<process>> sortPriorities(vector<process> &priority) {
    vector<std::vector<process>> priorities(6);
    for (process p : priority) {
        switch (p.getStaticPriority()) {
            case 1:
                priorities[1].push_back(p);
                break;
            case 2:
                priorities[2].push_back(p);
                break;
            case 3:
                priorities[3].push_back(p);
                break;
            case 4:
                priorities[4].push_back(p);
                break;
            case 5:
                priorities[5].push_back(p);
                break;
        }
    }
    return priorities;
}
