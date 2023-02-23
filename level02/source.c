int main(void) {
  // For rep stosq
  int64_t i;
  ulong *tmp_ptr;

  // Store 
  ulong read_buff;
  ulong user_buff;
  ulong pass_buff;

  int32_t byte_read;
  FILE *passfile;

  // Basically memset(0, 5/0xc/0xc) for 3 different buffer
  tmp_ptr = &user_buff;
  for (i = 0xc; i != 0; i--) {
    *tmp_ptr = 0;
    tmp_ptr = tmp_ptr + 1;
  }
  *tmp_ptr = 0;
  tmp_ptr = &read_buff;
  for (i = 5; i != 0; i--) {
    *tmp_ptr = 0;
    tmp_ptr = tmp_ptr + 1;
  }
  *tmp_ptr = 0;
  tmp_ptr = &pass_buff + 4;
  for (i = 0xc; i != 0; i--) {
    *tmp_ptr = 0;
    tmp_ptr = tmp_ptr + 1;
  }
  *tmp_ptr = 0;

  // Storing passfile content in a buffer, as a null terminated string
  passfile = fopen("/home/users/level03/.pass", "r");
  if (passfile == 0) {
    fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
    exit(1);
  }
  byte_read = fread(&read_buff, 1, 0x29, passfile);
  *(&read_buff + strcspn(&read_buff, "\n")) = 0;
  if (byte_read != 0x29) {
    fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
    fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
    exit(1);
  }
  fclose(passfile);

  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/**************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");

  // Storing user and pass as a null terminated strings on the stack
  printf("--[ Username: ");
  fgets(&user_buff, 100, stdin);
  *(&user_buff + strcspn(&user_buff, "\n")) = 0;
  printf("--[ Password: ");
  fgets(&pass_buff + 4, 100, stdin);
  *(&pass_buff + strcspn(&pass_buff + 4, "\n") + 4) = 0;

  // Fmt vulnerability through user_buff + read_buff value is on the stack = profit :)
  puts("*****************************************");
  if (strncmp(&read_buff, &pass_buff + 4, 0x29)) {
    printf(&user_buff);
    puts(" does not have access!");
    exit(1);
  }

  // On the second process run we can bypass the strncmp because there is no aslr + pic
  printf("Greetings, %s!\n", &user_buff);
  system("/bin/sh");
  return (0);
}
