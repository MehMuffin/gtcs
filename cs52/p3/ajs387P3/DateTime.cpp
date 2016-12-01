/*  DateTime.cpp
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
#include "DateTime.h"

using std::cout;
using std::endl;

//Original source C++ Programming From Problem Analysis To Program Design, 5th Ed.
//by D.S. Malik, page 750-757

//Implementation file date

using std::istream;

Date::Date(int year, int month, int day) : yyyy(year), mm(month), dd(day) {} //default constr
Date::Date(const Date &d){setDate(d);} //copy constr

void Date::setDate(int year, int month, int day){ //set from vals
    yyyy = year;
    mm = month;
    dd = day;
}

void Date::setDate(const Date &d){ //set from another date
    yyyy = d.yyyy;
    mm = d.mm;
    dd = d.dd;
}

std::istream& operator>>(std::istream& in, Date& d){
    char c = '/';

    //extract year, delim, month, delim, and then day.
    in >> d.yyyy >> c
       >> d.mm >> c
       >> d.dd;
    return in;
}

std::ostream& operator<<(std::ostream &out, const Date &d){
    out << std::setfill('0');

    //insert each value appropriately padded and followed by '/'.
    out << std::setw(4) << d.yyyy << '/'
        << std::setw(2) << d.mm << '/'
        << std::setw(2) << d.dd
        << std::setfill(' ');
    return out;
}


//comparison operators
bool Date::operator==(const Date &rhs) const{
    if(yyyy==rhs.yyyy && mm==rhs.mm && dd==rhs.dd) return true;
    return false;
}

bool Date::operator!=(const Date &rhs) const{
    if(yyyy!=rhs.yyyy || mm!=rhs.mm || dd!=rhs.dd) return true;
    return false;
}
bool Date::operator<=(const Date &rhs) const{
    if(yyyy < rhs.yyyy) return true;
    if(yyyy == rhs.yyyy){
        if(mm < rhs.mm) return true;
        if(mm == rhs.mm){
            if(dd <= rhs.dd) return true; //day is only checked if both others are equal
        }
    }
    return false;
}
//the following relational operators are all minor alterations to the above.
bool Date::operator<(const Date &rhs) const{
    if(yyyy < rhs.yyyy) return true;
    if(yyyy == rhs.yyyy){
        if(mm < rhs.mm) return true;
        if(mm == rhs.mm){
            if(dd < rhs.dd) return true;
        }
    }
    return false;
}
bool Date::operator>=(const Date &rhs) const{
    if(yyyy > rhs.yyyy) return true;
    if(yyyy == rhs.yyyy){
        if(mm > rhs.mm) return true;
        if(mm == rhs.mm){
            if(dd >= rhs.dd) return true;
        }
    }
    return false;
}
bool Date::operator>(const Date &rhs) const{
    if(yyyy > rhs.yyyy) return true;
    if(yyyy == rhs.yyyy){
        if(mm > rhs.mm) return true;
        if(mm == rhs.mm){
            if(dd > rhs.dd) return true;
        }
    }
    return false;
}
Date Date::operator=(const Date &rhs){
    if(this != &rhs) setDate(rhs); //to avoid self assignment.
    return rhs;
}

//time imp code:
Time::Time(int hour, int minute) {

    setTime(hour, minute);

}

void Time::setTime(int hour, int minute) {
    hh = hour;
    mm = minute;
}

std::istream& operator>>(std::istream &in, Time &t) {
    char ch;
    in >> t.hh;
    in >> ch;
    in >> t.mm;
    return in;
}

std::ostream& operator<<(std::ostream &os, const Time &t) {
    os << std::setfill('0');

    os << std::setw(2) << t.hh << ":";
    os << std::setw(2) << t.mm;

    os << std::setfill(' ');

    return os;
}

Time Time::operator=(const Time &rhsObj) {
    if(this != &rhsObj) {
        hh = rhsObj.hh;
        mm = rhsObj.mm;
    }

    return rhsObj;
}
