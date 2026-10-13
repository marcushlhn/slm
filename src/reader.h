#pragma once

#include <map>
#include <string>
#include <iostream>
#include "kgramcount.h"

class Reader {
    int k;
    std::map<std::string, KgramCount> kgram_counts;

    public:

    Reader () : k(10) {};

    Reader (int k);

    void add_kgram(std::string kgram, char following_char);

    void add_kgram(std::string kgram);

    int kgram_length() const;

    int count(std::string w) const;

    int count(std::string w, char c) const;

    float cond_probability(char c, std::string w) const;

    friend std::ostream& operator<<(std::ostream& stream, const Reader& reader);
};

std::ostream& operator<<(std::ostream& stream, const KgramCount& kc);

std::istream& operator>> (std::istream& file, Reader& reader);