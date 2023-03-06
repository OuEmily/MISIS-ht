#include <rational/rational.hpp>


Rational::Rational(){
    num = 0;
    denum = 1;
    }
Rational::Rational(int32_t numerator){
    num = numerator;
    denum = 1;
    }
Rational::Rational(int32_t numerator, int32_t denumerator) {
    if(denumerator == 0) {
        throw std::invalid_argument("Expected denumeratoir not equal to zero");
        }
    
    if(denumerator < 0) {
        denumerator *= -1;
        numerator *= -1;
    }
    num = numerator;
    denum = denumerator;
    
    simple();
    form();

    }

bool Rational::operator==(const Rational& rhs) {
    return (denum == rhs.GetDenum() && num == rhs.GetNum());
}

bool Rational::operator!=(const Rational& rhs) {
    return !(*this == rhs);
}

bool Rational::operator>(const Rational& rhs){
    return (num * rhs.GetDenum() > denum * rhs.GetNum());
}

bool Rational::operator<(const Rational& rhs){
    return (num * rhs.GetDenum() < denum * rhs.GetNum());
}

bool Rational::operator>=(const Rational& rhs){
    return !(*this < rhs);
}

bool Rational::operator<=(const Rational& rhs){
    return !(*this > rhs);
}


Rational& Rational::operator+=(const Rational& rhs) {
    int32_t BDN = denum * rhs.denum;
    num = rhs.num * (BDN/rhs.denum) + num * (BDN/denum);
    denum = BDN;
    simple();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int32_t BDN = denum * rhs.denum;
    num = rhs.num * (BDN/rhs.denum) - num * (BDN/denum);
    denum = BDN;
    simple();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num = rhs.num * num;
    denum = rhs.denum * denum;
    simple();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    num = rhs.num * denum;
    denum = rhs.denum * num;
    simple();
    return *this;
}


Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational temp(lhs);
    temp += rhs;
    return temp;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  return Rational(lhs) *= rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  return Rational(lhs) -= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  return Rational(lhs) /= rhs;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

Rational& Rational::operator--() {
    *this -= 1;
    simple();
    form();
    return *this;
}

Rational& Rational::operator++(int32_t) {
    Rational a(*this);
    ++(*this);
    return a;
}

Rational& Rational::operator--(int32_t) {
    Rational a(*this);
    --(*this);
    return a;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& temp){

 return temp.writeTo(ostrm);

}

std::istream& operator>>(std::istream& istrm, Rational& temp){

 return temp.readFrom(istrm);

}

std::ostream& Rational::writeTo(std::ostream& out) const {
    out << num << slesh << denum;
    return out;
}


// std::ostream& Rational::writeTo(std::ostream& ostrm) const{
 //   ostrm << num << slesh << denum;
//    return ostrm;

//}


//std::ostream& operator<<(std::ostream out,  const Rational& value) { 
 //   return(value.readFrom(out));
//}

std::istream& Rational::readFrom(std::istream& in) {
    int32_t Num = 0;
    int32_t Denum = 0;
    char Slesh = '0';

    if (!in.good()) {
        return in;
    }
    in >> Num >> Slesh >> Denum;

    if (Slesh != slesh || Denum <= 0) {
        in.setstate(in.failbit);

    }

    num = Num;
    denum = Denum;
    simple();
    form();
    return in;

//std::istream& operator>>(std::istream& in, Rational& value) { 
//    return value.writeTo(in);
//}

}
