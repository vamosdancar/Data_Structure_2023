#pragma once

#include <string>

using namespace std;

class MemberQueueNode
{
private:
	string name;        // Member's name
	int age;            // Member's age
	string date;        // Date 
	char terms;         // Type of membership terms
	MemberQueueNode* next;  // Pointer to the next node

public:
	//  constructor
	MemberQueueNode() : name(""), age(0), date(""), terms('A'), next(nullptr) {}

	// Constructor 
	MemberQueueNode(string n, int a, string d, char t) : name(n), age(a), date(d), terms(t), next(nullptr) {}

	// Constructor 
	MemberQueueNode(const string& n, int a, const string& d, const string& t) : name(n), age(a), date(d), terms(t.front()), next(nullptr) {}

	// Destructor
	~MemberQueueNode() {}

	// Getter methods
	string getName() const { return name; }             // Get member's name
	int getAge() const { return age; }                 // Get member's age
	string getDate() const { return date; }             // Get date 
	char getTerms() const { return terms; }             // Get type 

	MemberQueueNode* getNext() const { return next; }   // Get the next node 

	// Setter methods
	void setName(string n) { name = n; }                // Set member's name
	void setAge(int a) { age = a; }                    // Set member's age
	void setDate(string d) { date = d; }                // Set date
	void setTerms(char t) { terms = t; }                // Set type
	void setNext(MemberQueueNode* n) { next = n; }     // Set next node
};
