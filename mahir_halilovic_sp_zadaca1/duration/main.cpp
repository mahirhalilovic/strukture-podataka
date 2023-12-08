#include <iostream>
#include <string>
#include <exception>

//#include "duration.hpp"

class Duration {

    public:
        Duration() : hour{0}, min{0}, sec{0} {};

        Duration(int s) : hour{0}, min{0}, sec{s} {

            if(sec >= 60) {

                min = sec / 60;
                sec = sec % 60;
                if(min >= 60) {

                    hour = min / 60;
                    min = min % 60;
                }
            }
        }

        Duration(int h, int m, int s) : hour{h}, min{m}, sec{s} {

            if(s >= 60 || m >= 60)
                throw std::out_of_range{"Unos izvan granica."};
        }

        Duration(std::string d) {

            std::string temp = d.substr(0, 2);
            hour = std::stoi(temp);
            temp = d.substr(3, 5);
            min = std::stoi(temp);
            temp = d.substr(6, 8);
            sec = std::stoi(temp);
        }

        Duration& set_s(int s) { 

            if(s < 60)
                sec = s;
            else
                throw std::out_of_range("Unos izvan granica.");

            return *this;
         }
        const int get_s() { return sec; }

        Duration& set_m(int m) {

            if(m < 60)
                min = m;
            else
                throw std::out_of_range("Unos izvan granica.");

            return *this;
        }
        const int get_m() { return min; }

        Duration& set_h(int h) { 
            
            hour = h;
            return *this;
        }
        const int get_h() { return hour; }

        bool operator==(Duration& dur) {

            if(hour == dur.hour && min == dur.min && sec == dur.sec)
                return true;
            else
                return false;
        }

        bool operator!=(Duration& dur) {

            if(hour != dur.hour || min != dur.min || sec != dur.sec)
                return true;
            else
                return false;
        }

        bool operator>(Duration& dur) {

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

        bool operator<(Duration& dur) {

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

        bool operator>=(Duration& dur) {

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

        bool operator<=(Duration& dur) {

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

        operator bool() const {
            
            if(hour != 0 || min != 0 || sec != 0)
                return true;
            else
                return false;
        }
        bool operator!() const {
        
            if(hour != 0 || min != 0 || sec != 0)
                return false;
            else
                return true;
        }

        Duration& operator+=(Duration& dur) {

            sec += dur.sec;
            min += dur.min;
            hour += dur.hour;

            if(sec >= 60) {

                min += sec / 60;
                sec = sec % 60;
            }

            if(min >= 60) {

                hour += min / 60;
                min = min % 60;
            }

            return *this;
        }

        Duration& operator+(Duration& dur) {

            sec += dur.sec;
            min += dur.min;
            hour += dur.hour;

            if(sec >= 60) {

                min += sec / 60;
                sec = sec % 60;
            }

            if(min >= 60) {

                hour += min / 60;
                min = min % 60;
            }

            return *this;
        }

        Duration& operator-=(Duration& dur) {

            if(dur < *this) {

                hour -= dur.hour;
                min -= dur.min;
                if(min < 0) {

                    min += 60;
                    hour -= 1;
                }
                sec -= dur.sec;
                if(sec < 0) {

                    sec += 60;
                    min -= 1;
                }

                return *this;
            } else
                throw std::out_of_range("Rezultat ne moze biti negativan.");
        }

        Duration& operator-(Duration& dur) {

            if(dur < *this) {

                hour -= dur.hour;
                min -= dur.min;
                if(min < 0) {

                    min += 60;
                    hour -= 1;
                }
                sec -= dur.sec;
                if(sec < 0) {

                    sec += 60;
                    min -= 1;
                }

                return *this;
            } else
                throw std::out_of_range("Rezultat ne moze biti negativan.");
        }

        Duration& operator*=(int s) {

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

        Duration& operator*(int s) {

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

        Duration& operator/=(int s) {

            if(hour % s != 0)
                min += (s - 1) * 60;
                hour /= s;

            if(min & s != 0)
                sec += (s - 1) * 60;
                min /= s;
                sec /= s;

            return *this;
        }

        Duration& operator/(int s) {

            if(hour % s != 0)
                min += (s - 1) * 60;
                hour /= s;

            if(min & s != 0)
                sec += (s - 1) * 60;
                min /= s;
                sec /= s;

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const Duration& dur) {

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

        friend std::istream& operator>>(std::istream& in, Duration& dur) {

            std::string temph, tempm, temps;
            std::getline(in, temph, ':');
            std::getline(in, tempm, ':');
            std::getline(in, temps);

            dur.hour = std::stoi(temph);
            dur.min = std::stoi(tempm);
            dur.sec = std::stoi(temps);

            return in;
        }

    private:
        int hour = 0;
        int min = 0;
        int sec = 0;
};

int main() {

    Duration d{1, 30, 5};
    std::cout << d << std::endl; // ispis na ekran 01:30:05
    std::cin >> d; // korisnik unosi 10:05:00
    std::cout << d << std::endl;

    Duration e{"10:30:25"};
    std::cout << e;

    return 0;
}