#include <map>
#include <string>
#include "kgramcount.h"

class Reader {
    int k;
    std::map<std::string, KgramCount> kgram_counts;

    public:

    Reader () : k(10) {};

    Reader (int k);

    void add_kgram(std::string kgram, char following_char);

    void add_kgram(std::string kgram);

    int kgram_length();

    int count(std::string w);

    int count(std::string w, char c);

    float cond_probability(char c, std::string w);
};