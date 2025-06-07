# GDB
## Challenge 1
First we open the file in gdb.
![image](https://github.com/user-attachments/assets/87e4aa02-5e4a-4aab-83b3-f87fba8e2f75)
Then we use **info functions** to get the names and adresses of the functions.
![image](https://github.com/user-attachments/assets/c99315dd-c01c-4b16-ba05-4d54b9caa9f0)
Then we disassemble the main function using **disass main**.
![image](https://github.com/user-attachments/assets/65bf4762-2a8a-441d-a248-fc30ddbebdb2)
We can see what is in the eax register. Now we simply print this value in decimal format.
![image](https://github.com/user-attachments/assets/50914a38-95d0-4ee6-a99b-aee06f129d2f)
Thus, we get our our flag i.e. **picoCTF{549698}**. This was simple as we could directly see the value of the eax register in the main function.
## Challenge 2
First we use **info functions** and then **disass main** to see the structure of the main function.
![image](https://github.com/user-attachments/assets/3cb2b8ac-ac82-4d53-b939-164c80af2bae)
This time we cannot directly see the value of the eax register as eax is being assigned a value which is stored in the value of the address __[rbp-0x4]__. So, we have to try a different approach this time. We first change the layout to asm, set the break point at main and then run the program.
![image](https://github.com/user-attachments/assets/8790ec58-63d0-44f8-b0e7-9c85729b5d31)
Now, we set another breakpoint at the address of the return statement and continue the execution. This will allow us to get the address of the eax register at the end of the main function.
![image](https://github.com/user-attachments/assets/3e54fe22-8ac6-4eea-81c9-a4f07095ea11)
Now, we just print the value of the eax register in decimal using the command **p/d $eax**.
![image](https://github.com/user-attachments/assets/77ca61a5-7af0-4cd8-b387-d8fb9b7d3be5)
We got our flag i.e. **picoCTF{307019}**. We had to set specific breakpoints and then run the program to get the value of the eax register.
## Challenge 3
Again, we first use **disasss main**. We can see that the constant is loaded in the memory adddress __rbp-4__.
![image](https://github.com/user-attachments/assets/c4f9e93c-a1fe-4160-869b-3151607778aa)
We now change the layout to asm and set breakpoint at the pop statement and run.
![image](https://github.com/user-attachments/assets/63c30cd4-7dc2-469a-8f26-c2e8e75967b5)
Now we see the memory content using the **x/4xb $rbp-4** command.
![image](https://github.com/user-attachments/assets/7addf6cc-19dd-477e-9407-a2a63fccd76d)
We can see the 4 bytes stored in the memroy, so our flag is picoCTF{0x6bc96222}.
## Challenge 4
We first use **disass main**.
![image](https://github.com/user-attachments/assets/825fa1e1-a72f-4d11-b16b-3098538c2423)
We see that there is another function inside main named **func1**. So we disassemble this using **disasss func1**.
![image](https://github.com/user-attachments/assets/a610e44c-6028-4a46-91db-60e18c5f3370)
We can see that the eax register is getting multiplied by the constant **0x3269**. So now we just print the constant in decimal base.
![image](https://github.com/user-attachments/assets/be58bb39-4f60-4a37-98b1-0004066c0274)
We get our flag as **picoCTF{12905}**.
