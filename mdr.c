#include "types.h"
#include "user.h"
#include "utils.h"

#define MSG_SIZE 20


int main(void) {
    int pid = fork();

    if (pid < 0) {
        printf(1, "Fork failed!\n");
    }
    else if (pid > 0) {
        // Parent process
        char message[MSG_SIZE] = "Hello from parent!";
        char receivedMessage[MSG_SIZE];

        uint start = rdtsc();

        door_call(pid, message, receivedMessage);

        // printf(1, "Parent received: %s\n", receivedMessage);

        uint end = rdtsc();

        printf(1, "Elapsed Time: %x\n", end - start);

        wait();
    }
    else {
        // Child process
        char message[MSG_SIZE] = "Hello from child!";
        char receivedMessage[MSG_SIZE];

        door_wait(receivedMessage);

        // printf(1, "Child received: %s\n", receivedMessage);

        door_respond(message);
    }

    exit();
}
