void  main(void)
{
  char  *buffer[100];
  int   i;

  i = 0;
  fgets(buffer, 100, stdin);
  do {
    len = strlen(buffer) - 1;
    if (len <= i) {
      printf(buffer);
      exit(0);
    }
    if ((buffer[i] >= 'A') && (buffer[i] <= 'Z')) {
      togglecase(buffer[i]); // not a real function in the code -> buffer[i] ^= 0x20
    }
    i++;
  } while (true);
}
