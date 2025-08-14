# bin2cpp
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Static Badge](https://img.shields.io/badge/C%2B%2B-11-blue?)](https://isocpp.org/)

### A very fast and simple utility for converting a binary file into a C++ source file.

### Where it can be used
The resulting file can be used, for example, in **SFML** projects. As is known, SFML provides the function `openFromMemory(const void *data, std::size_t sizeInBytes)` for loading fonts, audio, images,  and other data from memory. However, the SFML library does not provide functions for loading resources into memory, so platform-specific functions must be used (for example, in WinAPI: FindResource, LoadResource, LockResource).

A similar situation exists in other libraries, for example, **wxWidgets**, which has the `wxMemoryInputStream` class for working with data from memory, but likewise does not provide cross-platform methods for loading resources into memory.

**bin2cpp** makes it possible to embed resources into the program’s executable file and load them into memory in a platform-independent way.

## bin2cpp GUI
![alt text](https://github.com/RoyalXXX/bin2cpp/blob/main/_scr.png)

This is the graphical user interface version of **bin2cpp**. It is the recommended way to use **bin2cpp**.

Compared to the console version, **bin2cpp GUI** offers several advantages:

- Several times faster than **bin2cpp console**
- Powered by an upgraded and high-performance algorithm
- Supports Unicode characters in file paths and names, including valid Unicode identifiers in C++ (names composed of characters with Unicode property XID_Start for the first character and XID_Continue for subsequent characters, in accordance with the C++ standard): https://en.cppreference.com/w/cpp/language/name.html
- Validates names and paths for correctness
- Displays error messages and conversion time

### Usage

Before starting the conversion process, you must select the path to the input file. All other fields are optional.

Click the **Start** button to begin the conversion.

The screenshot above shows an example of font conversion, which results in the creation of a file named `my_font.h` with the following contents:

```
//=================================== AUTOMATICALLY GENERATED FILE ===================================//
// DO NOT EDIT MANUALLY
// This file is generated from: my_font.ttf
//====================================================================================================//

#pragma once
#include <cstdint>

constexpr uint8_t my_font_data[130832] = {
	0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x01, 0x00, 0x00, 0x04, 0x00, 0x20, 0x47, 0x44, 0x45, 0x46, 0xaf,
// ...
	0x48, 0x06, 0x26, 0x03, 0xaf, 0x00, 0x00, 0x00, 0x07, 0x04, 0x0e, 0x03, 0x6a, 0x00, 0x00, 0x00, 0x00
};
```

## bin2cpp console

> [!WARNING]
> Errors may occur when using **bin2cpp console**, as it does not validate file names or paths. Moreover, it supports only ASCII characters in names.

The source code of **bin2cpp console** is available for download under the MIT License (the `bin2cpp.cpp` file in the repository).


### Usage
`bin2cpp <binary_file> <output_file> <array_name>`

### Example
`bin2cpp my_font.ttf my_font.h my_font_data`




