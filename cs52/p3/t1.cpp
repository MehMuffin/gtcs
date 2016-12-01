/****** Put this test code in function main() REPLACE all previous test code ******/

/* BEGIN: Milestone 3 component testing of LL<T> class */
#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//prototype.

int main (int argc, char* argv[]){
    vector<int> stupidvector;

    stupidvector.push_back(23);
    stupidvector.push_back(23);
    stupidvector.push_back(45);
    stupidvector.push_back(23);


    cout << stupidvector[2];

    return 0;


    }
    /* END: Milestone 3 component testing of LL<T> class */
