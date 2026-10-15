#include <string>
#include <stdexcept>
#include <iostream>
#include "reader.h"
#include <algorithm>

// Constructor

Reader::Reader (int k) {
    this->k = k;
    total_kgram_count = 0;
}

// Private methods

void Reader::add_kgram (std::string kgram, char following_char) {
    if (kgram.length() != k) 
        throw std::invalid_argument("kgram is not of appropriate length");

    kgram_counts[kgram].add_char(following_char);
    total_kgram_count += 1;
    if (std::find(alphabet.begin(), alphabet.end(), following_char) == alphabet.end()) {
        alphabet.push_back(following_char);
    }
}

void Reader::add_kgram (std::string kgram) {
    kgram_counts[kgram];
}

// Public methods

int Reader::count(std::string w) const {
    if (kgram_counts.contains(w))
        return kgram_counts.at(w).get_total();
    return 0;
}

int Reader::count(std::string w, char c) const {
    if (kgram_counts.contains(w))
        if (kgram_counts.at(w).contains(c))
            return kgram_counts.at(w).at(c);
    return 0;
} 

int Reader::kgram_length() const {
    return k;
}

int Reader::get_kgram_total() const {
    return total_kgram_count;
}

int Reader::alphabet_size() const {
    return alphabet.size();
}

std::vector<char> Reader::get_alphabet() const {
    return alphabet;
}

std::vector<std::string> Reader::get_kgrams() const {
    std::vector<std::string> kgrams;
    for (const auto& entry : kgram_counts) {
        kgrams.push_back(entry.first);
    }
    return kgrams;
}

std::vector<int> Reader::get_kgram_weights() const {
    std::vector<int> weights;
    for (const auto& entry : kgram_counts) {
        weights.push_back(entry.second.get_total());
    }
    return weights;
}

// Read from file

std::istream& operator>> (std::istream& file, Reader& reader) {
    std::string buffer;
    char c;
    int length = 0;
    int k = reader.kgram_length();
    while (file.get(c)) {
        if (c == '\n') 
            continue;
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

    return file;
}

std::ostream& operator<< (std::ostream& stream, const Reader& reader) {
    stream << "k = " << reader.kgram_length() << std::endl << "k-grams:" << std::endl;

    for (const auto& [w, kgramcount] : reader.kgram_counts) {
        stream << std::endl << "# [" << w << "]" << std::endl;
        stream << kgramcount;
    }
    return stream;
}



