#ifndef SCHEDULING_ALGORITHMS_TESTBENCH_PROCESS_H
#define SCHEDULING_ALGORITHMS_TESTBENCH_PROCESS_H

class process {
private:
    int proc_id;
    int cpuBurst;
    int arrivalTime;
    int staticPriority;
    int remExecTime;
public:
    void setRemExecTime(int remExecTime);
    int getProcId() const;
    int getCpuBurst() const;
    int getArrivalTime() const;
    int getStaticPriority() const;
    int getRemExecTime();
    explicit process(int id);
    process(int proc_id, int arrivalTime, int runPeriod);

};


#endif //SCHEDULING_ALGORITHMS_TESTBENCH_PROCESS_H
