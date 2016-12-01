/* DateTime.h
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
class Date {
    //4, 2, and 2 digit integers for year, month, and day
    int yyyy;
    int mm;
    int dd;

public:
    Date(int = 1923, int = 1, int = 1); //default--yyyy mm dd.
    Date(const Date&); //copy.

    void setDate(int, int, int); //yyyy mm dd.
    void setDate(const Date&);
    
    int getYear() const {return yyyy;}
    int getMonth() const {return mm;}
    int getDay() const {return dd;}

    bool operator==(const Date&) const;
    bool operator!=(const Date&) const;
    bool operator<=(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>=(const Date&) const;
    bool operator>(const Date&) const;

    Date operator=(const Date&);

    friend std::istream& operator>>(std::istream &in, Date& d);
    friend std::ostream& operator<<(std::ostream &out, const Date& d);
};

class Time {
    int hh;   //2 digit integer for hour
    int mm;   //2 digit integer for minute

public:
    Time(int = 0, int = 0);
    
    void setTime(int, int);
 
    int getHour() const {return hh;}
    int getMinute() const {return mm;}

    Time operator=(const Time&);
    
    friend std::istream& operator>>(std::istream &in, Time &t);
    friend std::ostream& operator<<(std::ostream &os, const Time &t);
};

//process timer
class ProcessTimer
{
    clock_t timeStart; 
    clock_t timeEnd; 
    
public:
    ProcessTimer();
    ProcessTimer(clock_t);
    ~ProcessTimer();
    
    void setTimeStart(clock_t);
    void setTimeEnd(clock_t);

    clock_t getTimeStart();
    clock_t getTimeEnd();
    double getTimeElapsed();

    friend std::ostream& operator<<(std::ostream&, const ProcessTimer&);
}; 
