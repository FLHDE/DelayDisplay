# DelayDisplay

[DelayDisplay](https://the-starport.com/forums/topic/1953/delaydisplay) is a plugin made by [M0tah](https://the-starport.com/forums/user/m0tah) that shows the cooldown for every weapon next to its ammo count in the contact list. However, its source code was never released into the public. This project aims to reconstruct the original source code as accurately as possible. The C++ setup and hook functions compile to the exact same instructions found in DelayDisplay.dll, making it effectively a 1:1 decompilation (see scratches below). Moreover, the code is written in such a way that it closely matches M0tah's coding style. This project was inspired by [Aingar's decompilation of DelayDisplay](https://github.com/TheStarport/FLUF/blob/master/modules/delay_display/Source/DelayDisplay.cpp) which although is accurate functionality-wise, it does not compile to the exact same bytes as in the original DLL.

## decomp.me scratches
- [Setup function](https://decomp.me/scratch/5CHsR)
- [Hook function](https://decomp.me/scratch/X2y3T)

## Compiling
The original DelayDisplay DLL was compiled using Visual C++ 7.1 .NET 2003. This project however comes with a VC6 makefile.
