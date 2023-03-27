#include <iostream>
using namespace std;

struct Process
{
	int jid;
	int size;
	string status = "wait";
	int pid = -1;

};

struct Partition 
{
	int pid;
	int size;
	bool isUsed = false;
	int jid = 0;
};

int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size);

int firstFit(Partition partition[], Process jobs[], int part_size, int proc_size);

int nextFit(Partition partition[], Process jobs[], int part_size, int proc_size);

int worstFit(Partition partition[], Process jobs[], int part_size, int proc_size);

void  printAlg(string alg, Partition partition[], Process jobs[], int proc_size) {
	int num = 0;
	int diff = 0;
	cout << "______________________________ " << alg << " ______________________________" << endl;
	cout << "Job ID \t\t Partition ID \t\t Waste \t\t Status" << endl;
	for (int i = 0; i < proc_size; i++) {
		num = jobs[i].pid;
		if(num < 0){
			diff = 0;
		}else{
			diff = partition[num - 1].size - jobs[i].size;
		}
		cout << jobs[i].jid << "\t\t\t" << jobs[i].pid << "\t\t  " << diff << "\t\t  " << jobs[i].status << endl;
	}
	cout << endl;
}


int main() {
	Process lists[10];
	Partition partitions[10];
	int part_size;
	int proc_size;

	Partition tempP;
	cout << "Number of partitions: ";
	cin >> part_size;
	for (int i = 0; i < part_size; i++) {
		cout << "Size:";
		cin >> tempP.size;
		tempP.pid = i + 1;
		partitions[i] = tempP;
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
	bestFit(partitions, lists, part_size, proc_size);
	firstFit(partitions, lists, part_size, proc_size);
	worstFit(partitions, lists, part_size, proc_size);
	nextFit(partitions, lists, part_size, proc_size);
	return 0;
}



// Inserts job into a partition that is equal(recommended) if not greater in size 
int bestFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	int best_index;
	for (int i = 0; i < proc_size; i++) {
		best_index = -1;
		for (int j = 0; j < part_size; j++) {
			if (jobs[i].size == partition[j].size && partition[j].isUsed == false) {
				jobs[i].status = "running";
				jobs[i].pid = partition[j].pid;
				partition[j].isUsed = true;
				best_index = -1;
				break;
			}
			else if (jobs[i].size < partition[j].size && partition[j].isUsed == false) {
				if (best_index < 0) {
					best_index = j;
				}
				else if (partition[best_index].size > partition[j].size) {
					best_index = j;
				}
			}
		}
		if(best_index > -1){
			jobs[i].status = "running";
			jobs[i].pid = partition[best_index].pid;
			partition[best_index].isUsed = true;
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
				jobs[i].status = "running";
				jobs[i].pid = partition[j].pid;
				partition[j].isUsed = true;
				position = j;
				break;
			}
		}
	}
	printAlg("NextFit", partition, jobs, proc_size);
	return 0;
}

// Inserts job into the biggest partition
int worstFit(Partition partition[], Process jobs[], int part_size, int proc_size) {
	int worst_index;
	for (int i = 0; i < proc_size; i++) {
		worst_index = -1;
		for (int j = 0; j < part_size; j++) {
			if(!partition[j].isUsed){
				if(jobs[i].size <= partition[j].size){
					if(worst_index < 0){
						worst_index = j;
					}
					else if(partition[j].size > partition[worst_index].size){
						worst_index = j;
					}
				}
			}
		}
		if(worst_index > -1){
			jobs[i].status = "running";
			jobs[i].pid = partition[worst_index].pid;
			partition[worst_index].isUsed = true;
		}
		
	}
	printAlg("WorstFIt", partition, jobs, proc_size);
	return 0;
}
