#include <iostream>
#include <vector>
#include <random>

#define NOMINMAX

#include <Windows.h>
#include "functions.h"
#include "textTable.h"


#define MAX_NUM_PROC 20

using namespace std;

class slice {
public:
    int getArrivalTime() const {
        return arrivalTime;
    }

    int getProcId() const {
        return proc_id;
    }

    int getCpuBurst() const {
        return cpuBurst;
    }

private:
    int arrivalTime;
    int cpuBurst;
    int proc_id;
public:


    slice(int proc_id, int arrivalTime, int runPeriod) {
        this->proc_id = proc_id;
        this->cpuBurst = runPeriod;
        this->arrivalTime = arrivalTime;
    }
};


class process {
private:
    int proc_id;
    int cpuBurst;
    int arrivalTime;
    int staticPriority;
    int RemExecTime;
public:
    void setRemExecTime(int remExecTime) {
        RemExecTime = remExecTime;
    }

    int getProcId() const {
        return proc_id;
    }

    int getCpuBurst() const {
        return cpuBurst;
    }

    int getArrivalTime() const {
        return arrivalTime;
    }

    int getStaticPriority() const {
        return staticPriority;
    }

    int getRemExecTime() const {
        return RemExecTime;
    }

    process(int id) {
        const int MAX_ARRIVAL_TIME = 40;
        const int MAX_CPU_BURST_TIME = 10;
        const int MAX_PRIORITY_NO = 5;
        proc_id = id;
        cpuBurst = RemExecTime = (rand() % MAX_CPU_BURST_TIME) + 1;
        arrivalTime = rand() % (MAX_ARRIVAL_TIME + 1);
        staticPriority = (rand() % MAX_PRIORITY_NO) + 1;

    }
};

void readChoice();

vector<process> processesList;


void showMenu() {
    cout << "*************************************************************" << endl;
    cout << "1. Show process set" << endl;
    cout << "2. Schedule by using FCFS" << endl;
    cout << "3. Schedule by using SJF" << endl;
    cout << "4. Schedule by using RR scheduling" << endl;
    cout << "5. Schedule by using Priority scheduling" << endl;
    cout << "6. Schedule by using Priority scheduling with RR." << endl;
    cout << "7. Run all scheduling algorithms." << endl << endl;
    cout << "*************************************************************" << endl;
    readChoice();
}

void ScheduleFCFS() {
    vector<process> FCFS = processesList;
    sort(FCFS.begin(), FCFS.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    printTimeline(FCFS);
}

void ScheduleSJF() {
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
                            [=](const process &p) { return p.getProcId() == available[0].getProcId(); }), SJF.end());

        currentTime += available[0].getCpuBurst();
        available.clear();
    }

    printTimeline(executed);
}

void ScheduleRR() {
    const int TIME_SLICE = 4;
    vector<process> RR = processesList;
    vector<slice> slices;
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
                    slice s(RR[i].getProcId(), currentTime, TIME_SLICE);
                    slices.push_back(s);
                    RR[i].setRemExecTime(RR[i].getRemExecTime() - TIME_SLICE);
                    currentTime += TIME_SLICE;
                } else if (RR[i].getRemExecTime() <= TIME_SLICE && RR[i].getRemExecTime() > 0) {
                    slice s(RR[i].getProcId(), currentTime, RR[i].getRemExecTime());
                    slices.push_back(s);
                    currentTime += RR[i].getRemExecTime();
                    RR[i].setRemExecTime(0);
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
        if(skipDueNotAvailable){
            currentTime += 1;
        }
    }
    printTimeline(slices);

}

void processChoice(int choice) {
    switch (choice) {
        case 1:
            showProcessesSet();
            break;
        case 2:
            ScheduleFCFS();
            break;
        case 3:
            ScheduleSJF();
            break;
        case 4:
            ScheduleRR();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

void showProcessesSet() {
    samilton::ConsoleTable table(1, 1, samilton::Alignment::centre);

    table[0][0] = "Process ID";
    table[0][1] = "Arrival Time";
    table[0][2] = "CPU Burst";
    table[0][3] = "Priority";

    for (int i = 0; i < processesList.size(); i++) {
//        setShellColor(i + 1);
        table[i + 1][0] = to_string(processesList[i].getProcId());
        table[i + 1][1] = to_string(processesList[i].getArrivalTime()) + " ms";
        table[i + 1][2] = to_string(processesList[i].getCpuBurst()) + " ms";
        table[i + 1][3] = to_string(processesList[i].getStaticPriority());
    }
    cout << table;
    readChoice();
}

void readChoice() {
    int choice;
    choice = readIntInput(1, 7, "choice ");
    processChoice(choice);
}

int readIntInput(int min, int max, string inputMassage) {
    int input;
    bool valid = false;
    //read
    do {
        cout << inputMassage << "[" << min << "-" << max << "]:";
        cin >> input;
        //Validation
        if (cin.good() && input >= min && input <= max) {
            valid = true;
        } else {
            //bad format.. reset buffer
            cin.clear();
            //and empty it
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl;
        }
    } while (!valid);
    cout << endl;

    return input;
}

vector<process> createProcess(int noOfProcesses) {
    vector<process> processesList;
    for (int i = 1; i <= noOfProcesses; i++) {
        process *p = new process(i);
        processesList.push_back(*p);
    }
    cout << noOfProcesses << " processes were created successfully" << endl;
    return processesList;
}

template<typename T>
void printTimeline(vector<T> plist) {
    int endTime = plist[0].getArrivalTime();
    setShellColor(plist[0].getProcId());
    cout << char(194) << plist[0].getArrivalTime() << " ms" << "\t";
    cout << "P" << plist[0].getProcId() << endl;
    for (int i = 0; i < plist.size(); i++) {
        endTime = ejectProcess(plist[i].getProcId(), endTime, plist[i].getCpuBurst());
        if (i + 1 < plist.size() && endTime < plist[i + 1].getArrivalTime())
            endTime = ejectIdle(endTime, plist[i + 1].getArrivalTime() - endTime);
    }

    setShellColor(15);
    cout << char(179) << "\t" << endl;
    cout << char(193) << endTime + 1 << " ms" << "\t" << endl;
    readChoice();
}

int ejectProcess(int procID, int startTime, int cpuBurst) {
    setShellColor(procID);
    for (int i = startTime; i < startTime + cpuBurst; i++) {
        cout << char(179) << "\t" << "P" << procID << endl;
        cout << char(195) << i + 1 << " ms" << "\t" << "P" << procID << endl;;
    }
    //return current time
    return startTime + cpuBurst;
}

int ejectIdle(int startTime, int endTime) {
    setShellColor(15);
    for (int i = startTime; i < startTime + endTime; i++) {
        cout << char(179) << "\t" << "idle" << endl;
        cout << char(195) << i + 1 << " ms" << "\t" << "idle" << endl;;
    }
    //return current time
    return startTime + endTime;
}

void setShellColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    int noOfProcesses;
    srand(time(0));
    noOfProcesses = readIntInput(1, MAX_NUM_PROC, "Please enter the number of process you want to create");
    processesList = createProcess(noOfProcesses);
    showMenu();
    return 0;
}



