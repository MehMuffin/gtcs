/*  LL.h
 *  COSC 052 Fall 2016
 *  Project #3
 *
 *  Due on: NOV 1, 2016
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
 *  or any code taken from the class textbooks.
 */
#include <exception>
#include <stdexcept>
#include <cstddef>
#include <iostream>

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

//linked list template
template<typename T>
class LL {
    unsigned long count; //stores number of items
    Node<T>* head; //the start of the list

    void copyList(const LL<T> &ListToCopy); //deep copy fn

public:
    LL(); //default constr
    ~LL() {this->clear();} //destructor. all dynamically allocated memory is already 
    			   //cleared by clear().


    LL(const LL<T> &otherLL); //copy constr

    LL<T> & operator=(const LL<T> &rhsObj); //assignment op

    //adding and removing objects
    void push_back(T);
    void insert(T);
    void pop_back();
    void clear();

    //accessing info
    unsigned long size() const {return count;}
    T & at(int ndx) const;

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
    copylist(rhsObj); //ditto
    return *this;
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

//LL.at
template<typename T>
T& LL<T>::at(int ndx) const {
    try{
        if(ndx >= this->size()) throw std::out_of_range("Index Out of Range Exception");
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
