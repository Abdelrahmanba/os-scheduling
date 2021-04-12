#include <iostream>
#include <vector>
#include <random>
#define NOMINMAX
#include <Windows.h>
#include "functions.h"
#include "textTable.h"


#define MAX_NUM_PROC 20

using namespace std;

class process {
private:
    int proc_id;
    int cpuBurst;
    int arrivalTime;
    int staticPriority;
    int RemExecTime;
public:
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
        const int MAX_ARRIVAL_TIME = 10;
        const int MAX_CPU_BURST_TIME = 15;
        const int MAX_PRIORITY_NO = 5;
        proc_id = id;
        cpuBurst = (rand() % MAX_CPU_BURST_TIME) + 1;
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
    cout << "4. Schedule by using Priority scheduling" << endl;
    cout << "5. Schedule by using RR scheduling" << endl;
    cout << "6. Schedule by using Priority scheduling with RR." << endl;
    cout << "7. Run all scheduling algorithms." << endl << endl;
    cout << "*************************************************************" << endl;
    readChoice();
}

void ScheduleFCFS() {
    vector<process> FCFS = processesList;
    sort(FCFS.begin(), FCFS.end(), [](auto &&l, auto &&r) { return l.getArrivalTime() < r.getArrivalTime(); });
    printTimeline(FCFS);
    readChoice();
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
            break;
        case 4:
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

void printTimeline(vector<process> plist) {
    int totalTime = plist[0].getArrivalTime();
    int activeBurst = plist[0].getArrivalTime() + plist[0].getCpuBurst();
    int activeProcess = 0;
    //calculate Timeline Length
    for (auto p : processesList) {
        totalTime += p.getCpuBurst();
    }
    //starting Point
    int i = plist[0].getArrivalTime();
    setShellColor(plist[activeProcess].getProcId());

    cout << char(194) << i << " ms" << "\t";
    cout << "P"<< plist[activeProcess].getProcId() << endl;

    for (i; i < totalTime; i++) {
        if (plist[0].getArrivalTime() <= i && i< activeBurst) {
            cout << char(179)  << "\t";
            cout << "P"<< plist[activeProcess].getProcId() << endl;
            setShellColor(plist[activeProcess].getProcId());
            cout << char(195) << i + 1 << " ms" << "\t";
            cout << "P"<< plist[activeProcess].getProcId() << endl;
        } else if (i == activeBurst) {
            if (activeProcess + 1 < plist.size())
                activeProcess++;
            setShellColor(plist[activeProcess].getProcId());
            cout << char(179)  << "\t";
            cout << "P"<< plist[activeProcess].getProcId() << endl;
            cout << char(195) << i + 1 << " ms" << "\t";
            cout << "P"<< plist[activeProcess].getProcId() << endl;
            if (activeProcess < plist.size())
                activeBurst += plist[activeProcess].getCpuBurst();
        }
    }
    setShellColor(15);
    cout << char(179) << "\t"<< endl;
    cout << char(193) << i + 1 << " ms" << "\t"<< endl;
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



