#pragma once

#include <map>
#include <string>

class KgramCount : map<char, int> {
    int total = 0;

    void add_char(char c);

    int operator[]();
}