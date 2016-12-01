/*  LL.h
 *  COSC 052 Fall 2016
 *  Project #5
 *
 *  Due on: DEC 1, 2016
 *  Author: Andrew Sedlack
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.*/
#include <exception>
#include <stdexcept>
#include <cstddef>
#include <iostream>

const int LOOP_OUTPUT_FREQUENCY = 5000;
const int SORT_OUTPUT_FREQUENCY = 750;


using std::cout;
using std::endl;

//DECLARATION

//Node template
template<typename T>
class Node {
public:
    T info;
    Node<T>* next;

    Node(T = T(), Node<T>* = NULL);
    //defaults to default info and null pointer
};

//iterator
template<typename T>
class LL_iterator {
    Node<T>* current;

public:
    LL_iterator(){current=NULL;}
    LL_iterator(Node<T> *ptr){current=ptr;}
    
    T& operator*(){return current->info;}
    LL_iterator operator++(int){current=current->next;}

    bool operator==(const LL_iterator& rhsObj) const{return current==rhsObj.current;}
    bool operator!=(const LL_iterator& rhsObj) const{return current!=rhsObj.current;}
};

//linked list template
template<typename T>
class LL {
    unsigned long count; //stores number of items
    Node<T>* head; //the start of the list

    void copyList(const LL<T> &ListToCopy); //deep copy fn

public:
    LL(); //default constr
    ~LL() {this->clear();} // destructor. all dynamically allocated memory is already cleared by clear().

    LL(const LL<T> &otherLL); //copy constr

    LL<T> & operator=(const LL<T> &rhsObj); //assignment op

    //adding and removing objects
    void push_back(T);
    void insert(T);
    void pop_back();
    void clear();

    //searching n sorting
    void bubbleSort();
    void bubbleSortI();
    void selectionSort();

    int linearSearch(T);
    int binarySearch(T);
    
    //iteration
    LL_iterator<T> begin() const {return LL_iterator<T>(head);}
    LL_iterator<T> end() const;

    //accessing info
    unsigned long size() const {return count;}
    T& at(int ndx) const;
    
    void dummy();
    //overloaded << operator for console output
    template<class U>
    friend std::ostream& operator<<(std::ostream& os, const LL<U>& rhsObj);
};

//IMPLEMENTATION

//node constr
template<typename T>
Node<T>::Node(T _info, Node<T>* _next) {
    info = _info;
    next = _next;
} //in lieu of values these will be set to defaults

//LL.copyList
template<typename T>
void LL<T>::copyList(const LL<T> &ListToCopy) {
    try {for(int i = 0; i < ListToCopy.size(); i++) this->push_back(ListToCopy.at(i));}
    catch (std::bad_alloc err) { //should the memory run out...
        std::cout << "Error in copyList: ";
        throw;
    }
}

//LL constr
template<typename T>
LL<T>::LL() {
    head = NULL;
    count = 0;
} //an empty list with no dynamic memory allocated, yet.

//LL copyconstr
template<typename T>
LL<T>::LL(const LL<T> &otherLL) {
    head = NULL;
    count = 0;
    copyList(otherLL); //uses copylist fn to avoid code duplication
}

//overloaded assignment
template<typename T>
LL<T> & LL<T>::operator=(const LL<T> &rhsObj) {
    if(this != &rhsObj) {     
        clear();
        copyList(rhsObj); //ditto
        return *this;
    }
}


//LL.push_back
template<typename T>
void LL<T>::push_back(T add) {
    try {
        if(!head) head = new Node<T>(add);
        else {
            Node<T>* curr = head;
            while(curr->next) curr = curr->next; //all list iteration is done via
            curr->next = new Node<T>(add);       //loops rather than recursion
        }
        count++;
    }
    catch (std::bad_alloc err){ //should memory run out
        std::cout << "Error in push_back: ";
        throw;
    }
}

//LL.insert
template<typename T>
void LL<T>::insert(T ins) {
    try {
        //first, if the list is empty
        if(!head) {
            head = new Node<T>(ins);
            count++; //as push_back is used below all of these ifs require unique count++'s
        }
        //if the inserted item is smaller than the head
        else if(ins < head->info) {
            Node<T>* tmp = head;
            head = new Node<T>(ins);
            head->next = tmp;
            count++;
        }
        //if the inserted item belongs at the end of the list
        //this is inefficient and probably unnecessary but was done as part of
        //the workarounds required to get all this mess to work and I'm not gonna
        //mess with it now
        else if(ins >= this->at(this->size()-1)) this->push_back(ins);
        //if the inserted item belongs anywhere in the middle
        else {
            Node<T>* curr = head;
            while(curr->next && ins >= curr->next->info) curr = curr->next;
            Node<T>* tmp = curr->next;
            curr->next = new Node<T>(ins);
            curr->next->next = tmp;
            count++;
        }
    }
    catch(std::bad_alloc err){ //should memory run out
        std::cout << "Error in insert: ";
        throw;
    }
}

//LL.pop_back
template<typename T>
void LL<T>::pop_back() {
    if(head) { //does nothing if the list only has one item
        Node<T>* curr = head;
        while(curr->next->next) curr = curr->next;
        delete curr->next;
        curr->next = NULL; //remove the dangling pointer
        count--; //decrement count with the removal of an item
    }
}

