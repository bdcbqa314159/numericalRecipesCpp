//
//  date.h
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 19/05/2021.
//

#ifndef date_h
#define date_h

#include <iostream>

class date {
    
private:
    int year_;
    int month_;
    int day_;
    
public:
    date();
    date(const int& d, const int& m, const int& y);
    date operator=(const date& d);
    ~date();
    
    
    bool valid() const;
    
    int day() const;
    int month() const;
    int year() const;
    
    void set_day(const int& d);
    void set_month(const int& m);
    void set_year(const int& y);
    void iso();
    
    date operator++();
    date operator++(int);
    date operator--();
    date operator--(int);
    
};


date next_date(const date& d);
date previous_date(const date& d);


std::ostream &operator<<(std::ostream &os, const date& d);
bool operator == (const date& d1, const date& d2);
bool operator != (const date& d1, const date& d2);
bool operator < (const date& d1, const date& d2);
bool operator > (const date& d1, const date& d2);
bool operator <= (const date& d1, const date& d2);
bool operator >= (const date& d1, const date& d2);


int testDates();

#endif /* date_h */
