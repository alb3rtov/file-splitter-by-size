# File splitter by size
This script will divide in folders a selected set data by a given size. Very useful for perform backups in a limited USB flash drives.

# Win32 API
This program only works for Windows OS because it's use the [Win32 API](https://docs.microsoft.com/en-us/windows/win32/api/).

# Compile and run
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



# Releases
https://github.com/alb3rtov/file-splitter-by-size/releases