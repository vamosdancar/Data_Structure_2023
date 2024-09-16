#include "NameBST.h"
#include "TermsBST.h"
#include "TermsList.h"
#include <fstream>
#include <ctime>


#pragma warning(disable:4819) 

// Constructor: Initializes the NameBST
NameBST::NameBST(TermsBST* tBST, TermsLIST* tList)
    : root(nullptr), termsBST(tBST), termsList(tList)
{

}

// Destructor
NameBST::~NameBST() {
   
}


// Returns the root of the BST
NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert
void NameBST::insert(const std::string& name, int age, const std::string& date, char term)
{
    if (search(name)) return; 
    // Check the BST

    NameBSTNode* newNode = new NameBSTNode(name, age, date, term);
    if (!newNode) {
        // Handle memory allocation failure
        throw std::bad_alloc();
    }

    // If BST is empty
    // set the root
    if (!root)
    {
        root = newNode;
        return;
    }

    // Find the appropriate position
    NameBSTNode* current = root;
    NameBSTNode* parent = nullptr;

    while (current)
    {
        parent = current;

        if (name == current->getName())
        {
            // Delete the newly created node and return
            delete newNode;  // release the allocated memory
            return;
        }
        else if (name < current->getName())
        {
            current = current->getLeft();
        }
        else
        {
            current = current->getRight();
        }
    }

    // Attach the new node
    if (name < parent->getName())
    {
        parent->setLeft(newNode);
    }
    else
    {
        parent->setRight(newNode);
    }
}



// search
NameBSTNode* NameBST::search(const std::string& name)
{
    NameBSTNode* current = root;
    while (current) //Search algorithms
    {
        if (name == current->getName())
        {
            return current;
        }
        else if (name < current->getName())
        {
            current = current->getLeft();
        }
        else
        {
            current = current->getRight();
        }
    }
    return nullptr;  // given name not found
}


// print all noes in the BST
void NameBST::print(std::ostream& flog) {
    flog << "Name_BST" << std::endl;
    printInOrder(root, flog);
}


// to compute the expiration date
std::string aa(const std::string& startDate, char term) {
    int monthsToAdd = 0;
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
    strptime(startDate.c_str(), "%Y-%m-%d", &timeStruct);

    // Handle the overflow
    timeStruct.tm_mon += monthsToAdd;
    int yearsToAdd = timeStruct.tm_mon / 12;
    timeStruct.tm_mon = timeStruct.tm_mon % 12;
    timeStruct.tm_year += yearsToAdd;

    // Convert the string format
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);
    return std::string(buffer);
}

// Print members with specific term
void NameBST::printMembersByTerm(std::ostream& flog, char term) {
    printMembersByTerm(root, flog, term);
}



// Recursive function with a specific term
void NameBST::printMembersByTerm(NameBSTNode* node, std::ostream& flog, char term) {
    if (!node) return;

    printMembersByTerm(node->getLeft(), flog, term);

    if (node->getTerm() == term) {
        flog << node->getName()
            << "/" << std::to_string(node->getAge())
            << "/" << node->getDate()
            << "/" << aa(node->getDate(), node->getTerm()) // ¸¸·á ÀÏÀÚ¸¦ °è»êÇÕ´Ï´Ù.
            << std::endl;
    }

    printMembersByTerm(node->getRight(), flog, term);
}

// Print all members
void NameBST::printInOrder(NameBSTNode* node, std::ostream& flog) {

    if (!node) return;

    printInOrder(node->getLeft(), flog);

    // declare the format
    flog << node->getName()
        << "/" << std::to_string(node->getAge())
        << "/" << node->getDate()
        << "/" << aa(node->getDate(), node->getTerm())
        << std::endl;

    printInOrder(node->getRight(), flog);
}

// Checks the BST is empty.
bool NameBST::isEmpty()  {
    return root == nullptr;  // If root is nullptr, BST is empty
}


// delete
void NameBST::deleteMembersBeforeDate(const std::string& expirationDate) {
    // Uses recursive function
    root = deleteRecursive(root, expirationDate);
}

//recursive function
NameBSTNode* NameBST::deleteRecursive(NameBSTNode* node, const std::string& expirationDate) {
    if (node == nullptr) return nullptr;

    // Deletes left subtree
    node->setLeft(deleteRecursive(node->getLeft(), expirationDate));

    // Deletes right subtree
    node->setRight(deleteRecursive(node->getRight(), expirationDate));

    // compare expiration date and delete node
    if (aa(node->getDate(), node->getTerm()) < expirationDate) {
        NameBSTNode* temp;
        if (node->getLeft() == nullptr) {
            temp = node->getRight();
            delete node;
            return temp;
        }
        else if (node->getRight() == nullptr) {
            temp = node->getLeft();
            delete node;
            return temp;
        }

        // If the node has two children
        temp = minValueNode(node->getRight());

        // Copies the values
        node->setName(temp->getName());
        node->setAge(temp->getAge());
        node->setDate(temp->getDate());
        node->setTerm(temp->getTerm());

        // Deletes the copied node
        node->setRight(deleteRecursive(node->getRight(), temp->getName()));
    }
    return node;
}



// Deletes a member from the BST
bool NameBST::deleteByName(const std::string& name) {
    NameBSTNode* targetNode = search(name);

    if (!targetNode) return false; // Returns false

    root = deleteNode(root, name);  

    // If deletion in NameBST successful
    if (search(name) == nullptr) {
        if (termsBST) {
            termsBST->deleteMember(name);
        }

        // if necessary delete the node from TermsList
        if (termsList) {
            termsList->deleteMember(name); 
        }

        return true; // Deletion successful
    }

    return false; // Deletion failed
}



// Recursive function to delete a node
NameBSTNode* NameBST::deleteNode(NameBSTNode* root, const std::string& name) {
    if (root == nullptr) return root;  // If the node is nullptr

    // If smaller than the root's name
    if (name < root->getName())
        root->setLeft(deleteNode(root->getLeft(), name));

    // If larger than the root's name
    else if (name > root->getName())
        root->setRight(deleteNode(root->getRight(), name));

    else {
        // Node with only a right child or no child
        if (root->getLeft() == nullptr) {
            NameBSTNode* temp = root->getRight();
            delete root;
            return temp;
        }
        else if (root->getRight() == nullptr) {  // Node with only a left child
            NameBSTNode* temp = root->getLeft();
            delete root;
            return temp;
        }

        NameBSTNode* temp = minValueNode(root->getRight());

        // Copy the inorder
        root->setName(temp->getName());
        root->setAge(temp->getAge());
        root->setDate(temp->getDate());
        root->setTerm(temp->getTerm());

        // Delete the inorder successor
        root->setRight(deleteNode(root->getRight(), temp->getName()));
    }
    return root;
}


// to find the node
NameBSTNode* NameBST::minValueNode(NameBSTNode* node) {
    NameBSTNode* current = node;

    // to find the smallest value.
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}