/*
    @author Barney Wilks
*/

#include "String.hpp"

std::vector<std::string> arch::SplitString(const std::string& string, char delim) {
    std::vector<std::string> elems;
    SplitString(string, delim, std::back_inserter(elems));
    return elems;
}

