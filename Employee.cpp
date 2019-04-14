//
//  Employee.cpp
//  CSCI 272
//
//  Created by Anthony Zamora on 4/9/19.
//  Copyright © 2019 Anthony Zamora. All rights reserved.
//

#include "Employee.hpp"

using namespace std;

// Setter Methods
void Employee::setID(int i)
{
    employeeID = i;
}

void Employee::setName(string n)
{
    name = n;
}

void Employee::setSalary(double s)
{
    salary = s;
}

void Employee::setYearHired(int y)
{
    yearHired = y;
}

// Getter Methods
int Employee::getID()
{
    return employeeID;
}

string Employee::getName()
{
    return name;
}

double Employee::getSalary()
{
    return salary;
}

int Employee::getYearHired()
{
    return yearHired;
}
