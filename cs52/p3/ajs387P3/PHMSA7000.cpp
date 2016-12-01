/*  PHMSA7000.cpp
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
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "PHMSA7000.h"

using std::ostream;
using std::string;
using std::cout;
using std::endl;

HazMat7k::~HazMat7k() {}

//default constr does nothing.
HazMat7k::HazMat7k(){}

//conversion through member initialization list calling constructors of basic variables.
HazMat7k::HazMat7k(const HazMatData &d) :
    reportReceivedDate(d.report_received_date),
    reportNumber(d.report_number),
    supplementalNumber(d.supplemental_number),
    reportType(d.report_type),
    operatorID(d.operator_id),
    name(d.name),
    operatorStreetAddress(d.operator_street_address),
    operatorCityName(d.operator_city_name),
    operatorStateAbbreviation(d.operator_state_abbreviation),
    operatorPostalCode(d.operator_postal_code),
    localDate(d.local_date),
    localTime(d.local_time),
    commodityReleasedType(d.commodity_released_type),
    unintentionalReleaseBbls(d.unintentional_release_bbls),
    intentionalReleaseBbls(d.intentional_release_bbls),
    recoveredBbls(d.recovered_bbls),
    igniteInd(d.ignite_ind),
    explodeInd(d.explode_ind),
    preparedDate(d.prepared_date),
    authorizerName(d.authorizer_name),
    authorizerEmail(d.authorizer_email)
{}

//standard summary report for LossOrDamage.
void HazMat7k::summaryReport() const {
    cout << "Report Number and Date:        " << reportNumber + "  " << reportReceivedDate << endl
         << "Local Date and Time:           " << localDate << "  " << localTime << endl
         << "Barrels Unintentionally Released: " << unintentionalReleaseBbls << endl
         << "Barrels Intentionally Released: " << intentionalReleaseBbls << endl
         << "Barrels Recovered: " << recoveredBbls << endl
         << "Commodity Released Type: " << commodityReleasedType << endl
         << "Authorizer Email: " << authorizerEmail << endl << endl;
}

//overridden ostream prints out the basics on one line.
std::ostream& operator<<(std::ostream& out, const HazMat7k &rhs){
    out << "Report Number and Date: " << rhs.reportNumber + ' '
        << rhs.reportReceivedDate << "   "
        << "Local Date and Time: " << rhs.localDate << ' '
        << rhs.localTime << "   ";
}

//sad lil default constr.
LossOrDamage::LossOrDamage() {}

//LossOrDamage's convert constr simply passes the whole thing off to HazMat7k.
LossOrDamage::LossOrDamage(const HazMatData &d) : HazMat7k(d) {}

//sad lil default constr.
FatalityOrInjury::FatalityOrInjury() {}

//has a few more members to pass in the initialization list than LossOrDamage.
FatalityOrInjury::FatalityOrInjury(const HazMatData &d) : HazMat7k(d),
    fatal(d.fatal),
    injure(d.injure),
    narrative(d.narrative)
{}

//overridden summary report.
void FatalityOrInjury::summaryReport() const {
    cout << "Report Number and Date:        " << getReportNumber() + "  " << getReportReceivedDate() << endl
         << "Local Date and Time:           " << getLocalDate() << "  " << getLocalTime() << endl
         << "Number of Injuries:       " << injure << endl
         << "Number of Fatalities:     " << fatal << endl
         << "Narrative Length: " << narrative.length() << endl
         << "Narrative: " << narrative << endl << endl << endl;
}

//similarly overridden ostream prints a different set of everything on one line.
std::ostream& operator<<(std::ostream& out, const FatalityOrInjury &rhs){
    out << "Report Number and Date: " << rhs.getReportNumber() + ' '
        << rhs.getReportReceivedDate() << "   "
        << "Local Date and Time: " << rhs.getLocalDate() << ' ' << rhs.getLocalTime() << "   "
        << "Number of Injuries: " << rhs.injure << "   "
        << "Number of Fatalities: " << rhs.fatal << "   "
        << "Narrative Length: " << rhs.narrative.length() << "   "
        << "Narrative: " << rhs.narrative;
}
