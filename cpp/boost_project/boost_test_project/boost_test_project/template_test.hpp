#pragma once


using namespace std;
template <typename T> 
inline T const& max(T const& a, T const& b)
{
	return a < b ? b : a;
}


inline char const* max1 (char const* a, char const* b) 
{ 
    std::cout<<"max1 char const* "<<std::endl;
    return std::strcmp(a,b) < 0 ? b : a; 
} 


// maximum of three values of any type (call-by-reference) 
template <typename T> 
inline T const& max (T const& a, T const& b, T const& c) 
{ 
    return max1(max1(a,b), c); // error, if max(a,b) uses call-by-value 
} 


template<typename T>
void myswap(T& a, T& b) {
	//-1
		T c = a;
	a = b;
	b = c;
};

template<typename T>
void Print(T& a, T& b) {
	//-2
		std::cout << "a=" << a << "\nb" << b << std::endl;
}

template<typename T1>
void MySort(T1 a) {
	//-3
		cout << "aaa" << endl;
}


template<typename T>
void Getnum(T a, int b) {
	//-4
	std::cout << "a=" << a << ";\nb="<<b<<std::endl;
}

/*
template <typename T> 
inline T* const& max (T* const& a, T* const& b);

//inline char const* const& max (char const* const& a, 
     //                          char const* const& b);

inline void max_printf(char const* a, char const* b);
inline char const* max1 (char const* a, char const* b);

*/

