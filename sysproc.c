#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "searchingPaths.h"

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

int sys_get_time(void) {
  struct rtcdate *t;
  if(argptr(0, (void*)&t, sizeof(&t)) < 0)
    return -1;
  cmostime(t);
  return (t->second) + (t->minute * 60) + (t->hour * 3600);
}

int sys_set_path(void) {
  cprintf("Inside kernel!\n");

  char* newPaths;
  if(argstr(0, &newPaths) < 0)
    return -1;
  int i = 0, j = 1, k;
    while (1) {
        while (j < strlen(newPaths) && newPaths[j] != ':') j++;
        if (j >= strlen(newPaths)) break;
        for (k = i ; k < j ; k++) {
            paths[numOfPaths][k-i] = newPaths[k];
        }   
        paths[numOfPaths][k-i] = '\0';
        numOfPaths ++;

        j++;
        i = j;
    }
    cprintf("PATH variable got updated!\n");
    return 1;
}

int sys_set_sleep(void) {
  int n;
  if(argint(0, &n) < 0)
    return -1;

  acquire(&tickslock);
  int startTime = ticks;
  while((ticks-startTime) < n * 90) {
    release(&tickslock);
    sti();
    acquire(&tickslock);
  }
  release(&tickslock);
  return 1;
}

int sys_count_num_of_digits(void) {
  cprintf("Inside kernel!\n");

  int num;
  struct proc *curproc = myproc();
  num = curproc->tf->ebx;

  int count = 0;
  while(num > 0) {
    count += 1;
    num /= 10;
  }
  cprintf("num of digits: %d\n", count);
  return count;
}

int sys_get_parent_id(void) {
  return myproc()->parent->pid;
}

int sys_get_children(void) {
  int pid;
  if (argint(0, &pid) < 0) 
    return -1;
  return getChildren(pid);
}

int sys_change_process_queue(void) {
  int pid, queue;
  if (argint(0, &pid) < 0) 
    return -1;
  if (argint(1, &queue) < 0) 
    return -1;
  return change_process_queue(pid, queue);
}

int sys_set_lottery_ticket(void) {
  int pid, numOfTickets;
  if (argint(0, &pid) < 0) 
    return -1;
  if (argint(1, &numOfTickets) < 0) 
    return -1;
  return set_lottery_ticket(pid, numOfTickets);
}

int sys_set_srpf_priority(void) {
  int pid, priority;
  if (argint(0, &pid) < 0) 
    return -1;
  if (argint(1, &priority) < 0) 
    return -1;
  return set_srpf_priority(pid, priority);
}

int sys_print_processes_info(void) {
  return print_processes_info();
}