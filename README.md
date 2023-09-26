﻿# Installation Guide
This guide teaches you how to download and install the game.
## Prerequirements:
- [CMake](https://cmake.org/download/) version 3.16 (minimum).
- A C++ compiler, such as g++ or Microsoft Visual C++.

## Windows:
### CMake check:
Make sure the `cmake` command is recognized in your terminal.  
To verify, launch your terminal and type:
```ps
cmake --version
```
If the `cmake` command is recognized, you will see some output like:
```
cmake version 3.27.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```
If your terminal says the command is not recognized. You need to set it up in your `environment variables`.
![open environment variable](/docs/img/EnvVar0.jpg)  
![open environment variable](/docs/img/EnvVar1.jpg)  
Now select `Path` and click `Edit`.
![open environment variable](/docs/img/EnvVar2.jpg)  
And click `New`.  
![open environment variable](/docs/img/EnvVar3.jpg)  
Navigate to where you downloaded CMake.  
![open environment variable](/docs/img/EnvVar4.jpg)  
And paste in the the address of `bin` directory there.  

## Installing:
After `CMake` has to set up, go ahead and extract the `.zip` file you downloaded. Navigate to the extracted directory. Press `Shift` + `Right Click` and open the `PowerShell` terminal.  
After the terminal window opens. Run following commands:
```ps
cmake -S . -B build
```
```ps
cmake --build build --config Release
```
