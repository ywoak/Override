#include <stdint.h>
#include <string.h>
#include <stdio.h>

void  main(int ac, char **av) {
  if (ac == 2) {
    uint32_t len = strlen(av[1]); // min 6 char
    uint32_t acc = (av[1][3] ^ 0x1337) + 0x5eeded; // base key
    int i = 0;

    while (i < len) {
      acc += (av[1][i] ^ acc) % 0x539; // Computer smarter than me on this one, one liner better
      i++;
    }
    printf("%u", acc);
    return ;

    // simul reg
//    uint32_t edx = 0;
//    uint32_t ecx = 0;
//    uint32_t eax = 0;
//    uint64_t tmp = 0;
//
//    while (i < len) {
//      eax = av[1][i];
//      // mov ecx, eax           // login[i]                         (in c)
//      ecx = eax;
//      // xor ecx, dword [acc]   // login[i] ^ acc                   (in c)
//      ecx = ecx ^ acc;
//      // mov edx, 0x88233b2b    // 0x88233b2b                       (in d)
//      edx = 0x88233b2b;
//      // mov eax, ecx           // login[i] ^ acc                   (in a)
//      eax = ecx;
//      // mul edx                // (login[i] ^ acc) * 0x88233b2b    (in d:a)
//      tmp = eax * edx;
//      tmp = tmp >> 4;
//      edx = tmp;
//      // mov eax, ecx           // login[i] ^ acc                   (in a)
//      eax = ecx;
//      // sub eax, edx           // (login[i] ^ acc) - edx           (in a)
//      eax -= edx;
//      // shr eax, 1             // (login[i] ^ acc) - edx / 2       (in a)
//      eax = eax >> 1;
//      // add eax, edx           // (login[i] ^ acc) - edx / 2 + edx (in a)
//      eax += edx;
//      // shr eax, 0xa           // a / 4096                         (in a)
//      eax = eax >> 0xa;
//      // imul eax, eax, 0x539   // a * 0x539                        (in a)
//      eax = eax * 0x539;
//      // mov edx, ecx           // login[i] ^ acc                   (in d)
//      edx = ecx;
//      // sub edx, eax           // (login[i] ^ acc) - a             (in d)
//      edx -= eax;
//      // mov eax, edx           // (login[i] ^ acc) - a             (in a)
//      eax = edx;
//      // add dword [acc], eax   // acc += a                         
//      acc += eax;
//      // add dword [i], 1       // i++
//      i++;
//    }
//    printf("%u", acc);
  }
}
