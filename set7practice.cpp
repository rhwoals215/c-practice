//
//  set7practice.cpp
//  
//
//  Created by Mincheol Ko on 20/04/2018.
//

#include "set7practice.hpp"
#include <vector>
#include <list>
#include <iostream>
using namespace std;
typedef std::vector<int> exponents;

int max(int m, int n)//method to find max
{
    if (m>n)
        return m;
    else
        return n;
}


struct monomial
{
    int coeff;
    vector<int> degree;
};

int lexi_order(monomial a, monomial b)
{
    for( int i=0; i < a.degree.size(); i++)
    {
        if (a.degree[i] > b.degree[i])
            return 1;
        if (a.degree[i] < b.degree[i])
            return -1;
    }
    return 0;
}

class polynomial{
public:
    std::list<monomial> terms;
    void insert(monomial mon)
    {
        list<monomial>::iterator iter=terms.begin();
        int comparison = 1;
        while( iter != terms.end() ){
            comparison = lexi_order(*iter, mon );
            if( comparison >= 0 )
                break;
            iter++;
        }
        if( comparison != 0 ){
            terms.insert(iter, mon);
        }
        else{
            iter->coeff += mon.coeff;
            if (iter->coeff == 0){
                iter = terms.erase(iter);
            }
        }
    }
    void print()
    {
        if (!is_zero()){
            list<monomial>::iterator iter=terms.begin();
            while( iter != terms.end() ){
                if ((iter) != terms.begin())
                    cout << "+";
                cout << iter->coeff;
                for (int i = 0; i < (iter->degree).size(); i++){
                    cout << "(x(" << i << ")^" << iter->degree[i] << ")";
                }
                iter++;
            }
            cout << endl;
        }
    }
    bool is_zero()
    {
        if (terms.empty())
            return true;
        return false;
    }
};
polynomial add(polynomial p1, polynomial p2)
{
    polynomial result = p1;
    list<monomial>::iterator iter=p2.terms.begin();
    while(iter != p2.terms.end()){
        result.insert(*iter);
        iter++;
    }
    return result;
}

monomial mon_multiply(monomial a, monomial b)
{
    monomial result;
    int x = max(a.degree.size(), b.degree.size());
    int zero_exponents = 0;
    a.degree.resize(x);
    b.degree.resize(x);
    result.degree.resize(x);
    for (int i=0; i < x; i++){
        result.degree.push_back(a.degree[i] + b.degree[i]);
    }
    result.coeff = a.coeff * b.coeff;
    return result;
}

polynomial multiply(polynomial p1, polynomial p2)
{
    polynomial result;
    list<monomial>::iterator iter1=p1.terms.begin();
    while(iter1 != p1.terms.end()){
        list<monomial>::iterator iter2=p2.terms.begin();
        while(iter2 != p2.terms.end()){
            if (mon_multiply(*iter1, *iter2).coeff != 0){
                result.insert(mon_multiply(*iter1, *iter2));
            }
            iter2++;
        }
        iter1++;
    }
    return result;
}

int main()
{
    monomial mon1;
    mon1.coeff = 5;
    mon1.degree.push_back(1);
    
    monomial mon2;
    mon2.coeff = 5;
    mon2.degree.push_back(0);
    mon2.degree.push_back(3);


    monomial mon3;
    mon3.coeff = 3;
    mon3.degree.push_back(3);
    
    polynomial poly1;
    poly1.insert(mon1);
    poly1.insert(mon2);
    poly1.insert(mon3);
    poly1.print();
    
    monomial mon4;
    mon4.coeff = 5;
    mon4.degree.push_back(1);
    
    monomial mon5;
    mon5.coeff = 5;
    mon5.degree.push_back(0);
    mon5.degree.push_back(1);
    mon5.degree.push_back(1);
    
    monomial mon6;
    mon6.coeff = 3;
    mon6.degree.push_back(4);
    
    polynomial poly2;
    poly2.insert(mon4);
    poly2.insert(mon5);
    poly2.insert(mon6);
    poly2.print();
    add(poly1,poly2).print();
    multiply(poly1,poly2).print();
    return 0;
}
