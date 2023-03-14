#include <iostream>
using namespace std;

struct Process
{
	int jid;
	int memory_needed;
	string status = "wait";
	int pid;

};

struct Partition 
{
	int pid;
	int size;
	bool isUsed = false;
	int jid;
};

void inputInfo(Partition *partition[], Process *jobs[], int &part_size, int &proc_size);

int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size);


int main() {

	Process lists[10];
	Partition process[10];
	int part_size = 3;
	int proc_size = 3;
	Partition tempP;
	for (int i = 0; i < part_size; i++) {
		cout << "Size:";
		cin >> tempP.size;
		tempP.pid = i + 1;
		process[i] = tempP;
	}
	for (int i = 0; i < part_size; i++) {
		cout << process[i].pid << endl;
	}
	
	return 0;
}



// Inserts job into a partition that is equal(recommended) if not greater in size 
int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	for (int i = 0; i < part_size; i++) {
		cout << partition[i].pid << endl;
	}
	for (int i = 0; i < proc_size; i++) {
		cout << jobs[i].jid << " " << jobs[i].status << endl;
	}
	return 0;
};

// Inserts job into the first partition that it sees if job fits 
int firstFit() {
	return 0;
}

// Saves position of partition, inserting job into partition that fits
int nextFit() {
	return 0;
}

// Inserts job into the biggest partition
int worstFit() {
	return 0;
}
