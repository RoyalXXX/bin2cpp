#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <binary_file> <output_file> <array_name>\n";
        return 1;
    }

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

    for (std::size_t i{}; i < buf.size(); ++i)
    {
        if (i != 0) output_file << ", ";
        if (i % 17 == 0) output_file << "\n\t";
        output_file << "0x"
                    << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<unsigned>(buf[i]);
    }

    output_file << "\n};\n";

    if (!output_file.flush())
    {
        std::cerr << "Error: Incomplete write to the output file.\n";
        return 1;
    }
}