//LL.clear
template<typename T>
void LL<T>::clear() {
    while(head) {//erases the entire list
        Node<T>* prev = head;
        head = head->next; //pretty simple: it saves the current item, moves to the next,
        delete prev;       //and repeats.
    }
    count = 0; //if the whole list has been deleted...
}

//bubblesort
template<typename T>
void LL<T>::bubbleSort() {
    long s = size();
    T tmp;
    int swapn = 0; //counting swaps
    //ordinary bubble sort algorithm
    for(int i = 0; i < s; i++) {
        for(int j = 0; j < s; j++) {
            if(at(i) < at(j)) {
                tmp = at(i);
                at(i) = at(j);
                at(j) = tmp;
                swapn++;
            }
        }
    }
    std::cout << "bubbleSort Complete, " << swapn << " total swaps.\n"; 
}

//bubblesortI
template<typename T>
void LL<T>::bubbleSortI() {
    int swapn = 0; //counting swaps
    LL_iterator<T> e = end();
    T tmp;
    //same thing, but using the iterators instead, for efficiency's sake
    for(LL_iterator<T> i = begin(); i != e; i++) {
        for(LL_iterator<T> j = begin(); j != e; j++) {
            if(*i < *j) {
                tmp = *i;
                *i = *j;
                *j = tmp;
                swapn++;
            }
        }
    }
    std::cout << "bubbleSortI Complete, " << swapn << " total swaps.\n"; 
}

//selectionsort
template<typename T>
void LL<T>::selectionSort() {
    int low = 0, s = size(), swapn = 0;
    T t1, t2; 
    //ordinary selection sort algorithm
    for(int i = 0; i < s-1; i++) {
        t2 = at(low); 
        for(int j = i+1; j < s; j++) if(at(j) < at(low)) low = j;
        t1 = at(i);
        at(i) = at(low);
        at(low) = t1;
        swapn++;
    }
    std::cout << "Selection sort Complete, " << swapn << " total swaps.\n"; 
}

//linearysearch
template<typename T>
int LL<T>::linearSearch(T val) { 
    int ndx = 0, s = size()-1;
    for(LL_iterator<T> i = begin(); ndx < s && *i != val; i++,ndx++);//traverses list to the end
    return (ndx == s ? -1 : ndx);//or till the value is found, returns -1 if not in list
}

//binarysearch
template<typename T>
int LL<T>::binarySearch(T val) {
    Node<T>* first = head, *last = head, *l, *mid;
    int ndx;
    while(last->next) last = last->next; //set last to the actual last node
    //for(int i = 0; i < size(); i++) last = last->next; 
    l = last; //save the last node for later
    do {
        if(first == NULL) mid = NULL;
        else { //otherwise, find the center of the linked list by moving two pointers through it
            Node<T>* slow = first, *fast = first->next;
            while(fast != last) { //fast moves two nodes for each node traversed by slow
                fast = fast->next; //and so when fast reaches the end, slow is at the center
                if(fast && fast != last) {
                    fast = fast->next;
                    slow = slow->next;
                }
            }
            mid = slow;
        }
        if(mid == NULL) return -1; //if it's not in the list.
        if(mid->info == val) { //if this is it, count how far to the end of the list and then 
            for(ndx = size()-1; mid != l; ndx--, mid = mid->next); //subtract to find the index
            return ndx; //and return it
        } //otherwise change the appropriate endpoint to the center and try again
        if(mid->info < val) {
            first = mid->next;
        }
        else {
            last = mid;
        }
    } while(last == NULL || last != first);
    return -1; //should only get here if the value isn't in the list
}

/*returns the center of two given iterators, hopefully on the same list.
template<typename T>
Node<T>* LL<T>::middle(Node<T>* first, Node<T>* last) const {
    if(first == NULL) return NULL; //if the list is empty 
    Node<T>* slow = first; //fast moves twice as fast as slow and hence once fast
    Node<T>* fast = first->next; //reaches last slow will be halfway there
    while(fast != last) {
        fast=fast->next; 
        if(fast != last && fast) {
            fast=fast->next;
            slow=slow->next;
        }
    }
    return slow;
}*/

//iterator
template<typename T>
LL_iterator<T> LL<T>::end() const {
    Node<T>* curr = head;
    for(int i = 0; i < size(); i++) curr = curr->next;
    return LL_iterator<T>(curr);
}

//LL.at
template<typename T>
T& LL<T>::at(int ndx) const {
    try{
        if(ndx >= size()) throw std::out_of_range("Index Out of Range Exception");
        //the above is in case an invalid number is somehow passed. this shouldn't be possible
        //unless a user or program fails to check against size() before calling at
        int i = 0;
        Node<T>* curr = head;
        while(curr->next && i < ndx) {
            i++;
            curr = curr->next;
        }
        return curr->info;
    }
    catch(std::out_of_range err) { //if the index requested was too big
        std::cout << "Error in at: ";
        throw;
    }
}

template<typename T>
void LL<T>::dummy() { //so I can print from gdb
    std::cout << this;
}

//LL ostream<<
template<typename T>
std::ostream& operator<<(std::ostream& os, const LL<T>& rhsObj) {
    Node<T>* curr = rhsObj.head;
    while(curr) { //needs to be curr and not curr->next to ensure that the last itm is printed,
                  //I learned after two hours of debugging...
        os << curr->info << std::endl;
        curr = curr->next;
    }
    return os; //send the stream on out to be free
}

