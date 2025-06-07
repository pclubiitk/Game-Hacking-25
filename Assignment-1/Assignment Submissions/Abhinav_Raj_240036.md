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

