#pragma once
#include "TermsBSTNode.h"
#include <string>
#include <string.h>

// Binary Search Tree for managing terms
class TermsBST
{
private:
	TermsBSTNode* root;  // Pointer to the root node 
	TermsBSTNode* insert(TermsBSTNode* node, const std::string& name, int age, const std::string& date, char term);  // Recursive function to insert a new node into the BST.

	// Function to calculate expiration date of personal information
	std::string calculateExpirationDate(const std::string& collectionDate, char term);

	bool deletedSuccessfully;  // successfully deleted


public:
	TermsBST();  // Constructor
	~TermsBST();  // Destructor

	TermsBSTNode* getRoot();  // Returns pointer 

	// Functions related to searching 
	TermsBSTNode* search(char term);
	TermsBSTNode* search(TermsBSTNode* node, char term);
	TermsBSTNode* rootForTerm(char term);

	// Helper functions for delete operations
	TermsBSTNode* minValueNode(TermsBSTNode* node);
	TermsBSTNode* deleteRecursive(TermsBSTNode* root, const std::string& key);


	// Function for in-order traversal
	void inOrderTraversal(TermsBSTNode* node, std::ostream& flog, char term);  

	// Function to delete nodes
	int deleteBeforeDate(const std::string& expirationDate);
	TermsBSTNode* deleteBeforeDateRecursive(TermsBSTNode* node, const std::string& givenDate, int& count);


	// Function to delete a specific member
	bool deleteMember(const std::string& name);
	TermsBSTNode* deleteMemberRecursive(TermsBSTNode* node, const std::string& name, bool& wasDeleted);

	// to print the BST
	void print();
	void print(TermsBSTNode* node);

	// Function to check
	bool isEmpty(char term);

	// Public interface 
	void insert(const std::string& name, int age, const std::string& date, char term);

};
