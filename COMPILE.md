# Squirrel 3.2 stable

What is in this distribution?

- **squirrel**  
    static library implementing the compiler and interpreter of the language

- **sqstdlib**  
    the standard utility libraries

- **sq**  
    stand alone interpreter

- **doc**  
    The manual

- **etc**  
    a minimalistic embedding sample

- **samples**  
    samples programs


# How to compile

## Visual Studio
If you want to build the shared libraries under Windows using Visual
Studio, you will have to use CMake version 3.21 or newer.

To build the project, you need to install:
- "Workload: Desktop development with C++"
- "Individual Component: CMake tools for Visual Studio"

After installing the visual studio with mentioned packages, you can
open up the folder using Visual Studio, the rest can be handled from
Visual Studio editor.

## Command Line
Make sure to install required compiler tools for C++ for your specific
platform and CMake (at least 3.21 version).

```cmake
cmake . --preset [preset_name] # For available presets checkout CMakePresets.json file
cmake --build . --preset [preset_name]
```