/*  IncidentLog.cpp
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
#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#include <vector>
#include "IncidentLog.h"

using std::cout;
using std::out_of_range;

//constructor and destructor.
IncidentLog::IncidentLog() {}
IncidentLog::~IncidentLog() {}

//prints all the reports.
void IncidentLog::displayReport() const {
    try{
        //prints each element of the vector.
        cout << endl << "FORM PHMSA F 7000-1 Accident Report - Hazardous Liquid Pipeline Systems ("
             << sizeFatalityOrInjury() << ") records with a fatality or injury:" << endl;

        for(int i = 0; i < sizeFatalityOrInjury(); i++) llFatalityOrInjury.at(i).summaryReport();

        cout << endl << "FORM PHMSA F 7000-1 Accident Report - Hazardous Liquid Pipeline Systems ("
             << sizeLossOrDamage() << ") records with only material loss or damage:" << endl;

        for(int i = 0; i < sizeLossOrDamage(); i++) llLossOrDamage.at(i).summaryReport();

    }
    //should something unexpected happen.
    catch (out_of_range oorErr) {
        cout << oorErr.what();
        throw;
    }
}

//adds a new object to each vector, as appropriate.
//new records are inserted rather than pushed so that the list automatically sorts them
//as they are entered.
void IncidentLog::appendObject(const LossOrDamage &a) {llLossOrDamage.insert(a);}
void IncidentLog::appendObject(const FatalityOrInjury &a) {llFatalityOrInjury.insert(a);}
//returns the size of each vector.
unsigned long IncidentLog::sizeLossOrDamage() const {return llLossOrDamage.size();}
unsigned long IncidentLog::sizeFatalityOrInjury() const {return llFatalityOrInjury.size();}
