#include "const_define.h"

void defining_constants() {

    const float cPI{ 3.1416f };

    #define dPI 3.1416f

}

void using_constants() {

    std::cout << "Notice that cPI here is no longer available in this separate scope\n" << std::endl;
    // std::cout << cPI << std::endl;
    std::cout << "But dPI is still available since #define directive is global replacing during preprocessing\n" << std::endl;
    std::cout << "It remains: ";
    std::cout << dPI << std::endl << std::endl;
   
}

void type_checking() {
    // Notice that the compiler will give an error since it will check 
    // the type of a const variable and the value it is assigned
    // const int cInt { "A string" };
    // While no error is reported for "Another string" defined by #define
    #define dInt "Another string"
}

void re_defining() {

    const int cInteger { 2147483647 };
    #define dInteger -2147483648
    std::cout << "First definition of dInteger: " << dInteger << std::endl;
    #undef dInteger
    // Utilizing #undef directive, we are free to redefine dInteger as many times as we like
    // Also, why we could 'initialize' dInteger to 2147483648? Should it not report an error? Don't forget #define don't support variable type!! 
    // Here 2147483648 is not an 32_bit integer, it actually is a string!!
    #define dInteger 2147483648
    std::cout << "Second definition of dInteger: " << dInteger << std::endl;
    
}