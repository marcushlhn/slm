#include "generator.h"
#include "reader.h"
#include <string>
#include <exception>
#include <random>
#include <iostream>
#include <numeric>


Generator::Generator (Reader reader, int max_output_length) {
    extract_reader(reader);
    pseudocount = 0;
    this->max_output_length = max_output_length;
}

Generator::Generator (Reader reader, int max_output_length, float alpha) {
    if (alpha < 0) {
        throw std::invalid_argument("alpha must be greater or equal to 0");
    }
    pseudocount = alpha;
    this->max_output_length = max_output_length;
    extract_reader(reader);
}

void Generator::extract_reader(Reader reader) {
    this->reader = reader;
    available_kgrams = reader.get_kgrams();
    kgram_frequences = reader.get_kgram_weights();
    alphabet = reader.get_alphabet();
    set_alphabet_probabilities();
}

void Generator::set_alphabet_probabilities() {
    for (const std::string& kgram : available_kgrams) {
        for (const char& c : alphabet) {
            kgram_alphabet_probabilities[kgram].push_back(probability(c, kgram));
        }
    }
}

float Generator::probability (std::string kgram) const {
    return reader.count(kgram) / reader.get_kgram_total();
}

float Generator::probability (char c, std::string kgram) const {
    int kgram_occurrences = reader.count(kgram);
    int char_kgram_occurrences = reader.count(kgram, c);
    if (kgram_occurrences + pseudocount == 0)
        return 0;
    return (char_kgram_occurrences + pseudocount) / (kgram_occurrences + pseudocount * reader.alphabet_size());
}

char Generator::next (std::string kgram) const {
    std::vector<float>& probabilities = kgram_alphabet_probabilities[kgram];
    //std::cout << "VECTOR " << probabilities << std::endl;
    if (probabilities.size() == 0) {
        for (const char& c : alphabet) {
            probabilities.push_back(probability(c, kgram));
            //std::cout << "VECTOR " << probabilities << std::endl;
        }
    }
    if (std::accumulate(probabilities.begin(), probabilities.end(), 0.0) == 0) {
        throw std::runtime_error("No transitions exist");
    }
    std::discrete_distribution<> distr(probabilities.begin(), probabilities.end());
    int index = distr(gen);
    return alphabet[index];
}

std::string Generator::start () const {
    std::discrete_distribution<> distr(kgram_frequences.begin(), kgram_frequences.end());
    int index = distr(gen);
    return available_kgrams[index];
}

int Generator::get_max_output_length () const {
    return max_output_length;
}

std::ostream& operator<< (std::ostream& stream, Generator& gen) {
    std::string buffer = gen.start();
    stream << buffer;
    bool generating = true;
    int printed_chars = buffer.length();
    int max_length = gen.get_max_output_length();
    while (generating) {
        try {
            char next_char = gen.next(buffer);
            stream << next_char;
            printed_chars++;
            buffer.erase(0, 1);
            buffer += next_char;
            //std::cout << "[" << buffer << "]";
        }
        catch (const std::runtime_error& e) {
            //std::cout << "END: " << e.what() << std::endl;
            break;
        }
        generating = printed_chars <= max_length;
    }
    return stream;
}