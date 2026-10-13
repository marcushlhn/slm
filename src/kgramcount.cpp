#include "kgramcount.h"

void KgramCount::add_char (char c) {
    (*this)[c] += 1;
    total += 1;
}

int KgramCount::operator[]() {
    return total;
}