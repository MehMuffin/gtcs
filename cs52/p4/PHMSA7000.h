/*  PHMSA7000.h
 *  COSC 052 Fall 2016
 *  Project #4
 *
 *  Due on: NOV 17, 2016
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
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DateTime.h"

using std::string;

//full strut is 4472 bytes long.
struct HazMatData
{
    Date report_received_date;
    char report_number[10+1];
    char supplemental_number[7+1];
    char report_type[20+1];
    char operator_id[7+1];
    char name[55+1];
    char operator_street_address[57+1];
    char operator_city_name[18+1];
    char operator_state_abbreviation[4+1];
    char operator_postal_code[12+1];
    Date local_date;
    Time local_time;
    char commodity_released_type[84+1];
    double unintentional_release_bbls;
    double intentional_release_bbls;
    double recovered_bbls;
    int fatal;
    int injure;
    char ignite_ind[5+1];
    char explode_ind[5+1];
    Date prepared_date;
    char authorizer_name[45+1];
    char authorizer_email[42+1];
    char narrative[4000+1];
};

class HazMat7k {

    Date reportReceivedDate;
    string reportNumber;
    string supplementalNumber;
    string reportType;
    string operatorID;
    string name;
    string operatorStreetAddress;
    string operatorCityName;
    string operatorStateAbbreviation;
    string operatorPostalCode;
    Date localDate;
    Time localTime;
    string commodityReleasedType;
    double unintentionalReleaseBbls;
    double intentionalReleaseBbls;
    double recoveredBbls;
    string igniteInd;
    string explodeInd;
    Date preparedDate;
    string authorizerName;
    string authorizerEmail;
    char incidentCode;

public:
    ~HazMat7k();
    HazMat7k();//default constr.
    HazMat7k(const HazMatData&);

    virtual void summaryReport() const;

    //accessors.
    Date getReportReceivedDate () const {return reportReceivedDate;}
    string getReportNumber () const {return reportNumber;}
    string getSupplementalNumber () const {return supplementalNumber;}
    string getReportType () const {return reportType;}
    string getOperatorID () const {return operatorID;}
    string getName () const {return name;}
    string getOperatorStreetAddress () const {return operatorStreetAddress;}
    string getOperatorCityName () const {return operatorCityName;}
    string getOperatorStateAbbreviation () const {return operatorStateAbbreviation;}
    string getOperatorPostalCode () const {return operatorPostalCode;}
    Date getLocalDate () const {return localDate;}
    Time getLocalTime () const {return localTime;}
    string getCommodityReleasedType () const {return commodityReleasedType;}
    double getUnintentionalReleaseBbls () const {return unintentionalReleaseBbls;}
    double getIntentionalReleaseBbls () const {return intentionalReleaseBbls;}
    double getRecoveredBbls () const {return recoveredBbls;}
    string getIgniteInd () const {return igniteInd;}
    string getExplodeInd () const {return explodeInd;}
    Date getPreparedDate () const {return preparedDate;}
    string getAuthorizerName () const {return authorizerName;}
    string getAuthorizerEmail () const {return authorizerEmail;}
    char getIncidentCode() const {return incidentCode;}

    //mutators.
    void setReportReceivedDate (Date val) {reportReceivedDate=val;}
    void setReportNumber (string val) {reportNumber=val;}
    void setSupplementalNumber (string val) {supplementalNumber=val;}
    void setReportType (string val) {reportType=val;}
    void setOperatorID (string val) {operatorID=val;}
    void setName (string val) {name=val;}
    void setOperatorStreetAddress (string val) {operatorStreetAddress=val;}
    void setOperatorCityName (string val) {operatorCityName=val;}
    void setOperatorStateAbbreviation (string val) {operatorStateAbbreviation=val;}
    void setOperatorPostalCode (string val) {operatorPostalCode=val;}
    void setLocalDate (Date val) {localDate=val;}
    void setLocalTime (Time val) {localTime=val;}
    void setCommodityReleasedType (string val) {commodityReleasedType=val;}
    void setUnintentionalReleaseBbls (double val) {unintentionalReleaseBbls=val;}
    void setIntentionalReleaseBbls (double val) {intentionalReleaseBbls=val;}
    void setRecoveredBbls (double val) {recoveredBbls=val;}
    void setIgniteInd (string val) {igniteInd=val;}
    void setExplodeInd (string val) {explodeInd=val;}
    void setPreparedDate (Date val) {preparedDate=val;}
    void setAuthorizerName (string val) {authorizerName=val;}
    void setAuthorizerEmail (string val) {authorizerEmail=val;}
    void setIncidentCode (char val) {incidentCode=val;}

    //stream insertion
    friend std::ostream& operator<<(std::ostream&, const HazMat7k&);

    //comparison
    bool operator==(const HazMat7k &h) {return reportNumber==h.reportNumber;}
    bool operator!=(const HazMat7k &h) {return reportNumber!=h.reportNumber;}
    bool operator<(const HazMat7k &h) {return reportNumber<h.reportNumber;}
    bool operator>=(const HazMat7k &h) {return reportNumber>=h.reportNumber;}

};

class LossOrDamage : public HazMat7k {
public:
    LossOrDamage();//default constr
    LossOrDamage(const HazMatData&);//convert constr
};

class FatalityOrInjury : public HazMat7k {
    int fatal;
    int injure;
    string narrative;

public:
    FatalityOrInjury();//default constr
    FatalityOrInjury(const HazMatData&);//convert constr

    //these two are overridden for FatalityOrInjury.
    void summaryReport() const;
    friend std::ostream& operator<<(std::ostream&, const FatalityOrInjury&);

    //new accessors.
    int getFatal () const {return fatal;}
    int getInjure () const {return injure;}
    string getNarrative () const {return narrative;}

    //new mutators.
    void setFatal (int val) {fatal=val;}
    void setInjure (int val) {injure=val;}
    void setNarrative (string val) {narrative=val;}
};
