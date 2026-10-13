#include <string>
#include <stdexcept>
#include <iostream>
#include "reader.h"

// Constructor

Reader::Reader (int k) {
    this->k = k;
}

// Private methods

void Reader::add_kgram (std::string kgram, char following_char) {
    if (!kgram.length() != k) 
        throw std::invalid_argument("kgram is not of appropriate length");

    kgram_counts[kgram].add_char(following_char);
}

void Reader::add_kgram (std::string kgram) {
    kgram_counts[kgram];
}

// Public methods

int Reader::count(std::string w) {
    if (kgram_counts.contains(w))
        return kgram_counts[w][];
    return 0;
}

int Reader::count(std::string w, char c) {
    if (kgram_counts.contains(w))
        if kgram_counts[w].contains(c)
            return kgram[w][c];
    return 0;
} 

float cond_possibility(char c, std::string w) {
    int nr_w = count(w);
    if (nr_w) == 0
        return 0;               // Is the possibility 0 here ?
    int nr_wc = count(w, c);
    return nr_wc / nr_w;
}

int Reader::kgram_length() {
    return k;
}

// Read from file

std::istream& operator>> (std::istream& file, Reader& reader) {
    std::string buffer;
    char c;
    int length = 0;
    int k = reader.kgram_length();
    while (file.get(c)) {
        if (length < k) {
            buffer += c;
            length += 1;
        }
        else {
            reader.add_kgram(buffer, c);
            buffer = buffer.substr(1) + c;
        }
    }
    if (length < k)
        throw std::runtime_error("File does not contain enough characters");
    reader.add_kgram(buffer);
    
    return file;
}



