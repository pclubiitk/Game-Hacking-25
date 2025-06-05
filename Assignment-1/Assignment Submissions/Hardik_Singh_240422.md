# Solutions
Following are the solutions for the challenges listed in the current assignment. They require prerequisition with GDB or GNU DeBugger for the first half of the challenges, while a fair knowledge of Reverse Engineering and System Architecture is required for the second half of the challenges; although the problems are quite beginner friendly! :P
## GDB

### 1. <a href = "https://play.picoctf.org/practice/challenge/395?category=3&page=1&search=GDB">GDB baby step 1 - picoCTF challenge 395 </a>
![image](https://github.com/user-attachments/assets/1267618b-e682-4916-af6a-fa8d0b86e6ee)

We can see that the challenge provides us with a file to debug using the GNU debugger. Make sure to give the file a 777 access so that you can properly run it, although that won't be necessary as we will see.

Run the commands
```
sudo chmod +777 ./debugger0_a
sudo gdb ./debugger0_a
```

You will be greeted by the gdb interface, which might look like this:
![image](https://github.com/user-attachments/assets/497c4d50-d18c-441b-979b-23efa73286cc)

Now follow up with the command to get a cleaner interface.
```
lay next
```
Once you reach here:
![image](https://github.com/user-attachments/assets/223feeeb-b255-4602-86d6-aef65f1b2014)
hit enter 3 times to get here:
![image](https://github.com/user-attachments/assets/063c42fe-8930-4935-b494-002ea8a04117)

Now set a breakpoint at main using the ```break``` command, then keep running the next instructions one-by-one using ```nexti``` until you reach the ```<main+15>``` instruction, where you will clearly see the value that the register ```rax``` is holding (note that the problem mentions the ```eax``` register but since most systems nowadays have the 64 bit architecture, you are most likely to encounter the ```rax``` register).
![image](https://github.com/user-attachments/assets/2911bbfc-e4a3-4ac1-9b4d-1b91de69ee23)

Thus our user friendly GDB interface greets us with not only the hex but also the decimal value of the register ```rax```, which is precisely what the question demands from us.

Finally, we get the flag

```
picoCTF{549698}
```

### 2. <a href="https://play.picoctf.org/practice/challenge/396?category=3&page=1&search=GDB">GDB baby step 2 - picoCTF challenge 396</a>

![image](https://github.com/user-attachments/assets/affa31de-63c5-420f-a38c-5a396a293c3b)

We can see that the challenge provides us with a file named ```debugger0_b```. Thus, we use our trusted friend GDB to debug the file once again!

Now go ahead and execute the command ```sudo gdb ./debugger0_b```, and follow it up by ```lay next``` inside the gdb environment, and then hit enter three times to show the registers value during the execution of the program.

![image](https://github.com/user-attachments/assets/1e9bdde6-2448-48ba-a78d-453fedf1c795)

Now go ahead and set a breakpoint at main and run the program.

```
break main
run
```

Now use the ```next``` command that will single step out of the main function and gdb will reward you with the value of ```eax``` (or ```rax``` for 64-bit systems). This is the value that we require and thus we submit the flag

```
picoCTF{307019}
```

### 3. <a href="https://play.picoctf.org/practice/challenge/397?category=3&page=1&search=GDB">GDB baby step 3 - picoCTF challenge 397</a>
![image](https://github.com/user-attachments/assets/29afb2e8-06f7-4d3c-ae34-dc6fdc3905b5)

The challenge provides us with a file ```debugger0_c```. In similar fashion to the previous two problems, we proceed to use ```gdb```.

```
$ sudo chmod +777 debugger0_c
$ sudo gdb ./debugger0_c
```
```
(gdb) lay next
(gdb) break main
Breakpoint 1 at 0x40110e
(gdb) run
Starting program: debugger0_c
...
Breakpoint 1 at 0x000000000040110e in main()
(gdb) nexti
0x0000000000401111 in main()
(gdb) nexti
0x0000000000401115 in main()
(gdb) nexti
0x000000000040111c in main()
(gdb) x/4xb $rbp-4
0x7fffffffe29c: 0x6b 0xc9 0x62 0x22
(gdb)
```

Thus we find the final flag to be:
```
picoCTF{0x6bc96222}
```
### 4. <a href = "https://play.picoctf.org/practice/challenge/398?category=3&page=1&search=GDB">GDB baby step 4 - picoCTF challenge 398</a>

![image](https://github.com/user-attachments/assets/ce7af193-3334-4f81-9fa1-ba775700dff8)

The challenge provides us with a file ```debugger0_d```. In similar fashion to the previous two problems, we proceed to use ```gdb```.

```
$ sudo chmod +777 debugger0_c
$ sudo gdb ./debugger0_c
```
Don't forget to hit return three times to show assembly code as well as register values in GDB.
![image](https://github.com/user-attachments/assets/76f0de8a-3536-4ebe-9785-7db1be7d3314)

As usual, we set breakpoint at main using ```b main``` and then ```run``` the program. Now we move instruction by instruction using ```nexti``` until we reach the ```0x401140``` instruction pointer. We see that at this point, ```eax``` holds the value ```654```.
![image](https://github.com/user-attachments/assets/cc9f588b-b4c6-4f13-9941-6239f1cfd5a6)

Now we move the instruction pointer to ```0x401147```, where we notice that the ```eax``` pointer now holds the value ```8439870```, and thus we find the constant to be ```12905```.
![image](https://github.com/user-attachments/assets/aec42db8-e3d4-4b7b-807e-2ce09b5434b3)


Thus, the final flag is:

```
picoCTF{12905}
```

## Reversing - crackmes

### 1. <a href="https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661">ezman's easy keyg3nme</a>

<div align="center">
  <em>A screenshot of the challenge</em>
</div>

![image](https://github.com/user-attachments/assets/f6568216-9b41-4a72-95ca-5a5adb6c5ddd)

Let's go ahead and download the file listed in the challenge. We obtain a `zip` file which is password-protected. The password is `crackmes.one`. We then get the file `keyg3nme`. Now open up your favorite disassembler (mine is IDA by Hex-Rays) and load this file.

<div align="center">
<em>This is what it should look like</em>
</div>

![image](https://github.com/user-attachments/assets/9ebb6294-576d-4d1b-a9cf-860943e18fc6)

Now press the `F5` key to open the pseudocode view. We notice the `validate_key` function in the `main` function. Double click on the `validate_key` label to see its contents.

<div align="center">
<em>Contents of the `validate_key` function</em>
</div>

![image](https://github.com/user-attachments/assets/de0980d0-d751-49fa-8716-049456134ccd)

As we can see, the funciton will only validate our key if it is divisible by 1223. Thus, we can run the file and enter any multiple of 1223, and surely enough, our key is validated.

<div align="center">
<em>Not so impressive, right?</em>
</div>

![image](https://github.com/user-attachments/assets/61ce4a61-bca9-430a-9c8f-ed64a8715df3)

### 2. <a href="https://crackmes.one/crackme/5c1a939633c5d41e58e005d1">cbm-hackers's jumpjumpjump</a>

<div align="center">
<em>A screenshot of the challenge</em>
</div>

![image](https://github.com/user-attachments/assets/852dcbdd-fac7-4a25-9495-b7813d9d1975)

Just like last time, we download the `zip` folder and extract the `rev03` file inside using the password `crackmes.one`, and load the file `rev03` in our favorite disassembler. Press `F5` to generate and open pseudocode view of the `main` function.

<div align="center">
<em>This is what the pseudocode should look like</em>
</div>

![image](https://github.com/user-attachments/assets/aefafef2-1b66-4302-a8d2-3b8ac011d5a5)

From here, we can easily infer that the function first checks the input size, and if it is any longer than 11 characters, the flag is not displayed. Then, we need to make sure that the ASCII values of the characters in our string add up to 1000 as is dictated by the flow of the program's logic. Let's take a look at the ASCII table then.

![image](https://github.com/user-attachments/assets/050e9ad4-77f6-4cd4-b19c-cffcd83994ff)

We see that `d` has the value 100. So we can use 10 d's to input as the key, right? Let's see!

![image](https://github.com/user-attachments/assets/8b356775-7667-4de3-a27e-a4cedf263f8b)

Oh no! This doesn't seem to work at all! Why could that be? This is why: since we are using the carriage return to return the input back to the program, the program also registers a  newline character (`'\n'` ) at the end of our input, which corresponds to the value 10. To account for that, we use 10 c's as the program's input.

![image](https://github.com/user-attachments/assets/4454888c-6e6d-4df7-847a-59dc4686c8fc)

Input:
```
cccccccccc
```

Output:
```
flag is flag{!#&*/5<DMW}
```
