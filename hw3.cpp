#include "hw3.hpp"
#include "stdc++.h"
#include <string>
#include <iostream>
using namespace std;
typedef std::vector<int> poly;

int max(int m, int n) //find max
{
    if (m>n)
        return m;
    else
        return n;
}

poly add(poly a, poly b) //add polynomials
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

poly subtract(poly a, poly b) //subtract polynomials
{
    poly result_poly;
    int order = max(a.size(),b.size());
    result_poly.resize(order);
    a.resize(order);
    b.resize(order);
    for( int i=0; i<order; i++)
    {
        result_poly[i]=a[i]-b[i];
    }
    return result_poly;
}

poly mul(poly a, poly b) //multiply polynomial
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

class node //variable+constant node
{

public:
    string info;
    int exp;
    node *left = NULL, *right = NULL;
    node(string a, int b)
    {
        info = a;
        exp = b;
    }
};

int toInt(string s) //string to int
{
    int num = 0;
    for (int i=0; i<s.length();  i++)
        num = num*10 + (int(s[i])-48);
    return num;
}


void print(node* root) //prints the node
{
    if (!root)
        return;
    cout << "(";
    print(root->left);
    cout << root->info;
    if (root->exp == 1)
        cout << "x";
    else if (root->exp > 1 ){
        cout << "x^" << root->exp;
    }
    print(root->right);
    cout << ")";
}

void printpoly(poly a) //prints the polynomial
{
    int size = a.size();
    for (int i = 0; i<size; i++){
        if (a[i]!=0){
            cout << "(" << a[i];
            if (i==1)
                cout << "x)";
            else if (i > 1)
                cout << "x^" << i << ")";
            if (i!= size-1)
                cout << "+";
        }
    }
}
poly eval(node* root) //evaluates the expression
{
    poly result;
    if (!root)
        return result;
    if (!root->left && !root->right){
        result.resize(root->exp+1);
        for (int i = 0; i<root->exp; i++){
            result[i] = 0;
        }
        result[root->exp] = toInt(root->info);
        return result;
    }
    poly left_value = eval(root->left);
    
    poly right_value = eval(root->right);
    
    if (root->info=="+")
        return add(left_value,right_value);
    
    if (root->info=="-")
        return subtract(left_value,right_value);
    
    if (root->info=="*")
        return mul(left_value,right_value);
}
void derive(node* root, poly a) //derives the expression
{
    int last = a[a.size()];
    root = new node("+",0);
    if (last !=0){
        root->left = new node(to_string((a.size()-2)*(a[a.size()-1])),a.size()-2); //takes the last term and derives it, adds it as the left node
    }
    a.resize(a.size()-1); //decrease the polynomial at the end
    if (a.size() == 2){
        root->right = new node(to_string(a[1]),0); //if this is the last term that can be derived, it will just add as the right node
        return;
    }
    derive(root->right, a);
    return;
}

int main() //execute
{
    node *root = new node("+",0);
    root->left = new node("*",0);
    root->left->left = new node("5",1);
    root->left->right = new node("4",1);
    root->right = new node("-",0);
    root->right->left = new node("100",1);
    root->right->right = new node("20",1);
    
    print(root);//prints the function expression
    cout <<endl;
    
    int size = eval(root).size();
    poly result = eval(root);
    printpoly(result);//prints the eval function
    
    delete(root);
    int realsize=0;
    for (int i = 0; i<size; i++){
        if (result[i]!=0)
            realsize++;
    }
    if (size ==1 || realsize == 0)
        node *root = new node("0",0); //if the only term is of 0 degree or no term
    else if (realsize == 1){
        for (int i = 0; i<size; i++){
            if (result[i] != 0)
                node *root = new node(to_string(i*result[i]),i-1); //if there is one term
        }
    }
    if (realsize > 1){
        root = new node("+",0);
        derive(root, result);//creates a tree of the derivative
    }
    cout <<endl;

    return 0;
}
