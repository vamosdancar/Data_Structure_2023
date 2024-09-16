#pragma once
#include "NameBSTNode.h"
#include <fstream>

// Forward declaration
class TermsBST;
class TermsLIST;

// Class representing a Binary Search Tree
class NameBST
{
private:
	NameBSTNode* root;  // Root of the BST
	NameBSTNode* deleteNode(NameBSTNode* root, const std::string& name);  
	// Helper function

	// Reference or pointer
	TermsBST* termsBST;
	TermsLIST* termsList;

public:
	// Default constructor
	NameBST() : root(nullptr), termsBST(nullptr), termsList(nullptr) {}

	// Constructor
	NameBST(TermsBST* tBST, TermsLIST* tList);

	// Destructor
	~NameBST();

	// Returns the root
	NameBSTNode* getRoot();

	// Insert a new member
	void insert(const std::string& name, int age, const std::string& date, char term);

	// Search for a member
	NameBSTNode* search(const std::string& name);

	// Print functions for displaying
	void print(std::ostream& flog);
	void printInOrder(NameBSTNode* node, std::ostream& flog);
	void printMembersByTerm(std::ostream& flog, char term);
	void printMembersByTerm(NameBSTNode* node, std::ostream& flog, char term);

	// Check the tree 
	bool isEmpty();

	// Delete functions
	void deleteMembersBeforeDate(const std::string& expirationDate);  // Delete members before date
	NameBSTNode* deleteRecursive(NameBSTNode* node, const std::string& expirationDate);  // Helper function
	NameBSTNode* minValueNode(NameBSTNode* node);  // Find the node 
	bool deleteByName(const std::string& name);  // Delete a member 

};
