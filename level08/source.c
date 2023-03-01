// Doesnt seem to be any vuln here
void log_wrapper(FILE *fd, char *message, char *file)
{
	char buff[272];

	strcpy(buff, message); // write the message to log in buff
	snprintf(&buff[strlen(buff)], 254 - strlen(buff), file); // write at the end of buffer, file (bound check)
	buff[strcspn(buff, "\n")] = 0; // null terminate the message in buff
	fprintf(fd, "LOG: %s\n", buff); // the whole thing loaded in backups/.log
	return ;
}

int main(int ac, char **av) {
  // Provide an arg_file
  if (ac != 2) {
    printf("Usage: %s filename\n", *av);
  }

  // Open our /backups/.log with write, call log_wrapper on it
  log_fd = fopen("./backups/.log", 'w');
  if (log_fd == 0) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }
  log_wrapper(log_fd, "Starting back up: ", av[1]);

  // Open our arg_file with read rights
  arg_fd = fopen(av[1], 'r');
  if (arg_fd == 0) {
    printf("ERROR: Failed to open %s\n", av[1]);
    exit(1);
  }

  // Some crazy code right here, at least i know the code right before is an strlen
  // Then catenate what in buff (probably populated by the above code) with arg_file
  strncat(buff, av[1], 99 - (strlen(av[1]) - 1));

  // open (with O_CREATE at least), backup/arg_file, according to the printf error
  // and since its on buff, i guess the code above strncat was just buff='./backups/'
  back_fd = open(buff, 0xc1, 0x1b0);
  if (back_fd <= -1) {
    printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
    exit(1);
  }

  // write in everything thats in our arg file to backup/arg_file
  while ((c = fgetc(arg_fd)) != -1) {
    write(back_fd, (unsigned char *)&c, 1);
  }

  // end block
  log_wrapper(log_fd, "Finished back up ", av[1]);
  fclose(log_fd);
  close(back_fd);
  return ;
}
