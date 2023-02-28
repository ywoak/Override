#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// No idea how this get triggered, but the name is explicit, and it forced me to relaunch gdb once
void prog_timeout (void) { exit(1); }

// Utterly useless ? But took me a while to understand what was going on
void  clear_stdin(void) {
  int c = 0;

  while (c != EOF || c != '\n') {
    c = getchar();
  }
}

// Only get unsigned int for inputs
uint32_t get_unum(void) {
  uint32_t nb;

  fflush(stdout);
  scanf("%u", nb);
  clear_stdin();
  return (nb);
}

int read_number(int32_t *tab)
{
    int32_t index;

    printf("Index: "); index = get_unum();
    printf("Number at data[%u] is %u\n", index, tab[index]);
    return 0;
}

int store_number(int32_t *tab) {
  uint32_t number;
  uint32_t index;

  printf("Number: "); number = get_unum();
  printf("Index: "); index = get_unum();

  if ((index % 3) && (number >> 0x18 != 0xb7)) {
    tab[index] = number;
    return (0);
  }
  puts("...");
  return(1);
}

int main(int ac, char **av, char **env) {
  int       tab[0x64];          // esp+0x24
  char      command_buff[0x14]; // esp+0x1b8
  uint32_t  ret_value = 0;      // esp+0x1b4

  memset(tab, 0, 0x64);

  while (*av) {
    memset(*av, 0, strlen(*av));
    av++;
  }
  while (*env) {
    memset(*env, 0, strlen(*env));
    env++;
  }

  puts("Welcome..");
  while (true) {
    ret_value = 1;
    printf("Input command: ");
    fgets(command_buff, 0x14, stdin);
    command_buff[strlen(command_buff) - 1] = '\0';
    if (!strncmp(command_buff, "store", 5)) {
      ret_value = store_number(tab);
    } else if (!strncmp(command_buff, "read", 4)) {
      ret_value = read_number(tab);
    } else if (!strncmp(command_buff, "quit", 4)) {
      return 0;
    }
    if (!ret_value) { printf("Completed %s command successfully\n", command_buff); }
    else { printf("Failed to do %s command\n", command_buff); }
    memset(command_buff, 0, 20);
  }
}
