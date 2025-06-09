# GDB
## [GDB baby step 1](https://play.picoctf.org/practice/challenge/395?category=3&page=1&search=GDB)
+ To find the contents of the eax register at the end of main function
  - First step was to obviously download the ELF file
  - Use the ***gdb*** command to use the debugger
  - Use the ***disas main*** command to unpack the assembly of the main
    ![disas main](https://github.com/user-attachments/assets/2e95d916-c0d4-43f8-add2-205ad3175d49)
  - It is clearly seen that <ins>0x86342</ins> hex constant is moved to eax register at the end of the main
  - The flag is ***picoCTF{549698}***

## [GDB baby step 2](https://play.picoctf.org/practice/challenge/396?category=3&page=1&search=GDB)
+ To find the contents of the eax register at the end of main function
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/740f1c31-6dcb-4564-b50b-41f79a469a1c)
  - Here there is a loop made using the kind of while condition **while(%eax < -0xc(%rbp) = 607)**
    ![loop](https://github.com/user-attachments/assets/8c2ddb3b-9f91-4195-a159-5aab07fe05da)
  - The initail value in eax register is 0, the iterations will be repeated until %eax < 607, in each iteration the eax register is incremented by 1
  - In each iteration the condition is followed **-0x4(%rbp) = -0x4(%rbp) + %eax** with -0x4(%rbp) initialised with **0x1e0da** hex constant
  - Once after the loop is completed the value in the eax register is replaced by value at -0xc(%rbp)
  - So final stored value would be 123098(deciamal conversion of 0x1e0da) + 183921 (606*607 / 2)
  - The flag is ***picoCTF{307019}***

## [GDB baby step 3](https://play.picoctf.org/practice/challenge/397?category=3&page=1&search=GDB)
+ To find the 4 bytes of memory as they are stored at the address where 0x2262c96b is loaded into memory in the main function
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/a9644fbd-634d-47de-ad88-f8e5350ce8a7)
  - Now set a break point at the address after which the 0x2262c96b is loaded into memory
    ![break point](https://github.com/user-attachments/assets/9f33d000-6a0a-45a7-9a40-324bcdaeb634)
  - Now run the program and when the break point is achieved run the command ***x/4xb $rbp-4***
    ![run and command](https://github.com/user-attachments/assets/8f276464-ab1a-4417-822e-a9e0cfd0984d)
  - The required flag is ***picoCTF{0x6bc96222}***

## [GDB baby step 4](https://play.picoctf.org/practice/challenge/398?category=3&page=1&search=GDB)
+ Main calls a function and multiplies eax by a constant, to find this constant
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/62d5b93c-89bf-40e3-b871-ab12d882585a)
  - Now use the command ***disas func1***
    ![disas func1](https://github.com/user-attachments/assets/8af83dfe-ca39-4624-a9c7-a50f17625eb7)
  - The flag is picoCTF{12905}

# Reversing Crackmes
## [Ezman's easy keyg3nme](https://crackmes.one/crackme/5da31ebc33c5d46f00e2c661)
+ After extracting the zip file you will find a file named "keyg3nme" (Password : crackmes.one)
+ Using the ***file keyg3nme*** command on "keyg3nme" we find that it is a unstripped ELF file
  ![file command](https://github.com/user-attachments/assets/a0278994-8126-4b69-95b8-af89fe42dc0b)
+ Using the ***strings keyg3nme*** command will show all the strings, may be we could find the hardcoded key :wink:
  ![Some intresting strings found](https://github.com/user-attachments/assets/455ce00f-d592-4f1e-8e2e-698296217eb4)
+ Unfortunately we find no hardcoded key
+ Now try executing the file and give some random keys to find one of the above strings as output
+ Open the binary in Ghidra
+ Navigating to the main function and decompiling it, we should see the following code snippet
  ![main](https://github.com/user-attachments/assets/51fa7c99-ebcf-487d-a073-90622132d671)
+ We see a function **validate_key** being called, navigate to it's code snippet
  ![validate_key](https://github.com/user-attachments/assets/a70c52c8-47f6-4270-9dd5-0b6a679fce18)
+ So any multiple of 1223 including 0 must do the work

##[Cbm-hacker's jumpjumpjump](https://crackmes.one/crackme/5c1a939633c5d41e58e005d1)
+ After extracting the zip file you will find a file named "rev03" (Password : crackmes.one)
+ Using the ***file rev03*** command on "keyg3nme" we find that it is a unstripped ELF file
  ![file](https://github.com/user-attachments/assets/c3171dbe-921a-43d8-aa02-af975389ca3d)
+ Checkout the strings as done in the previous crackmes problem
  ![intresting strings](https://github.com/user-attachments/assets/971940d1-446c-462c-a5d5-2db9509dab01)
+ Now try executing the file and give some random keys to find one of the above strings as output
+ Open the binary in Ghidra
+ Navigating to the main function and decompiling it, we should see the following code snippet
  ![main](https://github.com/user-attachments/assets/6c78c15a-d253-490f-a8bc-b65fae22a640)
+ So the length of the correct stiring must be less than 12 or else we will get the output as **too long...sorry no flag for you!!!**
+ The sum of the ASCII values of the characters of the valid ASCII string must be 1000 (Example : "cccccccccc\n")
  ![correct string](https://github.com/user-attachments/assets/e79a3b46-af53-4943-80ed-8ef4a1b7a418)







