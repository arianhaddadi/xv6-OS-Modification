#include "types.h"
#include "user.h"
#include "utils.h"

#define MSG_SIZE 30
#define READ_INDEX 0
#define WRITE_INDEX 1


int main(void) {
    int pipe_p_to_c[2];
    int pipe_c_to_p[2];
    
    // Create a pipe
    if (pipe(pipe_p_to_c) < 0 || pipe(pipe_c_to_p) < 0) {
        printf(1, "Error creating the pipes\n");
        exit();
    }

    int pid = fork();

    if (pid < 0) printf(1, "Fork failed!\n");
    
    else if (pid > 0) {
        // Parent process
        char message[MSG_SIZE] = "Hello from parent!";
        char receivedMessage[MSG_SIZE];

        close(pipe_p_to_c[READ_INDEX]);
        close(pipe_c_to_p[WRITE_INDEX]);

        uint start = rdtsc();

        if (write(pipe_p_to_c[WRITE_INDEX], message, MSG_SIZE) != MSG_SIZE) {
            printf(1, "Error writing to pipe in parent process\n");
            exit();
        }
        
        if (read(pipe_c_to_p[READ_INDEX], receivedMessage, MSG_SIZE) != MSG_SIZE) {
            printf(1, "Error reading from pipe in parent process\n");
            exit();
        }
        
        // printf(1, "Parent received: %s\n", receivedMessage);

        close(pipe_p_to_c[WRITE_INDEX]);
        close(pipe_c_to_p[READ_INDEX]);

        uint end = rdtsc();

        printf(1, "Elapsed Time: %x\n", end - start);

        
        wait();
    } 
    else {
        // Child process
        char message[MSG_SIZE] = "Hello back from child!";
        char receivedMessage[MSG_SIZE];

        close(pipe_p_to_c[WRITE_INDEX]);
        close(pipe_c_to_p[READ_INDEX]);


        if (read(pipe_p_to_c[READ_INDEX], receivedMessage, MSG_SIZE) != MSG_SIZE) {
            printf(1, "Error reading from pipe in child process\n");
            exit();
        }

        // printf(1, "Child received: %s\n", receivedMessage);

        if (write(pipe_c_to_p[WRITE_INDEX], message, MSG_SIZE) != MSG_SIZE) {
            printf(1, "Error writing to pipe in child process\n");
            exit();
        }

        
        close(pipe_p_to_c[READ_INDEX]);
        close(pipe_c_to_p[WRITE_INDEX]);
    }

    exit();
}
