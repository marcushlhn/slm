#include "kgramcount.h"
#include <iostream>

void KgramCount::add_char (char c) {
    (*this)[c] += 1;
    total += 1;
}

int KgramCount::get_total() const {
    return total;
}

std::ostream& operator<<(std::ostream& stream, const KgramCount& kc) {
    stream << "Total: " << kc.get_total() << std::endl;
    for (const auto& [c, count] : kc) {
        stream << c << ": " << count << std::endl;
    }
    return stream;
}