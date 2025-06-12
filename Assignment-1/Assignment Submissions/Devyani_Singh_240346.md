GDB\
Q1\
![image](https://github.com/user-attachments/assets/2216cfd9-ddbd-432b-98c4-ba9ae0df1f4a)
![image](https://github.com/user-attachments/assets/f9a765bc-54ef-4a02-8a4c-0c3da7f0f4c4)

Q2\
![image](https://github.com/user-attachments/assets/146f6b6e-a81e-4103-880a-4f22adc29862)

Q3\
![image](https://github.com/user-attachments/assets/8e502cdb-e0f0-4b4a-ac87-d9fa3baa42be)\
picoCTF{0x6bc96222} 

Q4\
![image](https://github.com/user-attachments/assets/21d5c907-99c8-476b-9b9f-24fc850d947b)
![image](https://github.com/user-attachments/assets/bb7a7a76-bdd0-4bb4-9cc5-8e79b00d6389)
![image](https://github.com/user-attachments/assets/a6c72e28-fe54-4a40-b652-a4a8d3890a1d)

Crackmes\
Q1\
![image](https://github.com/user-attachments/assets/05d69409-696e-434c-8d72-b07960d30876)
![image](https://github.com/user-attachments/assets/53e4fccc-8351-4614-9777-f384e5ba1bc4)\
The key is correct if iVar1=1, that is if validate_key(local_14)=true. For this to be possible local_14 should be divisible by 1223. 

Q2\
![image](https://github.com/user-attachments/assets/0d3ac36d-7a1e-44b2-8eee-c5648e48ce49)
![image](https://github.com/user-attachments/assets/f6171fcf-6ed4-48fc-b9f4-91ca77c67991)\
The flag is correct if sVar1(length of array local_98)<12. The while loop iterates adding elements of local_98 to local_1c, until it breaks when uVar2=sVar1. The sum of all the elements of our flag should be 1000.\
eg echo -n "dddddddddd" | ./rev03\
echo used to ensure that we did not enter a new line. 
