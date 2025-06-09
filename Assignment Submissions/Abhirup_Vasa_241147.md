# GDB\
## GDB baby step 1
+ To find the contents of the eax register at the end of main function\
  - First step was to obviously download the ELF file
  - Use the ***gdb*** command to use the debugger
  - Use the ***disas main*** command to unpack the assembly of the main
    ![disas main](https://github.com/user-attachments/assets/2e95d916-c0d4-43f8-add2-205ad3175d49)
  - It is clearly seen that <ins>0x86342</ins> hex constant is moved to eax register at the end of the main
  - The flag is ***picoCTF{549698}***

## GDB baby step 2
+ To find the contents of the eax register at the end of main function\
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/740f1c31-6dcb-4564-b50b-41f79a469a1c)
  - Here there is a loop made using the kind of while condition **while(%eax < -0xc(%rbp) = 607)**
    ![loop](https://github.com/user-attachments/assets/8c2ddb3b-9f91-4195-a159-5aab07fe05da)
  - The initail value in eax register is 0, the iterations will be repeated until %eax < 607, in each iteration the eax register is incremented by 1
  - In each iteration the condition is followed **-0x4(%rbp) = -0x4(%rbp) + %eax** with -0x4(%rbp) initialised with **0x1e0da** hex constant
  - Once after the loop is completed the value in the eax register is replaced by value at -0xc(%rbp)
  - So final stored value would be 123098(deciamal conversion of 0x1e0da) + 183921 (606*607 / 2)
  - The flag is ***picoCTF{307019}***

## GDB baby step 3
+ To find the 4 bytes of memory as they are stored at the address where 0x2262c96b is loaded into memory in the main function\
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/a9644fbd-634d-47de-ad88-f8e5350ce8a7)
  - Now set a break point at the address after which the 0x2262c96b is loaded into memory
    ![break point](https://github.com/user-attachments/assets/9f33d000-6a0a-45a7-9a40-324bcdaeb634)
  - Now run the program and when the break point is achieved run the command ***x/4xb $rbp-4***
    ![run and command](https://github.com/user-attachments/assets/8f276464-ab1a-4417-822e-a9e0cfd0984d)
  - The required flag is ***picoCTF{0x6bc96222}***

## GDB baby step 4
+ Main calls a function and multiplies eax by a constant, to find this constant
  - Same first three steps as the GDB baby step 1
    ![disas main](https://github.com/user-attachments/assets/62d5b93c-89bf-40e3-b871-ab12d882585a)
  - Now use the command ***disas func1***
    ![disas func1](https://github.com/user-attachments/assets/8af83dfe-ca39-4624-a9c7-a50f17625eb7)
  - The flag is picoCTF{12905}
