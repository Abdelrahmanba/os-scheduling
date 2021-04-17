#include <iostream>
#include <map>
#include "../include/textTable.h" //lib to print pretty tables in console

#include "../include/schedulingFunctions.h"
#include "../include/helperFunctions.h"
#include "../include/metrics.h"


#ifdef _WIN32
#define NOMINMAX //used to ignore MAX defined in Windows.h
#include <windows.h>


/**
 * sets the consle tect color based on ANSI
 *
 * @param color:the int value of the color
 *              15 : white, 1:dark blue ..
 */
void setShellColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);

}


#else


/**
 * sets the consle tect color based on ANSI
 *
 * @param color:the int value of the color
 *              15 : white, 1:dark blue ..
 */
void setShellColor(int color) {
    std::map<int,std::string> colorMap;
    colorMap[1]="\033[0;34m";
    colorMap[2]="\033[0;32m";
    colorMap[3]="\033[0;36m";
    colorMap[4]="\033[0;31m";
    colorMap[5]="\033[0;35m";
    colorMap[6]="\033[0;33m";
    colorMap[7]="\033[0;37m";
    colorMap[8]="\033[1;30m";
    colorMap[9]="\033[1;34m";
    colorMap[10]="\033[1;32m";
    colorMap[11]="\033[1;36m";
    colorMap[8]="\033[1;31m";
    colorMap[9]="\033[1;35m";
    colorMap[10]="\033[1;33m";
    colorMap[11]="\033[1;37m";


        std::cout << colorMap[color] ;

    }


#endif


/**
 * helper function to read and validate an integer input
 *
 * @param min:  minimum allowed value.
 * @param max:  maximum allowed value.
 * @param inputMassage:  massage to show before inputing.
 * @returns the value that was read.
 */
int readIntInput(int min, int max, std::string inputMassage) {
    int input;
    bool valid = false;
    //read
    do {
        std::cout << inputMassage << "[" << min << "-" << max << "]:";
        std::cin >> input;
        //Validation
        if (std::cin.good() && input >= min && input <= max) {
            valid = true;
        } else {
            //bad format.. reset buffer
            std::cin.clear();
            //and empty it
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input!" << std::endl;
        }
    } while (!valid);
    std::cout << std::endl;
    return input;
}

/**
 * prints menu of operations.
 */
void showMenu() {
    using namespace std;
    cout << "*************************************************************" << endl;
    cout << "1. Show process set" << endl;
    cout << "2. Schedule by using FCFS" << endl;
    cout << "3. Schedule by using SJF" << endl;
    cout << "4. Schedule by using RR scheduling" << endl;
    cout << "5. Schedule by using Priority scheduling" << endl;
    cout << "6. Schedule by using Priority scheduling with RR." << endl;
    cout << "7. Run all scheduling algorithms." << endl;
    cout << "8. Exit." << endl << endl;
    cout << "*************************************************************" << endl;
}

/**
 * creates list of processes with random data.
 *
 * @param noOfProcesses:  the number of proccess to be created.
 * @returns A Vector of created processes.
 */
std::vector<process> createProcess(int noOfProcesses) {
    std::vector<process> processesList;
    for (int i = 1; i <= noOfProcesses; i++) {
        process *p = new process(i);
        processesList.push_back(*p);
    }

//    process *p = new process(1,6,2,3);
//    processesList.push_back(*p);
//
//    p = new process(2,8,2,2);
//    processesList.push_back(*p);
//
//    p = new process(3,7,0,5);
//    processesList.push_back(*p);
//
//    p = new process(4,8,8,5);
//    processesList.push_back(*p);


    std::cout << noOfProcesses << " processes were created successfully" << std::endl;
    return processesList;
}

/**
 * creates list of processes with random data.
 *
 * @param processesList:  Reference to the processes list on which the operations will be applied.
 */
void readChoice(std::vector<process> &processesList) {
    using namespace std;
    bool running = true;
    vector<process> FCFS, SJF, Priority, RR, PriorityRR;
    while (running) {
        int choice;
        choice = readIntInput(1, 8, "choice ");
        switch (choice) {
            case 1:
                showProcessesSet(processesList);
                break;
            case 2:
                FCFS = ScheduleFCFS(processesList);
                printTimeline(FCFS);
                showMetrics(FCFS, processesList, "FCFS");
                break;
            case 3:
                SJF = ScheduleSJF(processesList);
                printTimeline(SJF);
                showMetrics(SJF, processesList, "SJF");

                break;
            case 4:
                RR = ScheduleRR(processesList);
                printTimeline(RR);
                showMetrics(RR, processesList, "Round Roben");
                break;
            case 5:
                Priority = SchedulePriority(processesList);
                printTimeline(Priority);
                showMetrics(Priority, processesList, "Priority");
                break;
            case 6:
                PriorityRR = SchedulePriorityWithRR(processesList);
                printTimeline(PriorityRR);
                showMetrics(PriorityRR, processesList, "Priority with RR");
                break;
            case 7:
                FCFS = ScheduleFCFS(processesList);
                SJF = ScheduleSJF(processesList);
                RR = ScheduleRR(processesList);
                Priority = SchedulePriority(processesList);
                PriorityRR = SchedulePriorityWithRR(processesList);
                showMetrics(FCFS, processesList, "FCFS");
                showMetrics(SJF, processesList, "SJF");
                showMetrics(RR, processesList, "Round Roben");
                showMetrics(Priority, processesList, "Priority");
                showMetrics(PriorityRR, processesList, "Priority with RR");
                break;
            case 8:
                //exit
                running = false;
        }
    }
}

