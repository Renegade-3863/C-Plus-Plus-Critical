#pragma once
#include <iostream>

// 一般不建议将内部有递归(无论尾递归或顺序递归)的函数进行内联，当然你加上内联修饰符不会有问题，
// 只是编译器不会采纳你将对于将这个递归函数看作内联函数的建议
// 原因，编译阶段无法确认只有运行时才能动态确认的递归调用栈深度

inline auto fibo(int n) -> decltype(n) {
    if (n == 0 || n == 1)
        return n;
    return fibo(n - 2) + fibo(n - 1);
}