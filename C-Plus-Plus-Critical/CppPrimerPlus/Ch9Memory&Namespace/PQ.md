#### 1.
``` C++
// golf.h -- for pe9-1.cpp
#pragma once

const int Len = 40;

struct golf 
{
    char fullname[Len];
    int handicap;
};

// non-interactive version:
// function sets golf structure to provided name, handicap
// using values passed as arguments to the function
void setgolf(golf & g, const char * name, int hc);

// interactive version:
// function solicits name and handicap from user
// returns 1 if name is entered, 0 if name is empty string
int setgolf(golf & g);

// function resets handicap to new value
void handicap(golf & g, int hc);

// function displays contents of golf structure
void showgolf(const golf & g);

// golf.cpp -- implement prototypes in golf.h
#include "golf.h"
#include <iostream>

// 这个函数把传入的 golf 类型变量 g 的对应字段设置成 name 和 hc
void setgolf(golf & g, const char * name, int hc)
{
    // 注意：name 是一个常量，所以不能直接用赋值运算符，因为 g 内部存储的是一个非常量字符数组
    strcpy(g.fullname, name);
    g.handicap = hc;
}

// 这个函数需要提示用户输入高尔夫手的姓名和球数，然后把输入的信息存储到 g 中
// 在用户输入出错时需要提示输入不合法，并重新接收用户的输入信息
int setgolf(golf & g)
{
    // 提示用户输入姓名
    std::cout << "Please enter the fullname of the golfer: ";
    // 接收用户输入的姓名，如果输入的姓名长度超过了 40 个字符，则截断
    std::cin.get(g.fullname, Len);
    // 如果用户输入的姓名是空字符串，那么直接返回 0 即可
    if(strlen(g.fullname) == 0)
    {
        return 0;
    }
    // 需要先清空输入缓存，防止之前输入名字的时候超出 Len 部分的字符被下面的 cin 读入到 handicap 中
    std::cin.clear();
    // 否则，姓名非空，那么我们进一步询问用户 g.handicap 的值
    std::cout << "Please enter the handicap of the golfer: ";
    std::cin >> g.handicap;
    // std::cin.clear();
    std::cin.get();
    // 按要求返回 1 即可
    return 1;
}

// 这个函数重置 g 中 hc 的值
void handicap(golf & g, int hc)
{
    g.handicap = hc;
}

// 这个函数显示 g 的姓名和球数
void showgolf(const golf & g)
{
    std::cout << "The fullname of the golfer is: " << g.fullname << std::endl;
    std::cout << "The handicap of the golfer is: " << g.handicap << std::endl;
}

// mainPQ1.cpp -- testing of function implemented for PQ1
#include "golf.h"
#include <iostream>

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    golf ann, andy, arrGolf[3];
    setgolf(ann, "Ann Birdfree", 24);
    showgolf(ann);

    if(setgolf(andy) == 1)
    {
        showgolf(andy);
    }
    handicap(andy, 20);
    showgolf(andy);

    int i = 0;
    while(i < 3 && setgolf(arrGolf[i]))
    {
        showgolf(arrGolf[i]);
        ++i;
        if(i < 3)
        {
            cout << "next one: " << endl;
        }
    }
    return 0;
}
```

#### 2.
``` C++
// static.cpp -- using a static local variable
#include <iostream>
#include <string>

// constants
const int ArSize = 10;

// function prototype
void strcount(std::string str);

int main()
{
    using namespace std;
    // char input[ArSize];
    string input;
    char next;

    cout << "Enter a line:\n";
    getline(cin, input);
    // 当输入为空时，循环结束
    while(input != "")
    {
        // cin.get(next);
        // while(next != '\n') // string didn't fit!
            // cin.get(next);  // dispose of remainder
        strcount(input);
        cout << "Enter next line (empty line to quit):\n";
        getline(cin, input);
    }
    cout << "Bye\n";
    return 0;
}

void strcount(std::string str)
{
    using namespace std;
    static int total = 0;   // static local variable
    int count = 0;          // automatic local variable

    cout << "\"" << str << "\" contains ";
    cout << str.size() << " characters\n";
    // cout << total << " characters total\n";
}
```

#### 3.
``` C++
// PQ3main.cpp -- testing of function implemented for PQ3
#include <iostream>

struct chaff
{
    char dross[20];
    int slag;
};

// 分配一个外部的静态内存块，用于后续的定位 new 空间分配
char buffer[512];

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    // 定位 new，从 buffer 开头开始，分配两块足够大的空间，给一个 chaff 对象数组
    chaff * ptr = new (buffer) chaff[2];
    // 给数组的第一个元素赋值
    strcpy(ptr->dross, "dross1");
    ptr->slag = 1;
    // 给数组的第二个元素赋值
    strcpy((ptr + 1)->dross, "dross2");
    (ptr + 1)->slag = 2;
    // 打印数组的第一个元素
    cout << "dross: " << ptr->dross << endl;
    cout << "slag: " << ptr->slag << endl;
    // 打印数组的第二个元素
    cout << "dross: " << (ptr + 1)->dross << endl;
    cout << "slag: " << (ptr + 1)->slag << endl;
    return 0;
}
```