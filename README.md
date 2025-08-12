# bin2cpp
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Static Badge](https://img.shields.io/badge/C%2B%2B-11-blue?)](https://isocpp.org/)

## A very fast and simple utility for converting a binary file into a C++ source file.

## Usage
`bin2cpp <binary_file> <output_file> <array_name>`

## Example
`bin2cpp opensans.ttf opensans.h opensans_font_data`

This will create a file `opensans.h` with the following contents:

```
//=================================== AUTOMATICALLY GENERATED FILE ===================================//
// DO NOT EDIT MANUALLY
// This file is generated from: opensans.ttf
//====================================================================================================//

#pragma once
#include <cstdint>

constexpr uint8_t opensans_font_data[130832] = {
	0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x01, 0x00, 0x00, 0x04, 0x00, 0x20, 0x47, 0x44, 0x45, 0x46, 0xaf,
// ...
	0x48, 0x06, 0x26, 0x03, 0xaf, 0x00, 0x00, 0x00, 0x07, 0x04, 0x0e, 0x03, 0x6a, 0x00, 0x00, 0x00, 0x00
};
```

## Where it can be used
The resulting file can be used, for example, in **SFML** projects. As is known, SFML provides the function `openFromMemory(const void *data, std::size_t sizeInBytes)` for loading fonts, audio, images,  and other data from memory. However, the SFML library does not provide functions for loading resources into memory, so platform-specific functions must be used (for example, in WinAPI: FindResource, LoadResource, LockResource).

A similar situation exists in other libraries, for example, **wxWidgets**, which has the `wxMemoryInputStream` class for working with data from memory, but likewise does not provide cross-platform methods for loading resources into memory.

**bin2cpp** makes it possible to embed resources into the program’s executable file and load them into memory in a platform-independent way.

