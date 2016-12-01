/* ajs387P4.cpp
*  COSC 052 Fall 2016
*  Project #4444*  Due on: NOV 17, 2016
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
#include <fstream>
#include <iostream>
#include "IncidentLog.h"
#define REPORT_SIZE 4472 //size of a full struct.

using namespace std;

//prototype.
void loadData(string, char, IncidentLog &);

int main (int argc, char* argv[]){
    IncidentLog l;
    try{
        //check that the appropriate arguments have been provided.
        //error descriptions are provided to the constructors of appropriate error classes.
        if(argc != 3) throw invalid_argument
            ("Invalid Argument Exception: Argument Number Exception\n");
        if((char)(*argv[2])!='b') throw invalid_argument
            ("Invalid Argument Exception: Filetype Exception\n");

        //and then load and print.
        loadData(argv[1], *argv[2], l);
        l.displayReport();
    }
    //error handling. all functions that throw should report who it is that's throwing
    catch (bad_alloc err) {cout << err.what();}
    catch (invalid_argument err) {cout << err.what();}
    catch (out_of_range err) {cout << err.what();}
    catch (string err) {cout << err << endl;}
    catch (...) {cout << "Unexpected Exception" << endl;} //should never be needed.
    return 0;
}

void loadData (string path, char type, IncidentLog &l){
    //a struct to load into.
    HazMatData* raw = new HazMatData;
    HazMat7k* data; 

    try{
        fstream file(path.c_str(), ios::in | ios::binary);
        if(file.fail()) throw string("File Read Exception: File Opening Failure");

        //initial read necessary to intialize first set of input as reading
        //is done at the end of the loop.
        file.read(reinterpret_cast<char *>(raw), REPORT_SIZE);
        while(!file.eof()){ //loop until the pointer reaches the end of the file.
            //load each report into the appropriate sort of object.
            if(raw->fatal == 0 && raw->injure == 0) data = new LossOrDamage(*raw);
            else data = new FatalityOrInjury(*raw);

            l.appendObject(data);
            
            file.read(reinterpret_cast<char *>(raw), REPORT_SIZE);
        }   //the file is read from here and prior to the loop because if read at the start of the
            //loop instead the pointer will be moved to the eof immediately before reading data
            //and the last report will be loaded twice.
        file.close(); //cleaning up.
        delete[] raw;
    }
    //should the file not open properly
    catch (string err){
        cout << "Error in loadData: ";
        throw;
    }
}
