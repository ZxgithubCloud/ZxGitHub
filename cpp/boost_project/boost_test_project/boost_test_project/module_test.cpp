#include <iostream> 
#include <cstring> 
#include <string> 
//#include "template_test.hpp"


using namespace std;

// maximum of two values of any type 
/*
template <typename T> 
inline T const& max (T const& a, T const& b) 
{ 
    return a < b ? b : a; 
} 
*/

// maximum of two pointers 
template <typename T> 
inline T* const& max (T* const& a, T* const& b) 
{ 
    std::cout<<"T* const& "<<std::endl;
    return *a < *b ? b : a; 
} 

// maximum of two C-strings 
/*
inline char const* const& max (char const* const& a, 
                               char const* const& b) 
{ 
    std::cout<<"char const* const& "<<std::endl;

    return std::strcmp(a,b) < 0 ? b : a; 
} 
*/


inline void max_printf(char const* a, char const* b)
{
	std::cout << "char const* " << std::endl;

	std::cout << "a address is " << &a;
	std::cout << "b address is " << &b;

	//return std::strcmp(a, b) < 0 ? b : a;
}

inline char const* max1 (char const* a, char const* b) 
{ 
    std::cout<<"char const* "<<std::endl;
    return std::strcmp(a,b) < 0 ? b : a; 
} 

