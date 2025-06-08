
# Assignment: 1
## Challenge: 1 {GDB baby step 1}

This challenge contains basic ctf challenge which is:
``` ELF 64-bit LSB pie executable``` 
1. Run it in gdb by ```gdb debugger0_a ```.

2. Check functions by 
``` info functions ``` ; this will open list of functions.
![Screenshot From 2025-06-08 17-36-28](https://github.com/user-attachments/assets/4e46699d-0482-41c4-bc76-e6dc381f4404)
3. Disassemble main function and you will see your required eax register value  ``` 0x86342 ```. When you convert it to decimal, we get ```549698```.

![Screenshot From 2025-06-08 17-36-44](https://github.com/user-attachments/assets/2fde4c83-9e71-47b0-b485-e1948576eb2b)
 
4. Hence, flag is ``` picoCTF{549698} ```.


## Challenge: 2 {GDB baby step 2}

This challenge contains ``` ELF 64-bit LSB pie executable``` 
1. Run it in gdb by ```gdb debugger0_b ```.

2. Check functions by ``` info functions ``` ; this will open list of functions.
![Screenshot From 2025-06-08 17-59-28](https://github.com/user-attachments/assets/4fc88dfb-1127-49b2-9627-4e587886f738)
3. Disassemble main function. Since, we need to find what is value of ```eax``` register at end of main function, so put a break there and run the elf.
![Screenshot From 2025-06-08 17-59-40](https://github.com/user-attachments/assets/70570b1d-998e-4619-9d48-2aa582d26408)
5. check value of ```eax``` register by ``` print $eax ```. You will get ``` 307019```.
6. Hence, flag is ``` picoCTF{307019} ```.

## Challenge: 3 {GDB baby step 3}

This challenge also contains ``` ELF 64-bit LSB pie executable``` 
1. Run it in gdb by ```gdb debugger0_c```.

2. Check functions by ``` info functions ``` ; this will open list of functions.

3. Disassemble main function. 
4. Upon inspection of ```main```, we note that ```mov``` moves the constant value into a memory location (rbp-4). So, we put a break point just after that memory address load in rbp.

   ![Screenshot From 2025-06-08 19-08-50](https://github.com/user-attachments/assets/6abf08d1-6aa7-420e-bbc4-c33913ab54e8)
4. Check address by given command ``` x/4xb $rbp-4 ```. It gives all bytes stored in memeory at that address ```0x6b 0xc9 0x62 0x22```
5. Hence, flag is ``` picoCTF{0x6bc96222}```.

## Challenge: 4 {GDB baby step 4}

This challenge also contains ``` ELF 64-bit LSB pie executable``` 
1. Run it in gdb by ```gdb debugger0_d```.

2. Check functions by ``` info functions ``` ; this will open list of functions.

3. Disassemble main function.
   ![Screenshot From 2025-06-08 19-19-24](https://github.com/user-attachments/assets/10b55ef2-702f-4743-affc-ee52c063b82c)
5. Upon inspection of ```main```and challenge description, ```func1``` multiplies ```eax``` bya constant. So, we put a break point just before and after that function and check value of ``eax ``` is both places.
  ![Screenshot From 2025-06-08 19-19-28](https://github.com/user-attachments/assets/d6936c56-0ed5-409c-802a-9461c2c86c4a)
4. Those values are `654` and `8439870`. On division we get our required constant `12905`.
5. Hence, flag is ``` picoCTF{12905} ```.

## Challenge: 5 {ezman's easy keyg3nme}
(unzip the zip file by password ```crackmes.one```)

This challenge also contains ``` ELF 64-bit LSB pie executable```, which ask for key to solve it.
1. Run it in ghidra. Open main function.
   
![Screenshot From 2025-06-08 19-41-02](https://github.com/user-attachments/assets/51c6c765-ce01-451b-8084-bd43974c572b)

2. ```main``` function pass user input to ```validate key```, which check if it dived by ```0x4c7```, which is in hex. on converting it ti decimal, number is ```1223```.

![Screenshot From 2025-06-08 19-41-37](https://github.com/user-attachments/assets/7be123bf-8f7a-43f1-8f86-05c33c36d657)

3. So, basically any input that is multiple of 1223, is key.

4. We got: 
``` 
chirag@hp:~/Downloads$ ./keyg3nme 
Enter your key:  1223
Good job mate, now go keygen me.
```


