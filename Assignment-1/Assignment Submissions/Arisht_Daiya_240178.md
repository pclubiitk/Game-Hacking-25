![image](https://github.com/user-attachments/assets/f16b0f76-e71a-45e4-8b06-12c8830bb9f8)# GDB
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
# Reversing - Crackmes
## Challenge 1
We first open the file in ghidra and see that in main function it is using a function **validate key** to check if our key is correct or not.
![image](https://github.com/user-attachments/assets/6711e7d2-e5e9-4227-9087-02216dc89d2f)
So, we now see the code of validtae key function and see that it returns 1 if the key is divisible by **0x4c7**(which is **1223** in decimal).
![image](https://github.com/user-attachments/assets/bdbecc3b-5157-4793-8326-97bacaa31b78)
Now, we just run the program and enter any number which is divisible by 1223.
![image](https://github.com/user-attachments/assets/f3a5755a-a9b4-49da-bb54-35fdab0e5698)
## Challenge 2
We open the file in ghidra and see the main function.
![image](https://github.com/user-attachments/assets/18a23eeb-f202-47d0-b7b4-54ba7940578f)
From the code we can see that we have to input a string which is less than 12 characters long(including the \n which fgets adds to the end of the input) such that the sum of the ASCII values of all the characters is equal to 1000(including the \n). So we input the string **nnnnnnnnn**.
![image](https://github.com/user-attachments/assets/40b8f22b-9750-4d0e-9ad3-d671d08b6cfe)
Our flag is **!#&*/5<DMW**. We could have also got this flag by analyzing the **strcat_str** function by calculating what the string would be.
![image](https://github.com/user-attachments/assets/bc8fcc1f-d392-42ce-8ff6-767784b17c97)
## Challenge 3
We open the file in ghidra and see the main function.
![image](https://github.com/user-attachments/assets/8deb7363-906d-4558-b2c4-51e46753ef27)
We see that we are storing the input string in local_58 and a password class is defined to local_88. We are storing the length of the input string in the iVar2 variable and passing the password class and iVar2 in the **checkLength** function. In the class we can see that there is an int member **(0x42/66)** and a string member **("x_.1:.-8.4.p6-e.!-")**. ***Note that this[4] is equal to 0x42 and that (string\*) this + 8 is the string "x_.1:.-8.4.p6-e.!-"***
![image](https://github.com/user-attachments/assets/7851aca5-a488-4f16-a9d6-e6b223a798ee)
We see that in the **checkLength** function, a local constant **0x168(360)** is defined and it is converted to string. Then we pcVar2 is defined as a character of that string and is then converted to a string and a variable iVar1 is then initialized and assigned the value of that number(the character corresponds to a number) + 1 and compared with the param_1 i.e. the length of the input string. If they are equal, the function returns 1 else it returns 0. We can see in main that in order to get the correct key we need the output of this to be 1. ***Also, note that \*(int \*)this is equal to iVar1. This will be helpful later on.*** 
![image](https://github.com/user-attachments/assets/deb35023-0805-423c-bedc-e89698adef47)
But we have a problem, we don't know which digit of 360 pcVar2 is assigned to. For this we analyze the at function and see that the default value is 1 so pcVar2 is equal to the 1st index of 360 which is **6**. Thus, we can conclude that we need a string of length **6+1=7**.
![image](https://github.com/user-attachments/assets/cf7d1e51-cd68-4732-9524-2b7da1d1180b)
The next step is the checkPassword function which takes the local_88(password class) and the input string as parameters and returns 0 or 1 depending on certain conditions. If this output is 1, we will get the right password. So we now analyze the checkPassword function. We see that a a loop runs where local_2c varies from 0 to length of the input string(which in ideal case should be 7) - 1 and each time the character at that index is getting XOR'd be local_a0[4] i.e. this[4] which we know from earlier is equal to **0x42**. So we can conclude that each charcter of the input string is getting XOR'd by a key i.e. **0x42**(which is **66** in decimal; here it will correspond to the chracter that has the ASCII value of 66 which is **'B'**). This new string is stored in local_78. Then we see a string copy function which is taking 3 parameters(the original string, from which index to start copying from, and the length of the copied string). We can see that the orginal string is equal to (string \*)this + 8 which we know is "x_.1:.-8.4.p6-e.!-". The length is similarly equal to \*(int \*) which is equal to 7. For the start index, we see the assembly code.
![image](https://github.com/user-attachments/assets/87aa7b9c-6114-4d21-bf0f-08025a9b59ab)
Here we can see that the value of the second parameter is hardcoded as 0x5(5). Thus, we got the local_48 string as **".-8.4.p"**. On reading further we see that this string and the XOR'd input string(local_78) are getting compared and we get 1 as output if they are equal. So, we need to enter a password of length 7 such that the XOR of which gives us the string **".-8.4.p"**. For this, we use a property of XOR that if we XOR an already XOR'd string, we get the original string. So the password is the XOR of the string ".-8.4.p" which is **"lozlvl2"**.
![image](https://github.com/user-attachments/assets/cabddcbb-28aa-4bed-b0ae-9be246b3b1ab)
And we see that it works!
## Challenge 4
We first open the file in ghidra and browse through the different functions. The function FUN_001012a1 seems useful as there is an if else statement which calls another function FUN_00101348 but the parameters are different. Also, the if condition compares 2 values one of which is user input(scanf). This is the password check block. Now, we just need to make the if condition true.
![image](https://github.com/user-attachments/assets/fe4c6c36-ecfb-4f2d-a188-d2c601c32587)
For this, we see the FUN_001013e3 function. This function checks if param_1 matches with a dynamically generated string(generated by the function FUN_00101175) with param_2 as the seed. If it does, it returns 0 which is our desired output.
![image](https://github.com/user-attachments/assets/10974809-0487-4e28-b17c-16337ca05ffc)
So, we now see what string the FUN_00101175 function generates. The string generated by this is ccs-passwd44. Thus, this is our password.
![image](https://github.com/user-attachments/assets/2c27d6a9-fbc9-46c1-bf7e-f4dd6de71455)
## Challenge 5
Found out the f_func, s_func, main and f but didn't know what to do after that.
