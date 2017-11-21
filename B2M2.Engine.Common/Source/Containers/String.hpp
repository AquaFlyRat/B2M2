/*
    @author Barney Wilks
*/

#pragma once

#include <vector>
#include <sstream>
#include <iostream>

namespace arch {
    template<typename T>
    void SplitString(const std::string &string, char delim, T result) {
        std::stringstream _stringstream(string);

        std::string item;
        while (std::getline(_stringstream, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> SplitString(const std::string &string, char delim);
}
