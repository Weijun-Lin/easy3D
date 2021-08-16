//@Brief: 一些公用的定义和工具包

#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <iostream>

#define SEE(x) std::cout << #x << " " << x << std::endl;

typedef unsigned long DWORD;
typedef DWORD COLORREF;

inline void swap_int(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

#endif // !__UTILITY__H__
