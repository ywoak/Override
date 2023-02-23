void decrypt(int key) {
  // Counter variables
  int reverse_len; // Weird 2s complement reverse counter check in another block
  int mask_counter;
  int strncmp_counter;

  // String variables
  int *crypt_string;
  int *gratz_string;
  int part1;
  int part2;
  int part3;
  int part4;
  int setb;

  // Canary set
  int canary = *(GS_OFFSET + 0x14);

  // Writing the string in consecutive memory block, then referencing it by its first address in a ptr
  part1 = 0x757c7d51 // 'Q}|u'
  part2 = 0x67667360 // '`sfg'
  part3 = 0x7b66737e // '~sf{'
  part4 = 0x33617c7d // '}|a3'

  // This is the len counter block, basically strlen crypt_string
  reverse_len = 0xffffffff;
  crypt_string = &part1;
  while (crypt_string && reverse_len)
    crypt_string++;
    reverse_len--;
  }

  // mask_counter = 0;
  // while( true ) {
  //   setb = mask_counter < ~reverse_len - 1;
  //   useless equal check in asm..
  //   if (!setb) break;
  //   *(&part1 + mask_counter) = key ^ *(&part1 + mask_counter);
  //   mask_counter++;
  // }
  // setb is the same name but not same bool as in the strncmp block
  // This is the mask block above is understandable but i dislike it so here is a pseudo alt
  // On each offset of the crypt string it apply a binary nor with the key passed in
  while (mask_counter < strlen(crypt_string)) {
     *(&crypt_string + mask_counter) = key ^ *(&crypt_string + mask_counter);
     mask_counter++;
  }

  // Spent way too much time on this block, its basically a strncmp gratz crypt 0x11
  strncmp_counter = 0x11;
  crypt_string = &part1;
  gratz_string = "Congratulations!";
  while (isequal && i) {
    crypt_string++;
    gratz_string++;
    i--;
    setb = *crypt_string < *gratz_string;
    isequal = *crypt_string == *gratz_string;
  }

  // WinBloc
  if (isequal && !setb) // Basicaly if !strncmp
    system("/bin/sh");
  else
    puts("\nInvalid Password");

  // Canary check
  if (canary != *(GS_OFFSET + 0x14))
    __stack_chk_fail();
  return ;
}

void test(int scanf_ret, int key) {
  int diff_args;

  diff_args = key - scanf_ret;

  if (diff_args < 0x16) {
    // mov eax, dword [diff_args]
    // shl eax, 2, equivalent to eax * 2^^2, here 4, its 2 bitshift to the left
    // add eax, 0x80489f0, add the weird value
    // mov eax, dword [eax], treat is an address to dereference
    // jmp eax
    switch(*(diff_args * 4 + 0x80489f0)) {
      case 0x8048775: // for 1
        decrypt(diff_args);
        break;
      case 0x8048785:// for 2
        decrypt(diff_args);
        break;
      case 0x8048795:// for 3
        decrypt(diff_args);
        break;
      case 0x80487a5:// for 3
        decrypt(diff_args);
        break;
      case 0x80487b5:// for 4
        decrypt(diff_args);
        break;
      case 0x80487c5:// for 5
        decrypt(diff_args);
        break;
      case 0x80487d5:// for 6
        decrypt(diff_args);
        break;
      case 0x80487e2:// for 7
        decrypt(diff_args);
        break;
      case 0x80487ef:// for 8
        decrypt(diff_args);
        break;
      case 0x80487fc:// for 9
        decrypt(diff_args);
        break;
      case 0x8048809:// for 10
        decrypt(diff_args);
        break;
      case 0x8048816:// for 11
        decrypt(diff_args);
        break;
      case 0x8048823:// for 12
        decrypt(diff_args);
        break;
      case 0x8048830:// for 13
        decrypt(diff_args);
        break;
      case 0x804883d:// for 14
        decrypt(diff_args);
        break;
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
      case 21:
      default:
        goto code_r;
    }
  }
  else {
    // We probably dont want that, since we wanna control what to send to decrypt
code_r:
    decrypt(rand());
  }
  return;
}

int main(void) {
  int scan_buff;

  srand(time(0));
  puts("***********************************\n");
  puts("*               level03         **\n");
  puts("***********************************\n");
  printf("Password:");
  scanf("%d", scan_buff);
  test(scan_buff, 0x1337d00d);
  return 0;
}
