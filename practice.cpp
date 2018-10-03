//
//  practice.cpp
//  
//
//  Created by Mincheol Ko on 16/03/2018.
//
#include <iostream>
#include <vector>

typedef std::vector<int> poly;
using namespace std;

int gcd_euclid(int m, int n)
{
    int r;
    r=m%n;         //E1
    
    if( r==0 )     //E2
        return n;
    else
    {              //E3
        m=n;
        n=r;
        return gcd_euclid(m, n);
    }
}

int max(int m, int n)
{
    if (m>n)
        return m;
    else
        return n;
}

poly add(poly a, poly b)
{
    poly result_poly;
    int order = max(a.size(),b.size());
    result_poly.resize(order);
    a.resize(order);
    b.resize(order);
    for( int i=0; i<order; i++)
    {
        result_poly[i]=a[i]+b[i];
    }
    return result_poly;
}

poly mul(poly a, poly b)
{
    poly result_poly;
    int order = a.size() + b.size();
    result_poly.resize(order);
    int tmp = 0;
    for( int i=0; i<a.size(); i++)
    {
        for( int j=0; j<b.size(); j++)
        {
            tmp = a[i]*b[j];
            result_poly[i+j]=tmp+result_poly[i+j];
            tmp = 0;
        }
    }
    return result_poly;
}

void print(poly p)
{
    bool first=true;
    for( int i=0; i<p.size(); i++ )
    {
        if( p[i]>0 )
        {
            if( !first )
                cout << "+";
            cout << p[i];
            if( i>0 )
                cout << "x^" << i;
            first=false;
        }
        if( p[i]<0 )
        {
            cout << p[i];
            if( i>0 )
                cout << "x^" << i;
            first=false;
        }
    }
    //nothing printed so far, so the polynomial is zero
    if( first==true )
        cout << "0";
}

void enterPolynomial(poly &p1)
{
    p1.clear();
    int deg=0;
    while( true )
    {
        cout << "Enter degree " << deg << " term (leave empty and press enter for the last term):";
        string str;
        getline(std::cin, str);
        if( str.length()==0 )
            break;
        else
            p1.push_back( std::stoi(str) );
        deg++;
        cout << "Polynomial is now ";
        print(p1);
        cout << endl;
    }
}
int main()
{
    poly p1, p2, p3;
    cout << "First polynomial";
    enterPolynomial(p1);
    cout << "Second polynomial";
    enterPolynomial(p2);
    cout << endl;
    
    p3=add(p1, p2);
    cout << "The sum equals ";
    print(p3);
    cout << endl;
    
    p3=mul(p1, p2);
    cout << "The product equals ";
    print(p3);
    cout << endl;
        
    cout << "And a gcd computation: gcd(15, 135)=" << gcd_euclid(15,135) << endl;
    
    return 0;
}
