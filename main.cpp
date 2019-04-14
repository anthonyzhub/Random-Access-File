//
//  main.cpp
//  CSCI 272
//
//  Created by Anthony Zamora on 4/9/19.
//  Copyright © 2019 Anthony Zamora. All rights reserved.
//

/*
 ios::in - Allows input (read operations) from stream
 ios::out - Allows output (write operations) to stream
 
 fstream allows to read and write a file
*/

#include <iostream>
#include <fstream> // Needed to read and write files
#include <iomanip> // Needed to exit program
#include <string> // Needed to cast string to value types

#include "Employee.hpp"

using namespace std;

void addEmployeeInformation(Employee person)
{
    string name, employeeID, yearHired, salary, response;
    
    // Open file
    fstream dataFile("dataFile.dat", ios::out | ios::app | ios::binary);
    
    // Enter data
    while (true)
    {
        // Enter personal information
        cout<<"\nEnter ID: ";
        cin>>employeeID;
        
        cout<<"Enter name: ";
        cin>>name;
        
        cout<<"Enter Year Hired: ";
        cin>>yearHired;
        
        cout<<"Enter Salary: ";
        cin>>salary;
        
        // Send data to class
        person.setID(stoi(employeeID));
        person.setName(name);
        person.setYearHired(stoi(yearHired));
        person.setSalary(stod(salary));
        
        // Write to data
        dataFile.seekp((stoi(employeeID) - 1) * sizeof(Employee));
        dataFile.write(reinterpret_cast< const char* >(&person), sizeof(Employee));
        
        // Ask user to quit
        cout<<"Exit? Y/n ";
        cin>>response;
        
        if (response == "Y" || response == "y")
            break;
        else
            continue;
    }
    
    // Close file
    dataFile.close();
    
    cout<<endl;
}

void editEmployeeInformation (Employee person)
{
    string id;
    string name, yearHired, salary;
    
    // Request employee's id
    cout<<"Enter employee's ID ";
    cin>>id;
    
    // Open file
    fstream fileData("dataFile.dat", ios::in | ios::out | ios::binary);
    
    // Locate information
    fileData.seekg( (stoi(id) - 1) * sizeof(Employee));
    
    // Enter new information
    cout<<"Enter name: ";
    cin>>name;
    
    cout<<"Enter Year Hired: ";
    cin>>yearHired;
    
    cout<<"Enter Salary: ";
    cin>>salary;
    
    // Send data to class
    person.setID(stoi(id));
    person.setName(name);
    person.setYearHired(stoi(yearHired));
    person.setSalary(stod(salary));
    
    // Go to soon-to-be override information
    fileData.seekp( (stoi(id) - 1) * sizeof(Employee));
    
    // Write to file
    fileData.write( reinterpret_cast< char *>(&person), sizeof(Employee));
    
    // Close file
    fileData.close();
    
}

void locateEmployeeInformation(Employee person)
{
    string id;
    
    // Request employee's id
    cout<<"Enter employee's ID: ";
    cin>>id;
    
    // Open file to read
    fstream fileData("dataFile.dat", ios::in | ios::binary);
    
    // Locate information
    fileData.seekg( (stoi(id) - 1) * sizeof(Employee) );
    fileData.read( reinterpret_cast< char* >(&person), sizeof(Employee));
    
    // Print information
    cout << "\nID" << setw(10) << "Name" << setw(16) << "Year Hired" << setw(10) << "Salary" << endl;
    cout << person.getID() << setw(14) << person.getName() << setw(10) << person.getYearHired() << setw(10) << person.getSalary()<<endl;
    
    // Close file
    fileData.close();
    
    cout<<endl;
}

void printDatabase(Employee person)
{
    // Open file
    fstream dataFile("dataFile.dat", ios::in | ios::binary);
    
    // Create header for table
    cout << "\nID" << setw(10) << "Name" << setw(16) << "Year Hired" << setw(10) << "Salary" << endl;
    
    // Read first line
    dataFile.read( reinterpret_cast< char* >(&person), sizeof(Employee));
    
    // Read entire file until the end of the line
    while (dataFile && !dataFile.eof())
    {
        // Print data of current employee
        cout << person.getID() << setw(14) << person.getName() << setw(10) << person.getYearHired() << setw(10) << person.getSalary()<<endl;
        
        // Go to next line
        //dataFile.read((char *) &person, sizeof(person));
        dataFile.read(reinterpret_cast< char* >(&person), sizeof(Employee));
    }
    
    // Close file
    dataFile.close();
    
    cout<<endl;
}

void createBlankRecords()
{
    // Create initializer
    Employee person;
    
    // Open file
    fstream dataFile("dataFile.dat", ios::out | ios::binary);
    
    // Write blank statements
    for (int i = 1; i <= 10; i++)
    {
        // Send data to class
        person.setID(i);
        person.setName("Nameless");
        person.setYearHired(2000);
        person.setSalary(1.0);
        
        // Seek and write at position
        dataFile.seekp((i - 1) * sizeof(Employee));
        dataFile.write(reinterpret_cast< char* >(&person), sizeof(Employee));
    }
    
    // Close file
    dataFile.close();
}

void createAndOpenFile()
{
    // Attempt to open file, if it exists.
    fstream openFile("dataFile.dat", ios::in | ios::binary);
    
    if (openFile.is_open())
    {
        cout << "Opening file! " << endl;
        
        // Close file
        openFile.close();
    } else {
        
        // Create a new file, if it doesn't exist
        fstream createFile("dataFile.dat", ios::out | ios::binary);
        cout << "Creating a new file!" << endl;
        
        // Close file
        createFile.close();
        
        // Make 10 blank records
        createBlankRecords();
    }
}

int main(int argc, const char * argv[])
{
    string userChoice;
    
    // Create initializer
    Employee person;
    
    // Check if file exists already
    createAndOpenFile();
    
    // User prompt
    while (true)
    {
        // Print Options
        cout<<"1. Add Employee"<<endl;
        cout<<"2. Print Database"<<endl;
        cout<<"3. Edit Employee's Information"<<endl;
        cout<<"4. Print Employee's Information"<<endl;
        cout<<"5. Quit Program"<<endl;
        cout<<"Command: ";
        cin>>userChoice;
        
        // Ask for user's command
        if (userChoice == "1")
        {
            addEmployeeInformation(person);
        }
        else if (userChoice == "2")
        {
            printDatabase(person);
        }
        else if (userChoice == "3")
        {
            editEmployeeInformation(person);
        }
        else if (userChoice == "4")
        {
            locateEmployeeInformation(person);
        }
        else if (userChoice == "Q")
        {
            // Terminate program
            exit(1);
        }
        else
        {
            cout<<"Invalid command: "<<userChoice<<endl;
        }
        
        cout<<endl;
    }
}
