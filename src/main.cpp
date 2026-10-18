#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "reader.h"
#include "generator.h"

void generate_text(int k, std::string path, int length, float pseudocount = 0.0f) {
    Reader reader(k);
    std::ifstream file = std::ifstream(path);
    if (!file)
        throw std::runtime_error("File not found");
    file >> reader;
    Generator gen(reader, length, pseudocount);
    std::cout << gen;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Too few arguments given. Usage: slm [k] [path] [length] [-a pseudocount]" << std::endl;
        return 1;
    }
    
    int pos = 0;
    int k;
    std::string path;
    int length;
    float pseudocount = 0;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-a") {
            if (i + 1 >= argc) {
                std::cerr << "No value given for keyword argument -a" << std::endl;
                return 1;
            }
            pseudocount = std::stof(argv[i+1]);
            i++;
            continue;
        }
        if (pos == 0)
            k = std::stoi(argv[i]);
        else if (pos == 1)
            path = argv[i];
        else if (pos == 2)
            length = std::stoi(argv[i]);
        else {
            std::cerr << "Too many positional arguments given" << std::endl;
            return 1;
        }
        pos++;
    }
    if (pos != 3) {
        std::cerr << "Missing positional arguments. Usage: slm [k] [path] [length] [-a pseudocount]" << std::endl;
        return 1;
    }

    if (length < k) {
        std::cerr << "Error: Output length must be atleast k" << std::endl;
        return 1;
    }

    try {
        generate_text(k, path, length, pseudocount);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
}