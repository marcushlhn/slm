#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "kgramcount.h"

class Reader {
    int k;
    int total_kgram_count;
    std::vector<char> alphabet;
    std::map<std::string, KgramCount> kgram_counts;

    public:

    Reader () : k(10) {};

    Reader (int k);

    void add_kgram(std::string kgram, char following_char);

    void add_kgram(std::string kgram);

    int kgram_length() const;

    int count(std::string w) const;

    int count(std::string w, char c) const;

    int get_kgram_total() const;

    int alphabet_size() const;

    std::vector<char> get_alphabet() const;

    std::vector<std::string> get_kgrams() const;

    std::vector<int> get_kgram_weights() const;

    friend std::ostream& operator<<(std::ostream& stream, const Reader& reader);
};

std::ostream& operator<<(std::ostream& stream, const KgramCount& kc);

std::istream& operator>> (std::istream& file, Reader& reader);