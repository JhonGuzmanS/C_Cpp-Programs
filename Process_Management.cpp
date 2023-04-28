#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

/*
Use 3 Algorithms:
 First Come : non-preemptive
 Priority : preemptive
 Shortest Job Next : non-preemptive

For input:
 Time required for job execution
 Arrival Time
 Priority

Output:
 Starting Time for each process
 Completion Time for each process
 Turnaround Time for each process
 Average turnaround time
 Order of execution of processes

Note:
 Create a class/struct that will include:
  Name of process/job
  Job Priority
  Turnaround Time
  Sart Time 
  Completion Time
  Required Burst/Execution Time

*/

struct Process {
    int pid;
    int priority;
    int arrival_time;   
    int burst_time;     // run time
    int start_time;
    int time_remainder;
    int turnaround_time;    // completion - start time
    int completion_time; 

};

void FCFS(vector<Process>& processes);
void Priority(vector<Process>& processes);
void SJN(vector<Process>& processes);

int main() {
    vector<Process> processes = {
        {1, 3, 2, 3},
        {2, 2, 2, 4},
        {3, 1, 3, 1},
        {4, 3, 5, 2}
    };
    /*
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);
    
    for (int i = 0; i < num_processes; i++) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time ;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
        processes[i].pid = i + 1;
    }
    */

    //FCFS(processes);
    /*
    cout << "PID\tArrival\tBurst\tFinish\tTurnaround\n";
    for (auto& p : processes) {
        cout << p.pid << "\t" << p.start_time << "\t" << p.burst_time << "\t" << p.completion_time
            << "\t" << p.turnaround_time << endl;
    }
    */
    SJN(processes);
    cout << "PID\tStart\tBurst\tFinish\tTurnaround\n";
    for (auto& p : processes) {
        cout << p.pid << "\t" << p.start_time << "\t" << p.burst_time << "\t" << p.completion_time
            << "\t" << p.turnaround_time << "---" << p.arrival_time << endl;
    }
}

void FCFS(vector<Process>&processes) {
    int n = processes.size(); 
    int time = 0;  
    for (int i = 0; i < n; i++) {
        time = processes[i].arrival_time;

        // Execute process
        processes[i].start_time = time;
        processes[i].completion_time = time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        // Update current time
        time = processes[i].completion_time;
    }

}

void Priority(vector<Process>& processes) {
    int n = processes.size();
    int time = 0;
    int completed_processes = 0;
    int highest_priority;
    int index;
    
    for (int i = 0; i < n; i++) {
        processes[i].time_remainder = processes[i].burst_time;
        processes[i].start_time = 0;
    }

    while (completed_processes < n) {
        highest_priority = 1000;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].time_remainder > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    index = i;
                    
                }
            }
        }
        if (index >= 0) {
            if (processes[index].start_time == 0) {
                processes[index].start_time = time;
            }
            processes[index].time_remainder--;
            time++;
            if (processes[index].time_remainder == 0) {
                completed_processes++;
                processes[index].completion_time = time;
                processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
            }
        }
        else {
            time++;
        }

    }
}

void SJN(vector<Process>& processes) {
    int n = processes.size();
    int time = 0;
    int short_burst = 0;
    int index = -1;
    int completed_processes = 0;
    vector<int> arr_index(0);

    for (auto job : processes) {
        cout << job.pid << " ";
    }
}
