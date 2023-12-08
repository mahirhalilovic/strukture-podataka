#include <iostream>
#include <exception>
#include <string>

#include "duration.hpp"

Duration::Duration() : hour{0}, min{0}, sec{0} {};

Duration::Duration(int s) : hour{0}, min{0}, sec{s} {

    if(sec >= 60) {

        min = sec / 60;
        sec = sec % 60;
        if(min >= 60) {

            hour = min / 60;
            min = min % 60;
        }
    }
}

Duration::Duration(int h, int m, int s) : hour{h}, min{m}, sec{s} {

    if(s >= 60 || m >= 60)
        throw std::out_of_range{"Unos izvan granica."};
}

Duration::Duration(std::string d) {

    std::string temp = d.substr(0, 2);
    hour = std::stoi(temp);
    temp = d.substr(3, 5);
    min = std::stoi(temp);
    temp = d.substr(6, 8);
    sec = std::stoi(temp);
}

Duration& Duration::set_s(int s) { 

    if(s >= 0 && s < 60)
        sec = s;
    else
        throw std::out_of_range("Unos izvan granica.");

    return *this;
    }
const int Duration::get_s() { return sec; }

Duration& Duration::set_m(int m) {

    if(m >= 0 && m < 60)
        min = m;
    else
        throw std::out_of_range("Unos izvan granica.");

    return *this;
}
const int Duration::get_m() { return min; }

Duration& Duration::set_h(int h) { 
    
  if(h >= 0)
    hour = h;
  else
    throw std::out_of_range("Unos izvan granica.");

  return *this;
}
const int Duration::get_h() { return hour; }

bool Duration::operator==(Duration& dur) {

    if(hour == dur.hour && min == dur.min && sec == dur.sec)
        return true;
    else
        return false;
}

bool Duration::operator!=(Duration& dur) {

    if(hour != dur.hour || min != dur.min || sec != dur.sec)
        return true;
    else
        return false;
}

bool Duration::operator>(Duration& dur) {

    if(hour > dur.hour)
        return true;
    else if(hour < dur.hour)
        return false;
    else if(min > dur.min)
        return true;
    else if(min < dur.min)
        return false;
    else if(sec > dur.sec)
            return true;
        else
            return false;
}

bool Duration::operator<(Duration& dur) {

    if(hour < dur.hour)
        return true;
    else if(hour > dur.hour)
        return false;
    else if(min < dur.min)
        return true;
    else if(min > dur.min)
        return false;
    else if(sec < dur.sec)
        return true;
    else
        return false;
}

bool Duration::operator>=(Duration& dur) {

    if(hour > dur.hour)
        return true;
    else if(hour < dur.hour)
        return false;
    else if(min > dur.min)
        return true;
    else if(min < dur.min)
        return false;
    else if(sec >= dur.sec)
        return true;
    else
        return false;
}

bool Duration::operator<=(Duration& dur) {

    if(hour <= dur.hour)
        return true;
    else if(hour > dur.hour)
        return false;
    else if(min <= dur.min)
        return true;
    else if(min > dur.min)
        return false;
    else if(sec <= dur.sec)
        return true;
    else
        return false;
}

Duration::operator bool() const {
    
    if(hour != 0 || min != 0 || sec != 0)
        return true;
    else
        return false;
}
bool Duration::operator!() const {

    if(hour != 0 || min != 0 || sec != 0)
        return false;
    else
        return true;
}

Duration& Duration::operator+=(Duration& dur) {

    this->sec += dur.sec;
    this->min += dur.min;
    this->hour += dur.hour;

    if(this->sec >= 60) {

        this->min += this->sec / 60;
        this->sec = this->sec % 60;
    }

    if(this->min >= 60) {

        this->hour += this->min / 60;
        this->min = this->min % 60;
    }

    return *this;
}

Duration Duration::operator+(Duration& dur) {

    Duration d{*this};

    d.sec += dur.sec;
    d.min += dur.min;
    d.hour += dur.hour;

    if(d.sec >= 60) {

        d.min += d.sec / 60;
        d.sec = d.sec % 60;
    }

    if(d.min >= 60) {

        d.hour += d.min / 60;
        d.min = d.min % 60;
    }

    return d;
}

Duration Duration::operator-(Duration& dur) {

  int secs = this->hour * 3600 + this->min * 60 + this->sec;
  int secs2 = dur.hour * 3600 + dur.min * 60 + dur.sec;

  if(secs < secs2)
    throw std::out_of_range("Rezultat ne moze biti negativan.");
  
  int s = secs - secs2;

  int h = s / 3600;
  s %= 3600;
  int m = s / 60;
  s %= 60;

  return Duration(h, m, s);
}

Duration& Duration::operator-=(Duration& dur) {

  int secs = this->hour * 3600 + this->min * 60 + this->sec;
  int secs2 = dur.hour * 3600 + dur.min * 60 + dur.sec;

  if(secs < secs2)
    throw std::out_of_range("Rezultat ne moze biti negativan.");

  this->sec = secs - secs2;

  this->hour = this->sec / 3600;
  this->sec %= 3600;
  this->min = this->sec / 60;
  this->sec %= 60;

  return *this;
}

Duration& Duration::operator*=(int s) {

    sec *= s;
    min *= s;
    hour *= s;

    if(sec >= 60) {

        min += sec / 60;
        sec %= 60;
    }

    if(min >= 60) {

        hour += min / 60;
        min %= 60;
    }

    return *this;
}

Duration& Duration::operator*(int s) {

    sec *= s;
    min *= s;
    hour *= s;

    if(sec >= 60) {

        min += sec / 60;
        sec %= 60;
    }

    if(min >= 60) {

        hour += min / 60;
        min %= 60;
    }

    return *this;
}

Duration& Duration::operator/=(int s) {

    if(hour % s != 0)
        min += (s - 1) * 60;
        hour /= s;

    if(min & s != 0)
        sec += (s - 1) * 60;
        min /= s;
        sec /= s;

    return *this;
}

Duration& Duration::operator/(int s) {

    if(hour % s != 0)
        min += (s - 1) * 60;
        hour /= s;

    if(min & s != 0)
        sec += (s - 1) * 60;
        min /= s;
        sec /= s;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Duration& dur) {

    if(dur.hour < 10)
        out << "0" << dur.hour;
    else
        out << dur.hour;
    if(dur.min < 10)
        out << ":0" << dur.min;
    else
        out << ":" << dur.min;
    if(dur.sec < 10)
        out << ":0" << dur.sec;
    else
        out << ":" << dur.sec;
    return out;
}

std::istream& operator>>(std::istream& in, Duration& dur) {

    std::string temph, tempm, temps;
    std::getline(in, temph, ':');
    std::getline(in, tempm, ':');
    std::getline(in, temps);

    dur.hour = std::stoi(temph);
    dur.min = std::stoi(tempm);
    dur.sec = std::stoi(temps);

    return in;
}
