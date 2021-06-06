//
//  date.cpp
//  financialNumericalRecipes
//
//  Created by Bernardo Cohen on 19/05/2021.
//

#include "date.h"

date::date()
: year_(0), month_(0), day_(0){
    
}

date::date(const int & d, const int & m, const int & y)
: year_(y), month_(m), day_(d){
    
}

date::~date(){
    
}

date date::operator=(const date& d){
    
    if (this != &d){
        day_ = d.day_;
        month_ = d.month_;
        year_ = d.year_;
    }
    
    return *this;
    
}

void date::iso(){
    
    std::cout<<year_<<"-"<<month_<<"-"<<day_<<std::endl;
}



int date::day() const {return day_;};
int date::month() const {return month_;};
int date::year() const {return year_;};

void date::set_day(const int &d){
    day_ = d;
}

void date::set_month(const int &m){
    month_ = m;
}

void date::set_year(const int &y){
    year_ = y;
}

bool date::valid() const{
    
    if(year_<0) return false;
    
    if(month_>12 || month_<1) return false;
    
    if(day_>31 || day_<1) return false;
    
    if((day_==31) && (month_== 2 || month_== 4 || month_== 6 || month_== 9 ||month_== 11)) return false;
    
    if(day_ == 30 && month_ == 2) return false;
    
    return true;
}

bool operator ==(const date& d1, const date& d2){
    
    if (!(d1.valid() && d2.valid())) return false;
    
    return ((d1.day() == d2.day()) && (d1.month() == d2.month()) && (d1.year() == d2.year()));
    
}

bool operator < (const date& d1, const date& d2){
    
    if (!(d1.valid() && d2.valid())) return false;
    
    if(d1.year() == d2.year()){
        if(d1.month() == d2.month())
            return (d1.day()<d2.day());
        else
            return (d1.month()<d2.month());
    }
    
    else
        return (d1.year()<d2.year());
    
}

bool operator <= (const date& d1, const date& d2){
    if (d1 == d2) return true;
    
    return (d1<d2);
}

bool operator >= (const date& d1, const date& d2){
    if (d1 == d2) return true;
    
    return (d1>d2);
}

bool operator > (const date& d1, const date& d2){
    
    return !(d1<=d2);
}

bool operator != (const date& d1, const date& d2){
    
    return !(d1==d2);
}

date next_date(const date& d){
    
    if (!d.valid()) return date();
    
    date ndat= date(d.day()+1, d.month(), d.year());
    if (ndat.valid()) return ndat;
    
    ndat = date(1, d.month(), d.year());
    if (ndat.valid()) return ndat;
    
    ndat = date(1, 1,d.year()+1);
    return ndat;

}

date previous_date(const date& d){
    
    if (!d.valid()) return date();
    
    date pdat= date(d.day()-1, d.month(), d.year());
    if (pdat.valid()) return pdat;
    
    pdat = date(31, d.month()-1, d.year());
    if (pdat.valid()) return pdat;
    
    pdat = date(31, d.month()-1, d.year());
    if (pdat.valid()) return pdat;
    
    pdat = date(29, d.month()-1, d.year());
    if (pdat.valid()) return pdat;
    
    pdat = date(28, d.month()-1, d.year());
    if (pdat.valid()) return pdat;
    
    pdat = date(31, 12, d.year()-1);
    return pdat;
    
}

date date::operator++(int){
    date d = *this;
    *this = next_date(d);
    return d;
}

date date::operator++(){
    *this = next_date(*this);
    return *this;
}

date date::operator--(int){
    date d = *this;
    *this = previous_date(d);
    return d;
}

date date::operator--(){
    *this = previous_date(*this);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const date& d){
    
    os<<d.year()<<"-"<<d.month()<<"-"<<d.day();
    return os;
}


int testDates(){
    
    std::cout<<std::boolalpha;
    
    date d(1,12,2001);
    std::cout<<"Is valid??"<<std::endl;
    std::cout<<d.valid()<<std::endl;
    d.iso();
    
    d++;
    ++d;
    
    d.iso();
    
    --d;
    d--;
    d--;
    
    d.iso();
    
    std::cout<<"Date : "<<std::endl;
    std::cout<<d<<std::endl;
    
    return 0;
}
