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