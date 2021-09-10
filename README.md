# Scheduling Algorithms Implemention & Testbench

An app that simulates most famous processes scheduling algorithms 

- Fisrt Come Fisrt Served
- Priority
- Priority With Round Roben
- Shortest Job Fisrt 
- Round Roben


## Project Structure

```
   |
   |-include : contains header files for source files
   |- src |- helperFunctions.cpp : contains functions to print, read input ..
          |- schedulingFunctions.cpp : contains the actual scheduling implementation
          |- metrics.cpp : contains function to calculate metrics of the algorithms
          |- textTable.h : external lib to print pretty tables
          |- process.cpp : process class implementation
   |- main.cpp : simple main to run the lib
```
## Getting Started

This is a cmake project for windows make sure to have cmake installed.

while you are in project directory:

FOR WINDOWS :

```
    $ mkdir build && cd build
    $ cmake ..
    $ cmake --build . --config Release
    $ ..\..\Scheduling_Algorithms_Testbench\build\Release\Scheduling_Algorithms_Testbench.exe
```
FOR LINUX:
* you must have g++, CMake, and libusb-1.0-dev installed on the machine.
* you can get them for ubuntu by these commands:
```
    $ sudo apt-get update
    $ sudo apt-get install cmake
    $ sudo apt-get install build-essential gdb
    $ sudo apt-get install libusb-1.0-0-dev
```
then:
```
    $ mkdir build && cd build
    $ cmake ..
    $ make
    $ ./Scheduling_Algorithms_Testbench
```   
## Screenshots


![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/1.PNG?raw=true)

![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/FCFS.PNG?raw=true)

![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/PRIORITY.PNG?raw=true)

![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/PRIORITY_WITH_RR.PNG?raw=true)

![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/RR.PNG?raw=true)

![alt text](https://github.com/Abdelrahmanba/os-scheduling/blob/main/SCREENSHOTS/SJF.PNG?raw=true)

