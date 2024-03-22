#pragma once
#include <iostream>
// 这一节主要讲一下decltype以及C++11为什么要加入decltype这个概念
// 首先，在C11之前(e.g. C98) 模板类的定义还不是非常完善(当然现在也迷惑得一批)
// 下面的模板定义会遇到一些问题:
template<class T1, class T2>
void ft(T1 x, T2 y) {
    // 这种初始化正确吗?
    T1 sum1 = x + y;
    std::cout << "sum1 is: " << sum1 << std::endl;
    T2 sum2 = x + y; 
    std::cout << "sum2 is: " << sum2 << std::endl;
}
// 直观上来看似乎没什么问题，但是，具体到运行时就会有一些细微的问题
// 例如:
//      假设T1是int类型，T2是double类型，那么x + y应该是优化成double类型
//      那么T1 sum = x + y这个初始化语句就会将x + y的值强制转换成double赋给sum1
//      假设T1是double类型，T2是float类型，那么x + y应该是优化成double类型
//      那么T2 sum = x + y这个初始化语句就会将x + y的值强制转换成float赋给sum2
//      这种过程在运行时可能不会出错，但也有出现非预期结果的可能性(毕竟有截断可能)

// 对模板有执念的程序员们向上面反应了这个问题，于是C11推出了decltype这个解决方案

// ft模板的一种显式具体化
template<> void ft(int x, double y) {
    decltype(x + y) xplusy = x + y;
    std::cout << "x + y (int+double) with type decline is: " << xplusy << std::endl;
    std::cout << "type of xplusy is: " << typeid(xplusy).name() << std::endl << std::endl;
    std::cout << "The template is not used for function generation\n";
}
// ft模板的另一种显式具体化
template<> void ft(double x, float y) {
    decltype(x + y) xplusy = x + y;
    std::cout << "x + y (double+float) with type decline is: " << xplusy << std::endl;
    std::cout << "type of xplusy is: " << typeid(xplusy).name() << std::endl << std::endl;
    std::cout << "The template is not used for function generation\n";
}

// 这样编译器就可以在编译时通过x与y的类型来推断xplusy的类型并动态指明xplusy的类型了

// 最后，再来关注下面这个问题
// 上面的例子我们有意的使用了void修饰符来表明函数没有返回值
// 那如果有返回值呢？
// 不难发现也会遇到类型声明的问题
// 是否可以这样解决?
// template<typename T1, typename T2>
// decltype(x1+x2) ft(T1 x1, T2, x2);
// 你应该发现这样是行不通的
// 正如下面这个例子:
// int t = x + y;
// int x=10, y=20;
// 你会发现x1和x2都是在decltype使用他们之后声明的
// 因此编译器会报错
// 那怎么处理返回值的声明问题呢?
// C11给出了auto和->的解答:
// 是的，没错，还是显式具体化，毕竟函数签名只包含名称和参数列表..
// template <> auto ft(double x, int y) -> decltype(x + y) {
// }
// 不过我遇到了一个很confusing的问题，这里使用上面的语句打算创建一个显式实体化函数，但是编译器会发生报错，告知不存在此类模板
// 也就是说，无法使用模板生成返回类型不同的函数，即使他们的参数列表和名称都相同
// 下面这个显式实例化同理
// template auto ft<double, int>(double x, double y) -> decltype(x + y) {
// }
// 其实道理很显然，模板是不能随意更改的，尤其是定义在函数体外的信息(返回类型也包含在内)
// 于是我又新做了一个模板..
// 至于为什么多加了一个形参z我觉得原因挺显然的，不然你试试把z去掉看看结果..
template<typename T1, typename T2>
auto ft(T1 x, T2 y, T2 z) -> decltype(x + y + z) {
    // 这样返回的值就跟x+y+z的类型一样了..
    return x + y + z;
}

// 关于decltype还有一丢丢有趣的性质，之后更新..