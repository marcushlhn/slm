#pragma once

#include <map>
#include <string>

class KgramCount : public std::map<char, int> {
    int total = 0;

    public:

    void add_char(char c);

    int get_total() const;
};

std::ostream& operator<<(std::ostream& stream, const KgramCount& kc);