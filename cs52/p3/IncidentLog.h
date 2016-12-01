/*  IncidentLog.h
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
#include <string>
#include <vector>
#include "PHMSA7000.h"
#include "LL.h"

using std::cout;
using std::endl;

//has two vector members, one for each report type.
class IncidentLog {
    LL<FatalityOrInjury> llFatalityOrInjury;
    LL<LossOrDamage> llLossOrDamage;

public:
    //sad lil constructor and destructor.
    IncidentLog();
    ~IncidentLog();

    //displays all reports in the Log.
    void displayReport() const;

    //appending additional reports.
    void appendObject(const FatalityOrInjury&);
    void appendObject(const LossOrDamage&);

    //return sizes of appropriate vectors.
    unsigned long sizeFatalityOrInjury() const;
    unsigned long sizeLossOrDamage() const;
};
