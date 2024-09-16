#pragma once
#include <string>
#include <string.h>

// Class representing a node in a Binary Search Tree
class NameBSTNode
{
private:
	NameBSTNode* left;  // Pointer to the left child
	NameBSTNode* right;  // Pointer to the right child

	std::string name;  // Member name
	int age;  // Member age
	std::string date;  // Date
	char term;  // Term type


public:
	// Default constructor
	NameBSTNode() : name(""), age(0), date(""), term('A'), left(nullptr), right(nullptr) {}

	// Parameterized constructor
	NameBSTNode(const std::string& n, int a, const std::string& d, char t)
		: name(n), age(a), date(d), term(t), left(nullptr), right(nullptr) {}

	// Destructor
	~NameBSTNode() {}

	// Getter methods
	NameBSTNode* getLeft() { return left; }  // Return left child
	NameBSTNode* getRight() { return right; }  // Return right child


	// getter methods
	std::string getName() const { return name; }  // Returns member name
	int getAge() const { return age; }  // Returns member age
	std::string getDate() const { return date; }  // Returns associated date
	char getTerm() const { return term; }  // Returns term type

		// Setter methods
	void setLeft(NameBSTNode* left) { this->left = left; }  // left child
	void setRight(NameBSTNode* right) { this->right = right; }  // right child

	// setter methods
	void setName(const std::string& n) { name = n; }  // Set member name
	void setAge(int a) { age = a; }  // Set member age
	void setDate(const std::string& d) { date = d; }  // Set associated date
	void setTerm(char t) { term = t; }  // Set term type
};
