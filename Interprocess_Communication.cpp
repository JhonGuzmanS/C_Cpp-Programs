#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main() {
    int fd1[2], fd2[2];
    int N;
    cout << "Enter in a number: ";
    cin >> N;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "Failed to create pipes." << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Failed to fork." << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        close(fd1[1]);
        close(fd2[0]);

        int sum = 0;
        int value;
        while (read(fd1[0], &value, sizeof(value))) {}

        cout << "Child reads: " << value << " from Parent" << endl;
        
        // compute partial sum of (N/2) to N
        for(int i = value; i <= N; i++){
            sum += i;
        }
        write(fd2[1], &sum, sizeof(sum));

        // Close used pipe ends
        close(fd1[0]);
        close(fd2[1]);

        return 0;
    } else {
        // Parent process
        close(fd1[0]);
        close(fd2[1]);
        
        int partial_sum = 0;
        int n = N / 2;
        write(fd1[1], &n, sizeof(n));
        close(fd1[1]);
        
        int child_sum;
        read(fd2[0], &child_sum, sizeof(child_sum));
        cout << "Parent reads: " << child_sum << " from child" << endl;
        
        // Computes partial sum of 1 to (N/2 - 1)
        for (int i = 1; i < n; i++){
            partial_sum += i;
        }

        int total_sum = partial_sum + child_sum;
        cout << "The partial sum of 1 through " << N << " is " << total_sum << endl;

        // Close used pipe ends
        close(fd2[0]);

        return 0;
    }
}
