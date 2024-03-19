#pragma once
// This header file is used to record some features about static and global variables in
// a C/C++ program. For example, their scope, what are their meaning to the compiler,
// assembler, linker and loader etc.

// First, what does this line mean?
// If you cannot answer this well, please check const_define.h / const_define.cpp
#define THING 100

// What is the scope of this "thing" THING ?
// Note that we use "thing" other than variable to describe it
// For a C/C++ program, the THING in the program will be replaced by the "text"(Not any data type) 
// behind it (which is 100)

// But wait a minute, we are talking about static and global varibles. Why you mention #define?
// I think I need to make it clear that static/global is used to describe variables. But what you #define
// is never a variable!

// Now back on track
// What are these?
int var1 = 2147483647;      // To make it surprising, we use MAX_INT32 (If you don't like this style, #include <limits.h> yourself
extern int var2;
static int var3;
void testing_var1();
void testing_var2();
void testing_var3();

// You may feel confused, you know var1 is global, but what is var2? 
// You may now go to static_nonstatic.cpp for checking their differences.

// static data members in class:
// Due to the property of a static variable, it ought to be initialized once and only once regardless of how many class objects are created
// it's like memory sharing, or you may treat it like the sharing context between threads
// If you change the value of the static data member in one object, all other objects' corresponding static data member would be changed
// since they are actually referring to the same memory address
// example:
class staticClass {
private:
    static int datam1;
    int pridatam2;
public:
    staticClass(): pridatam2(100){ }
    int getpridatam2() const { return this->pridatam2; }
    int getdatam1() const { return this->datam1; }
    // Define a mutator to change the static data member
    void incremdata1() { this->datam1++; }
};

// You may explicitly define the static data member for a class(not object! You should know why use this term)
int staticClass::datam1 = 12;

void testingStatic_member() {
    // Create one test subject
    staticClass* testClass1 = new staticClass;
    staticClass* testClass2 = new staticClass;
    std::cout << "datam1 for testClass1 is: " << testClass1->getdatam1() << std::endl;
    std::cout << "datam1 for testClass2 is: " << testClass2->getdatam1() << std::endl;
    testClass1->incremdata1();
    std::cout << "datam1 for testClass1 is: " << testClass1->getdatam1() << std::endl;
    std::cout << "datam1 for testClass2 is: " << testClass2->getdatam1() << std::endl;
    delete testClass1;
    testClass1 = nullptr;
    delete testClass2;
    testClass2 = nullptr;
    // Check the result of this function, you may see the meaning of static data members
}
