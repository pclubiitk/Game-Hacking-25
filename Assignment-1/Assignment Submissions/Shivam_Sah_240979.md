### GDB baby step 1
![image](https://github.com/user-attachments/assets/27fb9429-b7e6-4a57-bd7a-079ab8ac997c)<br>
First we have to give the file executable permissions using `chmod +x <binary_name>`.<br>
We can see the number 0x86342 being moved into EAX at the third last instruction.<br>
flag: picoCTF{549698}<br>
### GDB baby step 2
Pretty much the same. Break just before the `ret` instruction in main. Then `print $eax` and convert to decimal.<br>
flag: picoCTF{307019}<br>
### GDB baby step 3
![image](https://github.com/user-attachments/assets/6d42ca35-3ec2-401c-a27d-828d035c800f)

Disassemble main. Break at the 2nd last `pop` instruction. We see that the given number was being moved at address (rbp-0x4). So just display the bytes at that position using the cmd `x/4xb $rbp-0x4`.<br>
flag: picoCTF{0x6bc96222}
### GDB baby step 4
![image](https://github.com/user-attachments/assets/b247df9a-55e1-4c05-9eb0-5661a32e5ebe)<br>
Disassemble main. There we see a `call` instruction to `func1`. Disassemble `func1`. There we see a `imul` instruction that multiplies eas with 0x3269 (higlighted).<br>
flag: picoCTF{12905}<br<br>







