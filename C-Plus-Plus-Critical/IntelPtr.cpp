#include "IntelPtr.h"
// Implementation of functions in IntelPtr
// We may talk about exception later, you may ignore anything related to throw()
void normalAlloc(std::string& str) noexcept {
    // Use the referenced str to dynamically allocate a new string 
    // Use a normal pointer to point at it
    std::string* NeedDL = new std::string(str);
    // If the new pointer's allocation failed, throw an exception
    if (!NeedDL)
        throw std::exception();
    std::cout << "A new C++ string pointer was just created from the argument you passed!" << std::endl;
    std::cout << "The contents the pointer points at is: " << *NeedDL << std::endl;
    // Small quiz: what if we u
    // If you don't delete it, something called "memory leak" would happen to your system memory addr
    std::cout << "Deleting the pointer created..\n";
    delete NeedDL;
    // One interesting question: What are the differences between C++11 nullptr and C99 NULL?
    // To be updated..
    NeedDL = nullptr;
    return;
}

void smartAllocS(const std::string& str) throw(std::exception, int){
    // Use the referenced str to dynamically allocate a new string
    // Use a shared_pointer<std::string> to point at it
    // Some other questions:
    // Could we use this statement for initialization?
    // std::shared_ptr<std::string> Shared = new std::string(str);
    // Why could / Why couldn't?
    // 
    std::shared_ptr<std::string> Shared(new std::string(str));
    std::cout << "A new C++ string shared_pointer was just created from the argument you passed!" << std::endl;
    std::cout << "The contents the pointer points at is: " << *Shared << std::endl;
    std::cout << "Deleting the pointer created..\n";
    // We no longer need this delete statement (Although we have new above)
    // delete Shared;
    return;
}

void smartAllocU(const std::string& str) throw(std::exception, int) {
    // Use the referenced str to dynamically allocate a new string
    // Use a unique_pointer<std::string> to point at it
    std::unique_ptr<std::string> Unique(new std::string(str));
    std::cout << "A new C++ string unique_pointer was just created from the argument you passed!" << std::endl;
    std::cout << "The contents the pointer points at is: " << *Unique << std::endl;
    std::cout << "Deleting the pointer created..\n";
    // We no longer need this delete statement (Although we have new above)
    // delete Unique;
    return;
}

// Now you know the critical usage of smart pointers: getting rid of deleting pointers (which you may sometimes forget)
// But if this is the only purpose, why we still need two types (indeed, we have four types, other two are auto_pointer and weak_pointer, but auto_pointer is discarded)
// The answer to this lies in the name of the two types of pointer
void DistSU(const std::string& str1, const std::string& str2) throw(std::exception, int){
    // One simple example may be able to solve your confusion:
    std::unique_ptr<std::string> Unique1(new std::string(str1));
    std::cout << "Unique_ptr Unique1->" << *Unique1 << std::endl;
    // std::unique_ptr<std::string> Unique2(Unique1);
    std::shared_ptr<std::string> Shared1(new std::string(str2));
    std::cout << "Shared_ptr Shared1->" << *Shared1 << std::endl;
    std::cout << "Shared_ptr Shared1.count = " << Shared1.use_count() << std::endl;
    std::shared_ptr<std::string> Shared2(Shared1);
    std::cout << "Shared_ptr Shared2.count = " << Shared2.use_count() << std::endl;
    // You may see that the compiler tells you that the copy constructor for template class std::unique_ptr<Typemane x> has been deleted
    // Recall that in C++11, when we define a new class, we could explicitly declare its constructors to be deleted or default
    // e.g. Word() = delete; -> No default constructor for Word class
    //      Word(const Word&) = default -> default copy constructor for Word class
    // Then you could see, unique_pointer makes sure that one unique_pointer type pointer would only point to those memory address that are not shared by other unique_pointer's
    // shared_pointer's allow multiple shared_pointer's to point at the same memory location
}

// But here comes one more problem:
// You told me that smart pointer would be responsible for deleting the memory space it points at automatically
// But regarding shared_pointer, if we have multiple shared_pointer's pointing at the same location, wouldn't that cause double free?
// Sure! You are smart indeed!
// Check this:
void ProblemSptr(const std::string& str) throw(std::string) {
    std::string* normal = new std::string(str);
    std::shared_ptr<std::string> Shared1(normal), Shared2(normal);
    std::cout << "Shared_ptr Shared1.count = " << Shared1.use_count() << std::endl;
    std::cout << "Shared_ptr Shared2.count = " << Shared2.use_count() << std::endl;
    return;
    // This is forbidden!
    // One shall never initializer multiple shared_pointers using a normal pointer
    // This way, both Shared1 and Shared2 will count the shared number as 1
    // So both the two pointers will try to delete normal when the life cycle ends -> double free!
    // You may be even more confused: What is count?
    // Remember shared_ptr is a template class, and a class could have its own data members
    // shared_ptr class utilize a counter to realize its deletion of memory
    // Basic logic:
    // When calling destructor of a shared_ptr
    // Check its count data member, if count > 1, count--, no delete
    //                              if count == 1, count--, delete the memory it points at
    // So now you understand fully the implementation logic of shared_ptr! Congrat!
}

// Some more notifications about shared_ptr
// Do not use Shared1.get() to initialize other shared_ptr's, the reason is more or less the same
// as the reason that you couldn't use normal pointer to initialize multiple shared_ptr's
// which is the problem related to count.

// More advanced topic:
// DeadLock problem for shared_ptr, to introduce this, we need to learn about weak_ptr
// TBC..