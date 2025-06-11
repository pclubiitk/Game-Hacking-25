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

### 1. [First](https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661)
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

### [Second](https://crackmes.one/crackme/5c1a939633c5d41e58e005d1)
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

### [Third](https://crackmes.one/crackme/5ca0b6c833c5d4419da5567b)
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
  //Gets a pointer to the some character of the string "360"
  //from the assembly code we see that 1 is stored in esi
  //hence second character i.e. "6" is stored
  ch = *ptr;
  std::__cxx11::string::operator=((string *)str,ch);
  //Replaces the entire string with "6" by assigning the single character '3'
  ptr = (char *)std::__cxx11::string::c_str();
  //Gets a pointer to the null-terminated string "6".
  k = atoi(ptr); //k=6
  *(int *)this = k + 1; 
  k = *(int *)this; //k stores 7
  std::__cxx11::string::~string((string *)str);
  return CONCAT71((int7)((ulong)unaff_RBX >> 8),len == k) & 0xffffffff;
}
```
![](https://res.cloudinary.com/dwmy4l7ok/image/upload/v1749414520/Screenshot_from_2025-06-09_01-57-40_ytthhi.png)

eax stores 7 (length of valid password), and $rsp-0x4c points to the length of input string
![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-09_02-01-30_dimhjt.png)

checkLength function checks if length of the password is 7 (verified using gdb)


The password constructor:
```cpp
/* password::password() */

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
Decompiled `checkPassword()` with ghidra:
```cpp

/* WARNING: Type propagation algorithm not settling */
/* password::checkPassword(std::__cxx11::string) */

undefined4 __thiscall password::checkPassword(int *this,ulong input)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  undefined4 flag;
  ulong len;
  byte *pbVar4;
  ulong ui;
  long ptrarr [4];
  int *pswdptr;
  string key [32];
  string str [47];
  allocator alloc;
  long local_48;
  char *pass;
  long local_38;
  int i;
  
  ptrarr[0] = 0x10264e;
  ptrarr[3] = input;
  pswdptr = this;
  std::__cxx11::string::string(str);
  i = 0;
  while( true ) {
    ui = (ulong)i;
    ptrarr[0] = 0x10266a;
    len = std::__cxx11::string::length();
    if (len <= ui) break;
                    /* try { // try from 00102687 to 00102748 has its CatchHandler @ 001027d9 */
    ptrarr[0] = 0x10268c;
    pbVar4 = (byte *)std::__cxx11::string::at(ptrarr[3]);
    ptrarr[0] = 0x1026ad;
    std::__cxx11::string::operator+=(str,*(byte *)(pswdptr + 1) ^ *pbVar4);
    i = i + 1;
  }
  ptrarr[1] = (long)(*pswdptr + 1);
  local_38 = ptrarr[1] + -1;
  ptrarr[2] = 0;
  len = (ptrarr[1] + 15U) / 16;
  pass = (char *)(ptrarr + len * 0xfffffffffffffffe + 1);
  piVar1 = pswdptr + 2;
  iVar2 = *pswdptr;
  ptrarr[len * -2] = 0x102749;
  local_48 = std::__cxx11::string::copy
                       ((char *)piVar1,(ulong)(ptrarr + len * 0xfffffffffffffffe + 1),(long)iVar2);
  pass[local_48] = '\0';
  ptrarr[len * -2] = 0x102767;
  std::allocator<char>::allocator();
  pcVar3 = pass;
                    /* try { // try from 0010277c to 00102780 has its CatchHandler @ 001027c8 */
  ptrarr[len * -2] = 0x102781;
  std::__cxx11::string::string(key,pcVar3,&alloc);
  ptrarr[len * -2] = 0x10278d;
  std::allocator<char>::~allocator((allocator<char> *)&alloc);
  ptrarr[len * -2] = 0x1027a3;
  flag = std::operator==(str,key);
  ptrarr[len * -2] = 0x1027b5;
  std::__cxx11::string::~string(key);
  ptrarr[len * -2] = 0x1027c1;
  std::__cxx11::string::~string(str);
  return flag;
}
```
The above code seem to unfathomable to scrutinize. 
Hence binary ninja on [DogBolt](https://www.dogbolt.org) was used to decompile `checkPassword()`:
```cpp
uint64_t password::checkPassword(class std::string input @ rdi)
{
    int32_t* pswd = input;
    class std::string str;
    std::string::string(&str);
    int32_t i = 0;
    
    while (true)
    {
        std::string::size_type flag;
        class std::string* rsi;
        flag = i < std::string::length(rsi);
        
        if (!flag)
            break;
        
        char ch = *std::string::at(rsi, i);
        std::string::operator+=(&str, pswd[1] ^ ch);
        // pswd[1] is defined in password constructor i.e. this[4]='B'
        // the code takes the xor of each character of the string with 'B' and builts a new string
        i++;
    }
    
    int64_t rax_14 = *pswd ;
    int64_t var_38 = rax_14;
    int64_t var_b8 = rax_14 + 1;
    int64_t var_b0 = 0;
    void* __s = &var_b8 - COMBINE(0, rax_14 + 0x10) / 0x10 * 0x10;
    //set address to store the key string (char array)
    *(std::string::copy(&pswd[2], __s, *pswd, 5) + __s) = 0;
    // &pswd[2] points to "x_.1:.-8.4.p6-e.!-"
    class std::allocator<char> var_49;
    std::allocator<char>::allocator(&var_49);
    class std::string var_98;
    std::string::string(&var_98, __s);
    //char array -> std::string, 
    //var_98 points to string ".-8.4.p6"
    std::allocator<char>::~allocator(&var_49);
    int32_t ans = _ZSteqIcEN9__gnu_cxx11__enable_ifIXsrSt9__is_charIT_E7__valueEbE6__typeERKNSt7__cxx1112basic_stringIS3_St11char_traitsIS3_ESaIS3_EEESE_(&str, &var_98); // compare 
    std::string::~string(&var_98);
    std::string::~string(&str);
    return ans;
}
```
Hence after checking length is 7, it checks the password, applying a xor operation with each user input character with 'B' and then comparing with it ".-8.4.p". 
I have verified this on gdb for input string 1234567
![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-10_01-14-32_ba6qv9.png)
If a^b=c then c^b=a. Using this script we get password = `lozlvl2`

```python
user_input = ".-8.4.p"
decrypted = ""

for x in user_input:
    decrypted += chr(ord(x) ^ ord('B'))

print (decrypted)
```

```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5ca0b6c833c5d4419da5567b$ ./main
lozlvl2
Login successful
```
#### password = `lozlvl2`

### 4. [Fourth](https://crackmes.one/crackme/5db0ef9f33c5d46f00e2c729)
The binary is unzipped with the passcode `crackmes.one`. The file `login` is made executable and run. 

```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5db0ef9f33c5d46f00e2c729$ chmod +x login
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5db0ef9f33c5d46f00e2c729$ ./login 
Don't patch it!
Insert your password: 678967
Wrong!
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5db0ef9f33c5d46f00e2c729$ file login
login: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=49fdc1eeb5c801e572b1ed116e8d7de738bc5907, for GNU/Linux 3.2.0, stripped
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5db0ef9f33c5d46f00e2c729$ strings login 
/lib64/ld-linux-x86-64.so.2
libc.so.6
strcpy
__isoc99_scanf
__stack_chk_fail
stdout
fputs
__cxa_finalize
__libc_start_main
GLIBC_2.7
GLIBC_2.4
GLIBC_2.2.5
_ITM_deregisterTMCloneTable
__gmon_start__
_ITM_registerTMCloneTable
u/UH
gfff
gfff
[]A\A]A^A_
Gtu.}'uj{fq!p{$
Lszl{{%
vx{!whvt|twg?%
%64[^
fhz4yhx|~g=5
Ftyynjy*
Zwvup(
;*3$"
GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0
.shstrtab
.interp
.note.gnu.build-id
.note.ABI-tag
.gnu.hash
.dynsym
.dynstr
.gnu.version
.gnu.version_r
.rela.dyn
.rela.plt
.init
.plt.got
.text
.fini
.rodata
.eh_frame_hdr
.eh_frame
.init_array
.fini_array
.dynamic
.data
.bss
.comment

```
The strings "Don't patch it!","Insert your password:","Wrong!" are not stored directly, but in some encrypted format as in 
```
Gtu.}'uj{fq!p{$
Lszl{{%
vx{!whvt|twg?%
%64[^
fhz4yhx|~g=5
Ftyynjy*
Zwvup(
```

Since its a stripped binary, gdb cannot be used. Hence its loaded up on ghidra.
Its functions are inspected. main() function is not found.

![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-11_13-19-49_dfpk9d.png)

Let inspect the function entry()
```c

void processEntry entry(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  __libc_start_main(FUN_001012a1,param_2,&stack0x00000008,FUN_00101460,FUN_001014c0,param_1,
                    auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

```
Next, inspect the function FUN_001012a1()

```c

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
The above function looks a lot like the main function.


Next, lets see function FUN_00101348()
```c

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
This functions employs FUN_00101218() to decrypt a string and print it using fputs(if param_2 is 0) or puts(if param_2 is 1, appends '\n' ).
The much required analysis of FUN_00101218():
```c

char * FUN_00101218(char *param_1)

{
  int local_14;
  char *local_10;
  
  local_14 = 1969;
  for (local_10 = param_1; *local_10 != '\0'; local_10 = local_10 + 1) {
    local_14 = (local_14 * 7) % 65536;
    *local_10 = *local_10 + ((char)(local_14 / 10) * (char)10 - (char)local_14);
  }
  return param_1;
}
```
Let's see how it decrypts the words
```c
#include <stdio.h>
#include <string.h>
int main()
{

    char i = 'u';
    char j = 'A';
    int local_14 = 1969;
    char str[] = "Gtu.}\'uj{fq!p{$";
    for (int i = 0; i < strlen(str); i++)
    {

        local_14 = (local_14 * 7) % 65536;
        str[i] = str[i] + ((char)(local_14 / 10) * (char)10 - (char)local_14);
        printf("%c", str[i]);
    }
}
output:Don't patch it!
```

We observe that FUN_001013e3() and FUN_00101175() is used for validation:
```c

undefined8 FUN_001013e3(char *param_1,undefined8 param_2)
{
  char *pcVar1;
  char cVar2;
  undefined8 uVar3;
  char *local_20;
  int local_c;
  
  local_c = FUN_00101175(param_2);
  local_20 = param_1;
  while ((*local_20 != '\0' && (local_c != 0))) {
    pcVar1 = local_20 + 1;
    cVar2 = *local_20;
    local_20 = pcVar1;
    if (local_c != cVar2) break;
    local_c = FUN_00101175(0);
  }
  if ((local_c == 0) && (*local_20 == '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}


int FUN_00101175(char *param_1)
{
  int iVar1;
  
  if (param_1 != (char *)0x0) {
    DAT_00104010 = 1969;
    DAT_00104028 = param_1;
  }
  if (*DAT_00104028 == '\0') {
    iVar1 = 0;
  }
  else {
    DAT_00104010 = (DAT_00104010 * 7) % 65536;
    iVar1 = (int)*DAT_00104028 + ((DAT_00104010 / 10) * 10 - DAT_00104010);
    DAT_00104028 = DAT_00104028 + 1;
  }
  return iVar1;
}
```

The above methods effectively check if input matches the decrypted form of "fhz4yhx|~g=5" by maintaining static variables.

```c
#include <stdio.h>
#include <string.h>
int main()
{

    char i = 'u';
    char j = 'A';
    int local_14 = 1969;
    char str[] = "fhz4yhx|~g=5";
    for (int i = 0; i < strlen(str); i++)
    {

        local_14 = (local_14 * 7) % 65536;
        str[i] = str[i] + ((char)(local_14 / 10) * (char)10 - (char)local_14);
        printf("%c", str[i]);
    }
}
output:ccs-passwd44
```
```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5db0ef9f33c5d46f00e2c729$ ./login 
Don't patch it!
Insert your password: ccs-passwd44
Correct!
```

#### Hence the password is `ccs-passwd44`


### 5. [Fifth](https://crackmes.one/crackme/5d8dfa7433c5d46f00e2c544)



```bash
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x08049000  _init
0x08049030  printf@plt
0x08049040  puts@plt
0x08049050  __libc_start_main@plt
0x08049060  __isoc99_scanf@plt
0x08049070  _start
0x080490b0  _dl_relocate_static_pie
0x080490c0  __x86.get_pc_thunk.bx
0x080490d0  deregister_tm_clones
0x08049110  register_tm_clones
0x08049150  __do_global_dtors_aux
0x08049180  frame_dummy
0x08049182  __s_func
0x080491ad  __f_func
0x080491d8  f
0x08049218  main
0x08049239  __x86.get_pc_thunk.ax
0x08049240  __libc_csu_init
0x080492a0  __libc_csu_fini
0x080492a4  _fini
(gdb) disass main
Dump of assembler code for function main:
   0x08049218 <+0>:	push   ebp
   0x08049219 <+1>:	mov    ebp,esp
   0x0804921b <+3>:	and    esp,0xfffffff0
   0x0804921e <+6>:	call   0x8049239 <__x86.get_pc_thunk.ax>
   0x08049223 <+11>:	add    eax,0x2ddd
   0x08049228 <+16>:	call   0x80491d8 <f>
   0x0804922d <+21>:	call   0x80491ad <__f_func>
   0x08049232 <+26>:	mov    eax,0x0
   0x08049237 <+31>:	leave  
   0x08049238 <+32>:	ret    
End of assembler dump.
(gdb) disass __f_func
Dump of assembler code for function __f_func:
   0x080491ad <+0>:	push   ebp
   0x080491ae <+1>:	mov    ebp,esp
   0x080491b0 <+3>:	push   ebx
   0x080491b1 <+4>:	sub    esp,0x4
   0x080491b4 <+7>:	call   0x8049239 <__x86.get_pc_thunk.ax>
   0x080491b9 <+12>:	add    eax,0x2e47
   0x080491be <+17>:	sub    esp,0xc
   0x080491c1 <+20>:	lea    edx,[eax-0x1fef]
   0x080491c7 <+26>:	push   edx
   0x080491c8 <+27>:	mov    ebx,eax
   0x080491ca <+29>:	call   0x8049040 <puts@plt>
   0x080491cf <+34>:	add    esp,0x10
   0x080491d2 <+37>:	nop
   0x080491d3 <+38>:	mov    ebx,DWORD PTR [ebp-0x4]
   0x080491d6 <+41>:	leave  
   0x080491d7 <+42>:	ret    
End of assembler dump.
(gdb) disass __s_func
Dump of assembler code for function __s_func:
   0x08049182 <+0>:	push   ebp
   0x08049183 <+1>:	mov    ebp,esp
   0x08049185 <+3>:	push   ebx
   0x08049186 <+4>:	sub    esp,0x4
   0x08049189 <+7>:	call   0x8049239 <__x86.get_pc_thunk.ax>
   0x0804918e <+12>:	add    eax,0x2e72
   0x08049193 <+17>:	sub    esp,0xc
   0x08049196 <+20>:	lea    edx,[eax-0x1ff8]
   0x0804919c <+26>:	push   edx
   0x0804919d <+27>:	mov    ebx,eax
   0x0804919f <+29>:	call   0x8049040 <puts@plt>
   0x080491a4 <+34>:	add    esp,0x10
   0x080491a7 <+37>:	nop
   0x080491a8 <+38>:	mov    ebx,DWORD PTR [ebp-0x4]
   0x080491ab <+41>:	leave  
   0x080491ac <+42>:	ret    
End of assembler dump.
(gdb) disass f
Dump of assembler code for function f:
   0x080491d8 <+0>:	push   ebp
   0x080491d9 <+1>:	mov    ebp,esp
   0x080491db <+3>:	push   ebx
   0x080491dc <+4>:	sub    esp,0x24
   0x080491df <+7>:	call   0x80490c0 <__x86.get_pc_thunk.bx>
   0x080491e4 <+12>:	add    ebx,0x2e1c
   0x080491ea <+18>:	sub    esp,0xc
   0x080491ed <+21>:	lea    eax,[ebx-0x1fde]
   0x080491f3 <+27>:	push   eax
   0x080491f4 <+28>:	call   0x8049030 <printf@plt>
   0x080491f9 <+33>:	add    esp,0x10
   0x080491fc <+36>:	sub    esp,0x8
   0x080491ff <+39>:	lea    eax,[ebp-0x28] <= buffer is pasted here 
   0x08049202 <+42>:	push   eax
   0x08049203 <+43>:	lea    eax,[ebx-0x1fca]
   0x08049209 <+49>:	push   eax
   0x0804920a <+50>:	call   0x8049060 <__isoc99_scanf@plt>
   0x0804920f <+55>:	add    esp,0x10
   0x08049212 <+58>:	nop
   0x08049213 <+59>:	mov    ebx,DWORD PTR [ebp-0x4]
   0x08049216 <+62>:	leave  
   0x08049217 <+63>:	ret    
End of assembler dump.
```
We see that the normal flow of the program is that after accepting input in f(), the function `__f_func()` is called next. However to crack it, we need to call `__s_func()`.
The stack in function f() has the following structure

| Stack Offset / Register     | Value / Description         |   |
|----------------------------|-----------------------------|---|
| Return Address             | [Calling function address]  | <=ebp+4  |
| Saved EBP                  | previous ebp            | <=ebp   |
| Saved EBX                  | ebx                        |  <=ebp-4|
| Buffer byte 33-36                 | ...                         |  <=ebp-8 |
| Buffer byte 29-32                 | ...                         |  <=ebp-12 |
| Buffer byte 25-28                 | ...                         |  <=ebp-16|
| Buffer byte 21-24                 | ...                         |  <=ebp-20|
| Buffer byte 17-20                 | ...                         |  <=ebp-24 |
| Buffer byte 13-16                  | ...                         | <=ebp-28  |
| Buffer byte 9-12                   | ...                         |  <=ebp-32 |
| Buffer byte 5-8                   | ...                         |  <=ebp-36 |
| Buffer byte 1-4              | ...                         | <=ebp-40  |



The goal to cause buffer overflow to change to $ebp+4 to point to the address of `__s_func()` function. The input is stored on the stack at $ebp-0x28. To overflow to $ebp+4, we need 44 characters to fill $ebp-40 through $ebp and the characters beyond 44th character, get stored in $ebp+4, which is transfered to $eip after return from function f()

This can we verified using gdb:
for input aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz,
$eip contains wwxx after the program crashes.
![](https://res.cloudinary.com/dwmy4l7ok/image/upload/Screenshot_from_2025-06-11_13-03-57_orghbw.png)

The address of `__s_func() is 0x8049182`. We see that overflow to $ebp happen after 44 characters of input. Hence '\x82\x91\x04\x08' (little endian format) is appended to random 44 characters to call the function.

```bash
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5d8dfa7433c5d46f00e2c544$ python3 -c "import sys; sys.stdout.buffer.write(b'A'*44 + b'\x82\x91\x04\x08')" | ./crackme
enter the password:Great !!
Segmentation fault (core dumped)
(base) arnab@arnab-LOQ-15AHP9:~/Downloads/5d8dfa7433c5d46f00e2c544$ printf 'aaaaaaaaaaaagameaaapclubaaaaaaahackingaaaaaa\x82\x91\x04\x08' |./crackme
enter the password:Great !!
Segmentation fault (core dumped)
```