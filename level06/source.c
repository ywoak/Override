int auth(char *login_buff, int serial)
{
  int len;
  int i;
  int accumulator;
  int var_ch;

  len = strcspn(login_buff, serial); // \n basically, since it was with fgets
  login_buff[len] = 0; // Replace \n with \0 for len
  len = strnlen(login_buff, 32);
  // Dont want that
  if (len < 6) {
    ret = 1;
  }
  else {
    // Dont want that
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) { // Prevent tampering / patching process
      puts(); puts(); puts();
      ret = 1;
    }
    else {
      accumulator = (login_buff[3] ^ 0x1337U) + 0x5eeded; // annoying hashing func
      for (i = 0; i < len; i++) {
        // Dont want that
        if (login_buff[i] < ' ') { // Any \n/0/t/b/r
          return 1;
        }
        accumulator += (login_buff[i] ^ accumulator) % 0x539; // annoying hashing func part 2
      }
      // Win condition 
      if (serial == accumulator) {
        ret = 0;
      }
      // Dont want that
      else {
        ret = 1;
      }
    }
  }
  return ret;
}

int main(void)
{
    // sub esp, 0x50 // 84
    char login_buff[32];  // esp+0x2c // 44
    uint32_t serial;      // esp+0x28 // 40, 1 word before login_buff
    int canary = *(GS_OFFSET + 0x14);

    puts(); puts(); puts(); printf("Enter login");
    fgets(login_buff, 0x20, stdin);
    puts(); puts(); puts(); printf("Enter serial");
    scanf("%u", serial);
    if (!auth(login_buff, serial)) {
        puts("Authenticated");
        system("/bin/sh");
    }
    if (canary != *(GS_OFFSET + 0x14)) {
        __stack_chk_fail();
    }
    return 0;
}