/**
 * Prints the list of processes .
 *
 * @param processesList:  Reference to the processes vector to be shown.
 */
void showProcessesSet(std::vector<process> &processesList) {
    samilton::ConsoleTable table(1, 1, samilton::Alignment::centre);
    table[0][0] = "Process ID";
    table[0][1] = "Arrival Time";
    table[0][2] = "CPU Burst";
    table[0][3] = "Priority";

    for (int i = 0; i < processesList.size(); i++) {
        table[i + 1][0] = std::to_string(processesList[i].getProcId());
        table[i + 1][1] = std::to_string(processesList[i].getArrivalTime()) + " ms";
        table[i + 1][2] = std::to_string(processesList[i].getCpuBurst()) + " ms";
        table[i + 1][3] = std::to_string(processesList[i].getStaticPriority());
    }
    std::cout << table;
}

/**
 * Prints process timeline.
 * used after scheduling is ready.
 * @param plist: the scheduled list of processes
 */
//print process timeline
//used after scheduling is ready
void printTimeline(std::vector<process> plist) {
    using namespace std;
    //set current time to first process arrival time
    int currentTime = plist[0].getArrivalTime();
    //print timeline header
    setShellColor(plist[0].getProcId());
    cout << char(194) << plist[0].getArrivalTime() << " ms" << "\t";
    cout << "P" << plist[0].getProcId() << endl;

    for (int i = 0; i < plist.size(); i++) {
        //print process (or slice)
        currentTime = ejectProcess(plist[i].getProcId(), currentTime, plist[i].getCpuBurst());
        //check for idle intervals
        if (i + 1 < plist.size() && currentTime < plist[i + 1].getArrivalTime())
            //print idle
            currentTime = ejectIdle(currentTime, plist[i + 1].getArrivalTime() - currentTime);
    }

    //rest color to white
    setShellColor(15);
    //print footer
    cout << char(179) << "\t" << endl;
    cout << char(193) << currentTime + 1 << " ms" << "\t" << endl;
}

//helper function used by printTimeline to print process intervals
int ejectProcess(int procID, int startTime, int cpuBurst) {
    using namespace std;
    setShellColor(procID);
    for (int i = startTime; i < startTime + cpuBurst; i++) {
        cout << char(179) << "\t" << "P" << procID << endl;
        cout << char(195) << i + 1 << " ms" << "\t" << "P" << procID << endl;;
    }
    //return current time
    return startTime + cpuBurst;
}

//helper function used by printTimeline to print idle intervals
int ejectIdle(int startTime, int endTime) {
    using namespace std;
    setShellColor(15);
    for (int i = startTime; i < startTime + endTime; i++) {
        cout << char(179) << "\t" << "idle" << endl;
        cout << char(195) << i + 1 << " ms" << "\t" << "idle" << endl;;
    }
    //return current time
    return startTime + endTime;
}

/**
 * Prints a table of metrics for a specific algorithm
 *
 * @param plist:  scheduled process list.
 * @param processesList:  Reference to the original process set.
 * @param name:  Name of the algorithm.
 *
 */
void showMetrics(std::vector<process> plist, std::vector<process> &processesList, std::string name) {
    //init table
    samilton::ConsoleTable table(1, 1, samilton::Alignment::centre);
    //init array of maps
    std::map<int, int> metrics[3];
    metrics[0] = responseTime(plist, processesList);
    metrics[1] = turnAroundTime(plist, processesList);
    metrics[2] = waitingTime(processesList, metrics[1]);
    int throughputVal = throughput(plist, processesList);

    int index = 1;
    //to find min,max and avg
    for (auto metric : metrics) {
        double min = INT32_MAX, max = 0, avg = 0;
        for (auto currentEntry = metric.begin(); currentEntry != metric.end(); ++currentEntry) {
            if (currentEntry->second > max) {
                max = currentEntry->second;
            }
            if (currentEntry->second < min) {
                min = currentEntry->second;
            }
            avg += currentEntry->second;
        }
        avg /= metric.size();
        table[index][1] = min;
        table[index][2] = avg;
        table[index++][3] = max;
    }
    table[4][2] = std::to_string(throughputVal) + "per 10ms";


    table[0][0] = name;
    table[0][1] = "Minimum";
    table[0][2] = "Average";
    table[0][3] = "Maximum";

    table[1][0] = "Response time";
    table[2][0] = "Turnaround time";
    table[3][0] = "Waiting time";
    table[4][0] = "The throughput";


    std::cout << table;
}

