#include "TermsBST.h"
#include <iostream>
#include <ctime>
#pragma warning(disable:4819) 

// Constructor
TermsBST::TermsBST() : root(nullptr)
{

}

// Default destructor
TermsBST::~TermsBST()
{

}

// Return root node
TermsBSTNode* TermsBST::getRoot()
{
    return root;
}


// insert
void TermsBST::insert(const std::string& name, int age, const std::string& collectionDate, char term) {
    root = insert(root, name, age, collectionDate, term);
}

// Private recursive function
TermsBSTNode* TermsBST::insert(TermsBSTNode* node, const std::string& name, int age, const std::string& date, char term) {
    if (!node) {
        // Node is empty create and return
        TermsBSTNode* newNode = new TermsBSTNode();
        newNode->setTermType(term);
        newNode->setMemberName(name);
        newNode->setMemberAge(age);
        newNode->setMemberDate(date);        newNode->setMemberCount(1); // or appropriate count
        return newNode;
    }


    // Determine, the node based on the term
    if (term < node->getTermType())
        node->setLeft(insert(node->getLeft(), name, age, date, term));
    else if (term > node->getTermType())
        node->setRight(insert(node->getRight(), name, age, date, term));
    else { 
          // Create a node based on term and name
        if (name < node->getMemberName()) {
            node->setLeft(insert(node->getLeft(), name, age, date, term));
        }
        else {
            node->setRight(insert(node->getRight(), name, age, date, term));
        }
    }

    return node;
}



// Print the BST
void TermsBST::print() {
    inOrderTraversal(root, std::cout, '*');
}

// Print function for node
void TermsBST::print(TermsBSTNode* node)
{


}

// Check the BST
bool TermsBST::isEmpty(char term)
{
    return search(term) == nullptr;  //the BST is empty
}

//search function
TermsBSTNode* TermsBST::search(char term)
{
    return search(root, term);
}


// Private recursive function
TermsBSTNode* TermsBST::search(TermsBSTNode* node, char term)
{
    if (!node)
        return nullptr; // if node is empty

    if (term == node->getTermType())
        return node; // Return node

    // to search based on term
    else if (term < node->getTermType())
        return search(node->getLeft(), term);
    else
        return search(node->getRight(), term);
}


// Return root node
TermsBSTNode* TermsBST::rootForTerm(char term)
{
    return search(term);
}



// for in-order traversal
void TermsBST::inOrderTraversal(TermsBSTNode* node, std::ostream& flog, char term) {
    if (!node) return;
    inOrderTraversal(node->getLeft(), flog, term);

    //set the format of print
    if (node->getTermType() == term) {
        flog << node->getMemberName() << "/" << node->getMemberAge() << "/"
            << node->getMemberDate() << std::endl;
    }
    inOrderTraversal(node->getRight(), flog, term);
}

std::string TermsBST::calculateExpirationDate(const std::string& collectionDate, char term) {
    // Calculate the expiration date

    int monthsToAdd = 0;
    // Define months based on term

    switch (term) {
    case 'A':
        monthsToAdd = 6;
        break;
    case 'B':
        monthsToAdd = 12;
        break;
    case 'C':
        monthsToAdd = 24;
        break;
    case 'D':
        monthsToAdd = 36;
        break;
    default:
        throw std::invalid_argument("Invalid term.");
    }

    // Convert string to struct tm
    std::tm timeStruct = {};
    strptime(collectionDate.c_str(), "%Y-%m-%d", &timeStruct);

    // Handle the overflow
    timeStruct.tm_mon += monthsToAdd;
    int yearsToAdd = timeStruct.tm_mon / 12;
    timeStruct.tm_mon = timeStruct.tm_mon % 12;
    timeStruct.tm_year += yearsToAdd;

    // Convert the string format

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);

    std::cout << "Collection Date: " << collectionDate << ", Term: " << term << ", Calculated Expiration Date: " << buffer << std::endl;

    return std::string(buffer);
}


// Function to get the minimum value node
TermsBSTNode* TermsBST::minValueNode(TermsBSTNode* node) {
    TermsBSTNode* current = node;
    while (current && current->getLeft() != nullptr)
        current = current->getLeft();
    return current;
}

