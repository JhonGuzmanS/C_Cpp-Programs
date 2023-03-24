#include <iostream>
using namespace std;

struct Process
{
	int jid;
	int size;
	string status = "wait";
	int pid = 0;

};

struct Partition 
{
	int pid;
	int size;
	bool isUsed = false;
	int jid = 0;
};

void inputInfo(Partition *partition[], Process *jobs[], int &part_size, int &proc_size);

int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size);

int firstFit(Partition partition[], Process jobs[], int part_size, int proc_size);

int nextFit(Partition partition[], Process jobs[], int part_size, int proc_size);

void  printAlg(string alg, Partition partition[], Process jobs[], int proc_size) {
	cout << "____________________ " << alg << " ____________________" << endl;
	cout << "Job ID \t\t Partition ID \t\t Waste \t\t Status" << endl;
	for (int i = 0; i < proc_size; i++) {
		cout << jobs[i].jid << "\t\t\t" << jobs[i].pid << "\t\t    " << 0 << "\t\t   " << jobs[i].status << endl;
	}
}


int main() {
// start of main, should ask for number of partitions and jobs then ask for the size
	Process lists[10];
	Partition process[10];
	int part_size;
	int proc_size;
	Partition tempP;
	cout << "Number of partitions: ";
	cin >> part_size;
	const int temp = part_size;
	for (int i = 0; i < part_size; i++) {
		cout << "Size:";
		cin >> tempP.size;
		tempP.pid = i + 1;
		process[i] = tempP;
	}
	
	Process tempJ;
	cout << "Number of processes: ";
	cin >> proc_size;
	for (int i = 0; i < proc_size; i++) {
		cout << "Size:";
		cin >> tempJ.size;
		tempJ.jid = i + 1;
		lists[i] = tempJ;

	}
	nextFit(process, lists, part_size, proc_size);
	return 0;
}



// Inserts job into a partition that is equal(recommended) if not greater in size 
int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	int best_index = 0;
	for (int i = 0; i < proc_size; i++) {
		for (int j = 0; j < part_size; j++) {
			if (jobs[i].size == partition[j].size && partition[j].isUsed == false) {
				cout << jobs[i].jid << " : " << partition[j].pid << " : " << partition[j].isUsed << endl;
				jobs[i].status = "running";
				jobs[i].pid = partition[j].pid;
				partition[j].isUsed = true;
				break;
			}
			else if (jobs[i].size < partition[j].size && partition[j].isUsed == false) {
				if (best_index == 0) {
					best_index = j;
				}
				else if (partition[best_index].size > partition[j].size) {
					best_index = j;
				}
			}
		}
	}
	printAlg("BestFIt", partition, jobs, proc_size);
	return 0;
};

// Inserts job into the first partition that it sees if job fits 
int firstFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	for (int i = 0; i < proc_size; i++) {
		for (int j = 0; j < part_size; j++) {
			if (jobs[i].size <= partition[j].size && partition[j].isUsed == false) {
				cout << jobs[i].jid << " : " << partition[j].pid << " : " << partition[j].isUsed << endl;
				jobs[i].status = "running";
				jobs[i].pid = partition[j].pid;
				partition[j].isUsed = true;
				break;
			}
		}
	}
	printAlg("FirstFIt", partition, jobs, proc_size);
	return 0;
}

// Saves position of partition, inserting job into partition that fits
int nextFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	int position = 0;
	for (int i = 0; i < proc_size; i++) {
		for (int j = 0; j < part_size; j++) {
			if (position != 0) {
				j += position;
				position = 0;
			}
			if (jobs[i].size <= partition[j].size && partition[j].isUsed == false) {
				cout << jobs[i].jid << " : " << partition[j].pid << " : " << partition[j].isUsed << endl;
				jobs[i].status = "running";
				jobs[i].pid = partition[j].pid;
				partition[j].isUsed = true;
				position = j;
				break;
			}
		}
	}
	printAlg("NextFIt", partition, jobs, proc_size);
	return 0;
}

// Inserts job into the biggest partition
int worstFit() {
	return 0;
}
