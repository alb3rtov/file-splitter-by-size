# File splitter by size
This software helps making backup copies when the backup storage drive is not enough for whole copy, like USB sticks.

<p align="center">
<img src="https://user-images.githubusercontent.com/40604222/182697733-6c5228a3-b81e-4f2e-b381-46cc5164f720.gif" alt="animation" />
</p>

<!-- https://user-images.githubusercontent.com/40604222/182674767-d95edbe2-46e8-4338-9733-b43a1bd03142.gif -->

## How it works
The main use is to move data to other computers using a external drive that can't storage the whole backup itself. This software will automatically fill the external drive with the data until the maximum storage limit. Once the first copy is done, you can use other external drive to continue with the copy, or use the same external drive when it have enough space. The copy will continue from the last copied file, even if you close the software. 

The information of the copy process is storage in a file in the `data` folder. Each copy will have his own file, with an identifier generated with a md5 hash base on the source path. This file will contain a bitmap of all files listed of the source folder, where 0 value means not copied and 1 value means copied.

### Win32 API
This program only works for Windows OS because it's use the [Win32 API](https://docs.microsoft.com/en-us/windows/win32/api/) for some funcionalities. Maybe in the future I will code it for Linux systems.

## Compile and run
In order to compile C++ code on a Windows OS, you need the `g++` compiler.
- First, download the [Portable C and C++ Development Kit for x64 Windows](https://github.com/skeeto/w64devkit/releases) made by [skeeto](https://github.com/skeeto/).
- Unzip the ZIP file in your `C: drive`.
- Finally, you need to add to your path system variable the `bin` folder of `w64devkit`. Go to _Advanced system settings_ > _Environment Variables_ > _System Variables_ and find the **PATH enviroment variable**, select it and click on _edit_, click on _New_ and copy this path `C:\w64devkit\bin`.
  
Make sure that it works executing `g++ --version` on your CMD. The output must be something like this:

    C:\Users\user>g++ --version
    g++ (GCC) 11.1.0
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Now in order to compile and execute the program, type this commands:

    md exec/
    g++ -std=c++17 -g -I include src\main.cpp -o exec\main.exe
    .\exec\main.exe

## Releases
You can download an already compiled versions from [releases page](https://github.com/alb3rtov/file-splitter-by-size/releases).
