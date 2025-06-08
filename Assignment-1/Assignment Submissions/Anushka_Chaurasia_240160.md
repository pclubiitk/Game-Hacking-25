# GDB baby step-1
## We were supposed to debug the given file to find the flag which was the hexadecimal value moved to the eax register at the end of the main function. 
For this I have used GNU Debugger or GDB. 
- First, I copied the file link and used wget command in terminal to download the file. 
- Then, I wrote the command gdb debugger0_a(file name) to load a binary executable for debugging
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/1.jpg) . 
- Third command used was info functions to list down all the function names present in the file
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/2.jpg) .
- Then, I tried to set a breakpoint at main and run the program to check if it works. It gave a hexadecimal, which however was not the correct flag.
- Then I disassembled main function, reading and understanding of the assembly made me figure out that 0x86342 was the value moved to eax register. Hence, converting it to decimal using p/d  0x86342 gave me 549698, which was the correct flag.
- ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/3.jpg) 
## Below is the list of commands I used to correctly figure out the flag :
```
wget (file hyperlink)
gdb (file name)
break main
run 
disassemble main 
p/d 0x86342
```

# GDB baby step-2
## For this one, I copied the hyperlink of file and downloaded it using wget command.
- Then initialized the gdb debugging process. Using info functions, all the function names of the file were listed.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/4.jpg)
- Disassembling the main function, it was figured out that it was initialising a variable with 0x1e0da which is hexadecimal of 123098. ((0x401115 <+15>:  movl   $0x1e0da,-0x4(%rbp))) (add this line in code form).
- Then, another variable was inialised with 607 using this line ((0x40111c <+22>:  movl   $0x25f,-0xc(%rbp))).
One more variable was initialised with 0 using ((0x401123 <+29>:  movl   $0x0,-0x8(%rbp))).
- Then, the assembly code represents a loop which keeps adding all integers from1 to 606 to 123098. It returns the result of addition of 123098 + 183921 = 307019 which is the flag. Here, 183921 is the sum of first 606 natural numbers.
  ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/5.jpg)
## Below is the list of all commands used
```
wget (file hyperlink)
gdb (file name) 
info functions
disassemble main
p/d 0x1e0da
```
###Other calculations were done manually.

# GDB baby step-3
## For this CTF, we were supposed examine byte wise the memory that the constant 0x2262c96b in the main function is loaded in by using the GDB command x/4xb addr. We were told that the flag is the four bytes as they are stored in memory. 
- First step, was simply to copy the hyperlink and download it using wget command from the terminal. 
- Then, the command file (file name) was used to get information about the file, which revealed that it was a non-stripped ELF file. 
- Third step was to initiate the debugging process using gdb (file name).
  ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/6.jpg) 
- Then, I did info functions to list all function names present in the file. 
- Then, disassembling the main function, it was clearly visible that the given constant 0x2262c96b was moved to rbp-0x4.
  ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/7.jpg)
- Then, using the command mentioned in the question with $rbp-0x4, to point to the same memory location, the four bytes 0x6b 0xc9 0x62 0x22, combining which in the format given in description of the problem gave me the flag.
  ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/8.jpg)
## Below is the list of commands that I used :
```wget (file hyperlink)
file (file name)
gdb (file name) 
info functions
disassemble main
break *0x40111c
run 
x/4xb $rbp-0x4
```

# GDB baby step-4
## In this CTF, main calls a function that multiplies eax by a constant. The flag for this challenge is that constant in decimal base. 
- First step, was obviously to copy the hyperlink and download it using wget command. 
- Then, to know the file type and more type about the file, used the file command. Then, initiates the gdb debugging process. 
- ![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/9.jpg)
- Then, did info functions to list all function names.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/10.jpg)
- Then, disassembling main function, got that main function calls the function func1. 
- Then, I proceeded to disassemble func1 function.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/11.jpg) 
- Then, reading and understanding the assembly of the function, I figured out that 0x3269 is the constant being multiplied. Converting it to decimal gave 12905, which was the correct flag.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/12.jpg)
## Below is the list of all commands used :
```
wget (file hyperlink)
file (file name)
gdb (file name)
info functions
disassemble main
disassemble func1
p/d 0x3269
```
# Crackme 1
## For this crackme,  ghidra is used.
- I first downloaded the zip file and unzipped it which gave a binary elf file keyg3nme. 
- Running this file, it asked for a key, we were supposed to find out the key validation logic for this key.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/13.jpg)
- Proceeding, I imported the file in ghidra and let ghidra analyse it.
- Figuring out the main function from the the list of functions that ghidra displayed after analysing the file, I found out the main function which looked like this.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/14.jpg)
- In order to validate the key, it was calling a function validate_key, Hence the next step was to understand what this function was doing.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/15.jpg)
- It was performing a complex mathematical operation, which was ultimately trying to check if the key entred is divisible by 1223. Figuring out what this complicated mathematical expression meant entirely on my own was not an easy task, so I took some help of AI.
- It made me figure out that (int)((long)param_1 * 0x1acb0dad >> 0x27) This is an optimized way to do integer division by 1223.
# Crackme 2
## To start with, just like any other crackme, I downloaded the file using hyperlink and wget command. 
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/16.jpg)
- Then unzipped it to find a file named rev03. Running this file, it asked to enter a magic string, I entered a random string which ended up showing wrong string.
- Hence, I proceeded with using ghidra. The main function after analysing had the logic for checking if the string entered was correct.
![](https://raw.githubusercontent.com/anushka-2201/Game-Hacking-Assets/main/17.jpg)
- In order to understand the logic mentioned, I had to take help from writeups.
- The function stores input using fgets(local_98, 100, stdin). Then, it measures the length of the string with strlen. If the string is shorter than 12 bytes (if (sVar1 < 0xc)), it proceeds.
- From the function it seems like that any string with less than 12 characters and ascii sum equal to 1000 satisfies as a magic string. However, there seems to be a catch in the function logic due to input taken using fgets function, which automatically adds next line character (\n) if there is room.
- Since, \n has ascii value 10, the total ascii sum for the string to be correct becomes 990. Hence, any string with less than 12 characters and ascii sum as 990 is a magic string.
