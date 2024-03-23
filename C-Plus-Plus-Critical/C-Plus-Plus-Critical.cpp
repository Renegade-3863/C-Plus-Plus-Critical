#include "const_define.h"
#include "marginal_effect.h"
// #include "C11.h"
// #include "static_nonstatic.h"
#include "IntelPtr.h"
#include "templateC11.h"
#include "InlineRerc.h"
#include "ArrayName.h"

// 常见面试问题:
// 如何在main函数前执行一些程序？
// 一般比较容易想到的是使用构造函数
// 初始化全局变量或静态变量算不算执行程序了? (个人认为只要是类对象的东西都算)
// 使用C11 Lambda函数进行复制操作(虽然有些奇怪，但有时候也有用
// 使用函数对全局变量进行赋值(虽然也很奇怪，不过也是赋值了

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
    // std::string testing1 = "Normal allocation";
    // normalAlloc(testing1);
    // std::string testing2 = "Shared allocation";
    // smartAllocS(testing2);
    // std::string testing3 = "Unique allocation";
    // smartAllocU(testing3);
    // std::string testing4 = "Problematic allocation";
    // ProblemSptr(testing4);
    // std::string testing51 = "first string";
    // std::string testing52 = "second string";
    // DistSU(testing51, testing52);
    // std::cout << "decltype确定的返回值是: " << ft(10, 30.5, 23.33) << ", 类型是: " << typeid(ft(10, 30.5, 23.33)).name() << std::endl;
    // std::cout << fibo(20) << std::endl;
    // extern int arr[3];
    traverse(arr);
    traverse2D(arr2D);
    // ft('a', 12.00);
    return 0;
}