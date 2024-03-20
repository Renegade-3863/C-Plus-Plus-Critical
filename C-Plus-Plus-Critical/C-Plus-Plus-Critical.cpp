#include "const_define.h"
#include "marginal_effect.h"
// #include "C11.h"
// #include "static_nonstatic.h"
#include "IntelPtr.h"

int main() {

    // defining_constants();
    // using_constants();
    // Testing_MGNL();
    // Testing_MIN();
    // type_checking();
    // re_defining();
    // testing_brace_Init();
    // testing_var1();
    // testing_var2();
    // testing_var3();
    // Testing_RVO();
    // testingStatic_member();
    std::string testing1 = "Normal allocation";
    normalAlloc(testing1);
    std::string testing2 = "Shared allocation";
    smartAllocS(testing2);
    std::string testing3 = "Unique allocation";
    smartAllocU(testing3);
    std::string testing4 = "Problematic allocation";
    // ProblemSptr(testing4);
    std::string testing51 = "first string";
    std::string testing52 = "second string";
    DistSU(testing51, testing52);
    return 0;
}