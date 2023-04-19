#pragma once

#ifndef RATIONALHPP
#define RATIONALHPP

#include <sstream>
#include <cstdint>
#include <iosfwd>

class Rational {
    public:
        Rational();
        Rational(int32_t numerator);
        Rational(int32_t numerator, int32_t denumerator);
        
        bool operator==(const Rational&) const;
        bool operator!=(const Rational&);
        bool operator>(const Rational&);
        bool operator<(const Rational&);
        bool operator<=(const Rational&);
        bool operator>=(const Rational&);

        Rational& operator+=(const Rational&);
        Rational& operator-=(const Rational&);
        Rational& operator*=(const Rational&);
        Rational& operator/=(const Rational&);
        Rational& operator++();
        Rational& operator++(int);
        Rational& operator--();
        Rational& operator--(int);
        
        std::ostream& writeTo(std::ostream& ostrm) const;

        std::istream& readFrom(std::istream& istrm);


        int32_t GetNum() const { return num; }
        int32_t GetDenum () const { return denum; }
        
        Rational& operator=(const Rational& rhs) = default;
        ~Rational() = default;

        void simple() {
            int32_t nod = Nod(num, denum);
            num /= nod;
            denum /= nod;
        }
        void form() {
            if (num < 0 && denum < 0){
                denum = std::abs(denum);
                num = std::abs(num);
            }
        }

    private:
        int32_t num;
        int32_t denum;
        
        static const char slesh = '/';

        

        static int32_t Nod(int32_t a, int32_t b) {
            a = std::abs(a);
            b = std::abs(b);

            if(a == 0) {
                return b;
            }
            else if (b == 0) {
                return a;
            }
            else {
                return Nod(std::max(a,b) % std::min(a,b), std::min(a,b));
            }
        }
};

Rational operator-(const Rational& lhs, const Rational&);
Rational operator/(const Rational& lhs, const Rational&);
Rational operator+(const Rational& lhs, const Rational&);
Rational operator*(const Rational& lhs, const Rational&);

std::ostream& operator<<(std::ostream& ostrm, const Rational& temp);
std::istream& operator>>(std::istream& istrm, Rational& temp);

//std::istream& operator>>(std::istream& in, Rational& value);
//std::ostream& operator<<(std::ostream& out, Rational& value);
#endif