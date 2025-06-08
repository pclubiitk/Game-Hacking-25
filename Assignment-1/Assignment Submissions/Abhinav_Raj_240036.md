# GDB

## GDB Baby Step 1:
Opened file in GDB  
```$ gdb ./debugger0_a```
Looked for the functions
```
gef➤  info functions
All defined functions:

Non-debugging symbols:
0x0000000000001000  _init
0x0000000000001030  __cxa_finalize@plt
0x0000000000001040  _start
0x0000000000001070  deregister_tm_clones
0x00000000000010a0  register_tm_clones
0x00000000000010e0  __do_global_dtors_aux
0x0000000000001120  frame_dummy
0x0000000000001129  main
0x0000000000001140  __libc_csu_init
0x00000000000011b0  __libc_csu_fini
0x00000000000011b8  _fini
```
Disassembled main
```
gef➤  disass main
Dump of assembler code for function main:
   0x0000000000001129 <+0>:	endbr64
   0x000000000000112d <+4>:	push   rbp
   0x000000000000112e <+5>:	mov    rbp,rsp
   0x0000000000001131 <+8>:	mov    DWORD PTR [rbp-0x4],edi
   0x0000000000001134 <+11>:	mov    QWORD PTR [rbp-0x10],rsi
   0x0000000000001138 <+15>:	mov    eax,0x86342
   0x000000000000113d <+20>:	pop    rbp
   0x000000000000113e <+21>:	ret
End of assembler dump.
```
This shows value stored in eax register ``` 0x0000000000001138 <+15>:	mov    eax,0x86342```  
Its decimal is:
```
gef➤  p /d 0x86342
$4 = 549698
```
  **FLAG :** picoCTF{549698}
---
## GDB baby step 2:
Open in gdb:
```$ gdb ./debugger0_b```
Diassamble main:
```
gef➤  disass main
Dump of assembler code for function main:
   0x0000000000401106 <+0>:	endbr64
   0x000000000040110a <+4>:	push   rbp
   0x000000000040110b <+5>:	mov    rbp,rsp
   0x000000000040110e <+8>:	mov    DWORD PTR [rbp-0x14],edi
   0x0000000000401111 <+11>:	mov    QWORD PTR [rbp-0x20],rsi
   0x0000000000401115 <+15>:	mov    DWORD PTR [rbp-0x4],0x1e0da
   0x000000000040111c <+22>:	mov    DWORD PTR [rbp-0xc],0x25f
   0x0000000000401123 <+29>:	mov    DWORD PTR [rbp-0x8],0x0
   0x000000000040112a <+36>:	jmp    0x401136 <main+48>
   0x000000000040112c <+38>:	mov    eax,DWORD PTR [rbp-0x8]
   0x000000000040112f <+41>:	add    DWORD PTR [rbp-0x4],eax
   0x0000000000401132 <+44>:	add    DWORD PTR [rbp-0x8],0x1
   0x0000000000401136 <+48>:	mov    eax,DWORD PTR [rbp-0x8]
   0x0000000000401139 <+51>:	cmp    eax,DWORD PTR [rbp-0xc]
   0x000000000040113c <+54>:	jl     0x40112c <main+38>
   0x000000000040113e <+56>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000401141 <+59>:	pop    rbp
   0x0000000000401142 <+60>:	ret
End of assembler dump.
```
Decimals:
```
gef➤  p /d 0x1e0da
$1 = 123098
gef➤  p /d 0x25f
$2 = 607
```
So we see its basically assembly of a loop, wrote the pyhton code to get the value:
```
gef➤  python
>def main():
    eax = 123098  
    for i in range(607):
        eax += i
    return eax
print(main())
>end
307019
```
**FLAG:** picoCTF{307019}
---
## GDB baby step 3:
**Challenge:**  
Description  
Now for something a little different. 0x2262c96b is loaded into memory in the main function. Examine byte-wise the memory that the constant is loaded in by using the GDB command x/4xb addr. The flag is the four bytes as they are stored in memory. If you find the bytes 0x11 0x22 0x33 0x44 in the memory location, your flag would be: picoCTF{0x11223344}.

