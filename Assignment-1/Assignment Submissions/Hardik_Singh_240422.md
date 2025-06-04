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
