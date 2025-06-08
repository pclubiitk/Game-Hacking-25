### ASSIGNMENT 1
## (I) GDB picoCTF tasks 

#Task 1: GDB Baby step 1
Task was to find the contents of the eax register at the end of main. 
Here is the photo of disassembled main.
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image1.png')


Second last command shows moving 0x86342 into $eax register. If directly run, main will return all the registers before we get to examine them. So, putting a break point at main will help. 
This stops the flow at 0x0000555555555131 in main. Stepping until the command just after moving into $eax lets us examine the register.

A simple _print/d $eax_ gives the contents of eax in decimal form.
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image2.png')


#Task 2: GDB baby step 2
Task is to find the contents of the eax register inside main. 
The disassembled main is as follows:
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image3.png')

Disass of main shows a set of calculations being carried out. 
1. We can calculate the contents of eax ourselves.
2. We set a breakpoint just after the contents being moved into eax register and then use the command _info register eax_. 

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image4.png')

#Task 3: GDB baby step 3
Task is to find byte-wise the memory that the constant 0x2262c96b is loaded. 
Disassembled main is as follows:
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image5.png')

The constant is loaded  into the memory at the address 0x0000000000401115. It would be wise to place a break point just after this to examine the register into which it is moved.
Run the main function. Upon reaching the breakpoint, step once to load the contents. 
Use the command _x/4xb $rbp-4_ to find the order of the bytes that was loaded. 
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image6.png')

The contents of $rbp-4 shows big endianness. Printing the outputs of $eax will not give this output as the endianness characteristics is not followed. 

#Task 4 : GDB baby step 4
Task is to find the constant by which register $eax is multiplied.
Disassembled main is as follows:

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image7.png')

Main shows a function being called in memory address 0x0000000000401142. According to the hint, a function can be referenced by either its name or its starting address in gdb. Starting address is given as 0x401106.

Disassembled function is as follows:
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image8.png')

We can see the command imul where the constant $0x3269 is multiplied to $eax. Required constant is hence 12905, the decimal form of 0x3269.


## (II) CRACKME Reverse Engineering tasks 

# Task 1 : ezman's easy keyg3n
Upon running the keyg3nme binary, we observe that it is asking for a key. Task is to find this key.
Using ghidra, we disassemble this binary file.
Under the list of functions, we see the main function
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image9.png')

Inside the main, we see the use of another function _validate string_. Upon further investigation of the function _validate string_, we see the following:

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image10.png')

Hence, the key is decimal form of 0x4c7, which is 1223

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image11.png')

# Task 2 : cbm-hackers's jumpjumpjump
Disassembling the binary file ./rev03, shows us the main function

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image12.png')

The main function tells us how to get the fail. It first, takes input of a string, acStack_98 and it also stores the length of the string in sVar1. 
The if condition proceeds only if sVar1 is less than 0xc, which is 12, indicating that our _magic string is of length less than 12_. 
Inside the if statement, iStack_20 is initialized to 0 and a while loop begins.

uVar2 is the unsigned long version of iStack_20. 
The loop gets the character sum of entered magical string, which is stored in iStack_lc. 
If the character sum of entered string is 1000, the flag is given to us.
Hence, dddddddddd should work, as ord(d) = 100, character sum of dddddddddd = 100*10 = 1000.
To avoid newline character being considered, we enter
echo -n dddddddddd | ./rev03.

![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image13.png')


# Task 3 : Loz's Password Login 2
Having run ghidra through the binary file, .main, it showed two important things:
    1. Main function
    2. Password class
The main function gets a standard input and first passes the input through a function, password::checkLength(). 
The checkLength() uses a variable uStack_lc = 0x168 which is 360 in decimal form.
This number is converted to a string using the std::to_string function. An at function is applied to it, with 1 as the parameter.
Hence the returning value will be character "6" (index 1 of 360). Using the operator (=), this character is assigned to pcVar2, on which atoi() function is applied and integer 6 is obtained. 
Later, 1 is added to it. Hence, finally, the length of our desired password is 7.

In the main function, further calls are carried out only if length is equal 7. Once passed, the password is passed through function password::checkPassword().

checkPassword() function was highly confusing. Some major things in it where the comparison between asStack_78 
and asStack_98.
And, the line **std::__cxx11::string::operator+=(asStack_78,(byte)ppStack_a0[4] ^ *pbVar6);**
This shows that the each char of the string is being encoded by XOR'ing it with the key, pbVar6.

I then moved on to another function of the password class. 
There it was clear that the string being encoded is "x_.1:.-8.4.p6-e.!-" and the key is 0x42, which is 66 or char 'B'. 
Reverse encoding of the above string gives following
![All text]('/home/ton168/GH-Assignments/Game-Hacking-25/Assignment-1/Assignment Submissions/images/image14.png') 

Above was done with the python file, xor_decoding.py.
But, the above does not seem to be the password. 

# Task 4 : Silva97's login-cipher

