# Assignment 1 -- Arnab Datta

## GDB

### GDB baby step 1

##### *The file is a ELF binary*
(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ file debugger0_a

> debugger0_a: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=15a10290db2cd2ec0c123cf80b88ed7d7f5cf9ff, for GNU/Linux 3.2.0, not stripped

##### *The file is made executable*
(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ chmod +x debugger0_a

(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ gdb debugger0_a

```
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from debugger0_a...
(No debugging symbols found in debugger0_a)
```

##### *We can see that Hexadecimal (0x86342)<sub>16</sub> is stored in eax at the end.*
(gdb) disassemble main
``` 
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

(gdb) q

##### *Finding the decimal equivalent of (0x86342)<sub>16</sub> using `Python`*

(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ python3 -c `"print(0x86342)"`
> 549698

#### An alternative method could be printing the value of eax register at the end of the main function

(gdb) layout asm

![gdb1](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_12-08-59_a9mtan.png)

#### Hence the flag is `picoCTF{549698}`

---

### GDB baby step 2

##### The value of eax register at the end of the main function is found by setting a breakpooint before the function returns

![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_12-53-35_grakcf.png)

![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_12-52-42_arb5gk.png)

#### Hence the flag is `picoCTF{307019}`

---

### GDB baby step 3

(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ chmod +x debugger0_c
(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ gdb debugger0_c
```
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
.
.
.
Reading symbols from debugger0_c...
(No debugging symbols found in debugger0_c)
```
(gdb) info functions
```
All defined functions:

Non-debugging symbols:
0x0000000000401000  _init
0x0000000000401020  _start
0x0000000000401050  _dl_relocate_static_pie
0x0000000000401060  deregister_tm_clones
0x0000000000401090  register_tm_clones
0x00000000004010d0  __do_global_dtors_aux
0x0000000000401100  frame_dummy
0x0000000000401106  main
0x0000000000401130  __libc_csu_init
0x00000000004011a0  __libc_csu_fini
0x00000000004011a8  _fini
```
(gdb) disass main
```
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
(gdb) b main
> Breakpoint 1 at 0x40110e

(gdb) run
```
Starting program: /home/arnab/Downloads/debugger0_c 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, 0x000000000040110e in main ()
```
(gdb) layout asm

##### Navigate to appropriate assembly instruction and examine memory

![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_13-25-38_jq4ncd.png)

We see that $rbp-4 stores the pointer to value (576899435)<sub>10</sub> = (0x2262c96b)<sub>16</sub>  (evident from `print $eax`). Since the system stores these 4 bytes in little endian format, the order of the bytes is flipped. Hence on examining the memory we get `0x6b 0xc9 0x62 0x22` 

#### Hence the flag is `picoCTF{6bc96222}`

---

### GDB baby step 4

(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ chmod +x debugger0_d
(base) arnab@arnab-LOQ-15AHP9:~/Downloads$ gdb debugger0_d
```
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
.
.
.
Reading symbols from debugger0_d...
(No debugging symbols found in debugger0_d)
```
(gdb) info functions
```
All defined functions:

Non-debugging symbols:
0x0000000000401000  _init
0x0000000000401020  _start
0x0000000000401050  _dl_relocate_static_pie
0x0000000000401060  deregister_tm_clones
0x0000000000401090  register_tm_clones
0x00000000004010d0  __do_global_dtors_aux
0x0000000000401100  frame_dummy
-----------------------------   <-
| 0x0000000000401106  func1 |     } functions   
| 0x000000000040111c  main  |     } of interest
-----------------------------   <-
0x0000000000401150  __libc_csu_init
0x00000000004011c0  __libc_csu_fini
0x00000000004011c8  _fini
```
(gdb) b main
> Breakpoint 1 at 0x401124

(gdb) run
```
Starting program: /home/arnab/Downloads/debugger0_d 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, 0x0000000000401124 in main ()
```
(gdb) layout asm

![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_15-32-33_god4lt.png)

##### We see that in func1, eax is multiplied by 0x32690 
#### Hence the flag is `picoCTF{12905}`

---

## Reversing - Crackmes

### 1. <https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661>
The binary is unzipped with the passcode `crackmes.one`. The file `keyg3nme` is made executable and run. 

(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5da31ebc33c5d46f00e2c661$ chmod +x keyg3nmme

(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5da31ebc33c5d46f00e2c661$ ./keyg3nme 
```
Enter your key:  56 
nope.
```
`keyg3nme` is loaded on ghidra and decompiled.

The decompiled main function:

``` c
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

The `validate_key(...)` method is of particular interest, we navigate to it on ghidra.
![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-08_19-42-33_nlj3xq.png)

We can see from the decompiled validate_key(int ) that it checks whether a number is divisible by (0x4c7)<sub>16</sub>=(1223)<sub>10</sub>.
Hence any number divisible by 1223 is a valid key. (eg. 0,1223,2446, etc. )

### 2. <https://crackmes.one/crackme/5c1a939633c5d41e58e005d1>
The binary is unzipped with the passcode `crackmes.one`. The file `rev03` is made executable and run. 

(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ chmod +x rev03

(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ file rev03 
```
rev03: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=9d23fcc7b9cf9c42f809d46f50ccc249de567cc6, not stripped
```
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ ./rev03
```
enter the magic string
23ss
wrong string
No flag for you.
```
`rev03` is loaded on ghidra and decompiled.

The decompiled main function:

```c
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
On systematically renaming the variables on ghidra, we get :


```c
undefined8 main(void)

{
  size_t len;
  ulong uVar1;
  char str [112];
  long local_28;
  int i;
  int sum;
  
  sum = 0;
  puts("enter the magic string");
  fgets(str,100,stdin);
  len = strlen(str);
  if (len < 12) {
    i = 0;
    while( true ) {
      uVar1 = (ulong)i;
      len = strlen(str);
      if (len <= uVar1) break;
      sum = sum + str[i];
      i = i + 1;
    }
    if (sum == 1000) {
      local_28 = strcat_str();
      printf("flag is flag{");
      for (i = 0; i < 10; i = i + 1) {
        putchar((int)*(char *)(local_28 + i));
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

We need not worry about the comparisons and casting betwen signed and unsigned as all numbers in volved are positive. The code checks if the sum of the ascii values of the characters of a string containing less than 12 characters is 1000. If this condition is satisfied, it prints a flag.

Since fgets also appends '\n' to the output string when prompted for input, we can consider the string "dddddddddZ\n" ('\n' is newline). 
If we don't want to pass a newline character we can pipe the ouput of printf "dddddddddd" to the program. (echo appends a newline to the ouput string)

```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ ./rev03
enter the magic string
dddddddddZ
flag is flag{!#&*/5<DMW}
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ echo "dddddddddZ"|./rev03 
enter the magic string
flag is flag{!#&*/5<DMW}
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ printf "ddddddddd"|./rev03 
enter the magic string
wrong string
No flag for you.
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5c1a939633c5d41e58e005d1$ printf "dddddddddd"|./rev03 
enter the magic string
flag is flag{!#&*/5<DMW}
```
#### Hence the flag is flag{!#&*/5<DMW}

### 3. <https://crackmes.one/crackme/5ca0b6c833c5d4419da5567b>
The binary is unzipped with the passcode `crackmes.one`. The file `main` is made executable and run. 

```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5ca0b6c833c5d4419da5567b$ chmod +x main
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5ca0b6c833c5d4419da5567b$ file main
main: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=20f68d1ee9963ebdfba5be1cbe019bd41930b5df, not stripped

(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5ca0b6c833c5d4419da5567b$ ./main
6
Login failed
```

`main` is loaded on ghidra and decompiled.

The decompiled main function with variables renamed:

```cpp

undefined8 main(void)

{
  char flag;
  int len;
  password pswd [48];
  string input [32];
  string str [40];
  
  std::__cxx11::string::string(input);
                    /* try { // try from 00102398 to 0010239c has its CatchHandler @ 00102472 */
  std::getline<>((istream *)std::cin,input);
  password::password(pswd);
  len = std::__cxx11::string::length();
                    /* try { // try from 001023c0 to 001023f1 has its CatchHandler @ 00102461 */
  flag = password::checkLength(pswd,len);
  if (flag == 1) {
    std::__cxx11::string::string(str,input);
                    /* try { // try from 00102400 to 00102422 has its CatchHandler @ 00102450 */
    flag = password::checkPassword(pswd,str);
    if (flag == 0) {
      password::wrongPassword();
    }
    else {
      password::rightPassword();
    }
    std::__cxx11::string::~string(str);
  }
  else {
    password::wrongPassword();
  }
  password::~password(pswd);
  std::__cxx11::string::~string(input);
  return 0;
}
```

```cpp
/* password::checkLength(int) */
ulong __thiscall password::checkLength(password *this,int len)
{
  int k;
  char *ptr;
  undefined8 unaff_RBX;
  __cxx11 str [43];
  char ch;
  undefined4 n;
  
  n = 360;
  std::__cxx11::to_string(str,360);
//Converts the integer 360 into the string "360" and stores it in str

                    /* try { // try from 001025a4 to 001025c0 has its CatchHandler @ 001025fa */
  ptr = (char *)std::__cxx11::string::at((ulong)str);
  //Gets a pointer to the first character of the string "360", i.e., the character '3'
  ch = *ptr;
  std::__cxx11::string::operator=((string *)str,ch);
  //Replaces the entire string with "3" by assigning the single character '3'
  ptr = (char *)std::__cxx11::string::c_str();
  //Gets a pointer to the null-terminated string "3".
  k = atoi(ptr); //k=3
  *(int *)this = k + 1; 
  k = *(int *)this; //k stores 4
  std::__cxx11::string::~string((string *)str);
  return CONCAT71((int7)((ulong)unaff_RBX >> 8),len == k) & 0xffffffff;
}
```
checkLength function checks if length of the password is 4 (7??)





### 4. <https://crackmes.one/crackme/5db0ef9f33c5d46f00e2c729>


### 5. <https://crackmes.one/crackme/5d8dfa7433c5d46f00e2c544>



