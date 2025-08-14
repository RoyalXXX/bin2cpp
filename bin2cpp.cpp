/*
	bin2cpp
	
	Copyright (c) 2025 Royal_X (MIT License)
 
 	https://github.com/RoyalXXX
  	https://royalxxx.itch.io
   	https://sourceforge.net/u/royal-x
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

std::atomic<size_t> progress{ 0 };
std::atomic<bool> done{ false };
std::mutex cout_mutex;

void progress_monitor(size_t total_size)
{
    while (!done)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        size_t current = progress.load();
        float percentage = (static_cast<float>(current) / total_size) * 100.0f;

        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\rProgress: " << std::fixed << std::setprecision(1) << percentage << "%" << std::flush;
    }

    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "\rProgress: 100.0%" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <binary_file> <output_file> <array_name>\n";
        return 1;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream input_file(argv[1], std::ios::binary);
    if (!input_file)
    {
        std::cerr << "Error: Unable to open '" << argv[1] << "' for reading.\n";
        return 1;
    }

    input_file.seekg(0, std::ios::end);
    const size_t file_size = input_file.tellg();
    input_file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buf(file_size);
    input_file.read(reinterpret_cast<char*>(buf.data()), file_size);

    if (input_file.gcount() != static_cast<std::streamsize>(file_size))
    {
        std::cerr << "Error: Failed to read the entire input file.\n";
        return 1;
    }

    std::ofstream output_file(argv[2]);
    if (!output_file)
    {
        std::cerr << "Error: Unable to open '" << argv[2] << "' for writing.\n";
        return 1;
    }

    const std::string array_name = argv[3];

    output_file << "//=================================== AUTOMATICALLY GENERATED FILE ===================================//\n"
        << "// DO NOT EDIT MANUALLY\n"
        << "// This file is generated from: " << argv[1] << "\n"
        << "//====================================================================================================//\n\n"
        << "#pragma once\n"
        << "#include <cstdint>\n\n"
        << "constexpr uint8_t " << array_name << '[' << buf.size() << "] = {";

    std::thread progress_thread(progress_monitor, buf.size());

    for (std::size_t i{}; i < buf.size(); ++i)
    {
        if (i != 0) output_file << ", ";
        if (i % 17 == 0) {
            output_file << "\n\t";
            progress.store(i);
        }
        output_file << "0x"
            << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<unsigned>(buf[i]);
    }

    progress.store(buf.size());
    done = true;
    progress_thread.join();

    output_file << "\n};\n";

    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration<double>(end_time - start_time).count();

    std::cout << "Elapsed time: " << std::fixed << std::setprecision(3) << duration << " seconds" << std::endl;
}