**Solve:**  
Open the file in gdb:
```$ gdb ./debugger0_c```  
Disasssembled the main:
```
gef➤  disass main
Dump of assembler code for function main:
   0x0000000000401106 <+0>:	endbr64
   0x000000000040110a <+4>:	push   rbp
   0x000000000040110b <+5>:	mov    rbp,rsp
   0x000000000040110e <+8>:	mov    DWORD PTR [rbp-0x14],edi
   0x0000000000401111 <+11>:	mov    QWORD PTR [rbp-0x20],rsi
   0x0000000000401115 <+15>:	mov    DWORD PTR [rbp-0x4],0x2262c96b
   0x000000000040111c <+22>:	mov    eax,DWORD PTR [rbp-0x4]
   0x000000000040111f <+25>:	pop    rbp
   0x0000000000401120 <+26>:	ret
End of assembler dump.
```
So we see the content to be loaded in the eax register is ```0x2262c96b```. So basically the **Flag**F will be ```picoCTF{0x6bc96222}```. But the challenge says to examine byte-wise... soo...  

Put a break point at main: ```b main```  
Then run ```r```
Here's a part of the output:
```
0x401106 <main+0000>      endbr64 
     0x40110a <main+0004>      push   rbp
     0x40110b <main+0005>      mov    rbp, rsp
●→   0x40110e <main+0008>      mov    DWORD PTR [rbp-0x14], edi
     0x401111 <main+000b>      mov    QWORD PTR [rbp-0x20], rsi
     0x401115 <main+000f>      mov    DWORD PTR [rbp-0x4], 0x2262c96b
     0x40111c <main+0016>      mov    eax, DWORD PTR [rbp-0x4]
     0x40111f <main+0019>      pop    rbp
     0x401120 <main+001a>      ret
```
So eax is loaded before the memory location```0x40111f```. So we put a breakpoint at it ```b *0x40111f```.
Then continue ```c```  
As asked in the challenge used:
```
gef➤  x/4xb $rbp-4
0x7fffffffdd7c:	0x6b	0xc9	0x62	0x22
```
We get the same  

**Flag:** picoCTF{0x6bc96222}
---
## GDB baby step 4:
Open the file: ```$ gdb ./debugger0_d```  
Looked for the functions: 
```
gef➤  info func
All defined functions:

Non-debugging symbols:
0x0000000000401000  _init
0x0000000000401020  _start
0x0000000000401050  _dl_relocate_static_pie
0x0000000000401060  deregister_tm_clones
0x0000000000401090  register_tm_clones
0x00000000004010d0  __do_global_dtors_aux
0x0000000000401100  frame_dummy
0x0000000000401106  func1
0x000000000040111c  main
0x0000000000401150  __libc_csu_init
0x00000000004011c0  __libc_csu_fini
0x00000000004011c8  _fini
```
Disassembled main:
```
gef➤  disass main
Dump of assembler code for function main:
   0x000000000040111c <+0>:	endbr64
   0x0000000000401120 <+4>:	push   rbp
   0x0000000000401121 <+5>:	mov    rbp,rsp
   0x0000000000401124 <+8>:	sub    rsp,0x20
   0x0000000000401128 <+12>:	mov    DWORD PTR [rbp-0x14],edi
   0x000000000040112b <+15>:	mov    QWORD PTR [rbp-0x20],rsi
   0x000000000040112f <+19>:	mov    DWORD PTR [rbp-0x4],0x28e
   0x0000000000401136 <+26>:	mov    DWORD PTR [rbp-0x8],0x0
   0x000000000040113d <+33>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000401140 <+36>:	mov    edi,eax
   0x0000000000401142 <+38>:	call   0x401106 <func1>
   0x0000000000401147 <+43>:	mov    DWORD PTR [rbp-0x8],eax
   0x000000000040114a <+46>:	mov    eax,DWORD PTR [rbp-0x4]
   0x000000000040114d <+49>:	leave
   0x000000000040114e <+50>:	ret
End of assembler dump.
```
We see that main is calling ```func1```  
Disassembled func1:
```
gef➤  disass func1
Dump of assembler code for function func1:
   0x0000000000401106 <+0>:	endbr64
   0x000000000040110a <+4>:	push   rbp
   0x000000000040110b <+5>:	mov    rbp,rsp
   0x000000000040110e <+8>:	mov    DWORD PTR [rbp-0x4],edi
   0x0000000000401111 <+11>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000401114 <+14>:	imul   eax,eax,0x3269
   0x000000000040111a <+20>:	pop    rbp
   0x000000000040111b <+21>:	ret
End of assembler dump.
```
Got the integer that is multiplied: ```0x0000000000401114 <+14>:	imul   eax,eax,0x3269```  
Converted it into decimal:
```
gef➤  p /d 0x3269
$1 = 12905
```

**Flag:** picoCTF{12905}
---

