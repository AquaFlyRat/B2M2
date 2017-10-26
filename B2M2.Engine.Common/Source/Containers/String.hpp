/*
    @author Barney Wilks
*/

#pragma once

#include <vector>

namespace b2m2 {
    template<typename T>
    void SplitString(const std::string &string, char delim, T result) {
        std::stringstream stringstream(string);

        std::string item;
        while (std::getline(stringstream, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> SplitString(const std::string &string, char delim);
}
