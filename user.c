#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

const char* get_state(int pstate) {
    char state[10000] = "STATE=";
    
    if(pstate == 0) {
        strcat(state, "TASK_RUNNING,");
    }
    if(pstate & 0x1) {
        strcat(state, "TASK_INTERRUPTIBLE,");
    }
    if(pstate & 0x2) {
        strcat(state, "TASK_UNINTERRUPTIBLE,");
    }
    if(pstate & 0x4) {
        strcat(state, "__TASK_STOPPED,");
    }
    if(pstate & 0x8) {
        strcat(state, "__TASK_TRACED,");
    }
    if(pstate & 0x10) {
        strcat(state, "EXIT_DEAD,");
    }
    if(pstate & 0x20) {
        strcat(state, "EXIT_ZOMBIE,");
    }
    if(pstate & 0x40) {
        strcat(state, "TASK_PARKED,");
    }
    if(pstate & 0x80) {
        strcat(state, "TASK_DEAD,");
    }
    if(pstate & 0x100) {
        strcat(state, "TASK_WAKEKILL,");
    }
    if(pstate & 0x200) {
        strcat(state, "TASK_WAKING,");
    }
    if(pstate & 0x400) {
        strcat(state, "TASK_NOLOAD,");
    }
    if(pstate & 0x800) {
        strcat(state, "TASK_NEW,");
    }
    if(pstate & 0x1000) {
        strcat(state, "TASK_STATE_MAX,");
    }
    
    int size = 0;
    while(state[size] != '\0') {
        size = size + 1;
    }
    char* final_state = malloc((size) * sizeof(final_state[0]));
    strncpy(final_state, state, size - 1);
    final_state[size -1] = '\0';
    return final_state;
}

int main() {
    int buffer[10000];
    int fd = open("/dev/process_list", O_RDONLY);
    if(fd < 0) {
        perror("Fail to open the device!\n");
    }
    int ret = read(fd, buffer, 10000);
    if(ret < 0) {
        perror("Fail to read the device!\n");
    }
    int counter = 0;
    while(buffer[counter] != -1) {
        printf("PID=%d ",buffer[counter]);
        printf("PPID=%d ",buffer[counter + 1]);
        printf("CPU=%d ",buffer[counter + 2]);
        printf("%s\n",get_state(buffer[counter + 3]));
        //printf("STATE=%d\n", buffer[counter + 3]);
        counter = counter + 4;
    }
    //printf("Number of Processes: %d\n", counter / 4);
    return 0;
}
