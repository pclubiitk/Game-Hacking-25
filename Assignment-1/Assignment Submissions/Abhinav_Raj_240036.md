# GDB
---
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
Info func  
disass main  
b main  
r  
b *0x40111f  
c  
```
gef➤  x/4xb $rbp-4
0x7fffffffdd7c:	0x6b	0xc9	0x62	0x22
```

b 
