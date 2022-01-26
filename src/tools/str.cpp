#include "../../headers/tools/str.hpp"



std::string str_if(bool condition, std::string text) {
    if(condition) return text;
    else return "";
}