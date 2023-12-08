#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <string.h>
#include <cmath>

int gcd(int numerator, int denominator) {

    numerator = abs(numerator);
    denominator = abs(denominator);

    int shift;

    for (shift = 0; ((numerator | denominator) & 1) == 0; ++shift) {
        numerator >>= 1;
        denominator >>= 1;
      }

    while ((numerator & 1) == 0) {
        numerator >>= 1;
      }

    while (denominator != 0) {

        while ((denominator & 1) == 0) {
            denominator >>= 1;
          }

        if (numerator > denominator) {
            std::swap(numerator, denominator);
          }

        denominator -= numerator;
      }

    return numerator << shift;
}

Rational::Rational() : numerator_{0}, denominator_{1} {}

Rational::Rational(int numerator, int denominator) {

    if(denominator == 0)
        throw std::invalid_argument{"Nazivnik ne moze biti nula!"};
    else {

        numerator_ = numerator;
        denominator_ = denominator;

        if(denominator_ < 0) {
          
          numerator_ *= -1;
          denominator_ *= -1;
        }

        int gc = gcd(numerator_, denominator_);
        numerator_ /= gc;
        denominator_ /= gc;
    }
}

Rational::Rational(const char* rational) {

    std::string rat{rational};

    bool control{true};
    std::string num, den;

    for(int i = 0; i < rat.length(); i++) {

        if(rational[i] == '/') {

            num = rat.substr(0, i);
            den = rat.substr(i + 1, rat.length());

            for(int i = 0; i < num.length(); i++)
                if(!isdigit(num[i])) {

                    control = false;
                    break;
                }

            for(int i = 0; i < den.length(); i++)
                if(!isdigit(den[i])) {

                    control = false;
                    break;
                }
        }
    }

    if(control) {

        Rational(std::stoi(num), std::stoi(den));
    } else
        throw std::invalid_argument{"Nevalidan unos."};
}
  
Rational::Rational(const std::string& rational) {

    bool control{true};
    std::string num, den;

    for(int i = 0; i < rational.length(); i++) {

        if(rational[i] == '/') {

            num = rational.substr(0, i);
            den = rational.substr(i + 1, rational.length());

            for(int i = 0; i < num.length(); i++)
                if(!isdigit(num[i])) {

                    control = false;
                    break;
                }

            for(int i = 0; i < den.length(); i++)
                if(!isdigit(den[i])) {

                    control = false;
                    break;
                }
        }
    }
  
    if(control) {

        Rational(std::stoi(num), std::stoi(den));
    } else
        throw std::invalid_argument{"Nevalidan unos."};
}

Rational::Rational(const Rational& rational) {

    numerator_ = rational.numerator_;
    denominator_ = rational.denominator_;
}

Rational::Rational(Rational&& rational) {

    numerator_ = std::move(rational.numerator_);
    denominator_ = std::move(rational.denominator_);
}

Rational::~Rational() {}

Rational& Rational::operator=(const Rational& rational) {

    numerator_ = rational.numerator_;
    denominator_ = rational.denominator_;

    return *this;
}

Rational& Rational::operator=(Rational&& rational) {

    numerator_ = std::move(rational.numerator_);
    denominator_ = std::move(rational.denominator_);

    return *this;
}

Rational Rational::operator+(const Rational& rational) const {

    Rational temp(*this);

    temp.numerator_ += rational.numerator_;
    temp.denominator_ += rational.denominator_;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator+(int numerator) const {

    Rational temp(*this);

    temp.numerator_ += numerator * temp.denominator_;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator-(const Rational& rational) const {

    Rational temp(*this);

    temp.numerator_ -= rational.numerator_;
    temp.denominator_ -= rational.denominator_;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator-(int numerator) const {

    Rational temp(*this);

    temp.numerator_ -= numerator * temp.denominator_;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator*(const Rational& rational) const {

    Rational temp(*this);

    temp.numerator_ *= rational.numerator_;
    temp.denominator_ *= rational.denominator_;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator*(int numerator) const {

    Rational temp(*this);

    temp.numerator_ *= numerator;

    int gc = gcd(temp.numerator_, temp.denominator_);
    temp.numerator_ /= gc;
    temp.denominator_ /= gc;

    return temp;
}

Rational Rational::operator/(const Rational& rational) const {

    if((this->numerator_ % rational.numerator_ == 0) && (this->denominator_ % rational.denominator_ == 0))
        return Rational(this->numerator_ / rational.numerator_, this->denominator_ / rational.denominator_);
    else {

        Rational temp(*this);
        temp.numerator_ *= rational.denominator_;
        temp.denominator_ *= rational.numerator_;

        int gc = gcd(temp.numerator_, temp.denominator_);
        temp.numerator_ /= gc;
        temp.denominator_ /= gc;

        return temp;
    }
}

Rational Rational::operator/(int numerator) const {

    if(this->numerator_ % numerator == 0)
        return Rational(this->numerator_ / numerator, this->denominator_);
    else {

        Rational temp(*this);
        temp.denominator_ *= numerator;

        return temp;
    }
}

Rational Rational::operator^(int pow) const {

    Rational temp(*this);

    for(int i = 0; i < pow - 1; i++) {

        temp.numerator_ *= temp.numerator_;
        temp.denominator_ *= temp.denominator_;
    }

    return temp;
}

Rational& Rational::operator++() {

    this->numerator_ += this->denominator_;

    return *this;
}

Rational Rational::operator++(int) {

    Rational temp(*this);
    ++(*this);

    return temp;
}

Rational& Rational::operator--() {

    this->numerator_ -= this->denominator_;

    return *this;
}

Rational Rational::operator--(int) {

    Rational temp(*this);
    --(*this);

    return temp;
}

bool Rational::operator==(const Rational& rational) const {

    return (this->numerator_ == rational.numerator_) && (this->denominator_ == rational.denominator_);
}

bool Rational::operator==(const char* rational) const {

    Rational temp(rational);

    return *this == temp;
}

bool Rational::operator!=(const Rational& rational) const {

    return (this->numerator_ != rational.numerator_) || (this->denominator_ != rational.denominator_);
}

bool Rational::operator!=(const char* rational) const {

    Rational temp(*this);

    return *this != temp;
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {

    int num = rational.numerator();
    int den = rational.denominator();

    if(den == 1)
        os << num;
    else
        os << num << '/' << den;

    return os;
}
