#include "reader.h"
#include "generator.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
    Reader reader(2);
    std::ifstream file = std::ifstream("files/moby_dick.txt");
    if (!file) {
        std::cout << "File does not exist!" << std::endl;
    }
    file >> reader;

    Generator gen(reader, 500, 0.01);

    std::cout << gen;

}