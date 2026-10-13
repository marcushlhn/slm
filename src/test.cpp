#include "reader.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
    Reader reader(3);
    std::ifstream file = std::ifstream("files/test.txt");
    if (!file) {
        std::cout << "File does not exist!" << std::endl;
    }
    file >> reader;

    std::cout << reader << std::endl;
}