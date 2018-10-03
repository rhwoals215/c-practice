//
//  karatsuba2.cpp
//
//
//  Created by Mincheol Ko on 30/03/2018.
//

#include "karatsuba2.hpp"
#include <iostream>
#include <vector>

template < class T, class Alloc = allocator<T> > class list;
using namespace std;

int max(int m, int n)
{
    if (m>n)
        return m;
    else
        return n;
}

poly add(list a, list b)//addition
{
    int order = max(a.size(),b.size());
    list<int> result_poly[order];
    a.resize(order);
    b.resize(order);
    for( int i=0; i<order; i++)
    {
        result_poly[i]=a[i]+b[i];
    }
    return result_poly;
}

poly subtract(poly a, poly b)//subtraction
{
    poly result_poly;
    int order = max(a.size(),b.size());
    result_poly.resize(order);
    a.resize(order);
    b.resize(order);
    for( int i=0; i<order; i++)
    {
        result_poly[i]=a[i]-b[i];
        if (result_poly[i]==0 && result_poly[i+1]==NULL)
        {
            result_poly[i]= NULL;
        }
    }
    if (result_poly[0]==NULL)
        result_poly[0] = 0;
    return result_poly;
}

poly mul(poly a, poly b)
{
    poly result_poly;
    int order = a.size() + b.size()-1;
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

poly karatsuba(poly p1, poly p2)
{
    poly result_poly;
    if (p1.size()==1 && p2.size()==1)
    {
        result_poly.resize(1);
        result_poly[0] = p1[0]*p2[0];
        return result_poly;
    }
    poly p1a;
    poly p1b;
    poly p2a;
    poly p2b;
    poly e;
    poly f;
    int cut;
    int size = p1.size();
    if (size % 2 == 0)
        cut = size / 2;
    else
        cut = ((size + 1) / 2);
    p1a.resize(cut);
    p1b.resize(size-cut);
    p2a.resize(cut);
    p2b.resize(size-cut);
    for( int i = 0; i < cut; i++)
    {
        p1a[i] = p1[i];
    }
    for( int i = 0; i < (size - cut); i++)
    {
        p1b[i] = p1[i+cut];
    }
    for( int i = 0; i < cut; i++)
    {
        p2a[i] = p2[i];
    }
    for( int i = 0; i < (size - cut); i++)
    {
        p2b[i] = p2[i+cut];
    }
    poly c = karatsuba(p1b,p2b);
    poly d = subtract(subtract(karatsuba((add(p1a,p1b)),(add(p2a,p2b))),karatsuba(p1a,p2a)),karatsuba(p1b,p2b));
    e.resize(2*cut+c.size());
    for( int i = 0; i < 2*cut; i++)
    {
        e[i] = 0;
    }
    for( int i = 0; i < c.size(); i++)
    {
        e[i+2*cut] = c[i];
    }
    f.resize(cut+d.size());
    for( int i = 0; i < cut; i++)
    {
        f[i] = 0;
    }
    for( int i = 0; i < d.size(); i++)
    {
        f[i+cut] = d[i];
    }
    return add(add(e,f),karatsuba(p1a,p2a));
    
}

int main()
{
    poly p1;
    poly p2;
    p1.resize(2);
    p2.resize(2);
    int rand1[] = { 6,1,0,4,5,4,3,2,6,6,4,8,2,1,3,3,9,3,6,0,7,2,6,0,2,4,9,1,4,1,2,7,8,4,7,2,7,5,3,7,2,3,4,5,6,7,8,9,2,5,1,2,3,4,5,6,7,8,9,0,1 };
    int rand2[] = { 7,3,7,2,4,5,8,7,4,0,6,6,0,6,3,1,5,5,8,8,1,7,4,8,8,1,5,2,0,9,2,4,6,8,3,5,0,3,6,2,1,2,3,4,5,6,7,8,3,7,2,3,4,5,6,7,8,9,0,1,2 };
    
    for (int i = 0; i<2; i++){
        p1[i] = rand1[i];
    }
    for (int i = 0; i<2; i++){
        p2[i] = rand2[i];
    }
    cout << "The karatsuba product equals "<<endl;
    auto begin = chrono::high_resolution_clock::now();
    poly p3 = karatsuba(p1, p2);
    auto end = chrono::high_resolution_clock::now();
    for( int i = 0; i < p3.size(); i++)
    {
        cout << p3[i] << " ";
    }
    cout << endl;
    cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
    cout << "The classic product equals "<<endl;
    begin = chrono::high_resolution_clock::now();
    poly p4 = mul(p1,p2);
    end = std::chrono::high_resolution_clock::now();
    for( int i = 0; i < p4.size(); i++)
    {
        cout << p4[i] << " ";
    }
    cout << endl;
    cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
    return 0;
}


