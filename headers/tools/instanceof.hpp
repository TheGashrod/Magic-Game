#ifndef __TOOL_INSTANCEOF_INCLUDED__
#define __TOOL_INSTANCEOF_INCLUDED__



#include <type_traits>


/*
template<typename Base, typename Derived>
bool instanceof(const Derived*) {
	return is_base_of<Base, Derived>::value;
} 
*/

template<typename Base, typename T>
bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}




#endif