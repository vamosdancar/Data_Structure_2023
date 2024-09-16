#pragma once
#include <string>

using namespace std;

// node in a list
class TermsListNode
{
private:

	TermsListNode* next;  // Point to next node

	string name;  // The name
	int age;  // The age
	string date;  // The date
	char term;  // The term

	int membersCount = 0;  // Count of members

public:
	// Constructor
	TermsListNode(string n, int a, string d, char t)
		: name(n), age(a), date(d), term(t), next(nullptr) {}

	~TermsListNode() {}  // Destructor

	// Getter 
	TermsListNode* getNext() { return next; }

	// Setter 
	void setNext(TermsListNode* next) { this->next = next; }

	// Getters for member variables
	string getName() const { return name; }
	int getAge() const { return age; }
	string getDate() const { return date; }
	char getTerm() const { return term; }

	// Getter for members count
	int getMembersCount() const { return membersCount; }

	// Setters for member variables
	void setName(const string& n) { name = n; }
	void setAge(int a) { age = a; }
	void setDate(const string& d) { date = d; }
	void setTerm(char t) { term = t; }

	// decrease the members count
	void decreaseMembersCount(int count) { membersCount -= count; }

	// increase the members count
	void increaseMembersCount(int count) { membersCount += count; }

};



