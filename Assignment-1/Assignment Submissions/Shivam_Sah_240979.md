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

### easy keyg3nme
Open the binary in `ghidra` and run its analysis on it. In the main function, there is a validate key function that says that key should be multiple of 1223. (see below)<br>
![image](https://github.com/user-attachments/assets/f21ef805-9603-49f3-8a9b-b59d937d56ca)
![image](https://github.com/user-attachments/assets/3026d607-c9e0-44c4-be6f-43f828353329)<br>
key: 1223<br>
### jumpjumpjump
![image](https://github.com/user-attachments/assets/3aa678e2-2c3d-4345-898b-c2b42829855e)
<br>
weird flag. analysing the code on ghidra, the first condition is that the length should be less than 12. In the snippet, local_20 is just the counter for each digit of the input string. Second condition is that sum of the input characters should be equal to 1000.<br>
So I copied the code, and printed out the local_1c value everytime according to my input. Final input: `qwertyuiT`. `qwertyui` made up to 916 and T's value is 84. This was the last check and entering this we would get the flag.<br>
flag is flag{!#&*/5<DMW}

### Password Login 2

### login-cipher
analysing in ghidra, there were mainly 4 imp functions. What was happening was there are a bunch of encrypted string literals inside the binary and these were being decrypted to output the msgs. <br>
the main fxn was `FUN_001012a1` which called the check fxn `FUN_001013e3` and the output msgs were decrypted by calling to `FUN_00101348` which called the decrypting function `FUN_00101218`.<br>
```
char * FUN_00101218(char *param_1)
{
  int local_14;
  char *local_10;
  local_14 = 0x7b1; // 1969
  for (local_10 = param_1; *local_10 != '\0'; local_10 = local_10 + 1) {
    local_14 = (local_14 * 7) % 0x10000; // 65536
    *local_10 = *local_10 + ((char)(local_14 / 10) * 10 - (char)local_14);
  }
  return param_1;
}
```
<br>``
This is an excerpt from the main fxn:<br>
```
uVar1 = FUN_001013e3("%64[^\n]","fhz4yhx|~g=5");
if ((int)uVar1 == 0) {
  FUN_00101348("Ftyynjy*",'\x01');
}
else {
  FUN_00101348("Zwvup(",'\x01');
}
```
<br>``
So, using the decrypting function `FUN_00101218` I wrote another fxn to decrypt the strings.<br>
```
int main() {
    int local_14;
    char *local_10;
    char *trial = "fhz4yhx|~g=5";
    char *param_1 = malloc(strlen(trial)+1);
    strcpy(param_1, trial);
    local_14 = 0x7b1; // 1969
    for (local_10 = param_1; *local_10 != '\0'; local_10++) {
        local_14 = (local_14 * 7) % 0x10000;
        *local_10 = *local_10 + ((char)(local_14 / 10) * 10 - (char)local_14);
    }
    printf("%s\n", param_1);
    free(param_1);
    return 0;
}
```
<br>Decrypting the 2nd string in 13e3 fxn call `"fhz4yhx|~g=5"`, we found the pwd: `ccs-passwd44`.<br>
![image](https://github.com/user-attachments/assets/5e224c21-7569-43de-9bb7-c3222b18df1b)

### iso_32
open it in gdb. `info func` reveals `__f_func` and `__s_func`. disassemble them. we need to reach the `__s_func` fxn. break at the last `ret` instruction of `__f_func`. enter a value and then search for it using `search-pattern <value>`. use `i f` to find the address of eip. find the offset between the variable in which the entered value is being scanned into and eip. it comes out to be 44. then we write a simple buffer overflow script.<br>
![image](https://github.com/user-attachments/assets/0c2f9b0a-c6d6-4384-bbf9-f0fbdbf95033)
![image](https://github.com/user-attachments/assets/da753dfe-ca66-4da0-97e0-ca2bb08c5a7f)<br>
```
from pwn import *

target = process('./crackme')

payload = b""
payload += b"0"*44 
payload += p32(0x8049182)  
target.sendline(payload)

target.interactive()
```
<br>

![image](https://github.com/user-attachments/assets/7f7529ef-0584-4b31-8ca1-032f8543bc5b)

 



  










