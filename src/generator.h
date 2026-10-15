#pragma once

#include "reader.h"
#include <string>
#include <random>

class Generator {

    float pseudocount;
    Reader reader;
    std::vector<char> alphabet;
    int max_output_length;
    
    std::vector<std::string> available_kgrams;
    std::vector<int> kgram_frequences;
    mutable std::map<std::string, std::vector<float>> kgram_alphabet_probabilities;
    mutable std::mt19937 gen{std::random_device{}()};

    float probability (std::string kgram) const;

    float probability (char c, std::string kgram) const;

    void extract_reader(Reader reader);

    void set_alphabet_probabilities();

    public:

    Generator (Reader reader, int max_output_length);

    Generator (Reader reader, int max_output_length, float alpha);

    char next (std::string kgram) const;

    int get_max_output_length() const;

    std::string start () const;

};

std::ostream& operator<< (std::ostream& stream, Generator& gen);

