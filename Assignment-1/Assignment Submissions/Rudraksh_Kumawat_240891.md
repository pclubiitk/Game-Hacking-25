# Assignment 1

## [https://play.picoctf.org/practice/challenge/395?category=3&page=1&search=GDB](https://play.picoctf.org/practice/challenge/395?category=3&page=1&search=GDB)

![image.png](/Rudraksh_Kumawat_240891/image.png)

So on directly disassembling this using gdb we get -

![image.png](/Rudraksh_Kumawat_240891/image%201.png)

and here clearly wirtten `0x86342` before eax.
`0x86342` is in Hexadecimal form so we have to convert it to decimal form and its decimal form is `549698`.

Flag - `picoCTF{549698}`

---

---

## [https://play.picoctf.org/practice/challenge/397?category=3&page=1&search=GDB](https://play.picoctf.org/practice/challenge/397?category=3&page=1&search=GDB)

![image.png](/Rudraksh_Kumawat_240891/image%202.png)

So I this challenge I have to set a breaking point after the hex is being loaded to memory.

so here is how I done this

![image.png](/Rudraksh_Kumawat_240891/image%203.png)

Flag — `picoCTF{0x6bc96222}`

---

---

## [https://play.picoctf.org/practice/challenge/398?category=3&page=1&search=GDB](https://play.picoctf.org/practice/challenge/398?category=3&page=1&search=GDB)

![image.png](/Rudraksh_Kumawat_240891/image%204.png)

So this is the easiest one I think.

noting to do just on disassembling main file you see that a function named func1 is being called 

and on disassembling the function we get a step where `eax` is being multiplied by `0x3269` .

And the decimal value of `0x3269` is `12905` .

flag = `picoCTF{12905}`

![image.png](/Rudraksh_Kumawat_240891/image%205.png)

---

---

## [https://play.picoctf.org/practice/challenge/396?category=3&page=1&search=GDB](https://play.picoctf.org/practice/challenge/396?category=3&page=1&search=GDB)

![image.png](/Rudraksh_Kumawat_240891/image%206.png)

So in this we are supposed to analyse the main code by disassembling and get the flag.

`Disassembled Main :`

![image.png](/Rudraksh_Kumawat_240891/image%207.png)

We want to find the value stored inside register `-0x4(%rbp)` .

Initial value stored in the register `-0x4(%rbp)` is hex : `0x1e0da` which is 123098 in Decimal.

Here in the code we can see that at memory  `0x000000000040113c` there is a loop that runs on the basis of comparision b/w   `-0xc(%rbp)` & `%eax` and a the end of the loop.

at the end of the loop the decimal value stored in `-0x4(%rbp)` is 307019.

Flag == `picoCTF{307019}`

---

---

## [https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661](https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661)

![image.png](/Rudraksh_Kumawat_240891/image%208.png)

So If First I got a executable file named “ keyg3nme “

![image.png](/Rudraksh_Kumawat_240891/image%209.png)

form this I have to find out what logic is being used in key validation ( some Function )

I used ghidra to decompile the executable file , it has a function named validate_key in which logic is give as

```cpp

bool validate_key(int param_1)

{
  return param_1 % 0x4c7 == 0;
}
```

so the answer for question is param_1 % 0x4c7 == 0

![image.png](/Rudraksh_Kumawat_240891/image%2010.png)

So the key is 0 or any multiple of 1223.

---

---

## [https://crackmes.one/crackme/5c1a939633c5d41e58e005d1](https://crackmes.one/crackme/5c1a939633c5d41e58e005d1)

![image.png](/Rudraksh_Kumawat_240891/image%2011.png)

Not much given in the question so just directly executed the downloaded executable file “ rev03 “

File Type :

`rev03: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=9d23fcc7b9cf9c42f809d46f50ccc249de567cc6, not stripped`

So in console it runs like

```bash
> ./rev03
enter the magic string # On entring correct string it gives us the flag otherwise
hello # entered incorrect string
wrong string #output
No flag for you. 
```

I directly opened this file in ghidra and looked for functions , In main function the logic of code is give 

![image.png](/Rudraksh_Kumawat_240891/image%2012.png)

Here from this logic I able to reverse engineer the file.

Logic — Have to enter a string having length less than 12 ( string + character ‘ \n ‘) such that the sum of ASCII codes of character is equal to 1000 ( 10 chracter + ‘ \n ‘ having ASCII code 10 )

so we have to enter string of 9 characters and some of there ASCII code = 990.

Easiest combination “cccccccccc” —  ‘ c ‘ ASCII code = 99

so sum = 990 .

![image.png](/Rudraksh_Kumawat_240891/image%2013.png)

 

finally flag = `flag{!#&*/5<DMW}`

---