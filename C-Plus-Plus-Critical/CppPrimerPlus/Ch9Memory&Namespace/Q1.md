#### 1. 
- a. 如果 homer 是函数的形参，那么我们只需要把 homer 设置为局部的自动变量即可 (对应老版本 C++，也就是 C++ 98 及以前的版本，就是 register 变量)
- b. 如果 secret 变量由两个文件共享，那么我们只需要把它声明成全局的静态变量，对应 extern 关键字，换句话说，在两个文件中的任意一个中不使用 extern 关键字而在最外侧定义这个 secret 变量，之后在另一个函数中使用 extern 关键字引用声明这个外部定义的 secret 变量即可
    - **答案补充**: **除了使用 static 关键字，我们还可以在所有函数外，用一个未命名的名称空间来定义这个 secret 变量**
- c. 如果 topsecret 变量由一个文件中的所有函数共享，但对于其他文件来说是隐藏的，那么我们可以把它定义成一个内部的静态变量，也就是在文件内、所有函数外使用 static 关键字即可
- d. 如果 beencalled 变量需要记录包含它的函数被调用的次数，我们可以在包含它的函数内部用 static 关键字来定义它，基于 static 类型变量的定义，静态的变量都会在编译的时候分配空间，而在作用域内被被声明后直到作用域结束时可见，所以我们可以利用这种特征记录它所在函数被调用的次数

#### 2. 指出 using 声明和 using 编译指令之间的区别？
- 这两种用法之间的核心区别在于：using 声明的本质是 "声明我在当前作用域内可以使用一个参数名，同时不允许其它同名变量和我重复"，using 编译指令的本质在于 "告诉编译器，帮我在当前作用域引入某个名称空间的全部信息，让它们可以在编译时参与变量类型的解析"。
- 从实际编码的角度来说，**using 编译指令引入的变量名和一般的变量名一样，可以被更小作用域的变量名覆盖，而 using 声明引入的变量名不能再进一步被覆盖。**

#### 3. 重新编写下面的代码，使其不使用 using 声明和 using 编译指令
``` C++
// Template：
#include <iostream>
using namespace std;
int main()
{
    double x;
    cout << "Enter value: ";
    while(!(cin >> x))
    {
        cout << "Bad input. Please enter a number: ";
        cin.clear();
        while(cin.get() != '\n')
            continue;
    }
    cout << "Value = " << x << endl;
    return 0; 
}

// Answer：
#include <iostream>
// using namespace std;
int main()
{
    double x;
    std::cout << "Enter value: ";
    while(!(std::cin >> x))
    {
        std::cout << "Bad input. Please enter a number: ";
        std::cin.clear();
        while(std::cin.get() != '\n')
            continue;
    }
    std::cout << "Value = " << x << std::endl;
    return 0; 
}
```

#### 4. 重新编写下面的代码，使之使用 using 声明，而不是 using 编译指令
``` C++
// Template：
#include <iostream>
using namespace std;
int main()
{
    double x;
    cout << "Enter value: ";
    while(!(cin >> x))
    {
        cout << "Bad input. Please enter a number ";
        cin.clear();
        while(cin.get() != '\n')
            continue;
    }
    cout << "Value = " << x << endl;
    return 0;
}

// Answer：
#include <iostream>
// using namespace std;
int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    
    double x;
    cout << "Enter value: ";
    while(!(cin >> x))
    {
        cout << "Bad input. Please enter a number ";
        cin.clear();
        while(cin.get() != '\n')
            continue;
    }
    cout << "Value = " << x << endl;
    return 0;
}

```

#### 5. 
- 本题涉及到一些底层逻辑，我们首先要明确：函数重载不适用于本题，因为 C++ 中无法利用返回值不同对函数进行重载，可以认为原因是：有一种函数返回的是空值 void，此时这个函数理论上不返回任何东西，那么我们理论上可以无限重载返回值为空值的函数，但这是不现实的。
- 本题要求我们实现同名函数在同一程序的不同模块(文件)中返回不同的值，那么很明显是想让我们定义静态函数，我们只需要用 static 函数在两个模块中分别定义返回值不同的 average 函数即可

#### 6.
``` C++
// QRfile1.cpp
#include <iostream>
using namespace std;
void other();
void another();
int x = 10;
int y;

int main()
{
    // 这里的 x 来自上面的外部链接 x，也就是 10
    cout << x << endl;
    {
        int x = 4;
        // 这里的 x 来自作用域内部这个覆盖了外部变量的 x，也就是 4
        cout << x << endl;
        // 这个 y 来自外面定义的外部静态变量 y，被初始化成了0
        cout << y << endl;
    }
    other();
    another();
    return 0;
}

void other()
{
    int y = 1;
    // 这里的 x 来自本地的外部链接 x，也就是 10，y 来自内部覆盖了外部 y 的这个 y，也就是 1
    cout << "Other: " << x << ", " << y << endl;
}

// QRfile2.cpp
#include <iostream>
using namespace std;
extern int x;
// 等于 static int y = -4
namespace 
{
    int y = -4;
}

void another()
{
    // 这里的 x 来自 QRfile1.cpp，也就是 10，y 来自本地的 y，也就是 -4
    cout << "another(): " << x << ", " << y << endl;
}
```

#### 7.
``` C++
#include <iostream>
using namespace std;
void other();
namespace n1
{
    int x = 1;
}

namespace n2
{
    int x = 2;
}

int main()
{
    // using 编译指令，内部的变量可以被覆盖
    using namespace n1;
    // 这里的 x 是来自 n1 名称空间的 x，值为 1
    cout << x << endl;
    {
        int x = 4;
        // 第一个是作用域内的本地 x，也就是 4，第二个是 n1 名称空间中的 x，也就是 1，第三个是 n2 名称空间中的 x，也就是 2
        cout << x << ", " << n1::x << ", " << n2::x << endl;
    }
    using n2::x;
    // 这里的 x 就被覆盖成了 n2 名称空间中的 x，也就是 2
    cout << x << endl;
    // other 打开了一个新的函数作用域
    other();
    return 0;
}

void other()
{
    using namespace n2;
    // 这个 x 也是 n2 名称空间中的 x，也就是 2
    cout << x << endl;
    {
        int x = 4;
        // 这里的 x 是本地的 x，覆盖了外面 n2 名称空间中的 x
        cout << x << ", " << n1::x << ", " << n2::x << endl;
    }
    using n2::x;
    // 变回 n2 名称空间中的 x，也就是 2
    cout << x << endl;
}
```

- 第七题个人认为核心的 takeaway 在于：other 函数调用外面的这个 using n2::x 实际上和 other 函数本身无关，也就是说，无论是 using 编译指令还是 using 声明，它们都只作用在自身所在的作用域中，而不会延伸到内部函数创建出来的作用域中，换句话说，如果没有 other 函数内部的这个 using namespace n2，other 内部的第一行 cout << x << endl 就会报错，找不到 x
- 不过注意，函数作用域和一般的大括号作用域不同，大括号作用域是可以被 using 渗透的，函数作用域不行