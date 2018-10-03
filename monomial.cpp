#ifndef __POLYNOMIAL_H_
#define __POLYNOMIAL_H_

#include <iostream>
#include <list>
#include "Polynomial.cpp"

#define var = 'x' //varible to use in polynomial

using namespace std;

struct ZERO_T {
    static const short ZERO = 0;
};
template <typename NumT>
class Monomial
{
public:
    Monomial<NumT>(NumT c = 0, int d = 0) : coeff(c), expo(d)
    { };
    NumT coefficient(void) const { return coeff; };
    int degree(void) const { return expo; };
    void assign_coefficient(const NumT c) { coeff = c; };
    void assign_degree(const int d) { expo = d; };
    bool operator==(const Monomial<NumT> & m) const
    {
        return (coeff == m.coeff && expo == m.expo);};
    bool operator!=(const Monomial<NumT> & m) const
    {return (coeff != m.coeff || expo != m.expo);};
    
private:
    NumT coeff;
    int expo;
};
template <typename NumberType>
class Polynomial : public ZERO_T
{
public:
    Polynomial<NumberType>(NumberType c = 0, int d = 0)
    {
        const Monomial<NumberType> m(c, d);
        term_list.push_back(m); //creates a ZERO monomial
        number_of_terms = 1;
        highest_degree = d;
    }
    
    Polynomial<NumberType>(const Monomial<NumberType> & m) //type conversion constructor
    {
        term_list.push_back(m);
        number_of_terms = 1;
        highest_degree = m.degree();
    }
    
    ~Polynomial<NumberType>() { } // use default destructors and list's destructor
    
    Polynomial<NumberType>(const Polynomial<NumberType> & rhs) // copy constructor
    : term_list(rhs.term_list), number_of_terms(rhs.number_of_terms),
    highest_degree(rhs.highest_degree) { }
    
    const Polynomial<NumberType> & operator=(const Polynomial<NumberType> & rhs);
    //copy assignment
    Polynomial<NumberType> operator+=(const Monomial<NumberType> &m);
    Polynomial<NumberType> operator+=(const Polynomial<NumberType> & rhs);
    const Polynomial<NumberType> operator+(const Monomial<NumberType> &m)const;
    const Polynomial<NumberType> operator+(const Polynomial<NumberType> & rhs) const;
    Polynomial<NumberType> operator*=(const Monomial<NumberType> &m);
    Polynomial<NumberType> operator*=(const Polynomial<NumberType> & rhs);
    const Polynomial<NumberType> operator*(const Monomial<NumberType>  &m) const;
    const Polynomial<NumberType> operator*(constPolynomial<NumberType> & rhs) const;
    const NumberType evaluate(NumberType x);
    bool operator==(const Polynomial<NumberType> &p) const;
    bool operator!=(const Polynomial<NumberType> &p) const;
    const int gethighestdegree();
    void read(istream & in = cin);
    void print(ostream & out = cout) const;
    //static Polynomial<NumberType> ZERO;
private:
    list<Monomial<NumberType> > term_list;
    //sorted by decreasing degrees
    int number_of_terms;
    int highest_degree;
    void insert_in_poly(Polynomial<NumberType> & p, const Monomial<NumberType> & m);
    //helper function
    NumberType power(NumberType x, int n);
};
//template<> Polynomial<int> Polynomial<int>::ZERO = 0;
template <typename NumberType>
istream&operator>>(istream &  in, Polynomial<NumberType> & rhs);

template <typename NumberType>
ostream& operator<<(ostream & out, const Polynomial<NumberType> & rhs);

#include "polynomial.cpp"
#endif
