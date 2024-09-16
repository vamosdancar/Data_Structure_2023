#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
using namespace std;

class Manager
{
private:

    string name;             // member name holder
    int age;                 // member age holder
    string date;             // member joining date holder
    char term;               // member term holder

    MemberQueue Queue;      // Member Queue
    ifstream fcmd;           // Command input file stream
    ofstream flog;           // Log output file stream
    TermsLIST tList;         // Terms List
    TermsBST tBST;           // Terms Binary Search Tree
    NameBST nBST;            // Name Binary Search Tree

public:
    Manager();               // constructor
    ~Manager();              // Destructor

    // Execute commands
    void run(const char* command);

    // Load member data 
    void LOAD(const char* filename);

    // Add a new member
    void ADD(const string& add_name, int age, const string& date, char term);

    // Process the next member
    void QPOP();

    // Search for a member
    void SEARCH(const string& name);

    // Display the current state 
    void PRINT(const std::string& arg);

    // Delete members
    void DELETE(const std::string& type, const std::string& value);

    // Print a success message 
    void PrintSuccess(const char* cmd);

    // Print error message 
    void PrintErrorCode(int num);

    // Display the terms
    void printTermsAndMembers(char term);

};


