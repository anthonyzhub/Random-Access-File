#ifndef Employee_hpp
#define Employee_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Employee
{
private:
    int employeeID;
    string name;
    double salary;
    int yearHired;
    
public:
    
    // Setter methods
    void setID(int i);
    void setName(string n);
    void setSalary(double s);
    void setYearHired(int y);
    
    // Getter methods
    int getID();
    string getName();
    double getSalary();
    int getYearHired();
    
};

#endif /* Employee_hpp */
