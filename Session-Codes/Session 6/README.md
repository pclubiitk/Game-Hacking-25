# Usage
The code is for a External Hack for the game Assault Cube.

I used following command for compilation :

```bash
i686-w64-mingw32-g++ -m32 -std=c++17 AssaultCube_external_hack.cpp proc.cpp -o hack32.exe -luser32
```
But it might be possible that it compiles for you in some simpler way.

I also had to move 32 bit dlls to the same folder for it to compile : 
- libgcc_s_dw2-1.dll
- libstdc++-6.dll
- libwinpthread-1.dll

If still doesnt work, try adding folowing flags:
```bash
-static-libgcc -static-libstdc++
``` 
in the compilation command above.