# Reversing - Crackmes
## ezman's easy keyg3nme:
Downloaded the zip file.  
Used password: crackmes.one.  
Ran the file and entered a value:
```
$ ./keyg3nme 
Enter your key:  k
nope.
```
So we have to input a key. We have to get the logic to crack the password validation.  
Loaded the file in Ghidra.  
Opened the main function:
```
undefined8 main(void)

{
  int iVar1;
  long in_FS_OFFSET;
  undefined4 local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  printf("Enter your key:  ");
  __isoc99_scanf(&DAT_0010201a,&local_14);
  iVar1 = validate_key(local_14);
  if (iVar1 == 1) {
    puts("Good job mate, now go keygen me.");
  }
  else {
    puts("nope.");
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```
So we see that main function takes an input and then calls a funtion ```validate_key``` and passes the input to it.  
If the value returned by validate_key funtion is 1 then we pass the validation else we fail.  
Opened the validate_key funtion:
```
bool validate_key(int param_1)

{
  return param_1 % 0x4c7 == 0;
}
```
The function accepts an integer input and outputs boolean.  
We see if the input number is divisible by ```0x4c7``` that is ```1223``` in decimal. Then it passes the chech and return ```True``` or 1.  
So, entered 1223 in the challege, and boom.
```
$ ./keyg3nme 
Enter your key:  1223
Good job mate, now go keygen me.
```

---
## cbm-hackers's jumpjumpjump:
Downloaded the zip and extracted the file.  
```
$ file rev03
rev03: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=9d23fcc7b9cf9c42f809d46f50ccc249de567cc6, not stripped
```
A non stripped 64-bit executable.  
```
$ ./rev03 
enter the magic string
ad
wrong string
No flag for you.
```
Loaded the file in ghidra. opened the main:
```

undefined8 main(void)

{
  size_t sVar1;
  ulong uVar2;
  char local_98 [112];
  long local_28;
  int local_20;
  int local_1c;
  
  local_1c = 0;
  puts("enter the magic string");
  fgets(local_98,100,stdin);
  sVar1 = strlen(local_98);
  if (sVar1 < 0xc) {
    local_20 = 0;
    while( true ) {
      uVar2 = (ulong)local_20;
      sVar1 = strlen(local_98);
      if (sVar1 <= uVar2) break;
      local_1c = local_1c + local_98[local_20];
      local_20 = local_20 + 1;
    }
    if (local_1c == 1000) {
      local_28 = strcat_str();
      printf("flag is flag{");
      for (local_20 = 0; local_20 < 10; local_20 = local_20 + 1) {
        putchar((int)*(char *)(local_28 + local_20));
      }
      puts("}");
    }
    else {
      puts("wrong string\nNo flag for you.");
    }
  }
  else {
    puts("too long...sorry no flag for you!!!");
  }
  return 0;
}
```
We see that the program asks for a string which should be less than 12 characters long:  
```if (sVar1 < 0xc) {```  
Then it calculates the sum of ASCII values of the string and checks if its equal to `1000`  
Then calls a function ```strcat_str()``` to give the flag and then prints it.  
  
So if we think of ASCII 100 that is 'd', so we can  enter is 10 times and get the flag. But it came out wrong. read about fgets to see that it also includes new line character `\n` that has an ASCII value `10`.  

So, we have to enter a string with sum of  ASCII `990` so that `990+10` is 1000.  
So, the natural choice is  character with ASCII `99` x 10 =990, i.e., `c`  

So, the string is `cccccccccc`  
Entered and got the flag:
```
$ ./rev03 
enter the magic string
cccccccccc
flag is flag{!#&*/5<DMW}
```

