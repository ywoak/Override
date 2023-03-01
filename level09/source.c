/*
** Setup a buffer, send it for username and message
** index 180 we place 140
*/
void handle_msg(void) {
  char  buff[192];

  bzero(buff[140], 40); // Dont understand why they do this since strncpy will do it first thing
  buff[180] = 140;

  set_username(&buff);
  set_msg(&buff);
  puts("Msg sent\n");
  return ;
}

/*
** setup a buffer to fgets username input, bound-check, no overflow possible
** then copy the 41st char in buff[140]
*/
void set_username(char *buff)
{
  char  s[128]; // rbp - 0xa0
  int   i = 0;

  bzero(s, 16);
  puts(">:Enter your username >>:\n");
  fgets(s, 128, stdin);
  // while ((i < 0x29) && (s[i])) {
  //   buff[140 + i] = s[i];
  // }
  strncpy(buff[140], s, 41); // 41 and not 40 is weird but o well
  printf("Welcome %s", buff[140]);
  return ;
}

/*
** Setup a huge buffer with 128 bzero, to fgets message input, bound-check, no overflow possible
** Then strncpy the 140 first in the buffer
** Ok back to walkthrough for more detail
*/
void set_msg (char *buff) {
  char s[1024]; // rbp-0x400
  char *ptr;     // rbp-0x408

  // push rbp
  // mov rbp, rsp
  // sub rsp, 0x410
  // mov qword [dest], rdi       ; arg1
  // lea rax, [src]
  // mov rsi, rax
  // mov eax, 0
  // mov edx, 0x80
  // mov rdi, rsi
  // mov rcx, rdx
  // rep stosq qword [rdi], rax
  ptr = buff;
  bzero(s, 128);

  // lea rdi, str._:_Msg__Unix_Dude ; const char *s
  // call sym.imp.puts; int puts(const char *s)
  // lea rax, str.__:_
  // mov rdi, rax                ; const char *format
  // mov eax, 0
  // call sym.imp.printf; int printf(const char *format)
  puts(">: Msg @Unix-Dude >>:\n");

  // mov rax, qword [reloc.stdin]
  // mov rax, qword [rax]
  // mov rdx, rax                ; FILE *stream
  // lea rax, [src]
  // mov esi, 0x400              ; int size
  // mov rdi, rax                ; char *s
  // call sym.imp.fgets; char *fgets(char *s, int size, FILE *stream)
  fgets(&s, 1024, stdin);

  // mov rax, qword [dest] ; ptr
  // mov eax, dword [rax + 0xb4] ; buff[180] == 140
  // movsxd rdx, eax             ; size_t  n
  // lea rcx, [src]
  // mov rax, qword [dest]
  // mov rsi, rcx                ; const char *src
  // mov rdi, rax                ; char *dest
  // call sym.imp.strncpy; char *strncpy(char *dest, const char *src, size_t  n)
  strncpy(ptr, s, ptr[180]);
  return ;
}

int main(void) {
  puts("Welcome\n");
  handle_msg();
  return 0;
}

// Win func, obv
void secret_backdoor(void) {
  char command[128];

  fgets(&command, 128, stdin);
  system(command);
  return ;
}
