#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_door_call(void) 
{ 
  int dstprocess;
  char *message; 
  char *response;

  if (argint(0, &dstprocess) < 0 || argptr(1, &message, sizeof(char*)) < 0, argptr(2, &response, sizeof(char*)) < 0) {
    return -1;  // Invalid arguments
  }

  struct proc *destination_proc = getproc(dstprocess);
  struct door *destination_proc_door = &(destination_proc->pdoor);
  strncpy(destination_proc_door->incoming_message, message, strlen(message));

  destination_proc_door->caller_pid = myproc()->pid;
  destination_proc_door->door_call_ready = 1;
  
  door_yield(destination_proc);  

  strncpy(response, myproc()->pdoor.call_return_val, strlen(message));

  return 0;
}

int
sys_door_wait(void) 
{ 
  char *message; 

  if (argptr(0, &message, sizeof(char*)) < 0) {
    return -1;  // Invalid arguments
  }

  struct door *mydoor = &myproc()->pdoor;

  while(mydoor->door_call_ready == 0) yield();

  char *incoming_message = mydoor->incoming_message;
  strncpy(message, incoming_message, strlen(incoming_message));
  mydoor->door_call_ready = 0;

  return 0;
}


int
sys_door_respond(void) 
{ 
  char *response; 

  if (argptr(0, &response, sizeof(char*)) < 0) {
    return -1;  // Invalid arguments
  }

  struct proc *caller_proc = getproc(myproc()->pdoor.caller_pid);
  strncpy(caller_proc->pdoor.call_return_val, response, strlen(response));

  door_yield(caller_proc);

  return 0;
}