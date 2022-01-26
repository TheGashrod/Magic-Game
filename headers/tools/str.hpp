#ifndef __TOOL_STR_INCLUDED__
#define __TOOL_STR_INCLUDED__

#include <string>

/**
 * @brief Returns a string only if the condition is fulfilled
 * 
 * @param condition
 * @param text 
 * @return std::string "" for false, text for true
 */
std::string str_if(bool condition, std::string text);



#endif