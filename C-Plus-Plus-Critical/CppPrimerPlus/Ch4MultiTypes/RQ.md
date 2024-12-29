#### 1.
- a. 声明由 30 个 char 组成的数组：
``` C++
    char actor[30];
```
- b. 声明由 100 个 short 组成的数组：
``` C++
    short bestie[100];
```
- c. 声明由 13 个 float 组成的数组
``` C++
    float chuck[13];
```

- d. 声明由 64 个 long double 组成的数组
``` C++
    long double dipsea[64];
```

#### 2. 使用 array 而不是数组来完成问题1
- a.
``` C++
    array<char, 30> actor;
```
- b.
``` C++
    array<short, 100> betsie;
```

- c. 
``` C++
    array<float, 13> chuck;
```

- d.
``` C++
    array<long double, 64> dipsea;
```

#### 3. 声明一个包含 5 个元素的 int 数组，并将它初始化为前 5 个正奇数
``` C++
    int arr[5] = {1, 3, 5, 7, 9};
```

#### 4. 将问题 3 中数组第一个元素和最后一个元素的和赋给变量 even
``` C++
    int arr[5] = {1, 3, 5, 7, 9};
    int even = arr[0]+arr[4];
```

#### 5. 编写一条语句，显示 float 数组 ideas 中的第 2 个元素的值
``` C++
    std::cout << ideas[1] << std::endl;
```

#### 6. 声明一个 char 的数组，并将其初始化为字符串 "cheeseburger"
``` C++
    char arr[] = "cheeseburger";
```

#### 7. 声明一个 string 对象，并将其初始化为字符串 "Waldorf Salad"
``` C++
    string str = "Waldorf Salad";
```

#### 8. 设计一个描述鱼的结构声明，结构中应当包括品种、重量 (整数，单位为盎司) 和长度 (英寸，包括小数)
``` C++
    struct fish
    {
        char type[20];
        int weight;
        float length;
    };
```

#### 9. 声明一个问题 8 中定义的结构的变量，并对它进行初始化
``` C++
    fish f = {"Shark", 200, 23.1};
```

#### 10. 用 enum 定义一个名为 Response 的类型，它包含 Yes、No 和 Maybe 等枚举量，其中 Yes 的值为 1，No 为 0，Maybe 为 2
``` C++
    enum Response { No, Yes, Maybe };
```

#### 11. 假设 ted 是一个 double 变量，请声明一个指向 ted 的指针，并使用该指针来显示 ted 的值
``` C++
    double* ptrted = &ted;
    std::cout << *ptrted << std::endl;
```

#### 12. 假设 treacle 是一个包含 10 个元素的 float 数组，请声明一个指向 treacle 的第一个元素的指针，并使用该指针来显示数组的第一个元素和最后一个元素
``` C++
    float* ptrtreacle = &treacle[0];
    std::cout << *ptrtreacle << std::endl;
    std::cout << *(ptrtreacle+9) << std::endl;
```

#### 13. 编写一段代码，要求用户输入一个正整数，然后创建一个动态的 int 数组，其中包含的元素数目等于用户输入的值。首先使用 new 来完成这项任务，再使用 vector 对象来完成这项任务
``` C++
    int n;
    std::cout << "Please enter the size of the int array:\n";
    std::cin >> n;
    int* arr = new int[n];
    // vector<int> arr(n);
```

#### 14. 下面的代码是否有效？如果有效，它将打印出什么结果？
``` C++
    cout << (int *) "Home of the jolly bytes";
```
- 会打印出后面这段静态常量 C 风格字符串的内存地址 (大多数编译器输出的会是十六进制的结果)

#### 15. 编写一段代码，给问题 8 中描述的结构分配动态内存，再读取该结构的成员的值
``` C++
    // 略
```

#### 16. 本题只需要记住：cin 会跳过开头的所有空白，但不会跳过结尾的空白 (这里说的空白包括换行符、空格和制表符)

#### 17. 声明一个 vector 对象和一个 array 对象，它们都包含 10 个 string 对象。指出所需的头文件，但不要使用 using。使用 const 来指定要包含的 string 对象数
``` C++
#include <vector>
#include <array>
#include <string>
const int N = 10;
    std::vector<std::string> vec(N);
    std::array<std::string, N> arr;
```