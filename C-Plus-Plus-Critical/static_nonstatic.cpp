// Notice that we didn't include "static_nonstatic.h" here!!
#include <iostream>

void testing_var1() {
    // We see this again, what is it? You may try note it and see the consequence
    extern int var1;
    // Hey, you didn't define var, you just declared it, this result my be indefinite!
    // Try it multiple times and you will see it is always MAX_INT32
    std::cout << "var1 is: " << var1 << std::endl;
}

void testing_var2() {
    extern int var2;
    // Will this work?
    // If it won't, how to fix it?
    // std::cout << "var2 is: " << var2 << std::endl;
}

void testing_var3() {
    extern int var3;
    // Check this(remember we defined var3 as static int in "static_nonstatic.h")
    // std::cout << "var3 is: " << var3 << std::endl;
}




/*
    <summary>
    So what did you discovered?
    The static variable var3 is no longer available in testing_var3()
    and var2 is unavailable as well
    But var1 is still available
    Reasons:
    static:
        for any variable, if declared static, it won't be able to be used outside the scope defined it.
        this example we used a file's scope, if you define it inside a local function (main() function included)
        it would only be available within that function(scope)
        Notice that this means we could define multiple static variables in separate functions within one single file!
        just like this:
            foo() {
                static int same = 250;
            }
            foo() {
                static int same = 250;
            }
        The program WILL work properly.
        The compiler will deal with the resolution name of the two "same"s
        So, it is of good reasons to use static variables in your own design part if you want something 
        called "encapsulation" or "information hiding"
    global:
        From the example, you may notice that var1 is still available even if we didn't include "static_nonstatic.h"
        (If you included it, then nonsense talking about global variables..)
        it is because global means that the scope of the variable is the whole PROGRAM other than the individual file
        
        any variable DEFINED outside every function is global
        
        You may ask about var2: It is declared as extern, why I can't use it here?
        You had answered the question yourself:
        
        declare != define
        
        When you extern int var2, it only tells the complier that:
        "There SHOULD be some other files (not this file) had defined this outer variable var2"
        It is actually not a definition, just a notification.
        
        when you int var1, even without giving it a value, the complier would treat it as a definition.
        but extern int var2 is not a definition, it is a reference declaration!
        
        So you should be EXTREMELY careful when you want to define/declare some thing global
        Because they are global everywhere in the whole program, other programmers may change the variable you used here!
    
    static differences between C & C++(You may skip this if you haven't learnt about compiling principle):
        
        There are some noticeable things regarding static variable initialization in C std & C++ std
        if you do 
            static int con = 10;
        it will be OK in both C & C++
        But if you do
            int add1 = 10;
            int add2 = 20;
            static int con = add1 + add2;
        it will give Compile error in C but not in C++
        This is the difference between C(non OOP) and C++(kind of OOP)
        The GCC(C compiler) would care for static variable initialization during compile time,
        but G++(C++ compiler) would allow runtime initialization
        since we have many classes in C++, some of the classes are of dynamic size, it cannot be determined
        completely during compile time. So the C++ compiler allows the con to be initialized later during runtime(when add1 + add2 is able to be computed)
        
        Also some more about static data members in C++ class...


*/