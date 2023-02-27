# Override
Binary exploitation challenges with writeup for each level

## Do not spoil yourself
If you are a 42 student i heavily advise against reading those writeups ahead of doing the challenges
Feel free to come back after to compare solutions tho :)

## Reversing tools
Before this project i was using objdump and gdb to reverse, at the end with gdb-peda
Now and then i found the ghidra decompiler useful but my ghidra skill ended there
But throughout this project i became found of the radare2 reverse framework, no cutter tho
also more script, sometimes not even in this repo, but i learned the basics of pwntool, mostly used packing for now
So my writeups will naturally be made using those tools, but its still only a matter of efficiency and taste
Its not automating anything that i cant do with other more basic tool
I could still start with the usual command line tool, file, ldd, strings, ltrace, strace, checksec, checkfacl... gdb i f, i v, ifr..
So it wont affect the logic behind the writeup at all, nor the exploit at any point

## radare2
That being said how was my workflow in r2 for this project
1. Loading and analyzing the program, -A/aaa
2. Getting info on the process via the i command family, i did setup a panel mode layout for it
3. Static analysis was mostly done with graph mode, tab visual for hexdump, var/func analyze for specifics, hud for flag seek/management, def/p commands for advanced display
4. Patching im really bad at it, so i did bare min: overwriting one address at most, or a reg to follow a specific conditional branch
5. Debugging i usually start in command mode, but quickly move to panel to a 2nd custom layout for interactive Bp, stack, reg, bt.. ood to reload
6. Decompile when i need it i used r2ghidra over ESIL stuffs, which is used as a native plugin, toggle in visual or :pdg
7. Arithmetic, ? command family, v/b/i with specifier, $$ (current seek) often useful too
8. Shellcode pattern generation, cyclic(cyclic_find()) pwntool or ragg2 -P to generate a De Bruijn pattern, which i then inspect in a dummy r2 - with wopO addr
(again just niceties, just print a bunch of alphabet and count one by one if you really want)

## Ressources
Quick shoutout to rasviOverflow and liveOverflow binary exploitation youtube playlists
Professionally presented, helped a lot to really get my basics down
