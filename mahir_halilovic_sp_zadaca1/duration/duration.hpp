#pragma once

#include <iostream>
#include <string>

class Duration {

    public:
        Duration();
        Duration(int s);
        Duration(int h, int m, int s);
        Duration(std::string d);

        Duration& set_s(int s);
        const int get_s();
        Duration& set_m(int m);
        const int get_m();
        Duration& set_h(int h);
        const int get_h();

        bool operator==(Duration& dur);
        bool operator!=(Duration& dur);
        bool operator>(Duration& dur);
        bool operator<(Duration& dur);
        bool operator>=(Duration& dur);
        bool operator<=(Duration& dur);

        operator bool() const;
        bool operator!() const;

        Duration& operator+=(Duration& dur);
        Duration operator+(Duration& dur);
        Duration& operator-=(Duration& dur);
        Duration operator-(Duration& dur);
        Duration& operator*=(int s);
        Duration& operator*(int s);
        Duration& operator/=(int s);
        Duration& operator/(int s);

    private:
        int hour = 0;
        int min = 0;
        int sec = 0;

        friend std::ostream& operator<<(std::ostream& out, const Duration& dur);
        friend std::istream& operator>>(std::istream& in, Duration& dur);
};
