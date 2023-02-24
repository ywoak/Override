int main(void)
{
  int wstatus; // esp + 0x1c
  char buff[32]; // esp + 0x20
  int tmp; // esp + 0x28
  int ptrace_ret; // esp + 0xa8
  int pid; // esp + 0xac

  pid = fork();
  bzero(buff); // repz stosd

  if (pid == 0) {
    prctl(PR_SET_PDEATHSIG, 1);
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    puts("Give me some shellcode, k");
    gets(buff);
  }
  else {
    do {
      wait(&wstatus);
      if (((wstatus & 0x7f) == 0) || (tmp = wstatus,  0 < (wstatus & 0x7f) + 1 >> 1)) {
        puts("child is exiting...");
        return 0;
      }
      ptrace_ret = ptrace(PTRACE_PEEKUSER, pid, 0x2c, 0);
    } while (ptrace_ret != 0xb);
    puts("no exec() for you");
    kill(pid, 9);
  }
  return 0;
}
