#include "C11.h"

bool ll_Init(LinkList& head) {
    // One problem, could we simply combine these statements into one line:
    // head = new LNode{ -1, head }; ?
    // Proved to be not feasible, the assignment operation is executed at the very last moment, before that, if you want to use the symbol 'head' for 
    // initializaton, it is still the name of a nullptr(because in our caller function, we initialize head to be nullptr)
    // Note that one could only explicitly initialize the data members of a struct/class if they are public!!!
    head = new LNode{ -1, nullptr };
    if (!head) {
        std::cout << "Initialization failed!\n";
        return false;
    }
    head->next = head;
    return true;
}

bool ll_headInsert(LinkList& head, int val) {
    // Since this is head insertion, we make the new node points at head;
    LNode* newNode = new LNode{ val, head->next };
    // The memory allocation failed, return false
    if (!newNode) return false;
    head->next = newNode;
    return true;
}

bool ll_tailInsert(LinkList& head, int val, LNode*& tail) {
    // Here we also make the new node points at head, but it is because we are making a cyclic ll
    LNode* newNode = new LNode{ val, head };
    // Same error checking for memory allocation
    if (!newNode) return false;
    tail->next = newNode;
    return true;
}

bool ll_deleteNode(LinkList& head, unsigned index, unsigned count) {
    if (index >= count) {
        std::cout << "Invalid deletion!" << std::endl;
        return false;
    }
    if (head->next == head) {
        std::cout << "Deleting something from an empty list!" << std::endl;
        return false;
    }
    LNode* traverse = head->next;
    LNode* pre = head;
    while (index--) {
        pre = traverse;
        traverse = traverse->next;
    }
    std::cout << "Deleting node: [" << traverse->data << "]..." << std::endl;
    pre->next = traverse->next;
    delete traverse;
    Sleep(300);
    traverse = nullptr;
    return true;
}

// Use recursive method to do the list deletion
bool ll_deletion(LinkList& head) {
    LNode* traverse = head;
    if (traverse != head)
        ll_deletion(traverse->next);
    delete traverse;
    traverse = nullptr;
    return true;
}

// BF traversing..
bool ll_traverse(const LinkList& head) {
    if (!head) {
        std::cout << "Sorry, you passed me an empty ll!\n" << std::endl;
        return false;
    }
    LNode* traverse = head->next;
    std::cout << "The whole list you created is listed below:\n" << std::endl;
    do {
        std::cout << traverse->data;
        if(traverse->next != head)
            std::cout << "->";
        traverse = traverse->next;
    } while (traverse != head);
    std::cout << std::endl;
    return true;
}

void testing_brace_Init() {
    // Some discussions about brace initialization in C++11 or later C++17
    // Why do we need such new tech of intialization?
    // Earlier when we use C99, we could only use ()/= to do initialization of an object
    // It would introduce things called "dual meaning":
    // 1. What is this line?
    // (Check the difinition of Word in C11.h)
    //      Word word1 = word2;         -> absolutely a copy construction! Not assignment
    // 2. What is this line?
    //      Word word();                -> are you declaring a new function prototype(return type Word)
    //                                  -> or just using default constructor for creating word?
    //                                  -> if you have user-defined constructor, this may be fine, but it's still not good
    // => braces would solve this confusion:
    //      Word word1{word2};
    //      Word word{};
    // This could be good reasons for C++11 to introduce brace initialization
    std::cout << "Initializing and allocating spacess for the head node of a linked list..." << std::endl;
    LinkList head_test = new LNode{ -1, nullptr };
    delete head_test;
    head_test = nullptr;
    LinkList head;
    ll_Init(head);
    Sleep(3000);
    std::cout << "Yes! you successfully created a new linklist with head: " << "[" << head->data << ", nullptr]!\n";
    std::cout << "Now you may insert some new nodes to it one by one!" << std::endl;
    std::string entry;
    char move;
    char style;
    std::cout << "Please tell me whether you want head insert or tail insert(H for head insert, T for tail insert): ";
    
    while (std::cin >> style) {
        if (style == 'H'|| style == 'T')
            break;
        else {
            std::cout << "Your input is not valid, please reenter(H for head insert, T for tail insert): ";
            std::cin >> style;
        }
    }
    unsigned count = 0;
    while (1) {
        std::cout << "What do you want to do?(I to insert, D to delete, V to visualize the list, other characters to quit): ";
        std::cin >> move;
        bool success;
        if (move != 'I' && move != 'D' && move != 'V')
            break;
        if (move == 'V')
            ll_traverse(head);
        while (move == 'I') {
            std::cout << "Enter the entry of node " << count << "(Enter any symbol not an integer to quit): ";
            std::cin >> entry;
            if (!isdigit(entry[0]))
                break;
            int value = atoi(entry.c_str());
            if (style == 'H')
                success = ll_headInsert(head, value);
            else {
                LNode* tail = head;
                while (tail->next != head)
                    tail = tail->next;
                success = ll_tailInsert(head, value, tail);
            }
            if (success) {
                char check;
                std::cout << "Node successfully inserted, visualize the list's sitrep?(T/other characters for F): ";
                std::cin >> check;
                if (check == 'T')
                    ll_traverse(head);
                count++;
            }
            else {
                std::cout << "Insertion failed! Something's wrong with the program!\n";
                break;
            }
        }
        while (move == 'D') {
            unsigned index;
            std::cout << "Please enter the index of the node you want to delete(-1 to quit): ";
            std::cin >> index;
            if (index == -1)
                break;
            success = ll_deleteNode(head, index, count);
            if (success) {
                std::cout << "Deletion succeeded!\n" << std::endl;
                break;
            }
            else {
                std::cout << "Deletion failed! Maybe your deletion choice is invalid!\n";
                std::cout << "Recovering from the failure..\n";
                Sleep(200);
                break;
            }
        }
    }
    std::cout << "Process terminated, deleting the ll created.." << std::endl;
    ll_deletion(head);
    Sleep(3000);
}

// This function is used to test the Compiler optimization option newly offered in C++11/C++17
void Testing_RVO() {
    // Don't mind the name, just for fun~
    Word movie{ "honkaistarrail" }; movie.print();
    Word song = movie.to_upper_case(); song.print();
    // Here as routine, you may expect the console to print three copy message, but it turns out that
    // only one copy is printed
    // This is the RVO (return value optimization)
    // The compiler checked the code segment of the source file
    // It notice that the temporary object returned by movie.to_upper_case() is directly copied into song
    // So there's no meaning creating an other temporary object to store x and return that temp one.
    // It will directly bing song(which is outside the function call of to_upper_case) to the x created within to_upper_case.
    // You could treat the operation as:
    // void to_upper_case(Word& song) const
    // {
    //      Word song(*this);
    //      for(char* p = song.str; *p != '\0'; p++)
    //          *p += 'A' - 'a';
    //      (No return)
    // }
    // Notice that RVO is optional is C++11, but compulsory in C++17
    // In C++11, one could turn off RVO by adding compile option -fno-elide-constructors after the g++ compile command
}