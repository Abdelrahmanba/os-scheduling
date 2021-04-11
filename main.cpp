#include <iostream>
#define MAX_NUM_PROC 20
using namespace std;

int readProcess(){
    int noOfProcess;
    bool valid= false;
    //read
    do
    {
        cout << "Please enter the number of process you want to create [1-" << MAX_NUM_PROC << "]:" << endl;
        cin >> noOfProcess;
        //Validation
        if (cin.good() && noOfProcess > 0 && noOfProcess < MAX_NUM_PROC)
        {
            valid = true;
        }
        else
        {
            //bad format.. reset buffer
            cin.clear();
            //and empty it
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input!" << endl;
        }
    } while (!valid);
    return noOfProcess;
}

int main() {
    int noOfProcess;
    noOfProcess = readProcess();

    return 0;
}