**Flag:** flag{!#&*/5<DMW}
---
## Loz's Password Login 2
```
$ ./main
dfa
Login failed
```
So, we have to enter something and the program validates login.  
Opened the file in ghidra.  
The main function:
```

undefined8 main(void)

{
  char cVar1;
  int iVar2;
  password local_88 [48];
  string local_58 [32];
  string local_38 [40];
  
  std::__cxx11::string::string(local_58);
                    /* try { // try from 00102398 to 0010239c has its CatchHandler @ 00102472 */
  std::getline<>((istream *)std::cin,local_58);
  password::password(local_88);
  iVar2 = std::__cxx11::string::length();
                    /* try { // try from 001023c0 to 001023f1 has its CatchHandler @ 00102461 */
  cVar1 = password::checkLength(local_88,iVar2);
  if (cVar1 == '\x01') {
    std::__cxx11::string::string(local_38,local_58);
                    /* try { // try from 00102400 to 00102422 has its CatchHandler @ 00102450 */
    cVar1 = password::checkPassword(local_88,local_38);
    if (cVar1 == '\0') {
      password::wrongPassword();
    }
    else {
      password::rightPassword();
    }
    std::__cxx11::string::~string(local_38);
  }
  else {
    password::wrongPassword();
  }
  password::~password(local_88);
  std::__cxx11::string::~string(local_58);
  return 0;
}
```
We have a c++ program, we are asked for input. We have `password`, `checkLength`, `checkPassword` classes.  
  
The password class:
```
void __thiscall password::password(password *this)

{
  allocator local_19 [9];
  
  this[4] = (password)0x42;
  std::allocator<char>::allocator();
                    /* try { // try from 001028aa to 001028ae has its CatchHandler @ 001028bd */
  std::__cxx11::string::string((string *)(this + 8),"x_.1:.-8.4.p6-e.!-",local_19);
  std::allocator<char>::~allocator((allocator<char> *)local_19);
  return;
}
```
It basically it passes out `0x42` + `x_.1:.-8.4.p6-e.!-`  to the main function. Where it is stored in the `local_88` variable.  
Then the main funtion checks the length of the input by passing it to the checkLength function. Can't get the logic very nicely by seeing the decompiled code so opened GDB for dynamically analysing the memory.

Disassembled main. 
```
0x00005555555563b5 <+80>:	mov    edx,eax
   0x00005555555563b7 <+82>:	lea    rax,[rbp-0x80]
   0x00005555555563bb <+86>:	mov    esi,edx
   0x00005555555563bd <+88>:	mov    rdi,rax
   0x00005555555563c0 <+91>:	call   0x555555556570 <_ZN8password11checkLengthEi>
   0x00005555555563c5 <+96>:	xor    eax,0x1
   0x00005555555563c8 <+99>:	test   al,al
   0x00005555555563ca <+101>:	je     0x5555555563df <main+122>
   0x00005555555563cc <+103>:	lea    rax,[rbp-0x80]
```
Breakpoint at checkLength function:
```
gef➤  b *0x555555556570
Breakpoint 1 at 0x555555556570
```
Continued and entered a value. Then disassembled the checkLength funtion:
```
gef➤  disass 0x555555556570
Dump of assembler code for function _ZN8password11checkLengthEi:
=> 0x0000555555556570 <+0>:	push   rbp
   0x0000555555556571 <+1>:	mov    rbp,rsp
   0x0000555555556574 <+4>:	push   rbx
   0x0000555555556575 <+5>:	sub    rsp,0x48
   0x0000555555556579 <+9>:	mov    QWORD PTR [rbp-0x48],rdi
   0x000055555555657d <+13>:	mov    DWORD PTR [rbp-0x4c],esi
```
Saw this cmp instruction:
```
  0x00005555555565dc <+108>:	mov    DWORD PTR [rax],edx
   0x00005555555565de <+110>:	mov    rax,QWORD PTR [rbp-0x48]
   0x00005555555565e2 <+114>:	mov    eax,DWORD PTR [rax]
   0x00005555555565e4 <+116>:	cmp    DWORD PTR [rbp-0x4c],eax
   0x00005555555565e7 <+119>:	sete   bl
   0x00005555555565ea <+122>:	lea    rax,[rbp-0x40]
   0x00005555555565ee <+126>:	mov    rdi,rax
```
Put a breakpoint at ```0x00005555555565e4```
```
gef➤  x $eax
0x7:	Cannot access memory at address 0x7
gef➤  i r
rax            0x7                 0x7
rbx            0x7fffffffde98      0x7fffffffde98
rcx            0x7fffffffdca1      0x7fffffffdca1
rdx            0x7                 0x7
```
So, the checkLenght is comparing to `7`, the length of the password/.

Now, back to ghidra. Then the main function calls the `checkPassword` for checking the password.
```
undefined4 __thiscall password::checkPassword(password *this,ulong param_2)

{
  password *ppVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  long alStack_c0 [4];
  password *local_a0;
  string local_98 [32];
  string local_78 [47];
  allocator local_49;
  long local_48;
  char *local_40;
  long local_38;
  int local_2c;
  
  alStack_c0[0] = 0x10264e;
  alStack_c0[3] = param_2;
  local_a0 = this;
  std::__cxx11::string::string(local_78);
  local_2c = 0;
  while( true ) {
    uVar7 = (ulong)local_2c;
    alStack_c0[0] = 0x10266a;
    uVar5 = std::__cxx11::string::length();
    if (uVar5 <= uVar7) break;
                    /* try { // try from 00102687 to 00102748 has its CatchHandler @ 001027d9 */
    alStack_c0[0] = 0x10268c;
    pbVar6 = (byte *)std::__cxx11::string::at(alStack_c0[3]);
    alStack_c0[0] = 0x1026ad;
    std::__cxx11::string::operator+=(local_78,(byte)local_a0[4] ^ *pbVar6);
    local_2c = local_2c + 1;
  }
  alStack_c0[1] = (long)(*(int *)local_a0 + 1);
  local_38 = alStack_c0[1] + -1;
  alStack_c0[2] = 0;
  uVar5 = (alStack_c0[1] + 0xfU) / 0x10;
  local_40 = (char *)(alStack_c0 + uVar5 * 0xfffffffffffffffe + 1);
  ppVar1 = local_a0 + 8;
  iVar2 = *(int *)local_a0;
  alStack_c0[uVar5 * -2] = 0x102749;
  local_48 = std::__cxx11::string::copy
                       ((char *)ppVar1,(ulong)(alStack_c0 + uVar5 * 0xfffffffffffffffe + 1),
                        (long)iVar2);
  local_40[local_48] = '\0';
  alStack_c0[uVar5 * -2] = 0x102767;
  std::allocator<char>::allocator();
  pcVar3 = local_40;
                    /* try { // try from 0010277c to 00102780 has its CatchHandler @ 001027c8 */
  alStack_c0[uVar5 * -2] = 0x102781;
  std::__cxx11::string::string(local_98,pcVar3,&local_49);
  alStack_c0[uVar5 * -2] = 0x10278d;
  std::allocator<char>::~allocator((allocator<char> *)&local_49);
  alStack_c0[uVar5 * -2] = 0x1027a3;
  uVar4 = std::operator==(local_78,local_98);
  alStack_c0[uVar5 * -2] = 0x1027b5;
  std::__cxx11::string::~string(local_98);
  alStack_c0[uVar5 * -2] = 0x1027c1;
  std::__cxx11::string::~string(local_78);
  return uVar4;
}
```
After some analysis get to know the function is first xoring our input with `0x42`. Then compares it to a part of the string made at the `password` function. Wasn't able to get exactly what 7 characters were compared against. So, used ChatGpt to find it which gave `.-8.4.p`. Made a pyhthon file to get the password which is `lozlvl2`.

---
## Silva97's login-cipher:
Run the file:
```
$ ./login
Don't patch it!
Insert your password: dfds
Wrong!
```
Opened Ghidra. There is no main function. Looking the different function, mostly were empty. Got two different funtions with some code. One had some strings in it and other be some code logic to print/use the strings.


```
undefined8 FUN_001012a1(void)

{
  int iVar1;
  long in_FS_OFFSET;
  undefined1 local_58 [72];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  FUN_00101348("Gtu.}\'uj{fq!p{$",1);
  FUN_00101348(&DAT_00102014,0);
  __isoc99_scanf("%64[^\n]",local_58);
  iVar1 = FUN_001013e3(local_58,"fhz4yhx|~g=5");
  if (iVar1 == 0) {
    FUN_00101348("Ftyynjy*",1);
  }
  else {
    FUN_00101348("Zwvup(",1);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```
It calls this function:
```
void FUN_00101348(char *param_1,char param_2)

{
  long in_FS_OFFSET;
  char local_118 [264];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  strcpy(local_118,param_1);
  FUN_00101218(local_118);
  if (param_2 == '\0') {
    fputs(local_118,stdout);
  }
  else {
    puts(local_118);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
```
And this calls the next one which has the code logic:
```
char * FUN_00101218(char *param_1)

{
  int local_14;
  char *local_10;
  
  local_14 = 0x7b1;
  for (local_10 = param_1; *local_10 != '\0'; local_10 = local_10 + 1) {
    local_14 = (local_14 * 7) % 0x10000;
    *local_10 = *local_10 + ((char)(local_14 / 10) * '\n' - (char)local_14);
  }
  return param_1;
}
```

Made a c code to check the above function:
```
#include<stdio.h>
int main(){
	char str[] = "Gtu.}\'uj{fq!p{$";
	int c = 0x7b1;
	//char *ptr = sus_string;
	for (int i=0; str[i] != '\0'; i++) {
		c = (c * 7) % 0x10000;
		str[i] = str[i] + ((char)(c / 10) * '\n' - (char)c);
	}
	printf("%s",str);
}
```
When run:
```
$ ./logincrack 
Don't patch it!
```
Which was the sentence the file prints when run. So `fhz4yhx|~g=5` must be the password string as it is compared to print `Correct` in the 1st function. Used the string in the c code to get the password: ```ccs-passwd44```  
```
$ ./login
Don't patch it!
Insert your password: ccs-passwd44
Correct!
```
Bingo!