// Recursive delete function
TermsBSTNode* TermsBST::deleteRecursive(TermsBSTNode* current, const std::string& key) {
    if (!current)
        return current;

    //delete algorithm
    if (key < current->getMemberName()) {
        current->setLeft(deleteRecursive(current->getLeft(), key));
    }
    else if (key > current->getMemberName()) {
        current->setRight(deleteRecursive(current->getRight(), key));
    }
    else {
        // Node with only one child or no child
        if (!current->getLeft()) {
            TermsBSTNode* temp = current->getRight();
            delete current;
            return temp;
        }
        else if (!current->getRight()) {
            TermsBSTNode* temp = current->getLeft();
            delete current;
            return temp;
        }

        // To get the inorder successor
        TermsBSTNode* temp = minValueNode(current->getRight());

        // Copy the inorder successor's content
        current->setMemberName(temp->getMemberName());
        current->setMemberAge(temp->getMemberAge());
        current->setMemberDate(temp->getMemberDate());
        current->setTermType(temp->getTermType());
        current->setExpirationDate(temp->getExpirationDate()); 
        // implemented the getter and setter

        // Delete
        current->setRight(deleteRecursive(current->getRight(), temp->getMemberName()));
    }
    return current;
}


// Delete a member
bool TermsBST::deleteMember(const std::string& name) {
    bool wasDeleted = false;
    root = deleteMemberRecursive(root, name, wasDeleted);
    return wasDeleted;
}



TermsBSTNode* TermsBST::deleteMemberRecursive(TermsBSTNode* node, const std::string& name, bool& wasDeleted) {
    if (!node) return nullptr;

    // searching based on the expiration date.
    if (name < node->getExpirationDate()) {
        node->setLeft(deleteMemberRecursive(node->getLeft(), name, wasDeleted));
    }
    else if (name > node->getExpirationDate()) {
        node->setRight(deleteMemberRecursive(node->getRight(), name, wasDeleted));
    }
    else {  // Matching node 
        wasDeleted = true;

        // Leaf node or node get only one child
        if (!node->getLeft()) {
            TermsBSTNode* rightChild = node->getRight();
            delete node;
            return rightChild;
        }
        else if (!node->getRight()) {
            TermsBSTNode* leftChild = node->getLeft();
            delete node;
            return leftChild;
        }

        // Node with two children
        TermsBSTNode* temp = minValueNode(node->getRight());  
        // Find the smallest node

        // Copy the found node's data
        node->setMemberName(temp->getMemberName());
        node->setMemberAge(temp->getMemberAge());
        node->setMemberDate(temp->getMemberDate());
        node->setTermType(temp->getTermType());
        node->setExpirationDate(temp->getExpirationDate());

        // Delete the smallest node
        node->setRight(deleteRecursive(node->getRight(), temp->getExpirationDate()));
    }
    return node;
}

int TermsBST::deleteBeforeDate(const std::string& expirationDate) {
    int count = 0; // Store the number of nodes
    root = deleteBeforeDateRecursive(root, expirationDate, count);
    return count;
}

TermsBSTNode* TermsBST::deleteBeforeDateRecursive(TermsBSTNode* node, const std::string& givenDate, int& count) {

    if (!node) return nullptr;

    // Delete expired nodes.
    node->setLeft(deleteBeforeDateRecursive(node->getLeft(), givenDate, count));

    // Delete expired nodes
    node->setRight(deleteBeforeDateRecursive(node->getRight(), givenDate, count));

    // Check the current node
    if (node->getExpirationDate() < givenDate) { // Here, getExpirationDate() is a method that returns the expiration date of the node.
        count++; // Increment the number of node

        TermsBSTNode* temp;
        if (!node->getLeft()) {
            temp = node->getRight();
        }
        else if (!node->getRight()) {
            temp = node->getLeft();
        }
        else {
            temp = minValueNode(node->getRight());
            node->setRight(deleteRecursive(node->getRight(), temp->getMemberName()));
            temp->setLeft(node->getLeft());
        }

        delete node;
        return temp;
    }

    return node;
}
