#pragma once
#include <iostream>
#include <Windows.h>
#include <cstring>
enum Insert_style { H, T };
/*
    This header file records the new features of C++11 std and some functions utilized to
    test these features
    May update from time to time
*/

// First, we care about some new features added to class related features
// Some typical new features including brace initialization, lambda expression, MIL etc.
// Here we use a typical C++ class for illustration
class Word {
private:
    int frequency;
    char* str;
    void set(int f, const char* s)
        { frequency = f; str = new char[strlen(s) + 1]; strcpy(str, s); }
public:
    // User defined conversion constructor
    Word(const char* s, int k = 1) { set(k, s); std::cout << "conversion\n"; }
    // User defined copy constructor
    Word(const Word& w) { set(w.frequency, w.str); std::cout << "copy\n";  }
    // information visualization
    void print() const { std::cout << str << " : " << frequency << std::endl; }
    // create a temporary object with str member in upper case
    Word to_upper_case() const
    {
        Word x(*this);
        for (char* p = x.str; *p != '\0'; p++)
            *p += 'A' - 'a';
        return x;
    }
};

// RVO => Return Value Optimization
void Testing_RVO();

// Some other features related to normal data structures, we use a struct for combined description
// Don't mind I use LNode here, you could also review something about LinkList, couldn't you?
typedef struct LNode {
    // We use a singly linked cyclic linklist
    int data;
    LNode* next;
}LNode, *LinkList;

void testing_brace_Init();

bool ll_Init(LinkList& head);

// Please check this message:
// These are not part of the C++11 new features, it's the implementation of ordinary ll manipulation methods
bool ll_headInsert(LinkList& head, int val);

bool ll_tailInsert(LinkList& head, int val, LNode*& tail);

bool ll_deleteNode(LinkList& head, unsigned index, unsigned count);

bool ll_deletion(LinkList& head);

bool ll_traverse(const LinkList& head);